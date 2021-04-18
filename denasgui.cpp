#include "denasgui.h"
#include "ui_denasgui.h"
#include<QObject>
#include<QDebug>
#include <QLCDNumber>
#include <QHBoxLayout>
#include "unistd.h"
#include <math.h>

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
    ui->currentInfo->hide();
    ui->timer_min->hide();
    ui->timer_second->hide();
    ui->colon->hide();
    ui->recordingList->hide();

}

DenasGUI::~DenasGUI()
{
    delete ui;
}

void DenasGUI::updateBatterySlot(double remain){
    //set value of battery Bar
    ui->batteryBar->setValue(int(remain));
}

void DenasGUI::updateList(QStringList list){
    //redisplay the menu
    ui->listWidget->clear();
    ui->listWidget->addItems(list);
    ui->listWidget->setCurrentRow(0);
}

void DenasGUI::upPressed(){
    //if now in the menu, go to the row above it
    if(s == menu){
        if (ui->listWidget->currentRow() > 0){
                ui->listWidget->setCurrentRow((ui->listWidget->currentRow()-1));
        }
    }
}

void DenasGUI::downPressed(){
    //if now in the menu, go the the row below it
    if(s == menu){
        int num = ui->listWidget->count();
        int index = ui->listWidget->currentRow();
        if (index < (num-1)){
                ui->listWidget->setCurrentRow((ui->listWidget->currentRow()+1));
        }
    }
}

void DenasGUI::okPressed(){
    //if now in the menu
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
    }else if(s == init ){   //if now in init status
        //Send powerLevelSignal
        emit powerLevelSignal(TEMPORARY_POWER_LEVEL);
        qDebug()<<"send powerlevel signal:"<<TEMPORARY_POWER_LEVEL<<endl;
        //if skin not attached, show warning,
        if(!skinisOn){
            ui->warning->show();
            ui->warning->setText("No Skin attached");
        }else{
            //if skin is attached, hide warning
            ui->warning->hide();
        }
    //if treatmentApplied status
    }else if(s == treatmentApplied){
        //Send powerLevelSignal
        emit powerLevelSignal(TEMPORARY_POWER_LEVEL);
        QString s_TEMPORARY_POWER_LEVEL = QString::number(TEMPORARY_POWER_LEVEL);
        currentPowerlevel = s_TEMPORARY_POWER_LEVEL;
        qDebug()<<"send powerlevel signal:"<<TEMPORARY_POWER_LEVEL<<endl;
        QString currentProgramInfo = " Program: " + currentProgramName + "\n Current power level: " + currentPowerlevel +
                "\n Current frequency: " + currentFrequency;
        ui->currentInfo->setText(currentProgramInfo);
        //hide powerlevel adjust bar and value
        ui->powerLevel->hide();
        ui->tempPower->hide();
    }

}

void DenasGUI::menuPressed(){
    QStringList menuList  = {"Program", "Frequency", "Recording"};
    updateList(menuList);
    //when status is init or treatmentapplied, back to menu. hide display of treatment
    if(s == init || s == treatmentApplied){
        ui->powerLevel->hide();
        ui->tempPower->hide();
        ui->listWidget->show();
        emit quitProgramSignal();
        s = menu;
        qDebug()<<"back to menu"<<endl;
    }
    //when in the showing record, hide record, show menu
    if(s == showingRecord){
        ui->recordingList->hide();
        ui->listWidget->show();
        updateList(menuList);
        s = menu;
    }
}

void DenasGUI::backPressed(){
    //send signal to OS
    if(s == menu){
        QString currentselected = ui->listWidget->currentItem()->text();
        if(currentselected == "Program" || currentselected == "Frequency" ||currentselected == "Recording"){
            //if in first menu level, do nothing
        }else{
            //in second menu level, go back to first menu level
            menuPressed();}
    }else if(s == showingRecord){   //if in the showing record, back to menu
        ui->recordingList->hide();
        ui->listWidget->show();
        s = menu;
    }else if(s == init || s == treatmentApplied){   //if in status of init or treatment applied,
        skinisOn = false;                           //send quit program signal and display menu
        emit quitProgramSignal();
        s = menu;
    }
}

void DenasGUI::powerPressed(){
    //send signal to OS
    emit powerButtonSignal();
    qDebug()<<"power button pressed"<<endl;
}

void DenasGUI::leftPressed(){
    //only work when in init status and treatment applied status
    if(s == init || s == treatmentApplied){
        //has to >=0
        if(TEMPORARY_POWER_LEVEL >0){
            TEMPORARY_POWER_LEVEL = TEMPORARY_POWER_LEVEL - 5;
            QString qTempPower = QString::number(TEMPORARY_POWER_LEVEL);
            ui->tempPower->show();
            ui->powerLevel->show();
            ui->tempPower->setText(qTempPower);
            ui->powerLevel->setValue(TEMPORARY_POWER_LEVEL);
        }
    }
}

