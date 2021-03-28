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
    connect(ui->leftButton, &QPushButton::pressed, this, &DenasGUI::leftPressed);
    connect(ui->rightButton, &QPushButton::pressed, this, &DenasGUI::rightPressed);
    connect(ui->okButton, &QPushButton::pressed, this, &DenasGUI::okPressed);
    connect(ui->menuButton, &QPushButton::pressed, this, &DenasGUI::menuPressed);
    connect(ui->backButton, &QPushButton::pressed, this, &DenasGUI::backPressed);
    connect(ui->powerButton, &QPushButton::pressed, this, &DenasGUI::powerPressed);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &DenasGUI::itemClicked);
    menuPressed();

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

void DenasGUI::okPressed(){
    ui->listWidget->itemClicked(ui->listWidget->currentItem());
}

void DenasGUI::menuPressed(){
    QStringList menu  = {"Program", "Frequency", "Recording"};
    updateList(menu);
}

void DenasGUI::backPressed(){
    //send signal to OS that it may end program
    //or back to menu
    menuPressed();
}

void DenasGUI::powerPressed(){
    //send signal to OS
    //control menu display
}

void DenasGUI::leftPressed(){
    //send left to OS
}

void DenasGUI::rightPressed(){
    //send right to OS
}

void DenasGUI::itemClicked(QListWidgetItem *item){
    if (item->text() == "Program"){
        QStringList programs  = {"COLD", "ALLERGY", "KIDNEY", "JOINTS"};
        updateList(programs);
    }else if (item->text() == "Frequency"){
        QStringList frequency  = {"10 Hz", "20 Hz", "60 Hz", "77 Hz"};
        updateList(frequency);
    }else if (item->text() == "Recording"){
        QStringList recording  = {"View", "Clear"};
        updateList(recording);
    }
}


