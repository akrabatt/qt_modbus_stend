#include "stend_main_window.h"
#include "ui_stend_main_window.h"
#include <QMessageBox>
#include <QString>
#include <vector>
#include "libmodbus/modbus.h"
#include "modbus_funct/modbusrtu.h"


stend_main_window::stend_main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stend_main_window)
{
    ui->setupUi(this);

    // подлкючаем слот к сигналу кнопки(...(название кнопки, ..., ..., название метода))
    connect(ui->button_test_connection, &QPushButton::clicked, this, &stend_main_window::test_connection);
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
