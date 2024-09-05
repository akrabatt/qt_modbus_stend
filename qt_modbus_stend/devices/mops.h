#ifndef MOPS_H
#define MOPS_H


class mops
{
private:
    int id;         // mupses id
    bool operable;  // operable status

    // структура данных состояния мопса
    union tag_mops_stand_statment
    {
        struct
        {
            struct
            {
                int mops_online;                 // is there connection with module
                int mops_online_err;             // connection error
                int mops_offline;                // mops not connected special
                int mops_operable;               // is the module working properly or not
                int mops_not_operable;           // the module is not working properly
            }mops_statment;
            int mops_current_ch_status[8];                  // buffer for the value of the states
            struct
            {
                int mops_ch_err_break[8];                   // break(1)
                int mops_ch_err_normal[8];                  // normal(2)
                int mops_ch_err_attantion[8];               // attantion(4)
                int mops_ch_err_fire[8];                    // fire(5)
                int mops_ch_err_sc[8];                      // short current(6)
            }mops_ch_statement;
            struct
            {
                int mops_18v_error;
                int mops_24v_error;
                int mops_28v_error;
            }mops_power_supply_error;
        };
        int main_buff[56];
    }mops_stand_statment;

public:
    // пустой конструктор
    mops();

    /**
     * @brief mops параметризированный конструктор
     * @param id адрес мупса
     */
    mops(const int id);

    // деструктор
    ~mops();

    /**
     * @brief mops_set_operable_status устанавливает статус исправен или нет
     * @param status сам статус
     */
    void mops_set_operable_status(bool status);

    /**
     * @brief mops_set_id устанавливаем адресс модуля
     * @param id адресс модуля
     */
    void mops_set_id(int id);
};

#endif // MOPS_H
