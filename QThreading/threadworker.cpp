#include "threadworker.h"

void ThreadWorker::setRunnable(const std::function<void ()> &value)
{
    runnable = value;
}

QMutex& ThreadWorker::getMutex()
{
    return mutex;
}

QWaitCondition *ThreadWorker::getWaitCondition() const
{
    return waitCondition;
}

void ThreadWorker::setWaitCondition(QWaitCondition *value)
{
    waitCondition = value;
}

bool ThreadWorker::getShouldPause() const
{
    return shouldPause;
}

ThreadWorker::ThreadWorker(QObject *parent) : QObject(parent)
{
    waitCondition = new QWaitCondition;
}

ThreadWorker::ThreadWorker(std::function<void ()> func): runnable(func) {
    waitCondition = new QWaitCondition;
}

ThreadWorker::~ThreadWorker()
{    
    if(waitCondition != nullptr){
        delete waitCondition;
    }
}

void ThreadWorker::run()
{
    emit started();
    runnable();
    emit finished();
}

void ThreadWorker::cleanup()
{

}
