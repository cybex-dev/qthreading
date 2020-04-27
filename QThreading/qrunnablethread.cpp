#include "qrunnablethread.h"

QRunnableThread::QRunnableThread(QObject *parent) : QObject(parent)
{

}


QRunnableThread::QRunnableThread(std::function<void ()> _runnable, QObject *parent): QObject(parent), runnable(_runnable)
{

}

void QRunnableThread::handleEvents()
{
    mutex.lock();
   if(requestedPause) {
        waitCondition.wait(&mutex);
   }
   mutex.unlock();
}

bool QRunnableThread::getRequestedPause() const
{
    return requestedPause;
}

bool QRunnableThread::getRequestedStop() const
{
    return requestedStop;
}

QThread *QRunnableThread::getThread() const
{
    return _thread;
}


void QRunnableThread::run()
{
    _thread = thread();
    emit onStart();
    qDebug() << "Worker [" << _thread->currentThreadId() << "] Running";
    threadState = State::RUNNING;
    emit onStateChange(threadState);
    runnable();
    threadState = State::FINISHED;
    emit onStateChange(threadState);
    emit onFinished();
}


void QRunnableThread::pause()
{
    mutex.lock();
    threadState = PAUSED;
    emit onStateChange(threadState);
    requestedPause = true;
    mutex.unlock();
}


void QRunnableThread::resume()
{
    mutex.lock();
    threadState = State::RUNNING;
    emit onStateChange(threadState);
    requestedPause = false;
    mutex.unlock();
    waitCondition.wakeAll();
}


void QRunnableThread::cancel()
{
    requestedStop = true;
}


void QRunnableThread::kill()
{
    threadState = State::FINISHED;
    emit onStateChange(threadState);
    qDebug() << "Worker [" << _thread->currentThreadId() << "] Terminate";
}


bool QRunnableThread::isStarted()
{
    return threadState != State::NOTRUNNING;
}


bool QRunnableThread::isPaused()
{
    return threadState == State::PAUSED;
}


bool QRunnableThread::isRunning()
{
    return threadState == State::RUNNING;
}


bool QRunnableThread::isFinished()
{
    return threadState == State::FINISHED;
}

