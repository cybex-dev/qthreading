#ifndef QINTERRUPTABLE_H
#define QINTERRUPTABLE_H

class QInterruptable {
public:
    virtual void pause();
    virtual void resume();
    virtual void interrupt();
    virtual ~QInterruptable(){

    }
};

#endif // QINTERRUPTABLE_H
