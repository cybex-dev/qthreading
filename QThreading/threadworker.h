#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>
#include <functional>
#include <QWaitCondition>
#include <QMutex>

#include "QInterruptable.h"

class ThreadWorker : public QObject, public QInterruptable
{
    Q_OBJECT

private:
    QMutex mutex;
    QWaitCondition *waitCondition;
    std::function<void ()> runnable;
    bool shouldPause = false;

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
    virtual void run();
    virtual void cleanup();


    // QInterruptable interface
public:
    void pause()
    {
        shouldPause = true;
    }
    void resume()
    {
        shouldPause = false;
    }
    QMutex& getMutex();
    QWaitCondition *getWaitCondition() const;
    void setWaitCondition(QWaitCondition *value);
    bool getShouldPause() const;

    // QInterruptable interface
public:
    void interrupt()
    {

    }
};

#endif // THREADWORKER_H
