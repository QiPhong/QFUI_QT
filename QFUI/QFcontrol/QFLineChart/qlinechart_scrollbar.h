#ifndef QLINECHART_SCROLLBAR_H
#define QLINECHART_SCROLLBAR_H

#include <QWidget>

namespace Ui {
class QLineChart_ScrollBar;
}

class QLineChart_ScrollBar : public QWidget
{
    Q_OBJECT

public:
    explicit QLineChart_ScrollBar(QWidget *parent = nullptr);
    ~QLineChart_ScrollBar();

private:
    Ui::QLineChart_ScrollBar *ui;
};

#endif // QLINECHART_SCROLLBAR_H
