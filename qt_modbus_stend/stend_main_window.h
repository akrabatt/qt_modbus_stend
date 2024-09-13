#ifndef STEND_MAIN_WINDOW_H
#define STEND_MAIN_WINDOW_H

#include <QMainWindow>
#include "ui_stend_main_window.h"
#include <QMutex>
#include "test_worker_thread.h"

// GUI КЛАСС
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

    /**
     * @brief handle_test_error
     * @param error_message
     */
    void handle_test_error(const QString &error_message);

private:
    Ui::stend_main_window *ui;

    // мьютекс для синхронизации методов
    QMutex mutex;

    // флаг выполнения теста в данный момент для защиты
    bool isTestRunning = false;

    // указатель на поток
    QThread *test_thread;

    //указатель на объект класса с реализующий отдельный поток
    test_worker_thread *test_worker_thread_obj;
};
#endif // STEND_MAIN_WINDOW_H
