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
    enum status {
        off = 0,
        menu = 1,
        init = 2,
        treatmentApplied = 3,
        showingRecord = 4
    };

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
    void programTimerSlot(int timer);
    void exitProgramSlot();
    void sentRecordSlot(QStringList list);
    void treatmentStartSlot(QString programName, int powerLevel, int frequency, bool skinOn);



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
    int TEMPORARY_POWER_LEVEL = 50;
    bool skinisOn = false;
};

#endif // DENASGUI_H
