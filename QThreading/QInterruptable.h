#ifndef QINTERRUPTABLE_H
#define QINTERRUPTABLE_H

class QInterruptable {
public:
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void interrupt() = 0;
    virtual ~QInterruptable() = default;
};

#endif // QINTERRUPTABLE_H
