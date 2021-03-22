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

void TreatmentProgram::set_power_level(int power_level){
    this->power_level = power_level;
}

QString TreatmentProgram::get_title(){
    return title;
}

int TreatmentProgram::get_time(){
    return time;
}

int TreatmentProgram::get_frequency(){
    return frequency;
}

int TreatmentProgram::get_power_level(){
    return power_level;
}
