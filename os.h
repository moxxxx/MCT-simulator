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
    explicit OS(QWidget *parent = nullptr);
    double drainBattery(double amount);

public slots:
    void overideBattery(double remain);
    void drainBatterySlot(double power);
    void shutDown();
    void turnOn();
signals:
    void updateBatterySignal(double remain);
    void hideBlindSignal();
    void showBlindSignal();

private:
    Program* currentProgram;
    MenuProgram* menu;
    double powerRemain; // from 0-100
    double powerConstant = 0.1;
    bool powerOn;
    double chargeBattery(double amount);
    void fixBattery();



};

#endif // OS_H
