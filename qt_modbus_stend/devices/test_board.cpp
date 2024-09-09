#include "test_board.h"

// пустой конструктор
test_board::test_board(){}

/**
 * @brief test_board::test_board конструктор с пар-ми который вызывает конструктор базового касса
 * @param id адрес
 */
test_board::test_board(int id) : device_base_class(id){};

