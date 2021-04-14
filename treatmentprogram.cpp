#include "treatmentprogram.h"

TreatmentProgram::TreatmentProgram(QObject *parent, int programNum): QObject(parent)
{
    this->title = programs[programNum];
    this->frequency = pFrequency[programNum];
    //this->duration = pDuration[programNum] * 60;
    this->duration = pDuration[programNum];
    this->timer = nullptr;
}


TreatmentProgram::TreatmentProgram(QObject *parent, QString title, int frequency): QObject(parent)
{
    this->title = title;
    this->frequency = frequency;
    this->timer = nullptr;
}

TreatmentProgram::~TreatmentProgram()
{
    if (timer){
        delete timer;
        timer = nullptr;
    }

}

void TreatmentProgram::setPowerLevel(int powerLevel){
    this->powerLevel = powerLevel;
}

QString TreatmentProgram::getTitle(){
    return title;
}

int TreatmentProgram::getDuration(){
    return duration;
}

int TreatmentProgram::getFrequency(){
    return frequency;
}

int TreatmentProgram::getPowerLevel(){
    return powerLevel;
}

void TreatmentProgram::setDuration(int duration){
    this->duration = duration;
}

QString TreatmentProgram::quit(){
    //timer->~QTimer();
    timer->stop();
    delete timer;
    timer = nullptr;
    //return empty QString if not start
    if (runtime == 0){
        return "";
    }
    // Calculate min and sec
    QString min = QString::number(runtime / 60).rightJustified(2, '0');;
    QString sec = QString::number(runtime - (60 * (runtime / 60))).rightJustified(2, '0');
    //Build recording string
    QString s = "";
    if (duration == 0){
       s+= "Frequency ";
    }else{
       s+= "Program " ;
    }
    s += title + " Power " + QString::number(powerLevel) + " Time " + min + ":" + sec;
    qDebug() << s << endl;
    runtime = 0;
    return s;
}

void TreatmentProgram::start() {
    //Start timer tick evrey second
    timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &TreatmentProgram::update);
    timer->start(1000);
    qDebug() << title << "started!" << endl;
}

void TreatmentProgram::update(){
    runtime++;
    //drain battery power
    emit sendDrainSignal(powerLevel/10);
    //Update timer display
    if (duration == 0){
       emit updateTimerSignal(runtime);
    }else{
       emit updateTimerSignal(duration - runtime);
    }
    if (timer){
        qDebug() << title << "runs for" << runtime << "s"<< endl;
        // Check if program reached preset duration
        if ((duration != 0) && (runtime >= duration)){
            emit exitProgramSignal();
        }
    }
}

