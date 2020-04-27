#ifndef QINTERRUPTABLE_H
#define QINTERRUPTABLE_H

class QInterruptable
{
public:
    QInterruptable() {}
    virtual void pause()  = 0;
    virtual void resume()  = 0;
    virtual void cancel()  = 0;
    virtual bool isStarted()  = 0;
    virtual bool isPaused()  = 0;
    virtual bool isRunning()  = 0;
    virtual bool isFinished()  = 0;
};

#endif // QINTERRUPTABLE_H
