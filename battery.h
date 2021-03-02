#ifndef BATTERY_H
#define BATTERY_H
#include<QWidget>

class Battery: public QWidget
{
    Q_OBJECT
public:
    Battery();

private:
    int capacity;
    int remain;
};

#endif // BATTERY_H
