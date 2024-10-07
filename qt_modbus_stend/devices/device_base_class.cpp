#include "device_base_class.h"

// конструктор по умолчанию
device_base_class::device_base_class(){}

/**
 * @brief device_base_class::device_base_class конструктор устанавливаем адресс девайса
 * @param id адресс
 */
device_base_class::device_base_class(int id) : id(){}

// деструктор
device_base_class::~device_base_class(){};

/**
 * @brief device_base_class::device_metod_set_oper_status устанавливаем статус исправности
 * @param status булевое значение 1 - исправен, 0 - неисправен
 */
void device_base_class::device_metod_set_oper_status(bool status){this -> operable_status = status;}

/**
 * @brief device_base_class::device_metod_set_id_status устанавливает id девайса
 * @param id
 */
void device_base_class::device_metod_set_id_status(int id){this -> id = id;}

/**
 * @brief device_base_class::device_get_operable_status возвращает статус исправности
 * @return булевое значение 1 - исправно 2 - неисправно
 */
bool device_base_class::device_get_operable_status(){return this -> operable_status;}

/**
 * @brief device_base_class::device_get_id возвращает адресс девайса
 * @return id девайса
 */
int device_base_class::device_get_id(){return this -> id;}
