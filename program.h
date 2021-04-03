#ifndef PROGRAM_H
#define PROGRAM_H
#include<QObject>
class OS;
struct Program: public QObject
{
    Q_OBJECT
public:
    Program();
protected:
    OS* myOs;
};

#endif // PROGRAM_H
