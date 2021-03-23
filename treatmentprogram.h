#ifndef TREATMENTPROGRAM_H
#define TREATMENTPROGRAM_H
#include"program.h"

struct TreatmentProgram: public Program
{
public:
    TreatmentProgram(QString title, int frequency);
    TreatmentProgram(QString title, int frequency, int time);
    void setPowerLevel(int powerLevel);
    QString getTitle();
    int getFrequency();
    int getPowerLevel();
    int getTime();

private:
    QString title;
    int frequency;
    int powerLevel;
    int time;

};

#endif // TREATMENTPROGRAM_H
