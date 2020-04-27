#ifndef QRUNNABLETHREAD_H
#define QRUNNABLETHREAD_H

#include <QMutex>
#include <QObject>
#include <QRunnable>
#include <QWaitCondition>
#include <QThread>
#include <QDebug>

#include "qinterruptable.h"
#include "qthreadstate.h"
#include "functional"

class QRunnableThread : public QObject, public QRunnable, public QThreadState, public QInterruptable
{
    Q_OBJECT
public:
    explicit QRunnableThread(QObject *parent = nullptr);
    QRunnableThread(std::function<void ()> runnable, QObject *parent = nullptr);
    void setRunnable(std::function<void ()> runnable);
    void handleEvents();

private:
    QThread *_thread;
    QMutex mutex;
    QWaitCondition waitCondition;
    State threadState = NOTRUNNING;

    std::function<void ()> runnable;
    bool requestedStop = false;
    bool requestedPause = false;

signals:
    void onStateChange(State newState);
    void onStart();
    void onFinished();

    // QRunnable interface
public slots:
    void run();

    // QInterruptable interface
public:
    void pause();
    void resume();
    void cancel();
    bool isStarted();
    bool isPaused();
    bool isRunning();
    bool isFinished();
    QThread *getThread() const;
    bool getRequestedStop() const;
    bool getRequestedPause() const;
};

#endif // QRUNNABLETHREAD_H
