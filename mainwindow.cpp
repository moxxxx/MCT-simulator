#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    battery = new Battery;
    theOS = new OS();
    battery->move(640,480);
    battery->show();
    connections();
    ui->progressBar->setRange(0, Battery::CAPACITY);
    ui->progressBar->setValue(Battery::CAPACITY);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete battery;
}

void MainWindow::connections(){

    QObject::connect(battery, &Battery::sendRemain, theOS, &OS::overideBattery);
    QObject::connect(theOS, &OS::updateBatterySignal, this, &MainWindow::updateBatterySlot);
    //QObject::connect(theOS, &OS::consumePowerSignal, battery, &Battery::drain);
}

void MainWindow::updateBatterySlot(double remain){
    ui->progressBar->setValue(int(remain));
}

