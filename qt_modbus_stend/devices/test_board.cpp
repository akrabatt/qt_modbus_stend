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

/**
 * @brief process_checkboxes метод обработки чекбоксом
 * @param mops массив указателей на чек-боксы мопсов
 * @param mups массив указателей не чек-боксы мупсов
 * @param mops_count кол-во чек-боксов
 * @param mups_count кол-во чек-боксов
 * @param test_board_ptr указатель на объект тестовой платы
 * @param modbustru_ptr указатель на объект контекста соединения модбаса
 * @param window указатель на объект главного окна
 * @param 1 - успех, 0 - неуспех
 */
bool test_board::process_checkboxes(QCheckBox* mops[], QCheckBox* mups[], int mops_count, int mups_count, test_board *test_board_ptr, modbusRTU *modbusrtu_ptr, stend_main_window* window)
{
    // обрабатываем чек-боксы для МОПСов и МУПСов
    for (int i = 0; i < 10; ++i)
    {
        test_board_ptr->set_active_mops_checkbox(mops[i]->isChecked() ? 1 : 0, i);
        test_board_ptr->set_active_mups_checkbox(mups[i]->isChecked() ? 1 : 0, i);
    }

    // Проверяем количество отмеченных МОПСов и МУПСов
    int mops_var_sum = test_board_ptr->get_sum_mops_checkbox();
    int mups_var_sum = test_board_ptr->get_sum_mups_checkbox();

    // если не отмечены модули, то выводим ошибку и выходим
    if (mops_var_sum == 0 && mups_var_sum == 0)
    {
        QMetaObject::invokeMethod(window, [window]()
        {
            QMessageBox::warning(window, "Error", "The module is not selected");
        });
        return false; // Завершаем выполнение потока
    }

    // записываем регистры с МОПСами и МУПСами которые будем испытывать в плату
    bool success = test_board_ptr->wirte_active_mops_and_mups_to_test_board_flag(modbusrtu_ptr);

    // Проверяем успех операции
    if (!success)
    {
        throw std::runtime_error("Error writing registers.");
        return false;
    }

    // Проверяем успех операции
    if (success)
    {
        QMetaObject::invokeMethod(window, [window]()
        {
            QMessageBox::information(window, "Success", "Registers written successfully.");
            return true;
        });
    }
    else
    {
        QMetaObject::invokeMethod(window, [window]()
        {
            QMessageBox::warning(window, "Error", "Error writing registers.");
            return false;
        });
    }
    return true;
}

/**
 * @brief check_test_is_busy данный метод проверяет 9001 и 9003 регистры платы, которые являются флагами что в данный момент идет проверка
 * @param modbusrtu_ptr      указатель на объект контекста соединения модбаса
 * @param test_board_ptr     указатель на объект тестовой платы
 * @return                   если флаги не подняты, то возвращает - 1 и можно работать, если флаги подняты, то возвращает - 0
 */
bool test_board::check_test_is_busy(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr)
{
    // считываем зону запуска тестов и их флагов
    std::vector<uint16_t> stand_config_area = modbusrtu_ptr->mbm_03_read_registers(this->start_check_mops_button_reg, this->stand_config_area_quant_reg);

    // проверяем стоят ли какие либо флаги
    uint16_t result_sum = std::accumulate(stand_config_area.begin(), stand_config_area.end(), 0, std::plus<uint16_t>());

    return result_sum == 0 ? 1 : 0;
}

/**
 * @brief start_main_test_mops функция старта тестирования МОПСов
 * @param modbusrtu_ptr указатель на контекст подключения модбаса
 * @param window_ptr указатель на gui
 * @param test_board_ptr
 */
void test_board::start_main_test_mops(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr)
{
    // проверяем стоит ли какой либо из флагов, если да, то выходим
    if(test_board_ptr->check_test_is_busy(modbusrtu_ptr, test_board_ptr) == 0) {return;}

    // записываем флаг старта испытания МОПСов
    modbusrtu_ptr->mbm_16_write_single_register(this->start_check_mops_button_reg, 1);
}

/**
 * @brief start_main_test_mops функция старта тестирования МУПСов
 * @param modbusrtu_ptr указатель на контекст подключения модбаса
 * @param test_board_ptr
 */
void test_board::start_main_test_mups(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr)
{
    // проверяем стоит ли какой либо из флагов, если да, то выходим
    if(test_board_ptr->check_test_is_busy(modbusrtu_ptr, test_board_ptr) == 0) {return;}

    // записываем флаг старта испытания МОПСов
    modbusrtu_ptr->mbm_16_write_single_register(this->start_check_mups_button_reg, 1);
}

