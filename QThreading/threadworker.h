#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>
#include <functional>

class ThreadWorker : public QObject
{
    Q_OBJECT

private:
    std::function<void ()> runnable;

public:
    explicit ThreadWorker(QObject *parent = nullptr);
    ThreadWorker(std::function<void ()> func);
    ~ThreadWorker();

    void setRunnable(const std::function<void ()> &value);

signals:
    /**
     * Emitted when the QWorkerThread object has started work
     * @brief started
     */
    void started();

    /**
     * @brief progress reports on progress in method, user defined.
     * @param value reported using int
     */
    void progress(int value);

    /**
     * Emitted when the QWorkerThread object has finished its work, same signal is used from &QThread::finished
     * @brief started
     */
    void finished();

    /**
     * Emitted when the QWorkerThread has encountered an error, user defined.
     * @brief started
     */
    void error();

public slots:
    void run();
    void cleanup();
};

#endif // THREADWORKER_H
