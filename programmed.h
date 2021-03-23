#ifndef PROGRAMMED_H
#define PROGRAMMED_H
#include"treatmentprogram.h"

class Programmed: public TreatmentProgram
{
    Q_OBJECT
public:
    Programmed(int num);
    QString programs[4]  = {"COLD", "ALLERGY", "KIDNEY", "JOINTS"};
    int     duration[4]  = {10, 10, 20, 20};
    int     frequency[4] = {60, 7710, 77, 140};
};

#endif // PROGRAMMED_H
