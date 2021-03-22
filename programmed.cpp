#include "programmed.h"

Programmed::Programmed(int num) : TreatmentProgram(programs[num], frequency[num])
{
    TreatmentProgram::set_time(duration[num]);
}

