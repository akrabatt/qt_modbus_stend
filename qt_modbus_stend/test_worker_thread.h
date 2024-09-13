#ifndef TEST_WORKER_THREAD_H
#define TEST_WORKER_THREAD_H

#include <QThread>
#include <QMutex>

class test_worker_thread : public QObject
{
    Q_OBJECT
private:
    bool is_running;

public:
    /**
     * @brief test_worker_thread параметрезированный конструктор заранее определяющий элемент класса в false
     */
    test_worker_thread() : is_running(false){}

    /**
     * @brief stop метод остановки выполнения программы
     */
    void stop();

public slots:
    /**
     * @brief run метод запуска испытаня параллельно
     */
    void run();

signals:
    // сигнал завершения
    void finished();

    // сигнал сообщения об ошибке
    void error_occurred(const QString &error_message);
};

#endif // TEST_WORKER_THREAD_H
