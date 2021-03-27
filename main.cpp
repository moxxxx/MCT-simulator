#include "mainwindow.h"
#include <QApplication>
#include "battery.h"
#include "os.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DenasGUI w;
    OS theOS;
    Battery battery;
    w.show();
    battery.move(640,480);
    battery.show();
    QObject::connect(&battery, &Battery::sendRemain, &theOS, &OS::overideBattery);
    QObject::connect(&theOS, &OS::updateBatterySignal, &w, &MainWindow::updateBatterySlot);
    return a.exec();
}
