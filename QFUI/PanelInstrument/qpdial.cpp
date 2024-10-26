#include "qpdial.h"
#include <QPainter>
#include <QtMath>
#include <QTimer>
#define __Auxiliary_Line__ 0



void QPDial::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QPointF Center(width()/2.0,height()/2.0);
     float R=qMin(width(),height())/2.0;

#if __Auxiliary_Line__!=0

    //绘制+辅助线查看
    {
        QPointF auxP1(width()/2.0,0);
        QPointF auxP2(width()/2.0,height());
        QPointF auxP3(0,height()/2.0);
        QPointF auxP4(width(),height()/2.0);
        float r=R-m_dialFontHeight-m_largeScale-m_spaceRibbon/2.0;

        painter.save();
        painter.setBrush(Qt::NoBrush);
        QPen pen(QColor(0xff,0,0,0xff),1.0,Qt::PenStyle::DotLine);
        painter.setPen(pen);

        painter.drawLine(auxP1,auxP2);
         painter.drawLine(auxP3,auxP4);

//以3点钟方向为0度，在绘制一个135度和45度的辅助线
         painter.save();
         painter.translate(Center);
         painter.rotate(90-m_openAngle/2);
        painter.drawLine(0,0,R,0);
        painter.rotate(m_openAngle);
       painter.drawLine(0,0,R,0);
           painter.restore();
//绘制当前指针线
       float totalAng=360-m_openAngle;//总角度
       float  unitAng = totalAng/(m_maxV-m_minV);//单位角度
       float  ang=unitAng*m_value;//当前的角度
        painter.save();
        painter.translate(Center);
        painter.rotate(90+m_openAngle/2.0);//转到开始的角度
        painter.rotate(ang);
        painter.drawLine(0,0,r,0);


        painter.restore();


        painter.restore();
    }
//绘制一个圆
    {
        painter.save();
        QPointF LT(Center.x()-R,Center.y()-R);
        QPointF RB(Center.x()+R,Center.y()+R);
        QRectF rect(LT,RB);
        QPen pen(QColor(0xff,0,0,0xff),2.0);
        painter.setPen(pen);
        painter.drawEllipse(rect);
        painter.restore();
    }
#endif


    paintRail(painter);
    paintScale(painter);
    paintScaleW(painter);
    paintPointer(painter);
    paintTitle(painter);
}

QPDial::QPDial(QWidget *parent): QWidget(parent)
{
    initVar();

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, &QTimer::timeout, this, &QPDial::__TimerEvent);
     timer->start();
}

void QPDial::initVar()
{

    m_dialFontHeight=20.0;//字体的高度
    m_largeScaleHeight = 20.0;// 大的刻度高度
    m_smallScaleHeight = 5.0;// 大的刻度高度
    m_spaceRibbon=20.0;//刻度到导轨的空间带宽度
    m_railRibbon=8.0;//导轨带的宽度
    m_openAngle=120.0;//底下开口角度(角度制)
}

void QPDial::paintRail(QPainter &painter)
{
    QPointF Center(width()/2.0,height()/2.0);
     float R=qMin(width(),height())/2.0;
     float r = R-m_dialFontHeight-m_largeScaleHeight-m_spaceRibbon-m_railRibbon/2.0;
     if(r<=0)return;
    painter.save();
    QPointF LT(Center.x()-r,Center.y()-r);
    QPointF RB(Center.x()+r,Center.y()+r);
    QRectF rect(LT,RB);
    QPen pen(m_railColor,m_railRibbon);
    painter.setPen(pen);
    painter.drawArc(rect,(m_openAngle/2.0-90)*16,(360-m_openAngle)*16);
    painter.restore();
}

void QPDial::paintScaleW(QPainter &painter)
{
    QPointF Center(width()/2.0,height()/2.0);
    float R=qMin(width(),height())/2.0;
   painter.save();

    painter.translate(Center);
    // 设置画刷颜色
    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.setPen(m_strColor);

    //角度的步进
    float stepAng = (360-m_openAngle)/m_scaleCount;
    float stepV=(m_maxV-m_minV)/m_scaleCount;
   painter.save();                 // 先保存原始的坐标系
   painter.rotate(90+m_openAngle/2);
   QFont font(m_fontName,m_fontSize);
   painter.setFont(font);
    for(int i = 0; i < m_scaleCount+1; i++)
    {
        QString text =QString::number(m_minV+stepV*i);
        QFontMetrics metrics(painter.font());
        QSize size = metrics.size(0, text);
        int width = size.width();
        painter.save();
        painter.translate(R,0);
        painter.rotate(90);
        painter.drawText( -width/2.0,0, width, m_dialFontHeight,
                          Qt::AlignCenter,text );

        painter.restore();
        painter.rotate(stepAng);
    }
    painter.restore();              // 恢复到原始坐标系

    painter.restore();
}

