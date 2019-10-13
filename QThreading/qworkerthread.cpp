#include "qworkerthread.h"

QWorkerThread::QWorkerThread()
{

}

QWorkerThread::QWorkerThread(std::function<void ()> func)
{
    workerObject->setRunnable(func);
}

QWorkerThread::~QWorkerThread()
{
    //  Check if worker thread is running
    if(workerThread->isRunning()) {

        // Exit thread with -1
        workerThread->exit(-1);
    }

    if(!workerThread->isFinished()) {
        workerThread->wait();
    }

    // cleanup
    delete workerThread;
    delete workerObject;
}

void QWorkerThread::start(QThread::Priority priority)
{

    // Connect workerThread start signal to ThreadWorker object's run slot
    connect(workerThread, &QThread::started, workerObject, &ThreadWorker::run);

    // Connect threadWorker progress report to this progress report
    connect(workerObject, &ThreadWorker::progress, this, &QWorkerThread::progress);

    // Cleanup
    connect(workerObject, &ThreadWorker::finished, workerObject, &ThreadWorker::cleanup);

    // Delete
    connect(workerObject, &ThreadWorker::finished, workerObject, &ThreadWorker::deleteLater);
    connect(workerThread, &QThread::finished, workerThread, &QThread::deleteLater);

    // move workerObject to thread
    workerObject->moveToThread(workerThread);

    // emit signal that we are starting
    emit started();

    // Start WorkerThread which invokes object to start process method
    workerThread->start(priority);
}

void QWorkerThread::stop()
{
    // Exit thread safely with success
    workerThread->exit(0);
}

void QWorkerThread::wait()
{
    workerThread->wait();
}

void QWorkerThread::wait(unsigned long time)
{
    workerThread->wait(time);
}

void QWorkerThread::kill()
{
    // stop successfully
    stop();

    // Wait 500ms for kill
    wait(500);

    // check if still running
    if(workerThread->isRunning()){
        // forcefully kill
        workerThread->terminate();
    }
}

void QWorkerThread::setWorkerObject(ThreadWorker *value)
{
    workerObject = value;
}

QThread *QWorkerThread::getWorkerThread() const
{
    return workerThread;
}
