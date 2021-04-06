#include "programmed.h"

Programmed::Programmed(int num) : TreatmentProgram(nullptr, num)
{
     qDebug() << "a " << this->getTitle() << "just be created with " << this->getFrequency()  << endl;
}
