#include "menuprogram.h"

MenuProgram::MenuProgram()
{
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &MenuProgram::emitDrainPower);
    timer->start(50);
}

void MenuProgram::upPressed(){

}
void MenuProgram::downPressed(){

}
void MenuProgram::leftPressed(){

}
void MenuProgram::rightPressed(){

}
void MenuProgram::backPressed(){

}
void MenuProgram::shutdownProgram(){
    timer->~QTimer();
}
void MenuProgram::emitDrainPower(){
    emit sendDrainSignal(cost);
}
