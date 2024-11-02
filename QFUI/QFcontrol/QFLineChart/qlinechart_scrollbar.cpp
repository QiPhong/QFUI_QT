#include "qlinechart_scrollbar.h"
#include "ui_qlinechart_scrollbar.h"

QLineChart_ScrollBar::QLineChart_ScrollBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QLineChart_ScrollBar)
{
    ui->setupUi(this);
}

QLineChart_ScrollBar::~QLineChart_ScrollBar()
{
    delete ui;
}
