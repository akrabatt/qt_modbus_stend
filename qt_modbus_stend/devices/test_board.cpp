#include "test_board.h"
#include <numeric>
#include <iostream>

// пустой конструктор
test_board::test_board(){}

/**
 * @brief test_board::test_board конструктор с пар-ми который вызывает конструктор базового касса
 * @param id адрес
 */
test_board::test_board(int id) : device_base_class(id){}

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
 * @note данная функция записывает регистры, и проверяет свою запись считыванием этих же регистров из платы и сравнением
 */
bool test_board::wirte_active_mops_and_mups_to_test_board_flag(modbusRTU *modbusobj)
{
    // Главный вектор для хранения МОПСов и МУПСов (размер фиксированный)
    std::vector<uint16_t> main_buf(20, 0);

    // Вектор для хранения прочитанных данных
    std::vector<uint16_t> main_buf_read(20, 0);

    // Переменная успешности записи
    bool write_success = false;

    // Суммарное количество регистров для записи
    uint16_t main_quant_reg = this->mops_active_quant_reg + this->mups_active_quant_reg;

    // Заполняем буфер данными МОПСов и МУПСов
    std::copy(this->mops_active_checkbox.begin(), this->mops_active_checkbox.end(), main_buf.begin());          // МОПСы
    std::copy(this->mups_active_checkbox.begin(), this->mups_active_checkbox.end(), main_buf.begin() + 10);     // МУПСы

    // Пытаемся записать регистры
    try
    {
        write_success = modbusobj->mbm_16_write_registers_flag(this->mops_active_start_reg, main_quant_reg, main_buf);  // записываем

        if (!write_success)
        {
            // Если запись неуспешна, выбрасываем исключение
            throw std::runtime_error("Error write reg.");
        }
    }
    catch (const std::runtime_error &err)
    {
        // Логируем ошибку и возвращаем false
        std::cerr << "Write Error: " << err.what() << std::endl;
        return false;
    }

    // Пытаемся считать данные для проверки
    try
    {
        main_buf_read = modbusobj->mbm_03_read_registers(this->mops_active_start_reg, main_buf_read.size());  // считываем
    }
    catch (const std::runtime_error &err)
    {
        // Логируем ошибку и возвращаем false
        std::cerr << "Read Error: " << err.what() << std::endl;
        return false;
    }

    // Сравниваем записанные и прочитанные данные и возвращаем результат
    return std::equal(main_buf.begin(), main_buf.end(), main_buf_read.begin());
}

