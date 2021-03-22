#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    battery = new Battery();
    battery->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
