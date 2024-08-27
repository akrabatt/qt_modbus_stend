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
    modbusRTU(){};

    // конструктор с параметрами
    modbusRTU(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id)
    {
        // создаем контекст модбаса
        modbus_t* ctx = modbus_new_rtu(device.c_str(), baud, parity, data_bit, stop_bit);
        if(ctx == nullptr)
        {
            throw std::runtime_error("Unable to create the libmodbus context");
        }
    }
};

#endif // MODBUSRTU_H
