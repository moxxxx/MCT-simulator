#include "frequency.h"

Frequency::Frequency(int frequency) : TreatmentProgram (nullptr, QString::number(frequency) + " Hz", frequency)
{
    qDebug() << "a " << this->getTitle() << "just be created with " << this->getFrequency()  << endl ;
}
