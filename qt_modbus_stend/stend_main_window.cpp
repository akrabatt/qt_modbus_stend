#include "stend_main_window.h"
#include "ui_stend_main_window.h"
#include <QMessageBox>
#include <QString>
#include <vector>
#include "libmodbus/modbus.h"
#include "modbus_funct/modbusrtu.h"
#include "devices/test_board.h"
#include <numeric>
#include "stend_moduls_info_result.h"


stend_main_window::stend_main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stend_main_window)
{
    ui->setupUi(this);

    // подлкючаем слот к сигналу кнопки(...(название кнопки, ..., ..., название метода))
    // тест соединения с платой
    connect(ui->button_test_connection, &QPushButton::clicked, this, &stend_main_window::test_connection);

    // запуск испытаний МОПСов и МУПСов
    connect(ui->button_start_main_test, &QPushButton::clicked, this, &stend_main_window::start_main_test);

}

stend_main_window::~stend_main_window()
{
    delete ui;
}

/**
 * @brief test_connection обработчик нажатия кнопки по тестированию связи
 */
void stend_main_window::test_connection()
{
    // блокируем мьютекс, разблокируется автоматически по завершению фукнции
    QMutexLocker locker(&mutex);

    // Получаем текст из поля QLineEdit
    QString com_port_text = ui->line_in_com_num->text();

    // Проверяем, не пустое ли поле
    if (com_port_text.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Input COM port's num!");
        return;
    }

    // Преобразуем QString в std::string для использования в вашей функции
    const std::string com_port = com_port_text.toStdString();

    // создадим флаг обратной связи
    bool success = false;

    std::thread t1([this, &success, com_port]() // Захватываем указатель this для доступа к полям класса
    {
        try
        {
            modbusRTU modbus_check(com_port, 115200, 'N', 8, 1, 1); // создадим объект
            success = modbus_check.mbm_03_check_connection();   // выполняем функцию

            //modbusRTU modbus_check;   // создадим объект
            //modbus_check.create_modbus_context(com_port, 115200, 'N', 8, 1, 1); // создадим контекст
            //success = modbus_check.mbm_03_check_connection();   // запускаем проверку

            //success = modbus_check.init_and_check_connection(com_port, 115200, 'N', 8, 1, 1, 1, 3);

            // Обновляем лейбл в зависимости от результата подключения
            if (success)
            {
                QMetaObject::invokeMethod(this, [this]()
                {
                    ui->answer_connection_lable->setStyleSheet("QLabel { color : green; }"); // зеленый цвет лейбла
                    ui->answer_connection_lable->setText("Successful connection!"); // текст лейбла
                    QMessageBox::information(this, "Success", "Successful connection!");
                });
            }
        }
        catch (const std::exception &e) // в случае неуспеха
        {
            QMetaObject::invokeMethod(this, [this, e]()
            {
                QMessageBox::critical(this, "Error", QString("Failed connection: %1").arg(e.what())); // ошибка соединения
                ui->answer_connection_lable->setStyleSheet("QLabel { color : red; }"); // красный цвет лейбла
                ui->answer_connection_lable->setText("Connection error");
            });
        }
    });

    // запускаем поток параллельно
    t1.detach();
}

/**
 * @brief stend_main_window::start_main_test
 */
void stend_main_window::start_main_test()
{
    // блокируем мьютекс, разблокируется автоматически по завершению фукнции
    QMutexLocker locker(&mutex);

    // Получаем текст из поля QLineEdit
    QString com_port_text = ui->line_in_com_num->text();

    // Проверяем, не пустое ли поле
    if (com_port_text.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Input COM port's num!");
        return;
    }

    // Преобразуем QString в std::string для использования в вашей функции
    const std::string com_port = com_port_text.toStdString();

    try
    {
        // создадим объект испытательной платы
        test_board stand_test_board(1);

        // Массив указателей на QCheckBox для МОПС
        QCheckBox* mops_checkboxes[] = {
            ui->checkBox_active_mops_1, ui->checkBox_active_mops_2, ui->checkBox_active_mops_3,
            ui->checkBox_active_mops_4, ui->checkBox_active_mops_5, ui->checkBox_active_mops_6,
            ui->checkBox_active_mops_7, ui->checkBox_active_mops_8, ui->checkBox_active_mops_9,
            ui->checkBox_active_mops_10
        };

        // Массив указателей на QCheckBox для МУПС
        QCheckBox* mups_checkboxes[] = {
            ui->checkBox_active_mups_1, ui->checkBox_active_mups_2, ui->checkBox_active_mups_3,
            ui->checkBox_active_mups_4, ui->checkBox_active_mups_5, ui->checkBox_active_mups_6,
            ui->checkBox_active_mups_7, ui->checkBox_active_mups_8, ui->checkBox_active_mups_9,
            ui->checkBox_active_mups_10
        };

        // Обрабатываем чекбоксы для МОПС
        for (int i = 0; i < 10; ++i) {stand_test_board.set_active_mops_checkbox(mops_checkboxes[i]->isChecked() ? 1 : 0, i);}

        // Обрабатываем чекбоксы для МУПС
        for (int i = 0; i < 10; ++i) {stand_test_board.set_active_mups_checkbox(mups_checkboxes[i]->isChecked() ? 1 : 0, i);}

        int mops_var_sum = stand_test_board.get_sum_mops_checkbox();    // проверяем отмеченные МОПСы
        int mups_var_sum = stand_test_board.get_sum_mups_checkbox();    // проверяем отмеченные МУПСы
        // если не отмечены, то выводим ошибку и выходим
        if(mops_var_sum == 0 && mups_var_sum == 0)
        {
            QMessageBox::warning(this, "Error", "The module is not selected");
            return;
        }

        // создадим объект контекст подключения
        modbusRTU modbus_stand_board(com_port, 115200, 'N', 8, 1, 1);

        // записываем регистры с МОПСами и МУПСами которые будем испытывать в плату
        bool success = stand_test_board.wirte_active_mops_and_mups_to_test_board_flag(&modbus_stand_board);

        // информация о записи
        if(success){QMessageBox::information(this, "End", "End");}
        else {QMessageBox::warning(this, "Error", "Error");}

        stend_moduls_info_result *info_moduls_window = new stend_moduls_info_result(this);
        info_moduls_window->show();

    }
    catch (const std::exception &e)
    {
        QMetaObject::invokeMethod(this, [this, e]()
        {
            QMessageBox::critical(this, "Error", QString("Internal error: %1").arg(e.what())); // ошибка соединения
        });
    }
}
