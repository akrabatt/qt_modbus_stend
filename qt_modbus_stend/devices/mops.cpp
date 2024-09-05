#include "mops.h"

// пустой конструктор по умолчанию
mops::mops(){}

/**
 * @brief mops::mops констуктор котоырй использует наследование базового класса по присваиванию адреса модуля
 * @param id адрес модуля
 */
mops::mops(int id) : device_base_class(id) {}
