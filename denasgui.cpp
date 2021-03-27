#include "denasgui.h"
#include "ui_denasgui.h"
#include<QObject>
#include<QDebug>


DenasGUI::DenasGUI(QWidget *parent) :
    QMainWindow(parent),
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

