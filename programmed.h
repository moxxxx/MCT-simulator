#ifndef PROGRAMMED_H
#define PROGRAMMED_H
#include"treatmentprogram.h"

class Programmed: public TreatmentProgram
{
    Q_OBJECT
public:
    Programmed(int num);

private:
    void updateTimer();
};

#endif // PROGRAMMED_H
