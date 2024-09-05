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
    std::mutex mtx_constr;  // мьютикс конструктора

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
     * @brief create_modbus_context Создает и настраивает контекст Modbus RTU
     * @param device Устройство (например, COM порт)
     * @param baud Скорость (например, 115200)
     * @param parity Четность (например, 'N')
     * @param data_bit Кол-во бит данных (например, 8)
     * @param stop_bit Стоповый бит (например, 1)
     * @param slave_id Идентификатор slave устройства
     */
    void create_modbus_context(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id);

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
    std::vector<uint16_t> init_and_read_registers(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id, int start_address, int num_registers);

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
    bool init_and_check_connection(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id, int start_address, int num_registers);

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
    void init_and_write_registers(const std::string &device, int baud, char parity, int data_bit, int stop_bit, int slave_id, int start_address, const std::vector<uint16_t> &values);
};

#endif // MODBUSRTU_H
