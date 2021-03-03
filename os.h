#ifndef OS_H
#define OS_H

#include<QWidget>
#include"program.h"
#include"battery.h"
#include"menuprogram.h"
#include<QObject>

class OS: public QWidget
{
    Q_OBJECT
public:
    OS();
    double drainBattery(double amount);

public slots:
    void overideBattery(double remain);
    void drainBatterySlot(double power);

signals:


    void updateBatterySignal(double remain);

private:
    Program* currentProgram;
    MenuProgram* menu;
    double powerRemain; // from 0-100
    double powerConstant = 5;
    bool powerOn;
    double chargeBattery(double amount);
    void fixBattery();
    void turnOn();

};

#endif // OS_H
