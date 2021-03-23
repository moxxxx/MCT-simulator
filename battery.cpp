#include "battery.h"
#include "ui_battery.h"
#include<QDebug>

Battery::Battery(QWidget *parent) : QWidget(parent), ui(new Ui::Battery){
    ui->setupUi(this);
    ui->horizontalSlider->setRange(0, static_cast<int>(CAPACITY));
    ui->horizontalSlider->setTickInterval(1);
    ui->horizontalSlider->setSingleStep(1);
    connect(ui->pushButton, &QPushButton::released, this, &Battery::setRemain);
}

Battery::~Battery(){
    delete ui;
}

void Battery::setRemain(){
    qDebug() <<"send OS battery remain overide" <<endl;
    emit sendRemain(ui->horizontalSlider->value());
}

