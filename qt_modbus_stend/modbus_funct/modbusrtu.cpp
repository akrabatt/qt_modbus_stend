#include "../modbus_funct/modbusrtu.h"

modbusRTU::modbusRTU(){};   // пустой конструктор


/**
 * @brief modbusRTU::modbusRTU основной конструктор создает контекст соединения
 * @param device номер COM порта, причем надо указывать так: пример "COM1"
 * @param baud скорость в бодах, например 115200
 * @param parity четнойть, например 'N'
 * @param data_bit колличество данных в посылке, обычно 8
 * @param stop_bit стоп бит, например 1
 * @param slave_id id slave устройства, нашей платы
 */
modbusRTU::modbusRTU(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id)
    : device(device), baud(baud), parity(parity), data_bit(data_bit), stop_bit(stop_bit)
{
    // блокируем мьютексом конструктор
    std::lock_guard<std::mutex> lock(mtx_constr);

    // Создаем контекст Modbus RTU
    ctx = modbus_new_rtu(device.c_str(), baud, parity, data_bit, stop_bit);
    if (ctx == nullptr)
    {
        throw std::runtime_error("Unable to create the libmodbus context");
    }

    // Устанавливаем идентификатор slave
    if (modbus_set_slave(ctx, slave_id) == -1)
    {
        modbus_free(ctx);
        throw std::runtime_error("Unable to set slave ID");
    }

    // Устанавливаем таймауты (опционально)
    struct timeval response_timeout;
    response_timeout.tv_sec = 1;    // секунды
    response_timeout.tv_usec = 0;   // мил.сек
    modbus_set_response_timeout(ctx, response_timeout.tv_sec, response_timeout.tv_usec);

    // Подключаемся к устройству
    if (modbus_connect(ctx) == -1)
    {
        modbus_free(ctx);
        throw std::runtime_error("Connection failed: " + std::string(modbus_strerror(errno)));
    }
}

// деструктор
modbusRTU::~modbusRTU()
{
    // освобождаем ресурсы
    if(ctx)
    {
        modbus_close(ctx);
        modbus_free(ctx);
    }
}

/**
 * @brief create_modbus_context Создает и настраивает контекст Modbus RTU
 * @param device Устройство (например, COM порт)
 * @param baud Скорость (например, 115200)
 * @param parity Четность (например, 'N')
 * @param data_bit Кол-во бит данных (например, 8)
 * @param stop_bit Стоповый бит (например, 1)
 * @param slave_id Идентификатор slave устройства
 */
void modbusRTU::create_modbus_context(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id)
{
    // Блокируем мьютекс на время создания контекста
    std::lock_guard<std::mutex> lock(mtx_constr);

    // Создаем контекст Modbus RTU
    ctx = modbus_new_rtu(device.c_str(), baud, parity, data_bit, stop_bit);
    if (ctx == nullptr)
    {
        throw std::runtime_error("Unable to create the libmodbus context");
    }

    // Устанавливаем идентификатор slave
    if (modbus_set_slave(ctx, slave_id) == -1)
    {
        modbus_free(ctx);
        ctx = nullptr;  // Обнуляем указатель, чтобы избежать двойного освобождения
        throw std::runtime_error("Unable to set slave ID");
    }

    // Подключаемся к устройству
    if (modbus_connect(ctx) == -1)
    {
        modbus_free(ctx);
        ctx = nullptr;  // Обнуляем указатель, чтобы избежать двойного освобождения
        throw std::runtime_error("Connection failed: " + std::string(modbus_strerror(errno)));
    }
}

/**
 * @brief modbusRTU::mbm_16_write_registers Функция для записи регистров.
 * @param start_address Стартовый регистр.
 * @param size Количество регистров для записи.
 * @param values Вектор значений для записи.
 */
void modbusRTU::mbm_16_write_registers(const int &start_address, const int &size, const std::vector<uint16_t> &values)
{
    // Блокируем доступ к ресурсу с помощью мьютекса
    std::lock_guard<std::mutex> lock(mtx_constr);

    // Проверяем, что указанный размер не превышает размер вектора
    if (size > values.size()) {
        throw std::runtime_error("Size parameter exceeds the size of the values vector.");
    }

    // Пишем значения в несколько регистров
    if (modbus_write_registers(ctx, start_address, size, values.data()) == -1)
    {
        throw std::runtime_error("Failed to write registers: " + std::string(modbus_strerror(errno)));
    }
}

/**
 * @brief modbusRTU::mbm_16_write_single_register Функция для записи одного регистра с использованием modbus_write_registers.
 * @param start_address Адрес регистра для записи.
 * @param value Значение для записи в регистр.
 */
void modbusRTU::mbm_16_write_single_register(const int &start_address, const uint16_t &value)
{
    // Блокируем доступ к ресурсу с помощью мьютекса
    std::lock_guard<std::mutex> lock(mtx_constr);

    // Создаем массив с одним значением
    uint16_t values[1] = { value };

    // Пишем значение в один регистр с помощью modbus_write_registers
    if (modbus_write_registers(ctx, start_address, 1, values) == -1)
    {
        throw std::runtime_error("Failed to write register: " + std::string(modbus_strerror(errno)));
    }
}

/**
 * @brief modbusRTU::mbm_16_write_registers Функция для записи регистров. с флагом
 * @param start_address Стартовый регистр.
 * @param size Количество регистров для записи.
 * @param values Вектор значений для записи.
 * @return возвращает успех/неуспех
 */
