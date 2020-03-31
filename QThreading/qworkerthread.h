#ifndef QWORKERTHREAD_H
#define QWORKERTHREAD_H

#include <QObject>
#include <functional>
#include <QThread>
#include <QEventLoop>

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
    static QString parseState(QWorkerThread::State state);
    virtual void setRunnable(std::function <void()> runnable);
    virtual void start(QThread::Priority priority = QThread::Priority::InheritPriority);
    virtual void stop();
    virtual void wait(unsigned long time = ULONG_MAX);
    virtual void kill();
    virtual void setWorkerObject(ThreadWorker *value);

    virtual void pause();
    virtual void resume();
    virtual QWaitThread *getWorkerThread() const;

    State getState() const;


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
    QWaitThread *workerThread = nullptr;

    State state = State::NotRunning;

};

#endif // QWORKERTHREAD_H