void QPDial::paintScale(QPainter &painter)
{
    QPointF Center(width()/2.0,height()/2.0);
    float R=qMin(width(),height())/2.0;
    float r = R-m_dialFontHeight-m_largeScaleHeight;
    painter.save();
    painter.translate(Center);
    // 设置画刷颜色
    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.setPen(m_scaleColor);

    //角度的步进
    float stepAng = (360-m_openAngle)/m_scaleCount;

    float stepSmallAng=stepAng/(m_smallScaleCount+1);


   painter.rotate(90+m_openAngle/2);

    for(int i = 0; i < m_scaleCount+1; i++)
    {
         painter.drawLine(r,0,r+m_largeScaleHeight,0);
        painter.save();
        for(int j=-1;++j<=m_smallScaleCount && i <m_scaleCount ;){
            painter.drawLine(r,0,r+m_smallScaleHeight,0);
            painter.rotate(stepSmallAng);
        }
        painter.restore();
        painter.rotate(stepAng);
    }

    painter.restore();
}

void QPDial::paintPointer(QPainter &painter)
{
    QPointF Center(width()/2.0,height()/2.0);
    float R=qMin(width(),height())/2.0;
    float r = R-m_dialFontHeight-m_largeScaleHeight-m_spaceRibbon-m_railRibbon;
     float r1 = R-m_dialFontHeight-m_largeScaleHeight-m_spaceRibbon/2.0;
    float a=r*0.2;//三角形的边长
    painter.save();
    painter.translate(Center);
    float totalAng=360-m_openAngle;//总角度
    float  unitAng = totalAng/(m_maxV-m_minV);//单位角度
    float  ang=unitAng*m_value;//当前的角度
     painter.rotate(90+m_openAngle/2.0);//转到开始的角度
     painter.rotate(ang+90);



    QPainterPath path;
    path.translate(Center);
    path.lineTo(-a/2,0);
    path.lineTo(0,a/2*pow(3,0.5));
    path.lineTo(a/2,0);
    path.lineTo(0,-r1);
    path.lineTo(-a/2,0);
    painter.setBrush(QColor(0x03, 0xB7, 0xC9));
    painter.setPen(Qt::PenStyle::NoPen);
    painter.fillPath(path,QBrush(m_pointerColor));
//    painter.drawLine(-a/2,0,a/2,0);
//    painter.drawLine(-a/2,0,0,a/2*pow(3,0.5));
//    painter.drawLine(a/2,0,0,a/2*pow(3,0.5));

    painter.restore();
}

void QPDial::paintTitle(QPainter &painter)
{
    QPointF Center(width()/2.0,height()/2.0);
     float R=qMin(width(),height())/2.0;
     float r = R-m_dialFontHeight-m_largeScaleHeight-m_spaceRibbon-m_railRibbon;
     float a=r*0.2;//三角形的边长
     if(r<=0)return;
    painter.save();
        painter.translate(Center);
    //左边坐标
    QPointF p1(r*qCos((m_openAngle/2.0+90)*M_PI/180)
               ,r*qSin((m_openAngle/2.0+90)*M_PI/180));
      //右边坐标
    QPointF p2(r*qCos((90-m_openAngle/2.0)*M_PI/180)
               ,r*qSin((90-m_openAngle/2.0)*M_PI/180));




    painter.setBrush(Qt::BrushStyle::NoBrush);
    painter.setPen(m_strColor);



    QFont font(m_titleFontName,m_titleFontSize);
    painter.setFont(font);
    QFontMetrics metrics(painter.font());
   QString str= QString::number(m_value)+" "+m_unit;
    int fh=metrics.height();

    if(p1.y()<0){

        p1.setX(-Center.x());
        p1.setY(a/2*pow(3,0.5));
        p2.setX(Center.x());
        p2.setY(a/2*pow(3,0.5));
    }
    QPointF p3(p1);
    p3.setY(p1.y()+fh);
    QPointF p4(p2);
    p4.setY(p2.y()+fh);


    painter.drawText(QRectF(p1,QPointF(p2.x(),p4.y()))
                     , Qt::AlignCenter,str );
//    painter.drawRect(QRectF(p1,QPointF(p2.x(),p4.y())));
      QFontMetrics metricsTitle(painter.font());
    painter.drawText(QRectF(p3,QPointF(p4.x(),p4.y()+metricsTitle.height()))
                     , Qt::AlignCenter,m_Title );



    painter.restore();
}

