#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QObject>
#include<QDebug>


DenasGUI::DenasGUI(QWidget *parent) :
    DenasGUI(parent),
    ui(new Ui::DenasGUI)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0, Battery::CAPACITY);
    ui->progressBar->setValue(Battery::CAPACITY);
}

DenasGUI::~DenasGUI()
{
    delete ui;
}

void DenasGUI::updateBatterySlot(double remain){
    ui->progressBar->setValue(int(remain));
}

