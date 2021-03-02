#ifndef PROGRAM_H
#define PROGRAM_H

#include<QObject>
class OS;
// todo: how do we figure out the communication from program to OS?

struct Program: public QObject
{
    Q_OBJECT
public:
    Program();
    virtual void upPressed();
    virtual void downPressed();
    virtual void leftPressed();
    virtual void rightPressed();
    virtual void backPressed();
    virtual void shutdown();
private:
    OS* myOs;
};

#endif // PROGRAM_H
