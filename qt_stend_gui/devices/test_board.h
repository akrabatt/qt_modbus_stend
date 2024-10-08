#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include "device_base_class.h"
#include "modbus_funct/modbusrtu.h"
#include "stend_main_window.h"
#include <cstdint>
#include <vector>
#include <iostream>
#include <QWidget>
#include <QMessageBox>
#include <algorithm>
#include "mops.h"
#include "mups.h"
#include "define.h"

/**
 * @brief The test_board class
 */
class test_board : public device_base_class/*, public std::runtime_error*/
{
private:
    uint16_t start_check_mops_button_reg = 9000;    // регистр кнопки запуска проверки МОПСов
    uint16_t mops_diagnostics_in_progress = 9001;   // регистр флага проверки мопса(1 - если проверка идет в данный момент, 0 - если проверки нет в данный момент)

    uint16_t start_check_mups_button_reg = 9002;    // регистр кнопки запуска проверки МУПСов
    uint16_t mups_diagnostics_in_progress = 9003;   // регистр флага проверки мупса(1 - если проверка идет в данный момент, 0 - если проверки нет в данный момент)

    uint16_t stand_config_area_quant_reg = 4;       // кол-во регистров управляющей зоны запуском тестов

    uint16_t mups_quant_reg = 36;     // кол-во запрашиваемых регистров для МУПСов
    uint16_t mops_quant_reg = 56;     // кол-во запрашиваемых регистров для МОПСов

    uint16_t mops_active_start_reg = 500;   // стартовый регистр МОПСов для активации проверки
    uint16_t mops_active_quant_reg = 10;    // кол-во регистров

    uint16_t mups_active_start_reg = 510;   // стартовый регистр МУПСов для активации проверки
    uint16_t mups_active_quant_reg = 10;    // кол-во регистров


    uint16_t mups_start_reg_arr_18v[10] = {11000, 11036, 11072, 11108, 11144, 11180, 11216, 11252, 11288, 11324};       // стартовые регистры МУПСов в массиве 18v
    uint16_t mups_start_reg_arr_24v[10] = {13000, 13036, 13072, 13108, 13144, 13180, 13216, 13252, 13288, 13324};       // стартовые регистры МУПСов в массиве 24v
    uint16_t mups_start_reg_arr_28v[10] = {15000, 15036, 15072, 15108, 15144, 15180, 15216, 15252, 15288, 15324};       // стартовые регистры МУПСов в массиве 28v


    uint16_t mops_start_reg_arr_18v[10] = {10000, 10056, 10112, 10168, 10224, 10280, 10336, 10392, 10448, 10504};       // стартовые регистры МОПСов в массиве 18v
    uint16_t mops_start_reg_arr_24v[10] = {12000, 12056, 12112, 12168, 12224, 12280, 12336, 12392, 12448, 12504};       // стартовые регистры МОПСов в массиве 18v
    uint16_t mops_start_reg_arr_28v[10] = {14000, 14056, 14112, 14168, 14224, 14280, 14336, 14392, 14448, 14504};       // стартовые регистры МОПСов в массиве 18v

    std::vector<uint16_t> mops_active_checkbox;  // вектор хранящий выбранные для проверки МОПСы
    bool mops_flag_checbox = false;     // флаг означает что один из чекбоксов МОПСов отмечен

    std::vector<uint16_t> mups_active_checkbox;  // векстр хранящий выбранные для проверки МУПСы
    bool mups_flag_checbox = false;     // флаг означает что один из чекбоксов МУПСов отмечен

    std::vector<int> mops_id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // id
    std::vector<int> mups_id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // id

public:
    std::map<int, mops> mops_map;   // список с объектами МОПСов
    std::map<int, mups> mups_map;   // список с объектами МУПСов


    // пустой конструктор
    test_board();

    /**
     * @brief test_board конструктор с пар-ми
     * @param id адрес платы
     */
    test_board(int id);

    // деструктор
    ~test_board();

    // СЕТТЕРЫ

    /**
     * @brief set_active_mops_checkbox метод активации МОПСов для испытания
     * @param select_var если > 0 - включить в испытания, если == 0 - исключить из испытаний
     * @param position_in_arr позиция в векторе
     */
    void set_active_mops_checkbox(unsigned int select_var, int position_in_arr);

    /**
     * @brief set_active_mups_checkbox метод активации МУПСов для испытания
     * @param select_var если > 0 - включить в испытания, если == 0 - исключить из испытаний
     * @param position_in_arr позиция в векторе
     */
    void set_active_mups_checkbox(unsigned int select_var, int position_in_arr);

    // ГЕТТЕРЫ

