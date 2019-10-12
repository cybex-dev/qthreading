#include "threadworker.h"

void ThreadWorker::setRunnable(const std::function<void ()> &value)
{
    runnable = value;
}

ThreadWorker::ThreadWorker(QObject *parent) : QObject(parent)
{

}

ThreadWorker::ThreadWorker(std::function<void ()> func): runnable(func) {

}

ThreadWorker::~ThreadWorker()
{

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
