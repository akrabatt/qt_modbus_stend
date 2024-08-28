#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include <string>
#include "libmodbus/modbus.h"
#include <iostream>
#include <stdexcept>
#include <vector>

class modbusRTU
{
public:
    // пустой конструктор
    modbusRTU();

    /**
     * @brief modbusRTU::modbusRTU основной конструктор создает контекст соединения
     * @param device номер COM порта, причем надо указывать так: пример "COM1"
     * @param baud скорость в бодах, например 115200
     * @param parity четнойть, например 'N'
     * @param data_bit колличество данных в посылке, обычно 8
     * @param stop_bit стоп бит, например 1
     * @param slave_id id slave устройства, нашей платы
     */
    modbusRTU(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id);

    // деструктор
    ~modbusRTU();

    void mbm_16_write_registers(int start_address, const std::vector<uint16_t> &values)
    {

    }



private:
    modbus_t* ctx;        // контекст libmodbus
    std::string device;   // устройство
    int baud;             // скорость
    char parity;          // четность
    int data_bit;         // кол-во бит данных
    int stop_bit;         // стоповый бит

};

#endif // MODBUSRTU_H
