#include "menuprogram.h"

MenuProgram::MenuProgram()
{

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
void MenuProgram::shutdown(){

}
void MenuProgram::emitDrainPower(){
    emit sendDrainSignal(cost);
    qDebug() << "try send" << endl;
}
