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
    void warningSignal();

private:
    TreatmentProgram* currentProgram;
    MenuProgram* menu;
    double powerRemain; // from 0-100
    double powerConstant = 0.1; //0.1 is signidicant changed, when use it we can set it as 0.01
    double warningLevel = 5;
    bool powerOn; //
    bool treatmentOn; // indicate whether there is a treatment going on!
    double chargeBattery(double amount);
    void fixBattery();
    void shutDown();
    void turnOn();




};

#endif // OS_H
