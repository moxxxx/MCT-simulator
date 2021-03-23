#include "os.h"
#include<QDebug>

OS::OS(){
    powerRemain = Battery::CAPACITY;
}
void OS::overideBattery(double remain){
    powerRemain = remain;
    emit updateBatterySignal(powerRemain);
    qDebug() << "Battery is now at" << powerRemain << "%." << endl;
}

void OS::emitGetPower(){
    emit getPowerSignal();
}

void OS::emitConsumePower(double power){
    emit consumePowerSingal(power);
}

double OS::drainBattery(double amount) {
    powerRemain -= amount;
    fixBattery();
    emit updateBatterySignal(powerRemain);
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


