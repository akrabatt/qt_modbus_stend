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
    if (!isTestRunning) {return;}

    // Останавливаем тест
    isTestRunning = false;

    if (test_thread.joinable())
    {
        test_thread.join();  // Ждем завершения потока
    }

    // Включаем кнопку "Старт"
    ui->button_start_main_test->setEnabled(true);

    // включаем кнопку тест соединения
    ui->button_test_connection->setEnabled(true);

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
    // Отключаем кнопку тест соединения
    ui->button_test_connection->setEnabled(false);

    // Сбрасываем счетчики при новом запуске теста
    mops_num = 0;
    mups_num = 0;

    // Обновляем лейблы счетчиков
    QMetaObject::invokeMethod(this, [this]()
    {
        ui->just_lable_mops_ans->setText("0");
        ui->just_lable_mups_ans->setText("0");
    });

    // Запуск потока
    test_thread = std::thread([this, com_port]()
    {
        try
        {
            // Создаем объект контекст подключения
            modbusRTU modbus_stand_board(com_port, 115200, 'N', 8, 1, 1);

            // Создаем объект испытательной платы
            test_board stand_test_board(1);

            // проверим не выполняется ли тестирование в данный момент
            bool is_test_busy = stand_test_board.check_test_is_busy(&modbus_stand_board, &stand_test_board);
            if(!is_test_busy)
            {
                // Если checkboxes возвращает false, то останавливаем тест
                QMetaObject::invokeMethod(this, [this](){this->stop_main_test(); QMessageBox::warning(this, "Error", "Test is busy !");});
                return; // Завершаем поток
            }

            // Записываем id модулей в плату, которые будем испытывать и проверяем успех выполнения
            bool checkbox_res = false;  // переменная для проверки
            checkbox_res = stand_test_board.process_checkboxes(mops_checkboxes, mups_checkboxes, 10, 10, &stand_test_board, &modbus_stand_board, this);
            if (!checkbox_res)
            {
                // Если checkboxes возвращает false, то останавливаем тест
                QMetaObject::invokeMethod(this, [this](){this->stop_main_test();});
                return; // Завершаем поток
            }

            // Главный цикл испытаний
            while (isTestRunning)
            {
                // СТАРТ тест МОПСов
                stand_test_board.start_main_test_mops(&modbus_stand_board, this, &stand_test_board);

                // Устанавливаем лейбл, что в данный момент тестируется МОПС
                QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("МОПС");});

                // Цикл, который проверяет, занят ли тест
                while (isTestRunning)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    // Проверяем, занят ли тест
                    bool status = stand_test_board.check_test_is_busy(&modbus_stand_board, &stand_test_board);

                    // Если тест завершен, выходим из цикла
                    if (status == true)
                    {
                        // Устанавливаем лейбл, что ничего не тестируется
                        QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("");});
                        // Инкрементируем счетчик тестов МОПСа
                        mops_num++;
                        QMetaObject::invokeMethod(this, [this](){ui->just_lable_mops_ans->setText(QString("%1").arg(mops_num));});
                        break;
                    }

                    // Проверяем флаг isTestRunning, чтобы завершить цикл
                    if (!isTestRunning)
                    {
                        // Устанавливаем лейбл, что ничего не тестируется
                        QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("");});
                        break;
                    }
                }

                // СТАРТ тест МУПСов
                stand_test_board.start_main_test_mups(&modbus_stand_board, this, &stand_test_board);

                // Устанавливаем лейбл, что в данный момент тестируется МУПС
                QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("МУПС");});

                // Цикл, который проверяет, занят ли тест
                while (isTestRunning)
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    // Проверяем, занят ли тест
                    bool status = stand_test_board.check_test_is_busy(&modbus_stand_board, &stand_test_board);

                    // Если тест завершен, выходим из цикла
                    if (status == true)
                    {
                        // Устанавливаем лейбл, что ничего не тестируется
                        QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("");});
                        // Инкрементируем счетчик тестов МУПСа
                        mups_num++;
                        QMetaObject::invokeMethod(this, [this](){ui->just_lable_mups_ans->setText(QString("%1").arg(mups_num));});
                        break;
                    }

                    // Проверяем флаг isTestRunning, чтобы завершить цикл
                    if (!isTestRunning)
                    {
                        // Устанавливаем лейбл, что ничего не тестируется
                        QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("");});
                        break;
                    }
                }

                // при остановке теста
                if (!isTestRunning)
                {
                    // Устанавливаем лейбл, что ничего не тестируется
                    QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("");});
                    break;
                }
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



