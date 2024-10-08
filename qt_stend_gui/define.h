#ifndef DEFINE_H
#define DEFINE_H

/**
 * @brief макрос по выбору массива начальных адрессов МОПСов
 */
#define MACRO_SET_MOPS_18_24_28_ADDR(cond_var)      \
    ((cond_var) == 0 ? mops_start_reg_arr_18v :     \
     (cond_var) == 1 ? mops_start_reg_arr_24v :     \
                       mops_start_reg_arr_28v)


/**
 * @brief макрос по выбору массива начальных адрессов МУПСов
 */
#define MACRO_SET_MUPS_18_24_28_ADDR(cond_var)      \
    ((cond_var) == 0 ? mups_start_reg_arr_18v :     \
     (cond_var) == 1 ? mups_start_reg_arr_24v :     \
                       mups_start_reg_arr_28v)



#endif // DEFINE_H
