#ifndef DEFINE_H
#define DEFINE_H

// МОПС
/**
 * @brief макрос по выбору массива начальных адрессов МОПСов
 */
#define MACRO_SET_MOPS_18_24_28_ADDR(cond_var)      \
    ((cond_var) == 0 ? mops_start_reg_arr_18v :     \
     (cond_var) == 1 ? mops_start_reg_arr_24v :     \
                       mops_start_reg_arr_28v)

/**
 * @brief макрос по выбору массива объектов МОПСов 18 24 28
 */
#define MACRO_SET_MOPS_OBJ_ARR(cond_var)      \
    ((cond_var) == 0 ? mops_map_18v :         \
     (cond_var) == 1 ? mops_map_24v :         \
                       mops_map_28v)

/**
 * @brief макрос по выбору массива начальных объектов МОПСов глобальных
 */
#define MACRO_SET_MOPS_OBJ_ARR_GLOB(cond_var)      \
    ((cond_var) == 0 ? global_map_mops_18v :       \
     (cond_var) == 1 ? global_map_mops_24v :       \
                       global_map_mops_28v)


// МУПС
/**
 * @brief макрос по выбору массива начальных адрессов МУПСов
 */
#define MACRO_SET_MUPS_18_24_28_ADDR(cond_var)      \
    ((cond_var) == 0 ? mups_start_reg_arr_18v :     \
     (cond_var) == 1 ? mups_start_reg_arr_24v :     \
                       mups_start_reg_arr_28v)

/**
 * @brief макрос по выбору массива объектов МОПСов 18 24 28
 */
#define MACRO_SET_MUPS_OBJ_ARR(cond_var)      \
    ((cond_var) == 0 ? mups_map_18v :         \
     (cond_var) == 1 ? mups_map_24v :         \
                       mups_map_28v)

/**
 * @brief макрос по выбору массива объектов МОПСов 18 24 28
 */
#define MACRO_SET_MUPS_OBJ_ARR_GLOB(cond_var)        \
    ((cond_var) == 0 ? globla_map_mups_18v :         \
     (cond_var) == 1 ? globla_map_mups_24v :         \
                       globla_map_mups_28v)



/**
 * @brief выбор строки ошибки онлайн
 */
#define MACRO_SET_ONLINE_ERROR_STR(statment)    \
    ((statment) == 1 ? "Online error!"     :   \
     (statment) == 2 ? "crc error!"        :   \
     (statment) == 3 ? "illegal function!" :   \
     (statment) == 4 ? "illegal addr!"     :   \
     (statment) == 5 ? "illegal val!"      :   \
                       "online error!")

#endif // DEFINE_H
