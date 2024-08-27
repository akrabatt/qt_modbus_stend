#ifndef STEND_MAIN_WINDOW_H
#define STEND_MAIN_WINDOW_H

#include <QMainWindow>
#include "ui_stend_main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class stend_main_window; }
QT_END_NAMESPACE

class stend_main_window : public QMainWindow
{
    Q_OBJECT

public:
    stend_main_window(QWidget *parent = nullptr);
    ~stend_main_window();
private slots:
    //void on_button_start_send_message();

private:
    Ui::stend_main_window *ui;
};
#endif // STEND_MAIN_WINDOW_H
