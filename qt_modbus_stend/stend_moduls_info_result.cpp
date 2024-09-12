#include "stend_moduls_info_result.h"
#include "ui_stend_moduls_info_result.h"

stend_moduls_info_result::stend_moduls_info_result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stend_moduls_info_result)
{
    ui->setupUi(this);
}

stend_moduls_info_result::~stend_moduls_info_result()
{
    delete ui;
}
