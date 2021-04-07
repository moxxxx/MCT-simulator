#ifndef DENASGUI_H
#define DENASGUI_H
#include <QMainWindow>
#include"battery.h"
#include<QObject>
#include<QListWidget>

enum status {
    off = 0,
    menu = 1,
    init = 2,
    treatmentApplied = 3,
    showingRecord = 4
};

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
    void warningSlot();
    void turnONSucceedSlot();
    void shutdownSlot();
    void initProgramSucceedSlot();
    //void programTimerSlot(int timer);
    //void exitProgramSlot();
    //void sendRecordSlot(QStringList list);


signals:
   void powerButtonSignal();
   void programSignal(int programNum, int programType);
   void powerLevelSignal(int powerLevel);
   void skinSignal();
   void quitProgramSignal();
   void requestRecordSignal();
   void clearRecordSignal();

private slots:
   void on_skinSimulator_clicked();

private:
    Ui::DenasGUI *ui;
    status s;
    int temporaryPowerLevel;
};

#endif // DENASGUI_H
