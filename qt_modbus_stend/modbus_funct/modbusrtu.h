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

    // конструктор с параметрами
    modbusRTU(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id);

    // деструктор
    ~modbusRTU();

private:
    modbus_t* ctx;        // контекст libmodbus
    std::string device;   // устройство
    int baud;             // скорость
    char parity;          // четность
    int data_bit;         // кол-во бит данных
    int stop_bit;         // стоповый бит

};

#endif // MODBUSRTU_H
