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
    if (powerRemain <= warningLevel and powerRemain >=1 ){ // only send warning Signal when 1 =< powerRemain <= warning level
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
    emit turnONSucceedSignal();
}

void OS::shutDown(){
    //first shut down program, then save history 
    timer->~QTimer();
    //stop the current program if possible!

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
        currentProgram = new Programmed(programNum);
        emit initProgramSucceedSignal();
    }else if (programType == 0){
        // init frequency treatment!
        currentProgram = new Frequency(programNum);
        emit initProgramSucceedSignal();
    }else {
        qDebug() << "unregesiter programType " << endl;
    }
}

void OS::requestRecordSlot(){
    if (powerOn){
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

void OS::powerLevelSlot(int powerLevel){ //override the powerLevel of currentProgram
    if (powerOn && currentProgram){ // if power on and there is a treatment inited
        currentProgram->setPowerLevel(powerLevel);
    }else if (powerOn){
        qDebug() << "attempt to change powerLevel with OS is OFF" << endl;
    }else{
        qDebug() << "attempt to change powerLevel with currentProgram is NULL!. " << endl;
    }
}
