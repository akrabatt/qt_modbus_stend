#include "libmodbus/modbus.h"
#include <iostream>
#include <vector>

std::vector<unsigned short> mb_0x03()
{
    std::vector<unsigned short> values;  // Массив для хранения значений регистров

    // Создание нового контекста Modbus RTU
    modbus_t *ctx = modbus_new_rtu("COM6", 115200, 'N', 8, 1);
    if (ctx == NULL) {
        std::cerr << "Unable to create the libmodbus context\n";
        return values;  // Возвращаем пустой массив при ошибке
    }

    // Установка slave ID устройства
    if (modbus_set_slave(ctx, 1) == -1) {
        std::cerr << "Failed to set slave ID: " << modbus_strerror(errno) << '\n';
        modbus_free(ctx);
        return values;  // Возвращаем пустой массив при ошибке
    }

    // Установка таймаутов (опционально)
    struct timeval response_timeout;
    response_timeout.tv_sec = 1;
    response_timeout.tv_usec = 0;
    if (modbus_set_response_timeout(ctx, response_timeout.tv_sec, response_timeout.tv_usec) == -1) {
        std::cerr << "Failed to set response timeout: " << modbus_strerror(errno) << '\n';
        modbus_free(ctx);
        return values;  // Возвращаем пустой массив при ошибке
    }

    // Подключение к порту
    if (modbus_connect(ctx) == -1) {
        std::cerr << "Connection failed: " << modbus_strerror(errno) << '\n';
        modbus_free(ctx);
        return values;  // Возвращаем пустой массив при ошибке
    }

    // Определение адреса стартового регистра и количества регистров
    unsigned short start_register = 8000; // Начальный адрес регистра
    const unsigned short num_registers = 5; // Количество регистров для чтения

    // Резервирование места в векторе для значений регистров
    values.resize(num_registers);

    // Вызов функции 3 (0x03) для чтения множества регистров
    int rc = modbus_read_registers(ctx, start_register, num_registers, values.data());
    if (rc == -1)
    {
        std::cerr << "Failed to read registers: " << modbus_strerror(errno) << '\n';
        modbus_close(ctx);
        modbus_free(ctx);
        values.clear();  // Очищаем массив при ошибке
        return values;  // Возвращаем пустой массив при ошибке
    }

    // Закрытие соединения и освобождение памяти
    modbus_close(ctx);
    modbus_free(ctx);

    return values;  // Возвращаем массив значений регистров
}
