#ifndef MUPS_H
#define MUPS_H


#include "device_base_class.h"

/**
 * @brief The mups class
 * @note данный класс реализует состояние МУПСов и наследует класс device_base_class
 */
class mups : public device_base_class
{
public:

    // структура данных состояния мyпса
    union tag_mups_stand_statment
    {
        struct
        {
            struct
            {
                unsigned short mups_online;                 // is there connection with module
                unsigned short mups_online_err;             // connection error
                unsigned short mups_offline;                // mops not connected special
                unsigned short mups_operable;               // is the module working properly or not
                unsigned short mups_not_operable;           // the module is not working properly
            }mups_statment;
            unsigned short mups_current_ch_status[4];                   // buffer for the value of the states
            struct
            {
                unsigned short mups_ch_err_break_ch_off[4];                     // the line is broken, the channel is turned off(1)
                unsigned short mups_ch_err_norm_ch_off[4];                      // channel norm, the channel is off(2)
                unsigned short mups_ch_err_sc_ch_off[4];                        // short circuit of the channel, the channel is turned off(3)
                unsigned short mups_ch_err_norm_ch_on[4];                       // channel norm, the channel is on(4)
                unsigned short mups_ch_err_cur_up_ch_off_force[4];              // exceeding the channel current, the channel is forcibly turned off(5)
                unsigned short mups_ch_err_break_ch_on[4];                      // The channel is open, the channel is on(6)
            }mups_ch_statement;
            struct
            {
                unsigned short mups_18v_error;
                unsigned short mups_24v_error;
                unsigned short mups_28v_error;
            }mups_power_supply_error;
        };
        unsigned short main_buff[36];
    }mups_stand_statment;


public:
    // пустой конструктор
    mups();

    /**
     * @brief mups параметризированный конструктор устанавливает адресс
     * @param id адресс
     */
    mups(int id);

    // деструктор
    ~mups();
};

#endif // MUPS_H