void DenasGUI::rightPressed(){
    //only work when in init status and treatment applied status
    if(s == init || s == treatmentApplied){
        //has to <= 0
        if(TEMPORARY_POWER_LEVEL <100){
            TEMPORARY_POWER_LEVEL = TEMPORARY_POWER_LEVEL + 5;
            QString qTempPower = QString::number(TEMPORARY_POWER_LEVEL);
            ui->tempPower->show();
            ui->powerLevel->show();
            ui->tempPower->setText(qTempPower);
            ui->powerLevel->setValue(TEMPORARY_POWER_LEVEL);
        }

    }
}

void DenasGUI::itemClicked(QListWidgetItem *item){
    //menu display
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
    //when program is init, warning if skin is not attached
    //if power lower than a critical value,powerlow will be warning instead of skin warning
    if(s == init){
        skinisOn = !skinisOn;
        if(!skinisOn){
            ui->warning->show();
            ui->warning->setText("No Skin attached");
        }else{
            if(ui->batteryBar->value() > 5){
                //skin is attached
                qDebug()<<"emited skin signal"<<endl;
                emit skinSignal();
                ui->warning->hide();
                ui->tempPower->hide();
                ui->powerLevel->hide();
            }
        }
        qDebug()<<"skin is on: "<<skinisOn<<endl;
    }
    //if treatment has started
    else if(s == treatmentApplied){
        skinisOn = !skinisOn;
        if(!skinisOn){
            //warning and quit program if skin is not attached during treatment
            ui->warning->show();
            ui->warning->setText("No Skin attached");
            emit quitProgramSignal();
            ui->warning->hide();
        }
    }
}
void DenasGUI::warningSlot(){
    //warning when power lower than a critical value
    ui->warning->show();
    ui->warning->setText("POWER LOW");
}
void DenasGUI::turnONSucceedSlot(){
        //if power offed, open the device
        qDebug()<<"turnon"<<endl;
        ui->listWidget->show();
        ui->batteryBar->show();
        s = menu;
        menuPressed();
        qDebug()<<"s is"<<s<<endl;
}
void DenasGUI::shutdownSlot(){
    //if current device is on, turn all display off
    if(s != off){
        qDebug()<<"shutdown slot in gui is activated"<<endl;
        //hide all display
        ui->listWidget->hide();
        ui->warning->hide();
        ui->powerLevel->hide();
        ui->tempPower->hide();
        ui->batteryBar->hide();
        ui->currentInfo->hide();
        ui->timerBlind->hide();
        ui->timer_second->hide();
        ui->timer_min->hide();
        ui->recordingList->hide();
        skinisOn = false;
        //set status to off
        s = off;
        skinisOn = false;
        //set default powerlevel back to 50
        TEMPORARY_POWER_LEVEL = 50;
    }
}
void DenasGUI::initProgramSucceedSlot(){
    //if status is menu, init the program
    if(s == menu){
        ui->listWidget->hide();
        s = init;
        ui->powerLevel->show();
        ui->tempPower->show();
        QString qTempPower = QString::number(TEMPORARY_POWER_LEVEL);
        ui->tempPower->setText(qTempPower);
        //default as 50
        ui->powerLevel->setValue(TEMPORARY_POWER_LEVEL);
    }
}
void DenasGUI::programTimerSlot(int timer){
    //get timer signal and update timer ui in seconds.
    int min = static_cast<int>(floor(timer/60));
    int second = timer-(min*60);
    ui->timer_min->display(min);
    ui->timer_second->display(second);
}
void DenasGUI::exitProgramSlot(){
    //when in a program or it has init, exit it, hide display of it.
    if(s == treatmentApplied  || s == init){
        ui->currentInfo->hide();
        ui->timerBlind->hide();
        ui->timer_min->hide();
        ui->timer_second->hide();
        ui->powerLevel->hide();
        ui->tempPower->hide();
        skinisOn = false;
        TEMPORARY_POWER_LEVEL = 50;
        ui->warning->hide();
        ui->listWidget->show();
        s = menu;
    }
}
void DenasGUI::sentRecordSlot(QStringList list){
    //if current in menu, show record display
    if(s == menu){
        ui->recordingList->show();
        if(list.isEmpty()){
            qDebug()<<"is empty"<<endl;
            ui->recordingList->setText("no record");
        }
        else{
        QString str = list.join("\n");
        ui->recordingList->setWordWrap(true);
        ui->recordingList->setText(str);
        s = showingRecord;
        }
    }
}
void DenasGUI::treatmentStartSlot(QString programName, int powerLevel, int frequency, bool skinOn){
    if(s == init  && skinOn == true){
        QString spowerLevel = QString::number(powerLevel);
        QString sfrequency = QString::number(frequency);
        qDebug()<<sfrequency<<endl;
        QString currentProgramInfo = " Program: " + programName + "\n Current power level: " + spowerLevel +
                "\n Current frequency: " + sfrequency;
        currentProgramName = programName;
        currentPowerlevel = spowerLevel;
        currentFrequency = sfrequency;
        ui->currentInfo->show();
        ui->currentInfo->setText(currentProgramInfo);
        s = treatmentApplied;
        ui->timerBlind->show();
        ui->timer_min->show();
        ui->timer_second->show();
        ui->timer_min->display(0);
        ui->timer_second->display(0);
    }
}
