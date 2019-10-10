#ifndef QWORKERTHREAD_H
#define QWORKERTHREAD_H

#include <QObject>
#include <functional>

class QWorkerThread: public QObject
{
    Q_OBJECT

public:
    QWorkerThread();
    template <class ReturnType>
    explicit QWorkerThread(std::function<ReturnType()> func);
    ~QWorkerThread();
    void start();
    void stop();
    void wait();
    void kill();

signals:
    /**
     * Emitted when the QWorkerThread object has started work
     * @brief started
     */
    void started();

    template<class Type>
    /**
     * @brief progress reports on progress in method, user defined.
     * @param value reported using custom type `template< class Type>`
     */
    void progress(Type value);

    /**
     * Emitted when the QWorkerThread object has finished its work, same signal is used from &QThread::finished
     * @brief started
     */
    void finished();

    /**
     * Emitted when the QWorkerThread has encountered an error, user defined.
     * @brief started
     */
    void error();

private:
    /**
     * @brief workerObject - Contains the object and 'method' that will be moved to `workerThread`
     */
    QObject *workerObject = nullptr;

    /**
     * @brief workerThread - Worker Thread is seperate thread that runs the method
     */
    QThread *workerThread = nullptr;

};

#endif // QWORKERTHREAD_H
