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
    ui->warning->hide();
    ui->warning->setText("No Skin attached");
    ui->timerBlind->hide();
    ui->timer_min->hide();
    ui->timer_second->hide();
    ui->colon->hide();
    ui->recordingList->hide();






 //test purpose, should be delete once os sent status
    //init display
    QString qTempPower = QString::number(temporaryPowerLevel);
    ui->tempPower->setText(qTempPower);
//end of display test display
//test purpose for timer, should update timer slot once figure out what number we get
    ui->timer_min->display(5);
    ui->timer_second->display(8);
    ui->timer_second->display(700);
//end of test diplay timer

//test purpose for showing recording
    QStringList list;
    list << "what i am writing here is a bunch of bull shit to see if this function actually work" << "THis is a second paragraph to see how will it show on the screen" << "The third." ;
    QString str = list.join("\n");
    ui->recordingList->setWordWrap(true);
    ui->recordingList->setText(str);
//end of test showing recording

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
            s = init;
        }
        else if(currentselected == "ALLERGY"){
            emit programSignal(1,1);//ALLERGY,programed
            s = init;
        }
        else if(currentselected == "KIDNEY"){
            emit programSignal(2,1);//KIDNEY,programed
            s = init;
        }
        else if(currentselected == "JOINTS"){
            emit programSignal(3,1);//JOINTS,programed
            s = init;
        }
        else if(currentselected == "10 Hz"){
            emit programSignal(10,0);//10,frequency
            s = init;
        }
        else if(currentselected == "20 Hz"){
            emit programSignal(20,0);//20,frequency
            s = init;
        }
        else if(currentselected == "60 Hz"){
            emit programSignal(60,0);//60,frequency
            s = init;
        }
        else if(currentselected == "77 Hz"){
            emit programSignal(77,0);//77,frequency
            s = init;
        }
        else if(currentselected == "View"){
            emit requestRecordSignal();
            s = showingRecord;
            qDebug()<<"s is"<<s<<endl;
        }
        else if(currentselected == "Clear"){
            emit clearRecordSignal();
            emit requestRecordSignal();
            s = showingRecord;
        }
        else{
            s = menu;
        }
        qDebug()<<"s is"<<s<<endl;
    }else if(s == init || s == treatmentApplied){
        //Send powerLevelSignal
        emit powerLevelSignal(temporaryPowerLevel);
        qDebug()<<"send powerlevel signal:"<<temporaryPowerLevel<<endl;
        if(!skinisOn){
            ui->warning->show();
            ui->warning->setText("No Skin attached");
            skinisOn = true;
        }else{
            ui->warning->hide();
            skinisOn = false;
        }

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
    emit powerButtonSignal();
    /*
    if(s != off){
        ui->listWidget->hide();
        //currently not hiding because warning signal is sent after shutdown
        ui->warning->hide();
        ui->batteryBar->hide();
        qDebug()<<"shutdown slot is activated"<<endl;
        s = off;
    }else{
        ui->listWidget->show();
        ui->batteryBar->show();
        s = menu;
        menuPressed();
        qDebug()<<"s is"<<s<<endl;
    }
    */
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
        skinisOn = !skinisOn;
        qDebug()<<skinisOn<<endl;
        if(!skinisOn){
            ui->warning->show();
            ui->warning->setText("No Skin attached");

        }else{
            if(ui->batteryBar->value() > 5){
                ui->warning->hide();
            }
        }
        qDebug()<<skinisOn<<endl;
    }
    else if(s == treatmentApplied){
        emit skinSignal();
        qDebug()<<"skin is not detached"<<endl;
        ui->warning->show();
        ui->warning->setText("No Skin attached");
    }
}
void DenasGUI::warningSlot(){
    ui->warning->show();
    ui->warning->setText("POWER LOW");
}
void DenasGUI::turnONSucceedSlot(){
        //if power offed, open the device
        ui->listWidget->show();
        ui->batteryBar->show();
        s = menu;
        menuPressed();
        qDebug()<<"s is"<<s<<endl;
}
void DenasGUI::shutdownSlot(){
    if(s != off){
        ui->listWidget->hide();
        //currently not hiding because warning signal is sent after shutdown
        ui->warning->hide();
        ui->batteryBar->hide();
        qDebug()<<"shutdown slot is activated"<<endl;
        s = off;
    }
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
void DenasGUI::programTimerSlot(int timer){
    //get timer signal and update timer ui
    //min and second need to be update once know how to calculate.
    int min = timer;
    int second = timer;
    ui->timer_min->display(min);
    ui->timer_second->display(second);
}
void DenasGUI::exitProgramSlot(){
    if(s == treatmentApplied){
        ui->timerBlind->hide();
        ui->timer_min->hide();
        ui->timer_second->hide();
        ui->listWidget->show();
        s = menu;
    }
}
void DenasGUI::sentRecordSlot(QStringList list){
    if(s == menu){
        QString str = list.join("\n");
        ui->recordingList->setWordWrap(true);
        ui->recordingList->setText(str);
        s = showingRecord;
    }
}
void DenasGUI::treatmentStartSlot(QString programName, int powerLevel, int frequency, bool skinOn){
    if(s == init  && skinOn == true){
        //may be change depend ondifferent programName, may be 15:0 or 0:0
        s = treatmentApplied;
        ui->timerBlind->show();
        ui->timer_min->show();
        ui->timer_second->show();
        ui->timer_min->display(0);
        ui->timer_second->display(0);
    }
}
