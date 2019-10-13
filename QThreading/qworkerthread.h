#ifndef QWORKERTHREAD_H
#define QWORKERTHREAD_H

#include <QObject>
#include <functional>
#include <QThread>

#include "threadworker.h"

class QWorkerThread: public QObject
{
    Q_OBJECT

public:
    QWorkerThread();
    explicit QWorkerThread(std::function<void ()> func);
    ~QWorkerThread();
    void start(QThread::Priority priority = QThread::Priority::InheritPriority);
    void stop();
    void wait();
    void wait(unsigned long time = ULONG_MAX);
    void kill();
    void setWorkerObject(ThreadWorker *value);

    QThread *getWorkerThread() const;

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

private:
    /**
     * @brief workerObject - Contains the object and 'method' that will be moved to `workerThread`
     */
    ThreadWorker *workerObject = nullptr;

    /**
     * @brief workerThread - Worker Thread is seperate thread that runs the method
     */
    QThread *workerThread = nullptr;

};

#endif // QWORKERTHREAD_H
