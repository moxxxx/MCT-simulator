#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"os.h"
#include"denasgui.h"
#include"battery.h"
#include<QObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OS *theOS;
    DENASGUI *denasGUI;
    Battery *battery;
    void connections();
    int capacity;


};

#endif // MAINWINDOW_H
