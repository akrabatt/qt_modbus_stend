#include "stend_main_window.h"
#include "ui_stend_main_window.h"
#include <QMessageBox>
#include <QString>

stend_main_window::stend_main_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::stend_main_window)
{
    ui->setupUi(this);

    // подлкючаем слот к сигналу кнопки
    connect(ui->button_start_send_message, &QPushButton::clicked, this, &stend_main_window::on_button_start_send_message);
}

stend_main_window::~stend_main_window()
{
    delete ui;
}

void stend_main_window::on_button_start_send_message()
{

}
