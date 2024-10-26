#ifndef QRADAR_H
#define QRADAR_H

#include <QWidget>
#include <QImage>
class QRadar : public QWidget
{
    Q_OBJECT
public:
    explicit QRadar(QWidget *parent = nullptr);

    void setTimeCycle(int ms);
    void setStepAng(float ang);//设置步进角度
    void setDirection(int d);
protected:
    QImage src=QImage(":/Image/radar.png");
    int m_direction= 0;//0为顺时针，1为逆时针
     QTimer *timer;
     float m_curentAng=135;
     float m_stepAng=1;
private slots:
    void __TimerEvent();
signals:
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QRADAR_H
