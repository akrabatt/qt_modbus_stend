#ifndef TEST_BOARD_H
#define TEST_BOARD_H

#include "device_base_class.h"

/**
 * @brief The test_board class
 */
class test_board : public device_base_class
{


public:
    // пустой конструктор
    test_board();

    /**
     * @brief test_board конструктор с пар-ми
     * @param id адрес платы
     */
    test_board(int id);

};

#endif // TEST_BOARD_H
