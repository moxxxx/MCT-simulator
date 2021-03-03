#include "programmed.h"

Programmed::Programmed(int num) : TreatmentProgram(programs[num], frequency[num], duration[num])
{
     qDebug() << "a " << this->getTitle() << "just be created with " << this->getFrequency()  << endl;
}


