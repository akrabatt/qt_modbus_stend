#ifndef DEVICE_BASE_CLASS_H
#define DEVICE_BASE_CLASS_H

#include <iostream>

/**
 * @brief The device_base_class class
 * @note данный класс является базовым классом для всех девайсов, с помощью него задается id устройста
 *       а так же статус исправности(если требуется)
 */
class device_base_class
{
private:
    int id;                     // id девайса
    bool operable_status;       // статус исправности 1 - исправен, 0 - неисправен

public:

    //КОНСТРУКТОРЫ

    // пустой конструктор
    device_base_class();

    /**
     * @brief device_base_class конструктор с параметром настройки id девайса
     * @param id адресс девайса
     */
    device_base_class(int id);

    // деструктор
    ~device_base_class();

    // СЕТТЕРЫ И ГЕТТЕРЫ

    /**
     * @brief device_metod_set_oper_status метод установки состояния девайса
     * @param status исправен или не исправен
     */
    void device_metod_set_oper_status(bool status);

    /**
     * @brief device_metod_set_id_status устанавливаем адресс девайса
     * @param id адресс
     */
    void device_metod_set_id_status(int id);

    /**
     * @brief device_get_id геттер возвращает id девайса
     * @return id девайса
     */
    int device_get_id();

    /**
     * @brief device_get_operable_status возвращает статус исправности (1 - исправно) (0 - неисправно)
     * @return значение bool
     */
    bool device_get_operable_status();
};

#endif // DEVICE_BASE_CLASS_H
