#include "test_worker_thread.h"

//test_worker_thread::test_worker_thread()
//{

//}


/**
 * @brief test_worker_thread::run
 */
void test_worker_thread::run()
{
    // Логика выполнения параллельной задачи
    while (is_running)
    {
        // Пример: выполняем какую-то работу
        QThread::sleep(1); // Пример паузы между операциями

        // Здесь может быть основная логика работы потока
    }
    emit finished(); // Сигнал завершения работы
}

/**
 * @brief test_worker_thread::stop
 */
void test_worker_thread::stop()
{
    this->is_running = false;
}
