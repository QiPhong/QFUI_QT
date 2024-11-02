#include "qlinechart.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

QLineChart::QLineChart(QWidget *parent) : QWidget(parent)
{

        this->installEventFilter(this);//安装事件函数
        setMouseTracking(true);  // 开启鼠标跟踪模式,这样才有鼠标移动的消息
}

void QLineChart::mousePressEvent(QMouseEvent *)
{

}

void QLineChart::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    DrawBK(painter);
    DrawScale(painter);
}

bool QLineChart::eventFilter(QObject *watched, QEvent *event)
{
     int type = event->type();
     if (type == QEvent::MouseButtonPress) {
         QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
         qDebug()<<"鼠标有按键按下："<<mouseEvent->pos();

     } else if (type == QEvent::MouseButtonRelease) {
          QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
         qDebug()<<"鼠标有按键弹起："<<mouseEvent->pos();
     } else if (type == QEvent::MouseButtonDblClick) {
          QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
         qDebug()<<"鼠标有按键双击："<<mouseEvent->pos();
     }
     else if(type == QEvent::MouseMove){
          QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        qDebug()<<"鼠标移动："<<mouseEvent->pos();

     }


     return QWidget::eventFilter(watched, event);;
}

void QLineChart::DrawBK(QPainter &painter)
{
    // 创建线性渐变，从顶部到底部填充
            QLinearGradient gradient(0, 0, 0, height());

    // 设置渐变颜色的起点和终点
    gradient.setColorAt(0.0, m_bkc1); // 顶部颜色
    gradient.setColorAt(1.0, m_bkc2); // 底部颜色

    // 将渐变应用为画刷
    painter.setBrush(QBrush(gradient));
    painter.setPen(Qt::NoPen); // 无边框

    // 绘制填充矩形
    painter.drawRect(rect());


}

void QLineChart::DrawScale(QPainter &painter)
{
    float sx=getXAxisStartWidth()-m_lineWidth/2;
    float sy=getYAxisStartHeight();
    painter.save();
    painter.setPen(QPen(m_scaleColor,m_lineWidth));
    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.drawLine(sx,0,sx,height()-sy);//绘制y轴
    painter.drawLine(sx,height()-sy,width(),height()-sy);//绘制x轴

     QFontMetrics metrics(painter.font());
    //绘制y轴刻度数
    if(0 < m_yScaleInt){
        float step=(height()-sy)/m_yScaleInt;//y轴刻度数
        float vUnit=(m_yMaxV-m_yMinV)/(height()-sy);//单位值
        for(float y=height()-sy;y>0;y-=step){
            painter.drawLine(sx,y,sx-m_yScaleLength,y);
            //坐标轴上的y坐标
            float asy=(height()-sy-y)*vUnit;
            QString text=QString::number(asy);
           // 计算字符串的边界矩形
           QRectF rect = metrics.boundingRect(text);
           float h=rect.height();
           rect=QRectF(0,y-h/2,m_yStrWidth,h);
           painter.drawText(rect, Qt::AlignRight | Qt::AlignTop, text);
//           painter.drawRect(rect);

        }
    }
    //绘制x轴刻度数
    if(0 < m_xScaleInt){
        float step=(width()-sx)/m_xScaleInt;//x轴刻度数
        float vUnit=(m_xMaxV-m_xMinV)/(width()-sx);//单位值
        float y=height()-sy;
        for(float x=sx;x<width();x+=step){
            painter.drawLine(x,y,x,y+m_xScaleLength);
            //坐标轴上的x坐标
            float asx=(x-sx)*vUnit;
            QString text=QString::number(asx);
           // 计算字符串的边界矩形
           QRectF rect = metrics.boundingRect(text);
           float w=rect.width();
            w*=1.2;
           rect=QRectF(x-w/2,y+m_xScaleLength,w,m_xStrHeight);
           painter.drawText(rect, Qt::AlignRight | Qt::AlignTop, text);
//           painter.drawRect(rect);

        }
    }

    painter.restore();




}

inline float QLineChart::getXAxisStartWidth()
{
    return m_yStrWidth+m_yScaleLength;
}

inline float QLineChart::getYAxisStartHeight()
{
    return m_xStrHeight+m_xScaleLength;
}
