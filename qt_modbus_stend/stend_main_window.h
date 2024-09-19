#ifndef STEND_MAIN_WINDOW_H
#define STEND_MAIN_WINDOW_H

#include <QMainWindow>
#include "ui_stend_main_window.h"
#include <QMutex>
#include <thread>
#include <atomic>

// GUI КЛАСС
QT_BEGIN_NAMESPACE
namespace Ui { class stend_main_window; }
QT_END_NAMESPACE

class stend_main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit stend_main_window(QWidget *parent = nullptr);
    ~stend_main_window();

    // Подключаем слот для тестирования связи с оборудованием
private slots:
    /**
     * @brief test_connection Обработчик нажатия кнопки для тестирования связи
     */
    void test_connection();

    /**
     * @brief start_main_test Обработчик нажатия кнопки для старта тестов МОПСов и МУПСов
     */
    void start_main_test();

    /**
     * @brief stop_main_test Обработчик нажатия кнопки для остановки тестов
     */
    void stop_main_test();

private:
    Ui::stend_main_window *ui;

    // Мьютекс для синхронизации методов
    QMutex mutex;

    // Флаг выполнения теста в данный момент
    std::atomic<bool> isTestRunning = false;

    // Поток для выполнения тестов
    std::thread test_thread;

    // счетчик выполненных тестов МОПСов и МУПСов
    int mops_num;
    int mups_num;

    QCheckBox* mops_checkboxes[10];  // Массив указателей на чекбоксы МОПС
    QCheckBox* mups_checkboxes[10];  // Массив указателей на чекбоксы МУПС
};

#endif // STEND_MAIN_WINDOW_H
