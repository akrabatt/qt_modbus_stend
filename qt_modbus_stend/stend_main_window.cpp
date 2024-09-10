#include "stend_main_window.h"
#include "ui_stend_main_window.h"
#include <QMessageBox>
#include <QString>
#include <vector>
#include "libmodbus/modbus.h"
#include "modbus_funct/modbusrtu.h"
#include "devices/test_board.h"


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

void stend_main_window::start_main_test()
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

    try
    {
        // создадим объект испытательной платы
        test_board stand_test_board(1);

        // МОПС 1
        if (ui->checkBox_active_mops_1->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 0);}
        else {stand_test_board.set_active_mops_checkbox(0, 0);}

        // МОПС 2
        if (ui->checkBox_active_mops_2->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 1);}
        else {stand_test_board.set_active_mops_checkbox(0, 1);}

        // МОПС 3
        if (ui->checkBox_active_mops_3->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 2);}
        else {stand_test_board.set_active_mops_checkbox(0, 2);}

        // МОПС 4
        if (ui->checkBox_active_mops_4->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 3);}
        else {stand_test_board.set_active_mops_checkbox(0, 3);}

        // МОПС 5
        if (ui->checkBox_active_mops_5->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 4);}
        else {stand_test_board.set_active_mops_checkbox(0, 4);}

        // МОПС 6
        if (ui->checkBox_active_mops_6->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 5);}
        else {stand_test_board.set_active_mops_checkbox(0, 5);}

        // МОПС 7
        if (ui->checkBox_active_mops_7->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 6);}
        else {stand_test_board.set_active_mops_checkbox(0, 6);}

        // МОПС 8
        if (ui->checkBox_active_mops_8->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 7);}
        else {stand_test_board.set_active_mops_checkbox(0, 7);}

        // МОПС 9
        if (ui->checkBox_active_mops_9->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 8);}
        else {stand_test_board.set_active_mops_checkbox(0, 8);}

        // МОПС 10
        if (ui->checkBox_active_mops_10->isChecked()) {stand_test_board.set_active_mops_checkbox(1, 9);}
        else {stand_test_board.set_active_mops_checkbox(0, 9);}



        // МУПС 1
        if (ui->checkBox_active_mups_1->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 0);}
        else {stand_test_board.set_active_mups_checkbox(0, 0);}

        // МУПС 2
        if (ui->checkBox_active_mups_2->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 1);}
        else {stand_test_board.set_active_mups_checkbox(0, 1);}

        // МУПС 3
        if (ui->checkBox_active_mups_3->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 2);}
        else {stand_test_board.set_active_mups_checkbox(0, 2);}

        // МУПС 4
        if (ui->checkBox_active_mups_4->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 3);}
        else {stand_test_board.set_active_mups_checkbox(0, 3);}

        // МУПС 5
        if (ui->checkBox_active_mups_5->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 4);}
        else {stand_test_board.set_active_mups_checkbox(0, 4);}

        // МУПС 6
        if (ui->checkBox_active_mups_6->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 5);}
        else {stand_test_board.set_active_mups_checkbox(0, 5);}

        // МУПС 7
        if (ui->checkBox_active_mups_7->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 6);}
        else {stand_test_board.set_active_mups_checkbox(0, 6);}

        // МУПС 8
        if (ui->checkBox_active_mups_8->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 7);}
        else {stand_test_board.set_active_mups_checkbox(0, 7);}

        // МУПС 9
        if (ui->checkBox_active_mups_9->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 8);}
        else {stand_test_board.set_active_mups_checkbox(0, 8);}

        // МУПС 10
        if (ui->checkBox_active_mups_10->isChecked()) {stand_test_board.set_active_mups_checkbox(1, 9);}
        else {stand_test_board.set_active_mups_checkbox(0, 9);}
    }
    catch (const std::exception &e)
    {
        QMetaObject::invokeMethod(this, [this, e]()
        {
            QMessageBox::critical(this, "Error", QString("Internal error: %1").arg(e.what())); // ошибка соединения
            //ui->answer_connection_lable->setStyleSheet("QLabel { color : red; }"); // красный цвет лейбла
            //ui->answer_connection_lable->setText("Connection error");
        });
    }
}
