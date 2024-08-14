#include "libmodbus/modbus.h"
#include <iostream>

void mb_0x03(void)
{
    // Создание нового контекста Modbus RTU
        modbus_t *ctx = modbus_new_rtu("COM3", 9600, 'N', 8, 1);
        if (ctx == NULL) {
            std::cerr << "Unable to create the libmodbus context\n";
           // return -1;
        }

        // Установка slave ID устройства
        if (modbus_set_slave(ctx, 1) == -1) {
            std::cerr << "Failed to set slave ID: " << modbus_strerror(errno) << '\n';
            modbus_free(ctx);
           // return -1;
        }

        // Установка таймаутов (опционально)
        struct timeval response_timeout;
        response_timeout.tv_sec = 1;
        response_timeout.tv_usec = 0;
        if (modbus_set_response_timeout(ctx, response_timeout.tv_sec, response_timeout.tv_usec) == -1) {
            std::cerr << "Failed to set response timeout: " << modbus_strerror(errno) << '\n';
            modbus_free(ctx);
            //return -1;
        }

        // Подключение к порту
        if (modbus_connect(ctx) == -1) {
            std::cerr << "Connection failed: " << modbus_strerror(errno) << '\n';
            modbus_free(ctx);
           // return -1;
        }

        // Определение адреса стартового регистра и количества регистров
        unsigned short start_register = 0x0202; // Начальный адрес регистра
        const unsigned short num_registers = 5; // Количество регистров для чтения

        // Буфер для значений, которые будем читать
        uint16_t values[num_registers];

        // Вызов функции 3 (0x03) для чтения множества регистров
        int rc = modbus_read_registers(ctx, start_register, num_registers, values);
        if (rc == -1)
        {
            std::cerr << "Failed to read registers: " << modbus_strerror(errno) << '\n';
            modbus_close(ctx);
            modbus_free(ctx);
           // return -1;
        }

        // Вывод полученных данных
        std::cout << "Successfully read " << num_registers << " registers\n";
        for (int i = 0; i < num_registers; i++) {
            std::cout << "Register " << (start_register + i) << ": " << values[i] << '\n';
        }

        // Закрытие соединения и освобождение памяти
        modbus_close(ctx);
        modbus_free(ctx);

        //return 0;
}
