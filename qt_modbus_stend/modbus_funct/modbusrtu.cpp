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
 * @brief modbusRTU::mbm_16_write_registers данная функция служит для записи регистров
 * @param start_address стартовый регистр
 * @param values источник вектор со значениями
 */
void modbusRTU::mbm_16_write_registers(int start_address, const std::vector<uint16_t> &values)
{
    // Пишем значения в несколько регистров
            if (modbus_write_registers(ctx, start_address, values.size(), values.data()) == -1)
            {
                throw std::runtime_error("Failed to write registers: " + std::string(modbus_strerror(errno)));
            }
}

/**
 * @brief mbm_03_read_registers функция чтения регистров
 * @param start_address начальный регистр для чтения
 * @param num_registers кол-во регистров для чтения
 * @return возвращаем вектор с регистрами
 */
std::vector<uint16_t> modbusRTU::mbm_03_read_registers(int start_address, int num_registers)
{
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
    // создаем вектор с заданным кол-вом
    std::vector<uint16_t> values(3);

    // создаем булевое значение флаг
    bool connection_flag = true;

       // Читаем значения из регистров
       if (modbus_read_registers(ctx, 0, 3, values.data()) == -1)
       {
           connection_flag = false;
           throw std::runtime_error("Failed to read registers: " + std::string(modbus_strerror(errno)));
           throw std::runtime_error("Failed to connect to Modbus device on port " + device);
       }

       return connection_flag;
}

