#ifndef STEND_MODULS_INFO_RESULT_H
#define STEND_MODULS_INFO_RESULT_H

#include <QWidget>

namespace Ui {
class stend_moduls_info_result;
}

class stend_moduls_info_result : public QWidget
{
    Q_OBJECT

public:
    explicit stend_moduls_info_result(QWidget *parent = nullptr);
    ~stend_moduls_info_result();

private:
    Ui::stend_moduls_info_result *ui;
};

#endif // STEND_MODULS_INFO_RESULT_H
