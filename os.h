#ifndef OS_H
#define OS_H

#include<QObject>
#include"program.h"

class OS: public QObject
{
public:
    OS();
public slots:

signals:

private:
    Program* currentProgram;
    Program* menu;
    int powerRemain; // from 0-100

};

#endif // OS_H
