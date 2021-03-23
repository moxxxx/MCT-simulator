#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    capacity = 100;
    ui->setupUi(this);
    battery = new Battery();
    battery->show();
    theOS = new OS();

    connections();

    theOS->emitGetPower(); // demo, can be remove later!


}

MainWindow::~MainWindow()
{
    delete ui;
    delete battery;
}

void MainWindow::connections(){
    QObject::connect(theOS, &OS::getPowerSignal, battery, &Battery::getRemain);
    QObject::connect(battery, &Battery::sendRemain, theOS, &OS::getBatteryRemain);
    //QObject::connect(theOS, &OS::consumePowerSignal, battery, &Battery::drain);


}
