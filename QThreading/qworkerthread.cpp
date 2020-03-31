#include "qworkerthread.h"

QWorkerThread::QWorkerThread()
{
    state = State::NotRunning;
    workerThread = new QWaitThread;
    workerObject = new ThreadWorker;
    workerThread->setObjectName("WorkerThread");
}

QWorkerThread::QWorkerThread(std::function<void ()> func)
{
    state = State::NotRunning;
    workerThread = new QWaitThread;
    workerObject = new ThreadWorker(func);
    workerThread->setObjectName("QWorkerThread");
}

QWorkerThread::~QWorkerThread()
{
    //  Check if worker thread is running
    if(workerThread->isRunning()) {

        // Exit thread with -1
        workerThread->quit();
    }

    if(!workerThread->isFinished()) {
        workerThread->wait(5000);

        if(workerThread->isRunning()) {
            workerThread->terminate();
//            workerThread->wait();
        }
    }

    // cleanup
    delete workerObject;
    workerThread->deleteLater();
}

void QWorkerThread::setRunnable(std::function<void ()> runnable)
{
    workerObject->setRunnable(runnable);
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
    connect(workerThread, &QWaitThread::finished, this, [this] {
        workerObject->deleteLater();
    });

    // move workerObject to thread
    workerObject->moveToThread(workerThread);

    // Start WorkerThread which invokes object to start process method
    workerThread->start(priority);

    // emit signal that we are starting
    emit started();
}

void QWorkerThread::stop()
{
    state = State::Exiting;
    // Exit thread safely with success
    workerThread->terminate();
    workerThread->wait();

    emit finished();
}

void QWorkerThread::wait(unsigned long time)
{
    state = State::Waiting;
    workerThread->wait(time);
}

void QWorkerThread::kill()
{
    // try stopping
    stop();

    // check if still running
    if(workerThread->isRunning()){
        // forcefully kill
        workerThread->terminate();
        workerThread->wait();
    }

    emit finished();
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

QString QWorkerThread::parseState(QWorkerThread::State state) {
    switch (state) {
        case Running:
            return "Running";
        case Paused:
            return "Paused";
        case NotRunning:
            return "NotRunning";
        case Finished:
            return "Finished";
        case Waiting:
            return "Waiting";
        case Exiting:
            return "Exiting";
    }

    return QString("Unknown State [%1]").arg(QString::number(state)) ;
}

void QWorkerThread::pause()
{
    workerObject->pause();
    state = State::Paused;
}

void QWorkerThread::resume()
{
    workerObject->resume();
    state = State::Running;
}
