#ifndef TREATMENTPROGRAM_H
#define TREATMENTPROGRAM_H
#include"program.h"

struct TreatmentProgram: public Program
{
public:
    TreatmentProgram();

private:
    int frequency;
    int powerLevel;
    int time;

};

#endif // TREATMENTPROGRAM_H
