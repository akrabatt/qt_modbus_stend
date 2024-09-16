#include "stend_main_window.h"
#include "ui_stend_main_window.h"
#include <QMessageBox>
#include <QString>
#include <vector>
#include "libmodbus/modbus.h"
#include "modbus_funct/modbusrtu.h"
#include "devices/test_board.h"
#include <numeric>
#include <thread>
#include <mutex>


stend_main_window::stend_main_window(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::stend_main_window),
      isTestRunning(false)
{
    ui->setupUi(this);

    // Инициализация массива чекбоксов для МОПС
    mops_checkboxes[0] = ui->checkBox_active_mops_1;
    mops_checkboxes[1] = ui->checkBox_active_mops_2;
    mops_checkboxes[2] = ui->checkBox_active_mops_3;
    mops_checkboxes[3] = ui->checkBox_active_mops_4;
    mops_checkboxes[4] = ui->checkBox_active_mops_5;
    mops_checkboxes[5] = ui->checkBox_active_mops_6;
    mops_checkboxes[6] = ui->checkBox_active_mops_7;
    mops_checkboxes[7] = ui->checkBox_active_mops_8;
    mops_checkboxes[8] = ui->checkBox_active_mops_9;
    mops_checkboxes[9] = ui->checkBox_active_mops_10;

    // Инициализация массива чекбоксов для МУПС
    mups_checkboxes[0] = ui->checkBox_active_mups_1;
    mups_checkboxes[1] = ui->checkBox_active_mups_2;
    mups_checkboxes[2] = ui->checkBox_active_mups_3;
    mups_checkboxes[3] = ui->checkBox_active_mups_4;
    mups_checkboxes[4] = ui->checkBox_active_mups_5;
    mups_checkboxes[5] = ui->checkBox_active_mups_6;
    mups_checkboxes[6] = ui->checkBox_active_mups_7;
    mups_checkboxes[7] = ui->checkBox_active_mups_8;
    mups_checkboxes[8] = ui->checkBox_active_mups_9;
    mups_checkboxes[9] = ui->checkBox_active_mups_10;

    // Подключаем сигналы кнопок к слотам
    connect(ui->button_test_connection, &QPushButton::clicked, this, &stend_main_window::test_connection);
    connect(ui->button_start_main_test, &QPushButton::clicked, this, &stend_main_window::start_main_test);
    connect(ui->button_stop_main_test, &QPushButton::clicked, this, &stend_main_window::stop_main_test);
}

/**
 * @brief stend_main_window::~stend_main_window деструктор очищающий память
 */
stend_main_window::~stend_main_window()
{
    if (test_thread.joinable()) {
        isTestRunning = false;
        test_thread.join(); // Ждем завершения потока
    }

    delete ui;
}

/**
 * @brief Остановка теста
 */
void stend_main_window::stop_main_test()
{
    if (!isTestRunning) return;

    // Останавливаем тест
    isTestRunning = false;

    if (test_thread.joinable()) {
        test_thread.join();  // Ждем завершения потока
    }

    // Включаем кнопку "Старт"
    ui->button_start_main_test->setEnabled(true);

    // Обновляем статус лейбла
    ui->answer_connection_lable->setText("Test stopped.");
}

/**
 * @brief test_connection обработчик нажатия кнопки по тестированию связи
 */
void stend_main_window::test_connection()
{
    // Проверяем, не запущен ли тест уже
    if (isTestRunning)
    {
        QMessageBox::warning(this, "Warning", "Test is already running!");
        return;
    }

    // блокируем мьютекс, разблокируется автоматически по завершению фукнции
    QMutexLocker locker(&mutex);

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


/**
 * @brief Запуск теста в отдельном потоке с использованием std::thread
 */
void stend_main_window::start_main_test()
{
    // Проверяем, не запущен ли тест уже
    if (isTestRunning)
    {
        QMessageBox::warning(this, "Warning", "Test is already running!");
        return;
    }

    // Получаем текст из поля QLineEdit
    QString com_port_text = ui->line_in_com_num->text();

    // Проверяем, не пустое ли поле
    if (com_port_text.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Input COM port's num!");
        return;
    }

    // Преобразуем QString в std::string для использования в функции
    const std::string com_port = com_port_text.toStdString();

    // Устанавливаем флаг, что тест запущен
    isTestRunning = true;

    // Отключаем кнопку "Старт"
    ui->button_start_main_test->setEnabled(false);

    // Запуск потока
    test_thread = std::thread([this, com_port]()
    {
        try
        {
            // создаем объект контекст подключения
            modbusRTU modbus_stand_board(com_port, 115200, 'N', 8, 1, 1);

            // создадим объект испытательной платы
            test_board stand_test_board(1);

            stand_test_board.process_checkboxes(mops_checkboxes, mups_checkboxes, 10, 10, &stand_test_board, &modbus_stand_board, this);
            // Пример выполнения некоторой операции
            for (int i = 0; i < 10 && isTestRunning; ++i)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                // Пример обновления GUI из потока
                QMetaObject::invokeMethod(this, [this, i]()
                {
                    ui->answer_connection_lable->setText(QString("Testing... Step %1").arg(i+1));
                });

                if (!isTestRunning) break;
            }

            if (isTestRunning)
            {
                QMetaObject::invokeMethod(this, [this]()
                {
                    QMessageBox::information(this, "Test Finished", "Test completed successfully!");
                });
            }
        }
        catch (const std::exception &e)
        {
            QMetaObject::invokeMethod(this, [this, e]()
            {
                QMessageBox::critical(this, "Error", QString("Internal error: %1").arg(e.what()));
            });
        }

        // В конце теста, даже если он был прерван, сбрасываем флаг
        QMetaObject::invokeMethod(this, [this]()
        {
            this->stop_main_test();
        });
    });
}

