#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->widget->setTimeCycle(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
ui->widget->setStepAng(value);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{

    ui->widget->setDirection(ui->checkBox->isChecked());
}
