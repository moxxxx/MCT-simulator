#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"os.h"
#include<QObject>

namespace Ui {
class DenasGUI;
}

class DenasGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit DenasGUI(QWidget *parent = nullptr);
    ~DenasGUI();
public slots:
    void updateBatterySlot(double remain);

private:
    Ui::DenasGUI *ui;

};

#endif // MAINWINDOW_H
