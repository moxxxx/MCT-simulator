#ifndef TREATMENTPROGRAM_H
#define TREATMENTPROGRAM_H
#include"program.h"

struct TreatmentProgram: public Program
{
public:
    TreatmentProgram(QString title, int frequency);
    TreatmentProgram(QString title, int frequency, int time);
    void set_power_level(int power_level);
    QString get_title();
    int get_frequency();
    int get_power_level();
    int get_time();

private:
    QString title;
    int frequency;
    int power_level;
    int time;

};

#endif // TREATMENTPROGRAM_H
