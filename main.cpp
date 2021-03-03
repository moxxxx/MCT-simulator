#include "denasgui.h"
#include <QApplication>
#include "battery.h"
#include "os.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DenasGUI gui;
    OS theOS;
    Battery battery;
    gui.show();
    battery.move(640,480);
    battery.show();
    QObject::connect(&battery, &Battery::sendRemain, &theOS, &OS::overideBattery);
    QObject::connect(&theOS, &OS::updateBatterySignal, &gui, &DenasGUI::updateBatterySlot);
    QObject::connect(&gui, &DenasGUI::powerButtonSignal, &theOS, &OS::powerButtonSlot); //connect power button in GUI to os
    QObject::connect(&theOS, &OS::shutdownSignal, &gui, &DenasGUI::shutdownSlot); // connection OS shutdown signal to GUI (indicator the system has been shut down)
    QObject::connect(&theOS, &OS::warningSignal, &gui,&DenasGUI::warningSlot); //connect warning
    QObject::connect(&gui, &DenasGUI::programSignal, &theOS, &OS::initProgramSlot); //connect initprogramSignal from GUI to OS
    QObject::connect(&gui, &DenasGUI::requestRecordSignal, &theOS, &OS::requestRecordSlot);
    // QObject::connect(&theOS, &OS::sentRecordSignal, &gui, &DenasGUI::sentRecordSlot);
    QObject::connect(&gui, &DenasGUI::clearRecordSignal, &theOS, &OS::clearRecordSlot);
    //QObject::connect(&theOS, &OS::turnONSucceedSignal, &gui, &DenasGUI::turnONSucceedSlot);
    return a.exec();
}
