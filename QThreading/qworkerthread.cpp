#include "qworkerthread.h"

QWorkerThread::QWorkerThread()
{
    state = State::NotRunning;
    workerThread = new QWaitThread;
    workerObject = new ThreadWorker;
}

QWorkerThread::QWorkerThread(std::function<void ()> func)
{
    state = State::NotRunning;
    workerThread = new QWaitThread;
    workerObject = new ThreadWorker(func);
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

    state = State::Running;
    // Connect workerThread start signal to ThreadWorker object's run slot
    connect(workerThread, &QThread::started, workerObject, &ThreadWorker::started);
    connect(workerThread, &QThread::started, workerObject, &ThreadWorker::run);

    // Connect threadWorker progress report to this progress report
    connect(workerObject, &ThreadWorker::progress, this, &QWorkerThread::progress);

    // Cleanup
    connect(workerObject, &ThreadWorker::finished, this, [this](){
        state = State::Finished;
        emit finished();
    });
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
    state = State::Exiting;
    // Exit thread safely with success
    workerThread->exit(0);
}

void QWorkerThread::wait()
{
    state = State::Waiting;
    workerThread->wait();
}

void QWorkerThread::wait(unsigned long time)
{
    state = State::Waiting;
    workerThread->wait(time);
}

void QWorkerThread::kill()
{
    state = State::Exiting;

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

QWaitThread *QWorkerThread::getWorkerThread() const
{
    return workerThread;
}

QWorkerThread::State QWorkerThread::getState() const
{
    return state;
}

void QWorkerThread::pause()
{
    workerThread->pause();
    state = State::Paused;
}

void QWorkerThread::resume()
{
    workerThread->resume();
    state = State::Running;
}
