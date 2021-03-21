#ifndef BATTERY_H
#define BATTERY_H
#include<QWidget>

class Battery: public QWidget
{
    Q_OBJECT
public:
    Battery();
    int get_remain_int() const;
    double get_remain_double() const;
    double drain(double amount);
    double charge(double amount);
    void set(double amout);


private:
    const double capacity = 100;
    double remain;
    double screen_power_consumption = 0.1;
    void fix();
};

#endif // BATTERY_H
