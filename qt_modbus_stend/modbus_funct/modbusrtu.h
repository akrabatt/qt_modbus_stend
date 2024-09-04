#ifndef MODBUSRTU_H
#define MODBUSRTU_H

#include <string>
#include "libmodbus/modbus.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <thread>
#include <mutex>

class modbusRTU
{
private:
    modbus_t* ctx;        // контекст libmodbus
    std::string device;   // устройство
    int baud;             // скорость
    char parity;          // четность
    int data_bit;         // кол-во бит данных
    int stop_bit;         // стоповый бит
    std::mutex mtx;

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

    /**
     * @brief modbusRTU::mbm_16_write_registers данная функция служит для записи регистров
     * @param start_address стартовый регистр
     * @param values источник вектор со значениями
     */
    void mbm_16_write_registers(int start_address, const std::vector<uint16_t> &values);

    /**
     * @brief mbm_03_read_registers функция чтения регистров
     * @param start_address начальный регистр для чтения
     * @param num_registers кол-во регистров для чтения
     * @return возвращаем вектор с регистрами
     */
    std::vector<uint16_t> mbm_03_read_registers(int start_address, int num_registers);

    /**
     * @brief mbm_03_check_connection функция проверки связи с платой
     * @return возвращает булевое значение (true - соединение успешное) (false - ошибка соединения)
     */
    bool mbm_03_check_connection();
};

#endif // MODBUSRTU_H
