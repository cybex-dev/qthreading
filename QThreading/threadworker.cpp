#include "threadworker.h"

bool ThreadWorker::getInterruptRequested() const
{
    return interruptRequested;
}

void ThreadWorker::setInterruptRequested(bool value)
{
    interruptRequested = value;
}

ThreadWorker::ThreadWorker(QObject *parent) : QObject(parent)
{

}

void ThreadWorker::run()
{
    emit finished();
}
