#ifndef BATTERY_H
#define BATTERY_H
#include<QWidget>
#include <QProgressBar>
#include <QSlider>

namespace Ui { class Battery;}

class Battery: public QWidget
{
    Q_OBJECT
public:
    explicit Battery(QWidget *parent = nullptr);
    ~Battery();
    int get_remain_int() const;
    double get_remain_double() const;

public slots:
    double drain(double amount);
    double charge(double amount);
    void set(double amount);

signals:
    void valueChanged(int value);

private:
    Ui::Battery *ui;
    QProgressBar *progressBar;
    QSlider *slider;
    const double capacity = 100;
    double remain;
    double screen_power_consumption = 0.1;
    void fix();
    void update();
};

#endif // BATTERY_H
