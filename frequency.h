#ifndef FREQUENCY_H
#define FREQUENCY_H
#include"treatmentprogram.h"

class Frequency: public TreatmentProgram
{
    Q_OBJECT
public:
    Frequency(int frequency = 0);
private:
    void updateTimer();
};

#endif // FREQUENCY_H
