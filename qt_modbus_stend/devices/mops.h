#ifndef MOPS_H
#define MOPS_H

#include <cstdint>

class mops
{
private:
    int id;
    bool operable;
    union tag_mops_stand_statment
    {
        struct
        {
            struct
            {
                uint16_t mops_online;                 // is there connection with module
                uint16_t mops_online_err;             // connection error
                unsigned short mops_offline;                // mops not connected special
                unsigned short mops_operable;               // is the module working properly or not
                unsigned short mops_not_operable;           // the module is not working properly
            }mops_statment;
            unsigned short mops_current_ch_status[8];                   // buffer for the value of the states
            struct
            {
                unsigned short mops_ch_err_break[8];                   // break(1)
                unsigned short mops_ch_err_normal[8];                  // normal(2)
                unsigned short mops_ch_err_attantion[8];               // attantion(4)
                unsigned short mops_ch_err_fire[8];                    // fire(5)
                unsigned short mops_ch_err_sc[8];                      // short current(6)
            }mops_ch_statement;
            struct
            {
                unsigned short mops_18v_error;
                unsigned short mops_24v_error;
                unsigned short mops_28v_error;
            }mops_power_supply_error;
        };
        unsigned short main_buff[56];
    }mops_stand_statment;

public:
    mops();
};

#endif // MOPS_H
