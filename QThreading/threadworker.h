#ifndef THREADWORKER_H
#define THREADWORKER_H

#include <QObject>
#include <functional>

class ThreadWorker : public QObject
{
    Q_OBJECT

private:
    bool interruptRequested = false;
    std::function<void ()> func;

public:
    explicit ThreadWorker(QObject *parent = nullptr);
    ThreadWorker(std::function<void ()> func);
    ~ThreadWorker();
    void run();

    bool getInterruptRequested() const;
    void setInterruptRequested(bool value);

signals:
    void finished();
    void error();

public slots:

};

#endif // THREADWORKER_H
