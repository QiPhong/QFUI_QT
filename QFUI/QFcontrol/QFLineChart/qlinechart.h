#ifndef QLINECHART_H
#define QLINECHART_H

#include <QWidget>
#include "qlinechartdata.h"



class QLineChart : public QWidget
{
    Q_OBJECT
public:
    explicit QLineChart(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *)override ;
    void paintEvent(QPaintEvent *event)override ;
    bool eventFilter(QObject *watched, QEvent *event)override ;
signals:


protected:
    //背景颜色
    QColor m_bkc1=QColor(0x59,0x59,0x59,0xff);
    QColor m_bkc2=QColor(0x70,0x70,0x70,0xff);
    //左边字符的宽度
    float m_yStrWidth=50;
    //左边刻度的长度
    float m_yScaleLength=20;
    //y轴刻度的距离
    float m_yScaleInt=10;


    //左边刻度的范围
    float m_yMinV=0;
    float m_yMaxV=100;

    // 底边字符的 高度
    float m_xStrHeight=50;
    // 底边刻度的 高度
    float m_xScaleLength=20;
    //y轴刻度的距离
    float m_xScaleInt=10;
    //底边刻度的范围
    float m_xMinV=0;
    float m_xMaxV=100;
    //坐标轴线宽
    float m_lineWidth=2.0;
    //坐标轴颜色
    QColor m_scaleColor=QColor(0x00,0x00,0x00,0xff);

    std::vector<std::list<QlineChartData>> m_data;




protected:
    void DrawBK(QPainter& painter);//绘制背景
     void DrawScale(QPainter& painter);//绘制坐标轴
protected:
     //获取x轴左边开始的坐标x
    inline float getXAxisStartWidth();
    //获取y轴下边开始的坐标y
      inline float getYAxisStartHeight();
};

#endif // QLINECHART_H
