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
    ui->widget->setValue(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
     ui->widget->setLargeScaleHeight(value);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
  ui->widget->setSmallScaleHeight(value);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
      ui->widget->setRailRibbon(value);
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    ui->widget->setOpenAngle(value);
}

void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
     ui->widget->setScaleCount(value);
}

void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    ui->widget->setSmallScaleCount(value);
}

void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    ui->widget->setFontSize(value);
}

void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
        ui->widget->setTitleFontSize(value);
}
