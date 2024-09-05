#include "mops.h"

// пустой конструктор по умолчанию
mops::mops(){}

/**
 * @brief mops::mops параметризированный конструктор мопса
 * @param id адресс модуля
 */
mops::mops(const int id) : id(id) {}


/**
 * @brief mops::mops_set_operable_status устанавливает статус исправности
 * @param status передаем сам статус
 */
void mops::mops_set_operable_status(bool status)
{
    this -> operable = status;  // ставим сам статус
}


/**
 * @brief mops::mops_set_id
 * @param id
 */
void mops::mops_set_id(int id)
{
    this -> id = id;
}
