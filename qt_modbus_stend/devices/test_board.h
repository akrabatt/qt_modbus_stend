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

    enum : uint16_t
    {
        mups_id_1 = 11000,
        mups_id_2 = 11036,
        mups_id_3 = 11072,
        mups_id_4 = 11108,
        mups_id_5 = 11144,
        mups_id_6 = 11180,
        mups_id_7 = 11216,
        mups_id_8 = 11252,
        mups_id_9 = 11288,
        musp_id_10 = 11324
    }mups_start_reg;        // стартовые регистры для каждого из мупсов

    uint16_t mups_start_reg_arr[10] = {11000, 11036, 11072, 11108, 11144, 11180, 11216, 11252, 11288, 11324};       // стартовые регистры МУПСов в массиве

    enum : uint16_t
    {
        mops_id_1 = 10000,
        mops_id_2 = 10056,
        mops_id_3 = 10112,
        mops_id_4 = 10168,
        mops_id_5 = 10224,
        mops_id_6 = 10280,
        mops_id_7 = 10336,
        mops_id_8 = 10392,
        mops_id_9 = 10448,
        mops_id_10 = 10504
    }mops_start_reg;        // стартовые регистры для каждого из мопсов

    uint16_t mops_start_reg_arr[10] = {10000, 10056, 10112, 10168, 10224, 10280, 10336, 10392, 10448, 10504};       // стартовые регистры МОПСов в массиве

    std::vector<uint16_t> mops_active_checkbox;  // вектор хранящий выбранные для проверки МОПСы
    std::vector<uint16_t> mups_active_checkbox;  // векстр хранящий выбранные для проверки МУПСы

public:
    // объекты МОПСами
    std::map<int, mops> mops_map;   // список с объектами МОПСов
private:
    std::vector<int> mops_id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // id

public:
    // объекты МУПСами
    std::map<int, mups> mups_map;   // список с объектами МУПСов
private:
    std::vector<int> mups_id = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};     // id

public:
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
    void read_mops_status(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief read_mups_status метод считывающий результаты тестирования МУПСов с платы
     * @param modbusrtu_ptr
     * @param test_board_ptr
     */
    void read_mups_status(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief read_mops_status_return метод считывающий результаты тестирования МОПСов и возвращает обратно контейнер
     * @param modbusrtu_ptr
     * @param test_board_ptr
     * @return
     */
    std::map<int, mops> read_mops_status_return(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);

    /**
     * @brief read_mups_status_return
     * @param modbusrtu_ptr
     * @param test_board_ptr
     * @return
     */
    std::map<int, mops> read_mups_status_return(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr);
};

#endif // TEST_BOARD_H
