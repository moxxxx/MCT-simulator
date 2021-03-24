#include "treatmentprogram.h"

TreatmentProgram::TreatmentProgram(QString title, int frequency)
{
    this->title = title;
    this->frequency = frequency;
}

TreatmentProgram::TreatmentProgram(QString title, int frequency, int time)
{
    this->title = title;
    this->frequency = frequency;
    this->time = time;
}

void TreatmentProgram::setPowerLevel(int powerLevel){
    this->powerLevel = powerLevel;
}

QString TreatmentProgram::getTitle(){
    return title;
}

int TreatmentProgram::getTime(){
    return time;
}

int TreatmentProgram::getFrequency(){
    return frequency;
}

int TreatmentProgram::getPowerLevel(){
    return powerLevel;
}

void TreatmentProgram::setTime(int time){
    this->time = time;
}

QStringList TreatmentProgram::quit(){
    return {title, QString::number(powerLevel), QString::number(time)};
}
