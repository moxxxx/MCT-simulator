#include "denasgui.h"
#include "ui_denasgui.h"
#include<QObject>
#include<QDebug>
#include <QLCDNumber>
#include <QHBoxLayout>
#include "unistd.h"

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
    //init default gui setting
    ui->listWidget->hide();
    ui->batteryBar->hide();
    ui->powerLevel->hide();
    ui->tempPower->hide();
    //ui->warning->hide();
    ui->warning->setText("No Skin attached");


 //test purpose, should be delete once os sent status
    //init display
    QString qTempPower = QString::number(temporaryPowerLevel);
    ui->tempPower->setText(qTempPower);
//end of display test display

    QLCDNumber *min = new QLCDNumber(3,ui->timerscreen);
    QLCDNumber *second = new QLCDNumber(3,ui->timerscreen);
    QHBoxLayout *layout = new QHBoxLayout(ui->timerscreen);
       layout->addWidget(min);
       layout->addWidget(second);
       setLayout(layout);
    min->display(0);
    second->display(0);
    ui->timerscreen->hide();
    ui->colon->hide();
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
    if(s == menu){
        if (ui->listWidget->currentRow() > 0){
                ui->listWidget->setCurrentRow((ui->listWidget->currentRow()-1));
        }
    }
}

void DenasGUI::downPressed(){
    if(s == menu){
        int num = ui->listWidget->count();
        int index = ui->listWidget->currentRow();
        if (index < (num-1)){
                ui->listWidget->setCurrentRow((ui->listWidget->currentRow()+1));
        }
    }
}

void DenasGUI::okPressed(){
    if(s == menu){
        QString currentselected = ui->listWidget->currentItem()->text();
        ui->listWidget->itemClicked(ui->listWidget->currentItem());
        qDebug() << currentselected <<"is selected" << endl;
        if(currentselected == "COLD"){
            emit programSignal(0,1);//cold,programed
        }
        if(currentselected == "ALLERGY"){
            emit programSignal(1,1);//ALLERGY,programed
        }
        if(currentselected == "KIDNEY"){
            emit programSignal(2,1);//KIDNEY,programed
        }
        if(currentselected == "JOINTS"){
            emit programSignal(3,1);//JOINTS,programed
        }
        if(currentselected == "10 Hz"){
            emit programSignal(10,0);//10,frequency
        }
        if(currentselected == "20 Hz"){
            emit programSignal(20,0);//20,frequency
        }
        if(currentselected == "60 Hz"){
            emit programSignal(60,0);//60,frequency
        }
        if(currentselected == "77 Hz"){
            emit programSignal(77,0);//77,frequency
        }
        if(currentselected == "View"){
            emit requestRecordSignal();
        }
        if(currentselected == "Clear"){
            emit clearRecordSignal();
            emit requestRecordSignal();
        }
    }
    else if(s == init || s == treatmentApplied){
        //Send powerLevelSignal
        emit powerLevelSignal(temporaryPowerLevel);
        qDebug()<<"send powerlevel signal:"<<temporaryPowerLevel<<endl;
        ui->warning->setText("No Skin attached");

    }
}

void DenasGUI::menuPressed(){
    QStringList menuList  = {"Program", "Frequency", "Recording"};
    updateList(menuList);
    if(s == init || s == treatmentApplied){
        emit quitProgramSignal();
        s = menu;
        qDebug()<<"from treatment to menu"<<endl;
    }
}

void DenasGUI::backPressed(){
    //send signal to OS that it may end program
    //or back to menu
    if(s == menu){
        QString currentselected = ui->listWidget->currentItem()->text();
        if(currentselected == "Program" || currentselected == "Frequency" ||currentselected == "Recording"){
            //if in first menu level, do nothing
        }else{
            //in second menu level, go back to first menu level
            menuPressed();}
    }else if(s == showingRecord){
        menuPressed();
    }else if(s == init || s == treatmentApplied){
        emit quitProgramSignal();
        s = menu;
    }
}

void DenasGUI::powerPressed(){
    //send signal to OS
    //control menu display
    qDebug() <<"send OS power is pressed" <<endl;
    emit powerButtonSignal();
    if(s != off){
        //if power is currently on, close the device
        ui->listWidget->hide();
        ui->batteryBar->hide();
        s = off;
    }else{
        //if power offed, open the device
        ui->listWidget->show();
        ui->batteryBar->show();
        s = menu;
        menuPressed();
    }

}

void DenasGUI::leftPressed(){

    //if(s == init || s == treatmentApplied){
        if(temporaryPowerLevel >0){
            temporaryPowerLevel = temporaryPowerLevel - 5;
            QString qTempPower = QString::number(temporaryPowerLevel);
            ui->tempPower->setText(qTempPower);
            ui->powerLevel->setValue(temporaryPowerLevel);
        }
   // }
}

void DenasGUI::rightPressed(){
    //if(s == init || s == treatmentApplied){
        if(temporaryPowerLevel <100){
            temporaryPowerLevel = temporaryPowerLevel + 5;
            QString qTempPower = QString::number(temporaryPowerLevel);
            ui->tempPower->setText(qTempPower);
            ui->powerLevel->setValue(temporaryPowerLevel);
        }

    //}
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

void DenasGUI::on_skinSimulator_clicked()
{
    if(s == init){
        emit skinSignal();
        qDebug()<<"emited skin signal"<<endl;
        //if(battery > 5){
        ui->warning->hide();
        //}
        //start treatment

    }
    else if(s == treatmentApplied){
        emit skinSignal();
        qDebug()<<"skin is not detached"<<endl;
        ui->warning->show();
        ui->warning->setText("No Skin attached");
        //pause treatment
    }
}
void DenasGUI::warningSlot(){
    ui->warning->show();
    ui->warning->setText("POWER LOW");
}
void DenasGUI::turnONSucceedSlot(){
    s = menu;
}
void DenasGUI::shutdownSlot(){
    ui->listWidget->hide();
    ui->warning->hide();
    ui->batteryBar->hide();
    s = off;
}
void DenasGUI::initProgramSucceedSlot(){
    if(s == menu){
        ui->listWidget->hide();
        s = init;
        ui->powerLevel->show();
        QString qTempPower = QString::number(temporaryPowerLevel);
        ui->tempPower->setText(qTempPower);
        //default as 50
        ui->powerLevel->setValue(temporaryPowerLevel);
    }
}
//void programTimerSlot(int timer);
//void exitProgramSlot();
//void sendRecordSlot(QStringList list);
