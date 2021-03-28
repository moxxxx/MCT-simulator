#include "denasgui.h"
#include "ui_denasgui.h"
#include<QObject>
#include<QDebug>


DenasGUI::DenasGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DenasGUI)
{
    ui->setupUi(this);
    ui->batteryBar->setRange(0, Battery::CAPACITY);
    ui->batteryBar->setValue(Battery::CAPACITY);
    connect(ui->upButton, &QPushButton::pressed, this, &DenasGUI::upPressed);
    connect(ui->downButton, &QPushButton::pressed, this, &DenasGUI::downPressed);
    QStringList menu  = {"Program", "Frequency", "Recording"};
    updateList(menu);
}

DenasGUI::~DenasGUI()
{
    delete ui;
}

void DenasGUI::updateBatterySlot(double remain){
    ui->batteryBar->setValue(int(remain));
}

void DenasGUI::updateList(QStringList list){
    ui->listWidget->clear();
    ui->listWidget->addItems(list);
    ui->listWidget->setCurrentRow(0);
}

void DenasGUI::upPressed(){
    if (ui->listWidget->currentRow() > 0){
            ui->listWidget->setCurrentRow((ui->listWidget->currentRow()-1));
    }
}

void DenasGUI::downPressed(){
    int num = ui->listWidget->count();
    int index = ui->listWidget->currentRow();
    if (index < (num-1)){
            ui->listWidget->setCurrentRow((ui->listWidget->currentRow()+1));
    }
}



