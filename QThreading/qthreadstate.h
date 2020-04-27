#ifndef QTHREADSTATE_H
#define QTHREADSTATE_H

class QThreadState
{
public:
    enum State{
        NOTRUNNING,
        RUNNING,
        PAUSED,
        FINISHED
    };

public:
    QThreadState() {}
    State getThreadState();
};

#endif // QTHREADSTATE_H
