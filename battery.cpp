#include "battery.h"

Battery::Battery()
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
    return remain;
}

double Battery::charge(double amount) {
    remain += amount;
    fix();
    return remain;
}

void Battery::set(double amount) {
    remain = amount;
    fix();
}

void Battery::fix() {
    if (remain > capacity){
        remain = capacity;
    }else if (remain < 0){
        remain = 0;
    }
}
