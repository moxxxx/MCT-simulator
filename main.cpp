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
    return a.exec();
}
