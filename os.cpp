#include "os.h"
#include "denasgui.h"
#include<QDebug>

OS::OS(QWidget *parent): QWidget(parent) {
    // when we just open the simulator, the Denas is shutdonw mode and wait to be turn on
    powerRemain = Battery::CAPACITY;
    powerOn = false;
    treatmentOn = false;
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
    //init menuProgram
    menu = new MenuProgram();
    QObject::connect(menu, &MenuProgram::sendDrainSignal, this, &OS::drainBatterySlot);
}

void OS::shutDown(){
    //first shut down program, then save history
    powerOn = false;
    qDebug() << "send shutdonw Signal" << endl;
    menu->shutdownProgram();
    emit shutdownSignal();
}

void OS::drainBatterySlot(double power){
    drainBattery(power * powerConstant);
}

void OS:: powerButtonSlot(){
    if (powerOn){ //turn off
        shutDown();
    }else if (powerRemain > warningLevel){ //it is OFF and has enough power turn on!
        turnOn();
    }else{ //
        qDebug() << "not enough battery, please charge" << endl;
    }
}

void OS::initProgramSlot(int programNum, int programType){
    if (powerOn){
        if (programType == 0){//
            // init programmed treatment! launch a

        }else if (programType == 1){ //
            // init frequency treatment!
        }
        qDebug() << "program Num is "<< programNum << endl;
    }

}
