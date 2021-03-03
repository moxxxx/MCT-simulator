#include "treatmentprogram.h"

TreatmentProgram::TreatmentProgram(QString title, int frequency)
{
    this->title = title;
    this->frequency = frequency;
}

TreatmentProgram::TreatmentProgram(QString title, int frequency, int duration)
{
    this->title = title;
    this->frequency = frequency;
    this->duration = duration;
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

QStringList TreatmentProgram::quit(){
    timer->~QTimer();
    return {title, QString::number(powerLevel), QString::number(duration)};
}

void TreatmentProgram::start() {
    timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &TreatmentProgram::quit);
    timer->start(50);
}