    /**
     * @brief get_active_mops_checkbox геттер возвращает значение 1 или 0
     * @param position_in_arr позицию в векторе
     * @return 1 или 0
     */
    int get_active_mops_checkbox(unsigned int position_in_arr);

    /**
     * @brief get_active_mups_checkbox геттер возвращает значение 1 или 0
     * @param position_in_arr позицию в векторе
     * @return 1 или 0
     */
    int get_active_mups_checkbox(unsigned int position_in_arr);

    /**
     * @brief get_sum_mops_checkbox функция сложения всех элементов вектора МОПСов
     * @return сумма элементов вектора
     */
    int get_sum_mops_checkbox();

    /**
     * @brief get_sum_mups_checkbox функция сложения всех элементов вектора МУПСов
     * @return сумма элементов вектора
     */
    int get_sum_mups_checkbox();

    // МЕТОДЫ

    /**
     * @brief write_active_mops_to_test_board_flag метод записи МОПСов активных для испытания в плату
     * @param modbusobj ссылка на объект
     * @return успех/неуспех
     */
    bool write_active_mops_to_test_board_flag(modbusRTU *modbusobj);

    /**
     * @brief write_active_mups_to_test_board_flag метод записи МУПСов активных для испытания в плату
     * @param modbusobj ссылка на объект
     * @return успех/неуспех
     */
    bool write_active_mups_to_test_board_flag(modbusRTU *modbusobj);

    /**
     * @brief wirte_active_mops_and_mups_to_test_board_flag метод записи МОПСов и МУПСов активный для испытания в плату
     * @param modbusobj ссылка на объект
     * @return успех/неуспех
     * @note данная функция записывает регистры, и проверяет свою запись считыванием этих же регистров из платы и сравнением
     */
    bool wirte_active_mops_and_mups_to_test_board_flag(modbusRTU *modbusobj);

    /**
     * @brief process_checkboxes метод обработки чекбоксом
     * @param mops массив указателей на чек-боксы мопсов
     * @param mups массив указателей не чек-боксы мупсов
     * @param mops_count кол-во чек-боксов
     * @param mups_count кол-во чек-боксов
     * @param test_board_ptr указатель на объект тестовой платы
     * @param modbustru_ptr указатель на объект контекста соединения модбаса
     * @param window указатель на объект главного окна
     * @return 1 - успешно, 0 - неуспешно
     */
    bool process_checkboxes(QCheckBox* mops[], QCheckBox* mups[], int mops_count, int mups_count, test_board *test_board_ptr, modbusRTU *modbusrtu_ptr, stend_main_window* window);

    /**
     * @brief check_test_is_busy данный метод проверяет 9001 и 9003 регистры платы, которые являются флагами что в данный момент идет проверка
     * @param modbusrtu_ptr указатель на объект контекста соединения модбаса
     * @param test_board_ptr    указатель на объект тестовой платы
     * @return если флаги не подняты, то возвращает - 1 и можно работать, если флаги подняты, то возвращает - 0
     */
    bool check_test_is_busy(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief start_main_test_mops функция старта тестирования МОПСов
     * @param modbusrtu_ptr указатель на контекст подключения модбаса
     * @param test_board_ptr
     */
    void start_main_test_mops(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief start_main_test_mops функция старта тестирования МУПСов
     * @param modbusrtu_ptr указатель на контекст подключения модбаса
     * @param test_board_ptr
     */
    void start_main_test_mups(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief read_mops_status метод считывающий результаты тестирования МОПСов с платы
     * @param modbusrtu_ptr
     * @param test_board_ptr
     */
//    void read_mops_status(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief read_mups_status метод считывающий результаты тестирования МУПСов с платы
     * @param modbusrtu_ptr
     * @param test_board_ptr
     */
//    void read_mups_status(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief read_mops_status_return метод считывающий результаты тестирования МОПСов и возвращает обратно контейнер
     * @param modbusrtu_ptr
     * @param test_board_ptr
     * @param cond_var даной переменной выбирем массив МУПСов с питанием
     * @return
     */
    std::map<int, mops> read_mops_status_return(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr, int cond_var);

    /**
     * @brief read_mups_status_return
     * @param modbusrtu_ptr
     * @param test_board_ptr
     * @param cond_var данной переменной выбираем массив МУПСов спитанием
     * @return
     */
    std::map<int, mups> read_mups_status_return(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr, int cond_var);

    /**
     * @brief get_mops_checkbox_flag функция возвращает флаг который показывает установлен или хотя-бы один чекбокс МОПСов
     * @return
     */
    bool get_mops_checkbox_flag();

    /**
     * @brief get_mups_checkbox_flag функция возвращает флаг который показывает установлен или хотя-бы один чекбокс МУПСов
     * @return
     */
    bool get_mups_checkbox_flag();
};

#endif // TEST_BOARD_H
