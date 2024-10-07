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
 * @brief update_mops_gui данный метод обновляет ГУИ всех вкладок МУПСов
 * @param mops_map
 */
void stend_main_window::update_mops_gui(const std::map<int, mops>& mops_map)
{
    QMetaObject::invokeMethod(this, [this, mops_map]()
    {
        // Проходим по всем МОПСам в карте
        for (const auto& [id, mops_obj] : mops_map)
        {
            // статус исправности модуля
            QLabel* operable_label = findChild<QLabel*>(QString("just_lable_oper_status_ans_mops_%1").arg(id + 1));
            // статус онлайн/оффлайн статуса модуля
            QLabel* online_label = findChild<QLabel*>(QString("just_lable_online_status_ans_mops_%1").arg(id + 1));

            // получаем указатель на вкладку
            int tabIndex = id; // соответствует индексу вкладки
            QString tabName = QString("%1").arg(id + 1);   // название вкладки

            // Устанавливаем жирный шрифт для текста вкладки
            QFont tabFont = ui->tab_widget_for_mops->tabBar()->font();  // Получаем текущий шрифт вкладки
            tabFont.setBold(true);  // Делаем шрифт жирным
            ui->tab_widget_for_mops->tabBar()->setFont(tabFont);  // Применяем жирный шрифт

            // Обновляем статус работоспособности МОПСа
            if (operable_label)
            {
                if (mops_obj.mops_stand_statment.mops_statment.mops_operable > 0)
                {
                    operable_label->setText("Operable");
                    operable_label->setStyleSheet("QLabel { color : green; }");

                    // Изменяем текст вкладки (оставляем логику неизменной)
                    ui->tab_widget_for_mops->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mops->tabBar()->setTabTextColor(tabIndex, QColor("green"));
                }
                else
                {
                    operable_label->setText("Error");
                    operable_label->setStyleSheet("QLabel { color : red; }");

                    // Изменяем текст вкладки (оставляем логику неизменной)
                    ui->tab_widget_for_mops->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mops->tabBar()->setTabTextColor(tabIndex, QColor("red"));
                }
            }

            // Обновляем статус онлайн/оффлайн
            if (online_label)
            {
                if (mops_obj.mops_stand_statment.mops_statment.mops_offline > 0)
                {
                    online_label->setText("Offline");
                    online_label->setStyleSheet("QLabel { color : gray; }");
                    operable_label->setText("");

                    // Изменяем текст вкладки (оставляем логику неизменной)
                    ui->tab_widget_for_mops->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mops->tabBar()->setTabTextColor(tabIndex, QColor("gray"));
                    continue;
                }
                if (mops_obj.mops_stand_statment.mops_statment.mops_online)
                {
                    online_label->setText("Online");
                    online_label->setStyleSheet("QLabel { color : green; }");
                }
                else
                {
                    online_label->setText("Online error !");
                    online_label->setStyleSheet("QLabel { color : red; }");
                    continue;
                }
            }

            // Обновляем статус питания и каналов
            QLabel* v18_label = findChild<QLabel*>(QString("lable_18v_ans_mops_%1").arg(id + 1));
            QLabel* v24_label = findChild<QLabel*>(QString("lable_24v_ans_mops_%1").arg(id + 1));
            QLabel* v28_label = findChild<QLabel*>(QString("lable_28v_ans_mops_%1").arg(id + 1));
            if (v18_label)  // 18v
            {
                if (mops_obj.mops_stand_statment.mops_power_supply_error.mops_18v_error > 0)
                    {v18_label->setText("err"); v18_label->setStyleSheet("QLabel { color : red; }");}
                else
                    {v18_label->setText("ok"); v18_label->setStyleSheet("QLabel { color : green; }");}
            }
            if (v24_label) // 24v
            {
                if (mops_obj.mops_stand_statment.mops_power_supply_error.mops_24v_error > 0)
                    {v24_label->setText("err"); v24_label->setStyleSheet("QLabel { color : red; }");}
                else
                    {v24_label->setText("ok"); v24_label->setStyleSheet("QLabel { color : green; }");}
            }
            if (v28_label) // 28v
            {
                if (mops_obj.mops_stand_statment.mops_power_supply_error.mops_28v_error > 0)
                    {v28_label->setText("err"); v28_label->setStyleSheet("QLabel { color : red; }");}
                else
                    {v28_label->setText("ok"); v28_label->setStyleSheet("QLabel { color : green; }");}
            }


            // Обновляем статус каналов (логика не менялась, остается такой же)
            for (int ch = 0; ch < 8; ++ch)
            {
                // указатель на лейбл канала нормального статуса
                QLabel* norm_label = findChild<QLabel*>(QString("lable_norm_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на лейбл обрыва канала
                QLabel* break_label = findChild<QLabel*>(QString("lable_break_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на статус внимания канала
                QLabel* attn_label = findChild<QLabel*>(QString("lable_attantion_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на статус пожара канала
                QLabel* fire_label = findChild<QLabel*>(QString("lable_fire_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на статус короткого замыкания канала
                QLabel* sc_label = findChild<QLabel*>(QString("lable_break_mops_%1_sc_%2").arg(id + 1).arg(ch + 1));

                // обновляем статус канала
                if (norm_label)
                {
                    if (mops_obj.mops_stand_statment.mops_ch_statement.mops_ch_err_normal[ch] == 0)
                        {norm_label->setText("ok"); norm_label->setStyleSheet("QLabel { color : green; }");}
                    else
                        {norm_label->setText("err"); norm_label->setStyleSheet("QLabel { color : red; }");}
                }

                if (break_label)
                {
                    if (mops_obj.mops_stand_statment.mops_ch_statement.mops_ch_err_break[ch] == 0)
                        {break_label->setText("ok"); break_label->setStyleSheet("QLabel { color : green; }");}
                    else
                        {break_label->setText("err"); break_label->setStyleSheet("QLabel { color : red; }");}
                }

                if (attn_label)
                {
                    if (mops_obj.mops_stand_statment.mops_ch_statement.mops_ch_err_attantion[ch] == 0)
                        {attn_label->setText("ok"); attn_label->setStyleSheet("QLabel { color : green; }");}
                    else
                        {attn_label->setText("err"); attn_label->setStyleSheet("QLabel { color : red; }");}
                }


                if (fire_label)
                {
                    if (mops_obj.mops_stand_statment.mops_ch_statement.mops_ch_err_fire[ch] == 0)
                        {fire_label->setText("ok"); fire_label->setStyleSheet("QLabel { color : green; }");}
                    else
                        {fire_label->setText("err"); fire_label->setStyleSheet("QLabel { color : red; }");}
                }


                if (sc_label)
                {
                    if (mops_obj.mops_stand_statment.mops_ch_statement.mops_ch_err_sc[ch] == 0)
                        {sc_label->setText("ok"); sc_label->setStyleSheet("QLabel { color : green; }");}
                    else
                        {sc_label->setText("err");sc_label->setStyleSheet("QLabel { color : red; }");}
                }
            }
        }
    });
}

/**
 * @brief clear_mops_gui данный метод очищает ГУИ всех вкладок МУПСов
 */
void stend_main_window::clear_mops_gui()
{
    QMetaObject::invokeMethod(this, [this]()
    {
        // Проходим по всем МОПСам в карте
        for (int id = 0; id < 10; ++id)
        {
            // статус исправности модуля
            QLabel* operable_label = findChild<QLabel*>(QString("just_lable_oper_status_ans_mops_%1").arg(id + 1));
            // статус онлайн/оффлайн статуса модуля
            QLabel* online_label = findChild<QLabel*>(QString("just_lable_online_status_ans_mops_%1").arg(id + 1));

            // получаем указатель на вкладку
            int tabIndex = id; // соответствует индексу вкладки
            QString tabName = QString("%1").arg(id + 1);   // название вкладки

            // Устанавливаем обычный шрифт для текста вкладки
            QFont tabFont = ui->tab_widget_for_mops->tabBar()->font();  // Получаем текущий обычный вкладки
            tabFont.setBold(false);  // Делаем шрифт жирным
            ui->tab_widget_for_mops->tabBar()->setFont(tabFont);  // Применяем обычный шрифт

            // очищаем статус работоспособности МОПСа
            if (operable_label)
            {

                    operable_label->setText("");
                    operable_label->setStyleSheet("QLabel { color : black; }");

                    // Изменяем текст вкладки (оставляем логику неизменной)
                    ui->tab_widget_for_mops->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mops->tabBar()->setTabTextColor(tabIndex, QColor("black"));
            }

            // Обновляем статус онлайн/оффлайн
            if (online_label)
            {

                    online_label->setText("");
                    online_label->setStyleSheet("QLabel { color : black; }");
            }

            // Обновляем статус питания и каналов
            QLabel* v18_label = findChild<QLabel*>(QString("lable_18v_ans_mops_%1").arg(id + 1));
            QLabel* v24_label = findChild<QLabel*>(QString("lable_24v_ans_mops_%1").arg(id + 1));
            QLabel* v28_label = findChild<QLabel*>(QString("lable_28v_ans_mops_%1").arg(id + 1));
            if (v18_label)  // 18v
            {
                v18_label->setText(""); v18_label->setStyleSheet("QLabel { color : black; }");
            }
            if (v24_label) // 24v
            {
                v24_label->setText(""); v24_label->setStyleSheet("QLabel { color : black; }");
            }
            if (v28_label) // 28v
            {
                v28_label->setText(""); v28_label->setStyleSheet("QLabel { color : black; }");
            }


            // Обновляем статус каналов (логика не менялась, остается такой же)
            for (int ch = 0; ch < 8; ++ch)
            {
                // указатель на лейбл канала нормального статуса
                QLabel* norm_label = findChild<QLabel*>(QString("lable_norm_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на лейбл обрыва канала
                QLabel* break_label = findChild<QLabel*>(QString("lable_break_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на статус внимания канала
                QLabel* attn_label = findChild<QLabel*>(QString("lable_attantion_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на статус пожара канала
                QLabel* fire_label = findChild<QLabel*>(QString("lable_fire_mops_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // указатель на статус короткого замыкания канала
                QLabel* sc_label = findChild<QLabel*>(QString("lable_break_mops_%1_sc_%2").arg(id + 1).arg(ch + 1));

                // обновляем статус канала
                if (norm_label)
                {
                    norm_label->setText(""); norm_label->setStyleSheet("QLabel { color : black; }");
                }

                if (break_label)
                {
                    break_label->setText(""); break_label->setStyleSheet("QLabel { color : black; }");
                }

                if (attn_label)
                {
                    attn_label->setText(""); attn_label->setStyleSheet("QLabel { color : black; }");
                }


                if (fire_label)
                {
                    fire_label->setText(""); fire_label->setStyleSheet("QLabel { color : balck; }");
                }


                if (sc_label)
                {
                    sc_label->setText(""); sc_label->setStyleSheet("QLabel { color : black; }");
                }
            }
        }
    });
}


/**
 * @brief update_mups_gui данный метод обновляет ГУИ всех вкладок МУПСов
 * @param mups_map
 */
void stend_main_window::update_mups_gui(const std::map<int, mups>& mups_map)
{
    QMetaObject::invokeMethod(this, [this, mups_map]()
    {
        for(const auto& [id, mups_obj] : mups_map)
        {
            // статус исправности модуля
            QLabel* online_label = findChild<QLabel*>(QString("just_lable_online_status_ans_mups_%1").arg(id + 1));
            // статус исправности модуля
            QLabel* operable_label = findChild<QLabel*>(QString("just_lable_oper_status_ans_mups_%1").arg(id + 1));

            // получаем указатель на вкладку
            int tabIndex = id;  // соответстует индексу вкладки
            QString tabName = QString("%1").arg(id + 1); // текст название вкладки

            // устанавливаем жирный шрифт для текста вкладки
            QFont tabFont = ui->tab_widget_for_mups->tabBar()->font();  // получаем текущий шрифт вкладки
            tabFont.setBold(true);  // делаем шрифт жирным
            ui->tab_widget_for_mups->tabBar()->setFont(tabFont);    // применяем жирный шрифт

            // обновляем статус работоспособности МУПСа
            if(operable_label)
            {
                if(mups_obj.mups_stand_statment.mups_statment.mups_operable > 0)
                {
                    operable_label->setText("Operable");
                    operable_label->setStyleSheet("QLabel { color : green; }");

                    // Изменяем текст вкладки
                    ui->tab_widget_for_mups->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mups->tabBar()->setTabTextColor(tabIndex, QColor("green"));
                }
                else
                {
                    operable_label->setText("Error");
                    operable_label->setStyleSheet("QLabel { color : red; }");

                    // Изменяем текст вкладки
                    ui->tab_widget_for_mups->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mups->tabBar()->setTabTextColor(tabIndex, QColor("red"));
                }
            }

            // обновляем статус онлайн/оффлайн
            if(online_label)
            {
                // offline
                if(mups_obj.mups_stand_statment.mups_statment.mups_offline > 0)
                {
                    online_label->setText("Offline");
                    online_label->setStyleSheet("QLabel { color : gray; }");
                    operable_label->setText("");

                    // изменяем текст вкладки
                    ui->tab_widget_for_mups->setTabText(tabIndex, tabName);
                    ui->tab_widget_for_mups->tabBar()->setTabTextColor(tabIndex, QColor("gray"));
                    continue;
                }
                // online
                if(mups_obj.mups_stand_statment.mups_statment.mups_online)
                {
                    online_label->setText("Online");
                    online_label->setStyleSheet("QLabel { color : green; }");
                }
                else
                {
                    online_label->setText("Online error !");
                    online_label->setStyleSheet("QLabel { color : red; }");
                    continue;
                }
            }

            // объновляем статус питания и каналов
            QLabel* v18_label = findChild<QLabel*>(QString("lable_18v_ans_mups_%1").arg(id + 1));
            QLabel* v24_label = findChild<QLabel*>(QString("lable_24v_ans_mups_%1").arg(id + 1));
            QLabel* v28_label = findChild<QLabel*>(QString("lable_28v_ans_mups_%1").arg(id + 1));

            if(v18_label)   // 18
            {
                if(mups_obj.mups_stand_statment.mups_power_supply_error.mups_18v_error > 0)
                    {v18_label->setText("err"); v18_label->setStyleSheet("QLabel { color : red; }");}
                else
                    {v18_label->setText("Ok"); v18_label->setStyleSheet("QLabel { color : green; }");}
            }
            if(v24_label)   // 24
            {
                if(mups_obj.mups_stand_statment.mups_power_supply_error.mups_24v_error > 0)
                    {v24_label->setText("err"); v24_label->setStyleSheet("QLabel { color : red; }");}
                else
                    {v24_label->setText("Ok"); v24_label->setStyleSheet("QLabel { color : green; }");}
            }
            if(v28_label) // 28
            {
                if(mups_obj.mups_stand_statment.mups_power_supply_error.mups_28v_error > 0)
                    {v28_label->setText("err"); v28_label->setStyleSheet("QLabel { color : red; }");}
                else
                    {v28_label->setText("Ok"); v28_label->setStyleSheet("QLabel { color : green; }");}
            }

            // Обновляем статус каналов
            for(int ch = 0; ch < 4; ++ch)
            {
                // обрыв, канал выключен
                QLabel* break_ch_off = findChild<QLabel*> (QString("lable_break_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // обрыв, канал ыключен
                QLabel* break_ch_on = findChild<QLabel*> (QString("lable_break_ch_on_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));

                // норма, канал выключен
                QLabel* norm_ch_off = findChild<QLabel*> (QString("lable_norm_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // норма, канал ыключен
                QLabel* norm_ch_on = findChild<QLabel*> (QString("lable_norm_ch_on_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));

                // обрыв, канал выключен
                QLabel* sc_ch_off = findChild<QLabel*> (QString("lable_sc_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // превышение по току, канал принудительно отключен
                QLabel* curr_up_ch_for_off = findChild<QLabel*> (QString("lable_curr_off_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));

                if(break_ch_off)   // обрыв, канал отключен
                {
                    if(mups_obj.mups_stand_statment.mups_ch_statement.mups_ch_err_break_ch_off[ch] > 0)
                        {break_ch_off->setText("err"); break_ch_off->setStyleSheet("QLabel { color : red; }");}
                    else
                        {break_ch_off->setText("Ok"); break_ch_off->setStyleSheet("QLabel { color : green; }");}
                }

                if(break_ch_on)   // обрыв, канал включен
                {
                    if(mups_obj.mups_stand_statment.mups_ch_statement.mups_ch_err_break_ch_on[ch] > 0)
                        {break_ch_on->setText("err"); break_ch_on->setStyleSheet("QLabel { color : red; }");}
                    else
                        {break_ch_on->setText("Ok"); break_ch_on->setStyleSheet("QLabel { color : green; }");}
                }

                if(norm_ch_off)   // норма, канал выключен
                {
                    if(mups_obj.mups_stand_statment.mups_ch_statement.mups_ch_err_norm_ch_off[ch] > 0)
                        {norm_ch_off->setText("err"); norm_ch_off->setStyleSheet("QLabel { color : red; }");}
                    else
                        {norm_ch_off->setText("Ok"); norm_ch_off->setStyleSheet("QLabel { color : green; }");}
                }

                if(norm_ch_on)   // норма, канал включен
                {
                    if(mups_obj.mups_stand_statment.mups_ch_statement.mups_ch_err_norm_ch_on[ch] > 0)
                        {norm_ch_on->setText("err"); norm_ch_on->setStyleSheet("QLabel { color : red; }");}
                    else
                        {norm_ch_on->setText("Ok"); norm_ch_on->setStyleSheet("QLabel { color : green; }");}
                }

                if(sc_ch_off)   // КЗ, канал выключен
                {
                    if(mups_obj.mups_stand_statment.mups_ch_statement.mups_ch_err_sc_ch_off[ch] > 0)
                        {sc_ch_off->setText("err"); sc_ch_off->setStyleSheet("QLabel { color : red; }");}
                    else
                        {sc_ch_off->setText("Ok"); sc_ch_off->setStyleSheet("QLabel { color : green; }");}
                }

                if(curr_up_ch_for_off)   // превышение тока, канал принудительно отключен
                {
                    if(mups_obj.mups_stand_statment.mups_ch_statement.mups_ch_err_cur_up_ch_off_force[ch] > 0)
                        {curr_up_ch_for_off->setText("err"); curr_up_ch_for_off->setStyleSheet("QLabel { color : red; }");}
                    else
                        {curr_up_ch_for_off->setText("Ok"); curr_up_ch_for_off->setStyleSheet("QLabel { color : green; }");}
                }
            }
        }
    });
}


/**
 * @brief stend_main_window::clear_mups_gui данный метод очищает интерфейс МУПСов
 */
void stend_main_window::clear_mups_gui()
{
    QMetaObject::invokeMethod(this, [this]()
    {
        for(int id = 0; id < 10; ++id)
        {
            // статус исправности модуля
            QLabel* online_label = findChild<QLabel*>(QString("just_lable_online_status_ans_mups_%1").arg(id + 1));
            // статус исправности модуля
            QLabel* operable_label = findChild<QLabel*>(QString("just_lable_oper_status_ans_mups_%1").arg(id + 1));

            // получаем указатель на вкладку
            int tabIndex = id;  // соответстует индексу вкладки
            QString tabName = QString("%1").arg(id + 1); // текст название вкладки

            // устанавливаем обычный шрифт для текста вкладки
            QFont tabFont = ui->tab_widget_for_mups->tabBar()->font();  // получаем текущий шрифт вкладки
            tabFont.setBold(false);  // делаем шрифт обычным
            ui->tab_widget_for_mups->tabBar()->setFont(tabFont);    // применяем обычный шрифт

            // очищаем статус работоспособности МУПСа
            if(operable_label)
            {
                operable_label->setText("");
                operable_label->setStyleSheet("QLabel { color : black; }");

                // Изменяем текст вкладки
                ui->tab_widget_for_mups->setTabText(tabIndex, tabName);
                ui->tab_widget_for_mups->tabBar()->setTabTextColor(tabIndex, QColor("black"));
            }

            // очищаем статус онлайн/оффлайн
            if(online_label)
            {
                    online_label->setText("");
                    online_label->setStyleSheet("QLabel { color : black; }");
            }

            // 18v 24v 28v
            QLabel* v18_label = findChild<QLabel*>(QString("lable_18v_ans_mups_%1").arg(id + 1));
            QLabel* v24_label = findChild<QLabel*>(QString("lable_24v_ans_mups_%1").arg(id + 1));
            QLabel* v28_label = findChild<QLabel*>(QString("lable_28v_ans_mups_%1").arg(id + 1));

            // очищаем статус питания и каналов
            if(v18_label){v18_label->setText(""); v18_label->setStyleSheet("QLabel { color : black; }");}
            if(v24_label){v24_label->setText(""); v24_label->setStyleSheet("QLabel { color : black; }");}
            if(v28_label){v28_label->setText(""); v28_label->setStyleSheet("QLabel { color : black; }");}

            // Обновляем статус каналов
            for(int ch = 0; ch < 4; ++ch)
            {
                // обрыв, канал выключен
                QLabel* break_ch_off = findChild<QLabel*> (QString("lable_break_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // обрыв, канал ыключен
                QLabel* break_ch_on = findChild<QLabel*> (QString("lable_break_ch_on_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));

                // норма, канал выключен
                QLabel* norm_ch_off = findChild<QLabel*> (QString("lable_norm_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // норма, канал ыключен
                QLabel* norm_ch_on = findChild<QLabel*> (QString("lable_norm_ch_on_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));

                // обрыв, канал выключен
                QLabel* sc_ch_off = findChild<QLabel*> (QString("lable_sc_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));
                // превышение по току, канал принудительно отключен
                QLabel* curr_up_ch_for_off = findChild<QLabel*> (QString("lable_curr_off_ch_off_mups_%1_ch_%2").arg(id + 1).arg(ch + 1));

                // очищаем обрыв, канал выключен
                if(break_ch_off){break_ch_off->setText(""); break_ch_off->setStyleSheet("QLabel { color : black; }");}

                // очищаем обрыв, канал включен
                if(break_ch_on){break_ch_on->setText(""); break_ch_on->setStyleSheet("QLabel { color : black; }");}

                // очищаем норма, канал выключен
                if(norm_ch_off){norm_ch_off->setText(""); norm_ch_off->setStyleSheet("QLabel { color : black; }");}

                // очищаем норма, канал включен
                if(norm_ch_on){norm_ch_on->setText(""); norm_ch_on->setStyleSheet("QLabel { color : black; }");}

                // очищаем КЗ, канал выключен
                if(sc_ch_off){sc_ch_off->setText(""); sc_ch_off->setStyleSheet("QLabel { color : black; }");}

                // очищаем превышение тока, канал принудительно отключен
                if(curr_up_ch_for_off){curr_up_ch_for_off->setText(""); curr_up_ch_for_off->setStyleSheet("QLabel { color : black; }");}
            }
        }
    });
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

            // очищаем гуи мопсов и мупсов
            this->clear_mops_gui();
            this->clear_mups_gui();

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
                // проверяем условия выбран ли для проверки хотябы один МОПС
                if(stand_test_board.get_mops_checkbox_flag())
                {
                    // СТАРТ тест МОПСов
                    stand_test_board.start_main_test_mops(&modbus_stand_board, &stand_test_board);

                    // Устанавливаем лейбл, что в данный момент тестируется МОПС
                    QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("МОПС");});

                    // Цикл проверки МОПСов
                    while (isTestRunning)
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(1));

                        // Проверяем, занят ли тест
                        bool status = stand_test_board.check_test_is_busy(&modbus_stand_board, &stand_test_board);

                        // Если тест завершен, выходим из цикла
                        if (status == true)
                        {
                            // считываем результаты тестирования МОПСов
                            std::map<int, mops> mops_map_cont = stand_test_board.read_mops_status_return(&modbus_stand_board, &stand_test_board);  // считываем результаты

                            // обновляем ГУИ
                            this->update_mops_gui(mops_map_cont);

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
                }

                // проверяем установлин хотя-бы один чекбокс МУПСа
                if(stand_test_board.get_mups_checkbox_flag())
                {
                    // СТАРТ тест МУПСов
                    stand_test_board.start_main_test_mups(&modbus_stand_board, &stand_test_board);

                    // Устанавливаем лейбл, что в данный момент тестируется МУПС
                    QMetaObject::invokeMethod(this, [this](){ui->just_lable_in_test_ans->setText("МУПС");});

                    // Цикл проверки МУПСов
                    while (isTestRunning)
                    {
                        std::this_thread::sleep_for(std::chrono::seconds(1));

                        // Проверяем, занят ли тест
                        bool status = stand_test_board.check_test_is_busy(&modbus_stand_board, &stand_test_board);

                        // Если тест завершен, выходим из цикла
                        if (status == true)
                        {
                            // считываем результаты тестирования МYПСов
                            std::map<int, mups> mups_map_cont = stand_test_board.read_mups_status_return(&modbus_stand_board, &stand_test_board);  // считываем результаты

                            // обновляем ГУИ
                            this->update_mups_gui(mups_map_cont);

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



