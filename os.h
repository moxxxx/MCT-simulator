#ifndef OS_H
#define OS_H

#include<QWidget>
#include"program.h"
#include"battery.h"

class OS: public QWidget
{
    Q_OBJECT
public:
    OS();
    void emitGetPower(); // function to
    void emitConsumePower(double power);

public slots:
    void overideBattery(double remain);

signals:
    double getPowerSignal();
    void consumePowerSingal(double power);
    void updateBatterySignal(double remain);

private:
    Program* currentProgram;
    Program* menu;
    double powerRemain; // from 0-100
    double drainBattery(double amount);
    double chargeBattery(double amount);
    void fixBattery();

};

#endif // OS_H
