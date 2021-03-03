#ifndef OS_H
#define OS_H

#include<QWidget>
#include"treatmentprogram.h"
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
    void powerButtonSlot();
    void initProgramSlot(int programNum, int programType);

signals:
    void updateBatterySignal(double remain);
    void shutdownSignal();

private:
    TreatmentProgram* currentProgram;
    MenuProgram* menu;
    double powerRemain; // from 0-100
    double powerConstant = 0.1;
    bool powerOn; //
    bool treatmentOn; // indicate whether there is a treatment going on!
    double chargeBattery(double amount);
    void fixBattery();
    void turnOn();
    void shutDown();


};

#endif // OS_H