bool modbusRTU::mbm_16_write_registers_flag(const int &start_address, const int &size, const std::vector<uint16_t> &values)
{
    // Блокируем доступ к ресурсу с помощью мьютекса
    std::lock_guard<std::mutex> lock(mtx_constr);

    // Проверяем, что указанный размер не превышает размер вектора
    if (size > values.size())
    {
        throw std::runtime_error("Size parameter exceeds the size of the values vector.");
        return false;
    }

    // Пишем значения в несколько регистров
    if (modbus_write_registers(ctx, start_address, size, values.data()) == -1)
    {
        throw std::runtime_error("Failed to write registers: " + std::string(modbus_strerror(errno)));
        return false;
    }

    return true;
}

/**
 * @brief mbm_03_read_registers функция чтения регистров
 * @param start_address начальный регистр для чтения
 * @param num_registers кол-во регистров для чтения
 * @return возвращаем вектор с регистрами
 */
std::vector<uint16_t> modbusRTU::mbm_03_read_registers(int start_address, int num_registers)
{
    // блокируем доступ к ресурам
    std::lock_guard<std::mutex> lock(mtx_constr);

    // создаем вектор с заданным кол-вом
    std::vector<uint16_t> values(num_registers);

    // Читаем значения из регистров
    if (modbus_read_registers(ctx, start_address, num_registers, values.data()) == -1)
    {
        throw std::runtime_error("Failed to read registers: " + std::string(modbus_strerror(errno)));
    }

    return values;
}


/**
 * @brief mbm_03_check_connection функция проверки связи с оборудованием
 * @return возвращает булевое значение (true - соединение успешное) (false - ошибка соединения)
 */
bool modbusRTU::mbm_03_check_connection()
{
    // блокируем доступ к ресурам
    std::lock_guard<std::mutex> lock(mtx_constr);

    // создаем вектор с заданным кол-вом
    std::vector<uint16_t> values(3);

    // Читаем значения из регистров
    if (modbus_read_registers(ctx, 0, 3, values.data()) == -1)
    {

        throw std::runtime_error("Failed to read registers: " + std::string(modbus_strerror(errno)));
        return false;
    }

    return true;
}

/**
 * @brief init_and_read_registers Метод для создания контекста и чтения регистров.
 * @param device Устройство (например, COM порт)
 * @param baud Скорость (например, 115200)
 * @param parity Четность (например, 'N')
 * @param data_bit Кол-во бит данных (например, 8)
 * @param stop_bit Стоповый бит (например, 1)
 * @param slave_id Идентификатор slave устройства
 * @param start_address Адрес регистра для чтения
 * @param num_registers Кол-во регистров для чтения
 * @return Вектор с прочитанными регистрами
 */
std::vector<uint16_t> modbusRTU::init_and_read_registers(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id, int start_address, int num_registers)
{
    // Вызываем функцию для создания контекста
    create_modbus_context(device, baud, parity, data_bit, stop_bit, slave_id);

    // Читаем регистры
    std::vector<uint16_t> values(num_registers);
    if (modbus_read_registers(ctx, start_address, num_registers, values.data()) == -1)
    {
        throw std::runtime_error("Failed to read registers: " + std::string(modbus_strerror(errno)));
    }

    // Возвращаем прочитанные значения
    return values;
}

/**
 * @brief init_and_check_connection Метод для создания контекста и проверки подклчения к плате
 * @param device Устройство (например, COM порт)
 * @param baud Скорость (например, 115200)
 * @param parity Четность (например, 'N')
 * @param data_bit Кол-во бит данных (например, 8)
 * @param stop_bit Стоповый бит (например, 1)
 * @param slave_id Идентификатор slave устройства
 * @param start_address Адрес регистра для чтения
 * @param num_registers Кол-во регистров для чтения
 * @return результат подключения к плате 1 - успешно, 0 - неуспешно
 */
bool modbusRTU::init_and_check_connection(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id, int start_address, int num_registers)
{

    // Если контекст еще не был создан, создаем его
        if (ctx == nullptr)
    {
        create_modbus_context(device, baud, parity, data_bit, stop_bit, slave_id);
    }

    // Читаем регистры
    std::vector<uint16_t> values(num_registers);
    if (modbus_read_registers(ctx, start_address, num_registers, values.data()) == -1)
    {
        throw std::runtime_error("Failed to read registers: " + std::string(modbus_strerror(errno)));
        return false;
    }

    // Возвращаем прочитанные значения
    return true;
}

/**
 * @brief init_and_write_registers Метод для создания контекста и записи регистров.
 * @param device Устройство (например, COM порт)
 * @param baud Скорость (например, 115200)
 * @param parity Четность (например, 'N')
 * @param data_bit Кол-во бит данных (например, 8)
 * @param stop_bit Стоповый бит (например, 1)
 * @param slave_id Идентификатор slave устройства
 * @param start_address Адрес регистра для записи
 * @param values Вектор со значениями для записи
 */
void modbusRTU::init_and_write_registers(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id, int start_address, const std::vector<uint16_t> &values)
{
    // Вызываем функцию для создания контекста
    create_modbus_context(device, baud, parity, data_bit, stop_bit, slave_id);

    // Пишем значения в несколько регистров
    if (modbus_write_registers(ctx, start_address, values.size(), values.data()) == -1)
    {
        throw std::runtime_error("Failed to write registers: " + std::string(modbus_strerror(errno)));
    }
}


