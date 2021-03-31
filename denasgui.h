#ifndef DENASGUI_H
#define DENASGUI_H

#include <QMainWindow>
#include"battery.h"
#include<QObject>
#include<QListWidget>

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
    void updateList(QStringList list);
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void okPressed();
    void menuPressed();
    void backPressed();
    void powerPressed();
    void itemClicked(QListWidgetItem *item);
signals:
   void powerButtonOffSignal();
   void powerButtonOnSignal();
private:
    Ui::DenasGUI *ui;
    bool powerIsOn = false;
};

#endif // DENASGUI_H
