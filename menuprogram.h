#ifndef MENUPROGRAM_H
#define MENUPROGRAM_H
#import"program.h"

class MenuProgram: public Program
{
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
