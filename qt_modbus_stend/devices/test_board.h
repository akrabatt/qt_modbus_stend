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

    std::vector<uint16_t> mops_active_checkbox;  // вектор хранящий выбранные для проверки МОПСы
    std::vector<uint16_t> mups_active_checkbox;  // векстр хранящий выбранные для проверки МУПСы


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
     */
    void process_checkboxes(QCheckBox* mops[], QCheckBox* mups[], int mops_count, int mups_count, test_board *test_board_ptr, modbusRTU *modbusrtu_ptr, stend_main_window* window);

};

#endif // TEST_BOARD_H
