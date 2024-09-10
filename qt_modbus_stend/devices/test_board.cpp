#include "test_board.h"

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

