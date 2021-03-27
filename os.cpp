#include "os.h"
#include<QDebug>

OS::OS(QWidget *parent): QWidget(parent) {
    powerRemain = Battery::CAPACITY;
    turnOn();
}
void OS::overideBattery(double remain){
    powerRemain = remain;
    emit updateBatterySignal(powerRemain);
    qDebug() << "Battery is now at" << powerRemain << "%." << endl;
}

double OS::drainBattery(double amount) {
    powerRemain -= amount;
    fixBattery();
    emit updateBatterySignal(powerRemain);
    if (powerRemain <= 0){
        shutDown();
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
    }
}

void OS::turnOn(){ //start a new menu program and connect
    powerOn = true;
    //init menuProgram
    menu = new MenuProgram();
    QObject::connect(menu, &MenuProgram::sendDrainSignal, this, &OS::drainBatterySlot);
    menu->emitDrainPower();
}

void OS::shutDown(){
    powerOn = false;
}

void OS::drainBatterySlot(double power){
    drainBattery(power * powerConstant);
}


