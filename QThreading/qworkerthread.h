#ifndef QWORKERTHREAD_H
#define QWORKERTHREAD_H

#include <QObject>
#include <functional>
#include <QThread>

#include "qwaitthread.h"
#include "threadworker.h"

class QWorkerThread: public QObject
{
    Q_OBJECT

public:

    enum State {
        Running,
        Paused,
        NotRunning,
        Finished,
        Waiting,
        Exiting
    };

    QWorkerThread();
    explicit QWorkerThread(std::function<void ()> func);
    ~QWorkerThread();
    virtual void setRunnable(std::function <void()> runnable);
    virtual void start(QThread::Priority priority = QThread::Priority::InheritPriority);
    virtual void stop();
    virtual void wait();
    virtual void wait(unsigned long time = ULONG_MAX);
    virtual void kill();
    virtual void setWorkerObject(ThreadWorker *value);

    virtual void pause();
    virtual void resume();
    virtual QWaitThread *getWorkerThread() const;

    virtual State getState() const;

signals:
    /**
     * Emitted when the QWorkerThread object has started work
     * @brief started
     */
    virtual void started();

    /**
     * @brief progress reports on progress in method, user defined.
     * @param value reported using int
     */
    virtual void progress(int value);

    /**
     * Emitted when the QWorkerThread object has finished its work, same signal is used from &QThread::finished
     * @brief started
     */
    virtual void finished();

    /**
     * Emitted when the QWorkerThread has encountered an error, user defined.
     * @brief started
     */
    virtual void error();

private:
    /**
     * @brief workerObject - Contains the object and 'method' that will be moved to `workerThread`
     */
    ThreadWorker *workerObject = nullptr;

    /**
     * @brief workerThread - Worker Thread is seperate thread that runs the method
     */
    QWaitThread *workerThread = nullptr;

    State state;

};

#endif // QWORKERTHREAD_H
