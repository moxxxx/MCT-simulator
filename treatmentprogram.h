#ifndef TREATMENTPROGRAM_H
#define TREATMENTPROGRAM_H
#include <QTimer>
#include<QDebug>
#include <QDateTime>

class TreatmentProgram: public QObject
{
    Q_OBJECT
public:
    TreatmentProgram(QObject *parent, int programNum);
    TreatmentProgram(QObject *parent, QString title, int frequency);
    ~TreatmentProgram();
    void setPowerLevel(int powerLevel);
    QString getTitle();
    int getFrequency();
    int getPowerLevel();
    int getDuration();
    void setDuration(int duration);
    QString quit();
    void start();
    void stop();
    void update();
    int runtime = 0;

signals:
    void sendDrainSignal(double cost);
    void updateTimerSignal(int timer);
    void exitProgramSignal();

private:
    const QString programs[4]  = {"COLD", "ALLERGY", "KIDNEY", "JOINTS"};
    const int     pDuration[4]  = {10, 10, 20, 20};
    const int     pFrequency[4] = {60, 7710, 77, 140};
    QString title;
    int frequency;
    int powerLevel = 50;
    int duration;
    QString startTime = "";
    QTimer* timer;

};

#endif // TREATMENTPROGRAM_H
