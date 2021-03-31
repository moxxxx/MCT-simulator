#include "os.h"
#include "denasgui.h"
#include<QDebug>

OS::OS(QWidget *parent): QWidget(parent) {
    powerRemain = Battery::CAPACITY;
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
//void OS:: powerpressed(){}
void OS::turnOn(){ //start a new menu program and connect
    powerOn = true;
    qDebug() << "device is turning on" << endl;
    emit hideBlindSignal();
    //init menuProgram
    menu = new MenuProgram();
    //may need to be delete when reproduce menuprogram class
    QObject::connect(menu, &MenuProgram::sendDrainSignal, this, &OS::drainBatterySlot);
    menu->emitDrainPower();
}

void OS::shutDown(){
    powerOn = false;
    qDebug() << "device is shutting down" << endl;
    emit showBlindSignal();

}

void OS::drainBatterySlot(double power){
    drainBattery(power * powerConstant);
}


