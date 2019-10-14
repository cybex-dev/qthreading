#ifndef QWAITTHREAD_H
#define QWAITTHREAD_H

#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include <QMutex>

class QWaitThread : public QThread
{
    Q_OBJECT
public:
    explicit QWaitThread(QObject *parent = nullptr);
    ~QWaitThread();
    virtual void pause();
    virtual void resume();

signals:
    void paused();
    void resumed();

public slots:
    void pausing();
    void resuming();

private:
    QWaitCondition *waitCondition;
    QMutex mutex;
};

#endif // QWAITTHREAD_H
