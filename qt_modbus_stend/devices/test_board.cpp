#include "test_board.h"
#include <numeric>

// пустой конструктор
test_board::test_board(){}

/**
 * @brief test_board::test_board конструктор с пар-ми который вызывает конструктор базового касса
 * @param id адрес
 */
test_board::test_board(int id) : device_base_class(id){};

// деструктор
test_board::~test_board(){};

/**
 * @brief test_board::set_active_mops_checkbox метод установки
 * @param select_var 1 или 0
 * @param position_in_arr индекс элемента
 */
void test_board::set_active_mops_checkbox(unsigned int select_var, int position_in_arr)
{
    // проверяем достаточно ли места в векторе
    if((mops_active_checkbox.capacity() == 0) || (mops_active_checkbox.capacity() < 10)) {mops_active_checkbox.resize(10);}

    int local_bool = 0; // локальная переменная

    if(select_var > 0){local_bool = 1;}

    // добавляем значение на определенную позицию в векторе
    //mops_active_checkbox.insert(mops_active_checkbox.begin() + position_in_arr, local_bool);
    mops_active_checkbox[position_in_arr] = local_bool;
}

/**
 * @brief test_board::set_active_mups_checkbox метод установки
 * @param select_var 1 или 0
 * @param position_in_arr индекс элемента
 */
void test_board::set_active_mups_checkbox(unsigned int select_var, int position_in_arr)
{
    // проверяем достаточно ли места в векторе
    if((mups_active_checkbox.capacity() == 0) || (mups_active_checkbox.capacity() < 10)) {mups_active_checkbox.resize(10);}

    int local_bool = 0; // локальная переменная

    if(select_var > 0){local_bool = 1;}

    // добавляем значение на определенную позицию в векторе
    //mups_active_checkbox.insert(mups_active_checkbox.begin() + position_in_arr, local_bool);
    mups_active_checkbox[position_in_arr] = local_bool;
}

/**
 * @brief test_board::get_active_mops_checkbox метод возвращает значение определенного элемента
 * @param position_in_arr индекс элемента, не более 10
 * @return занчение
 */
int test_board::get_active_mops_checkbox(unsigned int position_in_arr)
{
    return mops_active_checkbox[position_in_arr];
}

/**
 * @brief test_board::get_active_mups_checkbox метод возвращает значение определенного элемента
 * @param position_in_arr индекс элемента, не более 10
 * @return занчение
 */
int test_board::get_active_mups_checkbox(unsigned int position_in_arr)
{
    return mups_active_checkbox[position_in_arr];
}

/**
 * @brief get_sum_mops_checkbox функция сложения всех элементов вектора
 * @return сумма элементов вектора
 */
int test_board::get_sum_mops_checkbox()
{
    return std::accumulate(this->mops_active_checkbox.begin(), this->mops_active_checkbox.end(), 0, std::plus<int>());
}

/**
 * @brief test_board::get_sum_mups_checkbox функция всех элементов вектора
 * @return сумма элементов векторов
 */
int test_board::get_sum_mups_checkbox()
{
    return std::accumulate(this->mups_active_checkbox.begin(), this->mups_active_checkbox.end(), 0, std::plus<int>());
}

/**
 * @brief write_active_mops_to_test_board_flag метод записи МОПСов активных для испытания в плату
 * @param modbusobj ссылка на объект
 * @return успех/неуспех
 */
bool test_board::write_active_mops_to_test_board_flag(modbusRTU *modbusobj)
{
   return modbusobj->mbm_16_write_registers_flag(this->mops_active_start_reg, this->mops_active_quant_reg, this->mops_active_checkbox);
}

/**
 * @brief write_active_mups_to_test_board_flag метод записи МУПСов активных для испытания в плату
 * @param modbusobj ссылка на объект
 * @return успех/неуспех
 */
bool test_board::write_active_mups_to_test_board_flag(modbusRTU *modbusobj)
{
    return modbusobj->mbm_16_write_registers_flag(this->mups_active_start_reg, this->mups_active_quant_reg, this->mups_active_checkbox);
}

/**
 * @brief wirte_active_mops_and_mups_to_test_board_flag метод записи МОПСов и МУПСов активный для испытания в плату
 * @param modbusobj ссылка на объект
 * @return успех/неуспех
 */
bool test_board::wirte_active_mops_and_mups_to_test_board_flag(modbusRTU *modbusobj)
{
    // создадим главный вектор который будет в себе содержать чекбоксы МОПСов и МУПСов
    std::vector<uint16_t> main_buf;

    // создадим сумарную переменную по кол-ву регистров для записи
    uint16_t main_quant_reg = this->mops_quant_reg + this->mups_quant_reg;

    // резервируем место в буфере под два вектора чекбоксов
    main_buf.reserve(this->mops_active_checkbox.size() + this->mups_active_checkbox.size());

   // добавляем в буфер МОПСы и МУПСы
    main_buf.insert(main_buf.end(), this->mops_active_checkbox.begin(), this->mops_active_checkbox.end());  // МОПСы
    main_buf.insert(main_buf.end(), this->mups_active_checkbox.begin(), this->mups_active_checkbox.end());  // МУПСы

    return modbusobj->mbm_16_write_registers_flag(this->mops_active_start_reg, main_quant_reg, main_buf);
}
