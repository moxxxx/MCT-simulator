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
    bool powerisOn = false;
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
    void shutdownSlot();
    void programStatusSlot(QString programName,int powerLevel,int frequency, bool skinOn);
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
};

#endif // DENASGUI_H
