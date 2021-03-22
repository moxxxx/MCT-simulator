#include "battery.h"
#include "ui_battery.h"

Battery::Battery(QWidget *parent) : QWidget(parent), ui(new Ui::Battery){
    ui->setupUi(this);
    progressBar = new QProgressBar();
    slider = new QSlider();
    progressBar->setRange(0, static_cast<int>(capacity));
    progressBar->setValue(get_remain_int());
    slider->setRange(0, static_cast<int>(capacity));
    slider->setTickInterval(1);
    slider->setSingleStep(1);
    slider->setValue(get_remain_int());

    connect(slider, &QSlider::valueChanged, this, &Battery::set);
}

Battery::~Battery()
{

}

int Battery::get_remain_int() const{
    return static_cast<int>(remain);
}

double Battery::get_remain_double() const{
    return remain;
}

double Battery::drain(double amount) {
    remain -= amount;
    fix();
    update();
    return remain;
}

double Battery::charge(double amount) {
    remain += amount;
    fix();
    update();
    return remain;
}

void Battery::set(double amount) {
    remain = amount;
    fix();
    update();
}

void Battery::valueChanged() {
    remain = slider->value();
    fix();
    update();
}

void Battery::fix() {
    if (remain > capacity){
        remain = capacity;
    }else if (remain < 0){
        remain = 0;
    }
}

void Battery::update() {
    slider->setValue(get_remain_int());
    progressBar->setValue(get_remain_int());
}

