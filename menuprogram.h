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
private:
    const double cost = 0.5; // cost of power per second
    QTimer *timer;
    int levelOfManu;// 0,1,2
    int indexInManu;// 0,1,2,3
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void backPressed();
    void shutdown();

signals:
    void sendDrainSignal(double);
};

#endif // MENUPROGRAM_H
