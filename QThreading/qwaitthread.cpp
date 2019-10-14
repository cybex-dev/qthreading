#include "qwaitthread.h"

QWaitThread::QWaitThread(QObject *parent) : QThread(parent)
{
    waitCondition = new QWaitCondition;
}

void QWaitThread::pause()
{
    emit paused();
    waitCondition->wait(&mutex);
}

void QWaitThread::resume()
{
    waitCondition->wakeAll();
    emit resumed();
}

void QWaitThread::pausing()
{
    pause();
}

void QWaitThread::resuming()
{
    resume();
}
