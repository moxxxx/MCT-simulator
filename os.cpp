#include "os.h"
#include "denasgui.h"
#include<QDebug>
#include<QObject>

#include<QThread>

OS::OS(QWidget *parent): QWidget(parent) {
    // when we just open the simulator, the Denas is shutdonw mode and wait to be turn on
    powerRemain = Battery::CAPACITY;
    powerOn = false;
    treatmentOn = false;
    //records << "record1" << "record 2"; //FOR TEST PURPOSE REMOVE LATER
    currentProgram = nullptr;


}
void OS::overideBattery(double remain){
    powerRemain = remain;
    emit updateBatterySignal(powerRemain);
    qDebug() << "Battery is now at" << powerRemain << "%." << endl;
}

double OS::drainBattery(double amount) { // will trigged by treatment program
    powerRemain -= amount;
    fixBattery();
    emit updateBatterySignal(powerRemain);
    if (powerRemain <= WARNING_LEVEL and powerRemain >=1 ){ // only send warning Signal when 1 =< powerRemain <= warning level
        emit warningSignal();
        qDebug() << "warning signal has been sent" << endl;
    }
    if (powerRemain < 1){
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
    }else if (powerRemain <= 0){
        powerRemain = 0;
    }
}

void OS::turnOn(){ //start a new menu program and connect
    powerOn = true;
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &OS::consume);
    timer->start(TIMER_INTERVAL);
    emit turnONSucceedSignal();
}

void OS::shutDown(){
    delete timer;
    timer = nullptr;
    //stop the current program if possible!
    if (currentProgram){
        exitTreatmentProgram();
    }
    qDebug() << records << endl;
    emit shutdownSignal();
    qDebug() << "emit shutdownSignal" << endl;
    powerOn = false;
}

void OS::drainBatterySlot(double power){ // this one is for treatment Program
    drainBattery(power * POWER_CONSTANT);
}

void OS:: powerButtonSlot(){
    if (powerOn){ //turn off
        shutDown();
    }else if (powerRemain > WARNING_LEVEL){ //it is OFF and has enough power turn on!
        turnOn();
    }else{
        qDebug() << "not enough battery, please charge" << endl;
        // feature #13
    }
}

void OS::initProgramSlot(int programNum, int programType){
    //qDebug() << "programNum" << programNum << "programType" << programType << endl;
    //get a initProgram request, init porgram
    if (!powerOn){
        qDebug() << "power off" << endl;
        return;
    }
    if (currentProgram){
        qDebug() << "one program is still runing!" << endl;
        return;
    }
    if (powerRemain < WARNING_LEVEL){
        qDebug() << "no enough battery" << endl;
        return;
    }
    if (programType > 1 or programType <0){
        qDebug() << "unregesiter programType " << endl;
    }
    if (programType == 1){
        // init programmed treatment!
        if (programNum > 3 or programNum < 0){
             qDebug() << "invalid program NUM" << endl;
             return;
        }
        currentProgram = new Programmed(programNum);
    }else if (programType == 0){
        // init frequency treatment!
        currentProgram = new Frequency(programNum);
    }
    emit initProgramSucceedSignal();
    connectTreatmentProgram();
    // test
    /*
    powerLevelSlot(60);
    skinSlot();

    */
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
       drainBattery(COST_CONSTANT * POWER_CONSTANT);
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

void OS::connectTreatmentProgram(){ //build connection OS and treatmentPorgram
    if (currentProgram){
        QObject::connect(currentProgram, &TreatmentProgram::updateTimerSignal, this, &OS::updateTimerSlot);
        QObject::connect(currentProgram, &TreatmentProgram::exitProgramSignal, this, &OS::exitProgramSlot);
        QObject::connect(currentProgram, &TreatmentProgram::sendDrainSignal, this, &OS::drainBatterySlot);
    }

}

void OS::skinSlot(){// GUI tell OS that skin is attached
    if (!powerOn){
        return;
    }
    if (!currentProgram){
        return;
    }
    if (treatmentOn){ // if treatment is already on then ignore
        return;
    }
    currentProgram->start(); //start program
    treatmentOn = true; // OS update
    qDebug() << "detected Skin ON, program Start!" << endl;
    //tell GUI that it start!
    emit treatmentStartSignal(currentProgram->getTitle() , currentProgram->getPowerLevel(), currentProgram->getFrequency(), true);
    qDebug() << "emit TreatmentStartSignal" << endl;

}

void OS::exitTreatmentProgram(){
    if (!powerOn){// power OFF, nothing to exit
        return;
    }
    if (!currentProgram){// currentProgram is null, nothing to exit
        return;
    }


    //get record
    if (treatmentOn){ 
        QString record = currentProgram->quit();
        records.append(record);
    }
    delete currentProgram;
    currentProgram = nullptr;
    treatmentOn = false;

    if (currentProgram){
        qDebug() <<"error! currentProgram is not free!!!" << endl;
    }
    // tell GUI that a program has exit
    emit exitProgramSignal();
    qDebug() << "send exitProgramSignal to GUI, a tretamentProgram has been terminated. " << endl;
    qDebug() << records << endl;

}

void OS::exitProgramSlot(){
    //treatmentProgram timeout, send exitProgramSignal to ask OS to quit
    if (!treatmentOn){
        qDebug() << "treatmentOn variable incosistant!" << endl;
        return;
    }
    exitTreatmentProgram();
}
void OS::quitProgramSlot(){// GUI interrupt to stop treatmentProgram
    exitTreatmentProgram();
}

void OS::updateTimerSlot(int timer){ // get timer from TreatmentProgram, tansfer the timer to GUI
    qDebug() << "OS send ProgramTimerSignal to GUI" << endl;
    emit programTimerSignal(timer);
}
