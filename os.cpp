#include "os.h"
#include<QDebug>

OS::OS(){
}
void OS::getBatteryRemain(double remain){
    this->powerRemain = remain;
    qDebug() << "Battery is now at " << this->powerRemain << "%." << endl;
}

void OS::emitGetPower(){
    emit getPowerSignal();
}

void OS::emitConsumePower(double power){
    emit consumePowerSingal(power);
}
