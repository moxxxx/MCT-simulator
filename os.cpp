#include "os.h"
#include "denasgui.h"
#include<QDebug>
#include<QObject>

OS::OS(QWidget *parent): QWidget(parent) {
    // when we just open the simulator, the Denas is shutdonw mode and wait to be turn on
    powerRemain = Battery::CAPACITY;
    powerOn = false;
    treatmentOn = false;
    records << "record1" << "record 2"; //FOR TEST PURPOSE REMOVE LATER
    currentProgram = nullptr;


}
void OS::overideBattery(double remain){
    powerRemain = remain;
    emit updateBatterySignal(powerRemain);
    qDebug() << "Battery is now at" << powerRemain << "%." << endl;
}

double OS::drainBattery(double amount) { // will trigged by treatment program and menuProgram
    powerRemain -= amount;
    fixBattery();
    emit updateBatterySignal(powerRemain);
    if (powerRemain <= warningLevel){ //
        emit warningSignal();
        qDebug() << "warning signal has been sent" << endl;
    }
    return powerRemain;
}
double OS::chargeBattery(double amount) {
    powerRemain += amount;
    fixBattery();
    emit updateBatterySignal(powerRemain);
    return powerRemain;
}
void OS::fixBattery() {
    if (powerRemain > Battery::CAPACITY){
        powerRemain = Battery::CAPACITY;
    }else if (powerRemain < 0){
        powerRemain = 0;
        shutDown();
    }
}

void OS::turnOn(){ //start a new menu program and connect
    powerOn = true;
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &OS::consume);
    timer->start(interval);

    //menu = new MenuProgram();
    //QObject::connect(menu, &MenuProgram::sendDrainSignal, this, &OS::drainBatterySlot);
}

void OS::shutDown(){
    //first shut down program, then save history 
    timer->~QTimer();

    powerOn = false;
    qDebug() << "send shutdonw Signal" << endl;
    emit shutdownSignal();
}

void OS::drainBatterySlot(double power){ // this one is for treatment Program
    drainBattery(power * powerConstant);
}

void OS:: powerButtonSlot(){
    if (powerOn){ //turn off
        shutDown();
    }else if (powerRemain > warningLevel){ //it is OFF and has enough power turn on!
        turnOn();
    }else{ //
        qDebug() << "not enough battery, please charge" << endl;
        // feature #13
    }
}


void OS::initProgramSlot(int programNum, int programType){
    qDebug() << "programNum" << programNum << "programType" << programType << endl;
    //get a initProgram request, init porgram
    if (!powerOn){
        qDebug() << "power off" << endl;
        return;
    }
    if (currentProgram){
        qDebug() << "one program is still runing!" << endl;
        return;
    }
    if (programType == 1){
        // init programmed treatment!
        if (programNum > 3 or programNum < 0){
             qDebug() << "invalid program NUM" << endl;
             return;
        }
        qDebug() << "programmed " << endl;
        currentProgram = new Programmed(programNum);
        connect(currentProgram, &TreatmentProgram::sendDrainSignal, this, &OS::drainBatterySlot);
        currentProgram->start(); //only for test, to be remove later
    }else if (programType == 0){
        // init frequency treatment!
        currentProgram = new Frequency(programNum);
    }else {
        qDebug() << "unregesiter programType " << endl;
    }
}


void OS::requestRecordSlot(){
    if (powerOn){
        currentProgram->quit();
        emit sentRecordSignal(records);
    }
}
void OS::clearRecordSlot(){
    if (powerOn){
        records.clear();
        qDebug() << "clear" << endl;
    }
}
void OS::consume(){ // this function will be called by timer in OS,
    if (powerOn){ //only consume power when user turn on machine!
       drainBattery(cost * powerConstant);
    }
}
