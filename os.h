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
    //double drainBattery(double amount);

public slots:
    void overideBattery(double remain);
    void drainBatterySlot(double power);
    void powerButtonSlot();
    void initProgramSlot(int programNum, int programType);
    void requestRecordSlot();
    void clearRecordSlot();
    void powerLevelSlot(int powerLevel);
    void skinSlot();// this slot is for GUI!
    void exitProgramSlot(); // this slot is for treatmentProgram!
    void quitProgramSlot(); // this slot is for GUI!
    void updateTimerSlot(int timer); // this slot is for treatmentProgram!


signals:
    void updateBatterySignal(double remain);
    void shutdownSignal();
    void warningSignal();
    void sentRecordSignal(QStringList records);
    void turnONSucceedSignal();
    void initProgramSucceedSignal();
    void treatmentStartSignal(QString ProgramName, int powerLevel,int frequency, bool skinOn);
    void programTimerSignal(int timer);
    void exitProgramSignal();

private:
    QStringList records;
    TreatmentProgram* currentProgram;
    //MenuProgram* menu;
    const double POWER_CONSTANT = 0.1; //0.1 is signidicant changed, when use it we can set it as 0.01
    const double COST_CONSTANT = 5; //
    const double WARNING_LEVEL = 5;
    const int TIMER_INTERVAL = 1000;
    QTimer *timer;
    double powerRemain; // from 0-100
    bool powerOn;
    bool treatmentOn; // indicate whether there is a treatment going on!
    double chargeBattery(double amount);
    double drainBattery(double amount);
    void fixBattery();
    void shutDown();
    void turnOn();
    void consume();
    void connectTreatmentProgram();
    void exitTreatmentProgram();




};

#endif // OS_H
