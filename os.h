#ifndef OS_H
#define OS_H
#include<QWidget>
#include"treatmentprogram.h"
#include"battery.h"
#include<QObject>
#include<QTimer>
#include"programmed.h"
#include"frequency.h"
#include<QString>

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
    void requestRecordSlot();
    void clearRecordSlot();
    void powerLevelSlot(int powerLevel);
    void skinSlot();
    //void treatmentStartSignal(QString * programName, int powerLevel, int frequency, bool skinOn);
    void exitProgramSlot(); // this slot is for treatmentProgram!
    void quitProgramSlot(); // this slot is for GUI!

signals:
    void updateBatterySignal(double remain);
    void shutdownSignal();
    void warningSignal();
    void sentRecordSignal(QStringList records);
    void turnONSucceedSignal();
    void initProgramSucceedSignal();

private:
    QStringList records;
    TreatmentProgram* currentProgram;
    //MenuProgram* menu;
    const double powerConstant = 0.1; //0.1 is signidicant changed, when use it we can set it as 0.01
    const double cost = 0.5; //
    const double warningLevel = 5;
    const int interval = 50;
    QTimer *timer;
    double powerRemain; // from 0-100
    bool powerOn;
    bool treatmentOn; // indicate whether there is a treatment going on!
    double chargeBattery(double amount);
    void fixBattery();
    void shutDown();
    void turnOn();
    void consume();
    void connectTreatmentProgram();
    void exitTreatmentProgram();




};

#endif // OS_H
