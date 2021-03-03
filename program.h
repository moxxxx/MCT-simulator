#ifndef PROGRAM_H
#define PROGRAM_H

#include<QObject>
class OS;
struct Program: public QObject
{
    Q_OBJECT
public:
    Program();
    virtual void upPressed()= 0;
    virtual void downPressed()= 0;
    virtual void leftPressed()= 0;
    virtual void rightPressed()= 0;
    virtual void backPressed()= 0;
    virtual void shutdownProgram()= 0;
protected:
    OS* myOs;
};

#endif // PROGRAM_H
