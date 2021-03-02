#ifndef MENUPROGRAM_H
#define MENUPROGRAM_H
#include "program.h"

class MenuProgram: public Program
{
    Q_OBJECT
public:
    MenuProgram();
private:
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void backPressed();
    void shutdown();
};

#endif // MENUPROGRAM_H
