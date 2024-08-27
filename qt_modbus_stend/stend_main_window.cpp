#include "stend_main_window.h"
#include "ui_stend_main_window.h"
#include <QMessageBox>
#include <QString>
#include <vector>
#include "libmodbus/modbus.h"
#include "modbus_funct/0x03.h"

stend_main_window::stend_main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stend_main_window)
{
    ui->setupUi(this);

    // подлкючаем слот к сигналу кнопки
    //connect(ui->button_read, &QPushButton::clicked, this, &stend_main_window::on_button_start_send_message);
}

stend_main_window::~stend_main_window()
{
    delete ui;
}

// обработчик нажатия кнопки
//void stend_main_window::on_button_start_send_message()
//{
    // запускаем функцию чтения регистров
    //std::vector<unsigned short> registers = mb_0x03();

    // устанавливаем значения в лейблы
    //ui->lab_reg_1->setText(QString::number(registers[0]));
    //ui->lab_reg_2->setText(QString::number(registers[1]));
    //ui->lab_reg_3->setText(QString::number(registers[2]));
    //ui->lab_reg_4->setText(QString::number(registers[3]));
    //ui->lab_reg_5->setText(QString::number(registers[4]));
//}
