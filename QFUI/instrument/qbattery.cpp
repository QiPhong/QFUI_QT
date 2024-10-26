#include "qbattery.h"
#include "qpainter.h"
#include <QTimer>
#include <QDebug>
QBattery::QBattery(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, &QTimer::timeout, this, &QBattery::__TimerEvent);
     timer->start();
}

void QBattery::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //开始绘制
    //绘制边框
    painter.save();
    //绘制电池边框( 纵向的)
    float headHeight = height() *m_Proportion_H;
//    double batteryHeight = height() - headHeight;
    QPointF topLeft(m_borderLineW, m_borderLineW+headHeight);
    QPointF bottomRight(width()-m_borderLineW, height() - m_borderLineW);
    QRectF batteryRect = QRectF(topLeft, bottomRight);

    painter.setPen(QPen(m_borderColor, m_borderLineW));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(batteryRect, m_borderRadius, m_borderRadius);
    painter.restore();
     //绘制电池顶端( 纵向的)
    painter.save();

    QPointF CenterPt(width()/2.0,0);

    QPointF headRectTopLeft(CenterPt.x()-width()*m_Proportion_W/2, 0);
    QPointF headRectBottomRight(CenterPt.x()+width()*m_Proportion_W/2,headHeight+m_borderLineW );
    QRectF headRect(headRectTopLeft, headRectBottomRight);
    QBrush brush(m_borderColor);

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_borderColor);
    painter.drawRoundedRect(headRect, m_borderTRadius, m_borderTRadius);
    painter.restore();

//绘制进度（纵向）
    if (m_cerrentV >= m_minV) {
        painter.save();
        QLinearGradient lgBrush(QPointF(0, height()),QPointF(0, m_borderLineW+headHeight));
        lgBrush.setColorAt(0.0, m_internalColor1);
        lgBrush.setColorAt(1.0, m_internalColor2);

//从底部往上一个m_borderLineW位置开始绘制到顶部一个m_borderLineW和headHeight结束
        //总长度计算
        float totlLen=(height()-m_borderLineW*2-headHeight-m_capCollapse*2);
        //总共占比计算
        float ato =totlLen/(m_maxV-m_minV);

        //没有使用的长度
        float otherLen=(m_maxV-m_cerrentV)*ato;

        //开始的坐标
        float startX=m_borderLineW+headHeight;
        QPointF startPT(m_borderLineW+m_capCollapse,otherLen+startX+m_capCollapse);//容量填充开始坐标
        QPointF endPT(width()-m_borderLineW-m_capCollapse, height()-m_borderLineW-m_capCollapse);//容量填充结束坐标

        QRectF capRect(startPT, endPT);

        painter.setPen(Qt::NoPen);
        painter.setBrush(lgBrush);
        painter.drawRoundedRect(capRect, m_capRadius, m_capRadius);
        painter.restore();


    }








}

void QBattery::setValue(int value)
{
    setValue((float)value);
}

void QBattery::__TimerEvent()
{

    float step = (m_maxV - m_minV)*m_stepRat;
    if(m_TargeV>m_cerrentV){
            if(m_TargeV-m_cerrentV>step){
                m_cerrentV+=step;

            }else {
                m_cerrentV=m_TargeV;
                 timer->stop();
            }

    }else if(m_cerrentV >m_TargeV ){
        if(m_cerrentV-m_TargeV >step){
            m_cerrentV-=step;

        }else {
            m_cerrentV=m_TargeV;
            timer->stop();
        }

    }
        update();
}

float QBattery::getMinValue() const
{
    return m_minV;
}

void QBattery::setMinValue(float minValue)
{
    if(minValue >= m_maxV)return;
    if(minValue>m_cerrentV)m_cerrentV=minValue;
    if(minValue>m_TargeV)m_TargeV=minValue;
    m_minV=minValue;
    update();

}

float QBattery::getMaxValue() const
{
    return m_maxV;
}

void QBattery::setMaxValue(float maxValue)
{
    if(maxValue <= m_minV)return;
    if(maxValue<m_cerrentV)m_cerrentV=maxValue;
    if(maxValue<m_TargeV)m_TargeV=maxValue;
    m_maxV=maxValue;
    update();
}

float QBattery::getValue() const
{
    return m_TargeV;
}

void QBattery::setValue(float value)
{
    if(value<m_minV || value>m_maxV)return;
//    m_cerrentV=value;
    m_TargeV = value;
    if(m_isAnimation){
         timer->stop();
        timer->start();
    }else{
        timer->stop();
        m_cerrentV=value;
    }

    update();
}

float QBattery::setBorderLineWidth(float w)
{
    if(w<=0)return m_borderLineW;
    float buf =m_borderLineW;
    m_borderLineW=w;
    update();
    return buf;
}

float QBattery::setBorderRadius(float r)
{
    if(r<=0)return m_borderRadius;
    float buf =m_borderRadius;
    m_borderRadius=r;
      update();
    return buf;
}

QColor QBattery::setBorderColor(QColor color)
{

    QColor buf =m_borderColor;
    m_borderColor=color;
      update();
    return buf;
}

float QBattery::setProportionHeightRatio(float ato)
{
    if(ato<=0)return m_Proportion_H;
    float buf =m_Proportion_H;
    m_Proportion_H=ato;
      update();
    return buf;
}

float QBattery::setProportionWidthRatio(float ato)
{
    if(ato<=0)return m_Proportion_W;
    float buf =m_Proportion_W;
    m_Proportion_W=ato;
      update();
    return buf;
}

float QBattery::setBorderTRadius(float r)
{
    if(r<=0)return m_borderTRadius;
    float buf =m_borderTRadius;
    m_borderTRadius=r;
      update();
    return buf;
}

float QBattery::setStepRatio(float rat)
{
    if(rat<=0)return m_stepRat;
    float buf =m_stepRat;
    m_stepRat=rat;
      update();
    return buf;
}

bool QBattery::isAnimation(bool flag)
{
    bool buf =m_isAnimation;
    m_isAnimation=flag;
      update();
    return buf;
}

void QBattery::setInternalColor(QColor c1, QColor c2)
{
    m_internalColor1=c1;
    m_internalColor2=c2;
    update();

}

float QBattery::setCapRadius(float r)
{
    if(r<=0)return m_capRadius;
    float buf =m_capRadius;
    m_capRadius=r;
      update();
    return buf;
}

float QBattery::setCapCollapse(float cc)
{
    if(cc<=0)return m_capCollapse;
    float buf =m_capCollapse;
    m_capCollapse=cc;
     update();
    return buf;
}
