#ifndef QWORKERTHREAD_H
#define QWORKERTHREAD_H

#include <QObject>
#include <functional>
#include <QThread>

#include "threadworker.h"


template <class ReturnType>

class QWorkerThread: public QObject
{
    Q_OBJECT

public:
    QWorkerThread();
    explicit QWorkerThread(std::function<ReturnType()> func);
    ~QWorkerThread();
    void start();
    void start(QThread::Priority priority = QThread::Priority::InheritPriority);
    void stop();
    void wait();
    void wait(unsigned long time = ULONG_MAX);
    void kill();

signals:
    /**
     * Emitted when the QWorkerThread object has started work
     * @brief started
     */
    void started();

    template<class Type>
    /**
     * @brief progress reports on progress in method, user defined.
     * @param value reported using custom type `template< class Type>`
     */
    void progress(Type value);

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
    ThreadWorker<Retur *workerObject = nullptr;

    /**
     * @brief workerThread - Worker Thread is seperate thread that runs the method
     */
    QThread *workerThread = nullptr;

};

#endif // QWORKERTHREAD_H
