#ifndef BATTERY_H
#define BATTERY_H
#include<QWidget>
#include <QSlider>

namespace Ui { class Battery;}

class Battery: public QWidget
{
    Q_OBJECT

public:
    explicit Battery(QWidget *parent = nullptr);
    ~Battery();
    static const int CAPACITY = 100;

public slots:
    void setRemain();

signals:
   void sendRemain(double remain);

private:
    Ui::Battery *ui;
};

#endif // BATTERY_H
