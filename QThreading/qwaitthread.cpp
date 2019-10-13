#include "qwaitthread.h"

QWaitThread::QWaitThread(QObject *parent) : QThread(parent)
{
    waitCondition = new QWaitCondition;
}

void QWaitThread::pause()
{
    waitCondition->wait(&mutex);
    emit paused();
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