void QPDial::setValue(float v)
{
    if(v<m_minV || v>m_maxV)return;
    m_TargeV = v;
    if(m_isAnimation){
         timer->stop();
        timer->start();
    }else{
        timer->stop();
        m_value=v;
    }

    update();
}

float QPDial::getValue()
{
    return m_TargeV;
}

int QPDial::setScaleCount(int count)
{
    int buf = m_scaleCount;
    m_scaleCount=count;
    update();
    return buf;
}

QString QPDial::setUnit(const QString &u)
{
    QString buf = m_unit;
    m_unit=u;
    update();
     return buf;
}

QString QPDial::setTitle(const QString &t)
{
      QString buf = m_Title;
      m_Title=t;
      update();
       return buf;



}

int QPDial::setSmallScaleCount(int count)
{
    int buf = m_smallScaleCount;
    m_smallScaleCount=count;
    update();
     return buf;
}

int QPDial::setFontSize(int size)
{
    int buf = m_fontSize;
    m_fontSize=size;
    update();
     return buf;
}

QString QPDial::setFontName(QString name)
{
    QString buf = m_fontName;
    m_fontName=name;
    update();
     return buf;
}

int QPDial::setTitleFontSize(int size)
{
    int buf = m_titleFontSize;
    m_titleFontSize=size;
    update();
     return buf;
}

QString QPDial::setTitleFontName(QString name)
{
    QString buf = m_titleFontName;
    m_titleFontName=name;
    update();
     return buf;
}

QColor QPDial::setStrColor(QColor color)
{
    QColor buf = m_strColor;
    m_strColor=color;
    update();
     return buf;
}

QColor QPDial::setScaleColor(QColor color)
{
    QColor buf = m_scaleColor;
    m_scaleColor=color;
    update();
     return buf;
}

QColor QPDial::setRailColor(QColor color)
{
    QColor buf = m_railColor;
    m_railColor=color;
    update();
     return buf;
}

QColor QPDial::setPointerColor(QColor color)
{
    QColor buf = m_pointerColor;
    m_pointerColor=color;
    update();
     return buf;
}

float QPDial::setStepRatio(float rat)
{
    float buf = m_stepRat;
    m_stepRat=rat;
    update();
     return buf;
}

bool QPDial::isAnimation(bool flag)
{
    bool buf = m_isAnimation;
    m_isAnimation=flag;
    update();
     return buf;
}

void QPDial::__TimerEvent()
{
    float step = (m_maxV - m_minV)*m_stepRat;
    if(m_TargeV>m_value){
            if(m_TargeV-m_value>step){
                m_value+=step;

            }else {
                m_value=m_TargeV;
                 timer->stop();
            }

    }else if(m_value >m_TargeV ){
        if(m_value-m_TargeV >step){
            m_value-=step;

        }else {
            m_value=m_TargeV;
            timer->stop();
        }

    }
    update();
}

float QPDial::setFontHeight(float h)
{
    float buf = m_dialFontHeight;
    m_dialFontHeight=h;
    update();
     return buf;
}

float QPDial::setLargeScaleHeight(float h)
{
    float buf = m_largeScaleHeight;
    m_largeScaleHeight=h;
    update();
     return buf;
}

float QPDial::setSmallScaleHeight(float h)
{
    float buf = m_smallScaleHeight;
    m_smallScaleHeight=h;
    update();
     return buf;
}

float QPDial::setSpaceRibbon(float h)
{
    float buf = m_spaceRibbon;
    m_spaceRibbon=h;
    update();
     return buf;
}

float QPDial::setRailRibbon(float h)
{
    float buf = m_railRibbon;
    m_railRibbon=h;
    update();
     return buf;
}

float QPDial::setOpenAngle(float ang)
{
    float buf = m_openAngle;
    m_openAngle=ang;
    update();
     return buf;
}

float QPDial::setMinV(float v)
{
    float buf = m_minV;
    m_minV=v;
    update();
     return buf;
}

float QPDial::setMaxV(float v)
{
    float buf = m_maxV;
    m_maxV=v;
    update();
     return buf;
}
