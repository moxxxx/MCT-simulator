#include "treatmentprogram.h"

TreatmentProgram::TreatmentProgram(QObject *parent, int programNum): QObject(parent)
{
    this->title = programs[programNum];
    this->frequency = pFrequency[programNum];
    this->duration = pDuration[programNum] * 60;
}


TreatmentProgram::TreatmentProgram(QObject *parent, QString title, int frequency): QObject(parent)
{
    this->title = title;
    this->frequency = frequency;
}

TreatmentProgram::~TreatmentProgram()
{
    delete timer;
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
    timer->~QTimer();
    QString min = QString::number(runtime / 60).rightJustified(2, '0');;
    QString sec = QString::number(runtime - (60 * (runtime / 60))).rightJustified(2, '0');
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
    timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &TreatmentProgram::update);
    timer->start(1000);
}

void TreatmentProgram::update(){
    runtime++;
    if ((duration != 0) && (runtime >= duration)){
        emit exitProgramSignal();
    }
    emit sendDrainSignal(powerLevel/10);
    if (duration == 0){
       emit updateSignal(runtime);
    }else{
       emit updateSignal(duration - runtime);
    }
    qDebug() << title << "runs for" << runtime << "s"<< endl;
}


