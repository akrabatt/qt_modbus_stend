#include "mups.h"

// пустой конструктор по умолчанию
mups::mups(){}

/**
 * @brief mups::mups параметризированный конструктор который вызывает базовый конструктор дял установки id
 * @param id сам адрес
 */
mups::mups(int id) : device_base_class(id){}

// деструктор
mups::~mups(){};
