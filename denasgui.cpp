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
        QString currentselected = ui->listWidget->currentItem()->text();
        ui->listWidget->itemClicked(ui->listWidget->currentItem());
        qDebug() << currentselected <<"is selected" << endl;
        if(currentselected == "COLD"){
            emit programSignal(0,0);//cold,programed
        }
        if(currentselected == "ALLERGY"){
            emit programSignal(1,0);//ALLERGY,programed
        }
        if(currentselected == "KIDNEY"){
            emit programSignal(2,0);//KIDNEY,programed
        }
        if(currentselected == "JOINTS"){
            emit programSignal(3,0);//JOINTS,programed
        }
        if(currentselected == "10"){
            emit programSignal(10,1);//10,frequency
        }
        if(currentselected == "20"){
            emit programSignal(20,1);//20,frequency
        }
        if(currentselected == "60"){
            emit programSignal(60,1);//60,frequency
        }
        if(currentselected == "77"){
            emit programSignal(77,1);//77,frequency
        }
        if(currentselected == "View"){
            emit requestRecordSignal();
        }
        if(currentselected == "Clear"){
            emit clearRecordSignal();
        }

}

void DenasGUI::menuPressed(){
        QStringList menu  = {"Program", "Frequency", "Recording"};
        updateList(menu);
        emit quitProgramSignal();
}

void DenasGUI::backPressed(){
    //send signal to OS that it may end program
    //or back to menu
        menuPressed();
        emit quitProgramSignal();
}

void DenasGUI::powerPressed(){
    //send signal to OS
    //control menu display
    qDebug() <<"send OS power is pressed" <<endl;
    emit powerButtonSignal();
    if(powerisOn){
        ui->listWidget->hide();
        powerisOn = false;
    }else{
        ui->listWidget->show();
        powerisOn = true;
    }

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

void DenasGUI::on_skinSimulator_clicked()
{
    if(powerisOn==true){
        emit skinSignal();
        qDebug()<<"emited skin signal"<<endl;
    }
}
void DenasGUI:: warningSlot(){

}
//void shutdownSlot();
//void programStatusSlot(QString programName,int powerLevel,int frequency, bool skinOn);
//void programTimerSlot(int timer);
//void exitProgramSlot();
//void sendRecordSlot(QStringList list);
