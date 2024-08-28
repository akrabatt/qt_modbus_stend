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


