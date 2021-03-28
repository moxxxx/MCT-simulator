#ifndef DENASGUI_H
#define DENASGUI_H

#include <QMainWindow>
#include"battery.h"
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
    void updateList(QStringList list);
    void upPressed();
    void downPressed();

private:
    Ui::DenasGUI *ui;
};

#endif // DENASGUI_H
