#ifndef TREATMENTPROGRAM_H
#define TREATMENTPROGRAM_H
#include"program.h"
#include <QTimer>

struct TreatmentProgram: public Program
{
public:
    TreatmentProgram(QString title, int frequency);
    TreatmentProgram(QString title, int frequency, int duration);
    void setPowerLevel(int powerLevel);
    QString getTitle();
    int getFrequency();
    int getPowerLevel();
    int getDuration();
    void setDuration(int duration);
    QStringList quit();
    void start();
    void stop();

private:
    QString title;
    int frequency;
    int powerLevel;
    int duration;
    bool isStarted;
    QTimer* timer;

};

#endif // TREATMENTPROGRAM_H
