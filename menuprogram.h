#ifndef MENUPROGRAM_H
#define MENUPROGRAM_H
#include "program.h"
#include<QTimer>
#include<QDebug>


class MenuProgram: public Program
{
    Q_OBJECT
public:
    MenuProgram();
    void emitDrainPower();
    void shutdownProgram();
private:
    const double cost = 0.5; // cost of power per second
    QTimer *timer;
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void backPressed();


signals:
    void sendDrainSignal(double);
};

#endif // MENUPROGRAM_H
