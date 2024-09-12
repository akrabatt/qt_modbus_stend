#ifndef STEND_MAIN_WINDOW_H
#define STEND_MAIN_WINDOW_H

#include <QMainWindow>
#include "ui_stend_main_window.h"
#include <QMutex>
#include "stend_moduls_info_result.h"

QT_BEGIN_NAMESPACE
namespace Ui { class stend_main_window; }
QT_END_NAMESPACE

class stend_main_window : public QMainWindow
{
    Q_OBJECT

public:
    stend_main_window(QWidget *parent = nullptr);
    ~stend_main_window();

    // подлкючаем слот по тестирования связи с оборудованием
private slots:
    /**
     * @brief test_connection обработчик нажатия кнопки по тестированию связи
     */
    void test_connection();

    /**
     * @brief start_main_test обработчик нажатия кнопки по старту испытаний МОПСов и МУПСов
     */
    void start_main_test();

    /**
     * @brief stop_main_test обработчик нажатия кнопки по завершению испытаний
     */
    void stop_main_test();

private:
    Ui::stend_main_window *ui;

    // мьютекс для синхронизации методов
    QMutex mutex;

    // флаг выполнения теста
    bool isTestRunning = false;
};
#endif // STEND_MAIN_WINDOW_H
