#include "qworkerthread.h"

QWorkerThread::QWorkerThread()
{

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

void QWorkerThread::start()
{
    // Start thread with default priority
    start(QThread::Priority::InheritPriority);
}

void QWorkerThread::start(QThread::Priority priority)
{

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
    workerThread->exit(0);

    // Wait 500ms for kill
    workerThread->wait(500);

    // check if still running
    if(workerThread->isRunning()){
        // forcefully kill
        workerThread->terminate();
    }
}
