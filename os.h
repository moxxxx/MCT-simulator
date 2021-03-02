#ifndef OS_H
#define OS_H

#include<QWidget>
#include"program.h"

class OS: public QWidget
{
    Q_OBJECT
public:
    OS();
    void emitGetPower(); // function to
    void emitConsumePower(double power);
public slots:
    void getBatteryRemain(double remain);
signals:
    void getPowerSignal();
    void consumePowerSingal(double power);

private:
    Program* currentProgram;
    Program* menu;
    double powerRemain; // from 0-100


};

#endif // OS_H