/**
 * @brief test_board::read_mops_status
 * @param modbusrtu_ptr
 * @param test_board_ptr
 */
void test_board::read_mops_status(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr)
{
    // очищаем наш список с объектами мопсов
    this->mops_map.clear();

    // создаем переменную равную кол-ву модулей
    size_t mops_addr_start_reg_size = sizeof(this->mops_start_reg_arr)/sizeof(this->mops_start_reg_arr[0]);

    // запускаем цикл
    for(int i = 0; i < mops_addr_start_reg_size; i++)
    {
        // считываем данные i-ого МОПСа
        std::vector<uint16_t> current_buffer = modbusrtu_ptr->mbm_03_read_registers(this->mops_start_reg_arr[i], this->mops_quant_reg);

        // создаем МОПС
        mops mops_obj(i);

        // Копируем данные из current_buffer в поля структуры mops_stand_statment вручную
        if (current_buffer.size() >= 56) // Проверяем, что буфер содержит достаточно данных
        {
            for (size_t j = 0; j < 56; j++)
            {
                mops_obj.mops_stand_statment.main_buff[j] = static_cast<int>(current_buffer[j]);  // Преобразуем uint16_t в int
            }
        }

        // добавляем мопс
        //this->mops_map.insert({i, mops_obj});
        this->mops_map[i] = mops_obj;
    }
}


/**
 * @brief read_mops_status_return метод считывающий результаты тестирования МОПСов и возвращает обратно контейнер
 * @param modbusrtu_ptr
 * @param test_board_ptr
 * @return
 */
std::map<int, mops> test_board::read_mops_status_return(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr)
{
    // создаем локальный контейнер
    std::map<int, mops> local_mops_map;

    // очищаем наш список с объектами мопсов
    this->mops_map.clear();

    // создаем переменную равную кол-ву модулей
    size_t mops_addr_start_reg_size = sizeof(this->mops_start_reg_arr)/sizeof(this->mops_start_reg_arr[0]);

    // запускаем цикл
    for(int i = 0; i < mops_addr_start_reg_size; i++)
    {
        // считываем данные i-ого МОПСа
        std::vector<uint16_t> current_buffer = modbusrtu_ptr->mbm_03_read_registers(this->mops_start_reg_arr[i], this->mops_quant_reg);

        // создаем МОПС
        mops mops_obj(i);

        // Копируем данные из current_buffer в поля структуры mops_stand_statment вручную
        if (current_buffer.size() >= 56) // Проверяем, что буфер содержит достаточно данных
        {
            for (size_t j = 0; j < 56; j++)
            {
                mops_obj.mops_stand_statment.main_buff[j] = static_cast<int>(current_buffer[j]);  // Преобразуем uint16_t в int
            }
        }

        // добавляем мопс
        //this->mops_map.insert({i, mops_obj});
        local_mops_map[i] = mops_obj;
    }

    return local_mops_map;
}

/**
 * @brief read_mups_status_return метод считывающий результаты тестирования МУПСов и возвращает обратно контейнер
 * @param modbusrtu_ptr
 * @param test_board_ptr
 * @return
 */
std::map<int, mups> test_board::read_mups_status_return(modbusRTU *modbusrtu_ptr, test_board *test_board_ptr)
{
    // создаем локальный контейнер
    std::map<int, mups> local_mups_map;

    // очищаем наш список с объектами мопсов
    this->mups_map.clear();

    // создаем переменную равную кол-ву модулей
    size_t mups_addr_start_reg_size = sizeof(this->mups_start_reg_arr)/sizeof(this->mups_start_reg_arr[0]);

    // запускаем цикл
    for(int i = 0; i < mups_addr_start_reg_size; i++)
    {
        // считываем данные i-ого МУПСа
        std::vector<uint16_t> current_buffer = modbusrtu_ptr->mbm_03_read_registers(this->mups_start_reg_arr[i], this->mups_quant_reg);

        // создаем МОПС
        mups mups_obj(i);

        // Копируем данные из current_buffer в поля структуры mops_stand_statment вручную
        if (current_buffer.size() >= 36) // Проверяем, что буфер содержит достаточно данных
        {
            for (size_t j = 0; j < 36; j++)
            {
                mups_obj.mups_stand_statment.main_buff[j] = static_cast<int>(current_buffer[j]);  // Преобразуем uint16_t в int
            }
        }

        // добавляем мопс
        //this->mops_map.insert({i, mops_obj});
        local_mups_map[i] = mups_obj;
    }

    return local_mups_map;
}
