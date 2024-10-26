#include "qradar.h"
#include <QPainter>
#include <QTimer>
QRadar::QRadar(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    timer->setInterval(100);
    connect(timer, &QTimer::timeout, this, &QRadar::__TimerEvent);
     timer->start();

}

void QRadar::setTimeCycle(int ms)
{

    timer->setInterval(ms);
    timer->stop();
    timer->start();
}

void QRadar::setStepAng(float ang)
{
    if(ang<=0)return;
    m_stepAng=ang;
}

void QRadar::setDirection(int d)
{
    m_direction=d;
}

void QRadar::__TimerEvent()
{
        if(1 ==m_direction){
            if(m_curentAng<360){
                    m_curentAng+=m_stepAng;
                    if(m_curentAng>360)m_curentAng=360;
            }else{
                m_curentAng=0;
            }
        }
        else if(0 ==m_direction ){
            if(0<m_curentAng){
                    m_curentAng-=m_stepAng;
                    if(m_curentAng<0)m_curentAng=0;

            }else{
                m_curentAng=360;
            }

        }
        update();
}

void QRadar::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.save();


    float R= qMin(height(),width())/2.0-8;
    QRectF crect(0,0,width(),height());
    //设置裁切区域
        QPainterPath path;

        float radius=R/5.0;
        path.addEllipse(crect.center(), radius,radius);  //绘制裁切区域的大小
        paint.setPen(QPen(QColor(0xff,0,0,0xff),1.0,Qt::PenStyle::DashDotLine));
//        paint.drawLine(0,height()/2.0,width(),height()/2.0);
//        paint.drawLine(width()/2.0,0,width()/2.0,height());
//        paint.drawPath(path);
        paint.setClipPath(path);  //设置裁切区域，设置后，图片只显示设定的裁切区域内容

        // 指定绘制的矩形区域
                QRect targetRect(width()/2.0-radius, height()/2.0-radius, radius*2,radius*2); // 替换为你需要的矩形区域


     // 绘制缩放后的图片
     paint.drawImage(targetRect, src);
//        paint.drawPixmap(0,0,pix);

    paint.restore();
     paint.save();
//    QPainterPath path_circular;
//    path_circular.addEllipse(crect.center(), radius,radius);  //绘制裁切区域的大小
//     paint.setClipPath(path_circular);  //裁剪一个有效圆部分
        QPointF po=crect.center();
        // 创建一个区域，包含外圆

        float outOffset=100;
        QRegion outerCircle(po.x()-R-outOffset,po.y()-R-outOffset, po.x()+R+outOffset,po.y()+R+outOffset, QRegion::Ellipse);

        // 创建内圆区域
        QRegion innerCircle(targetRect, QRegion::Ellipse);
//        QPainterPath path1;
//        path1.addRegion(innerCircle);
//           paint.drawPath(path1);

//          paint.setClipRegion(innerCircle, Qt::ReplaceClip); // 从剪裁区域中减去内圆
        // 从外圆区域中减去内圆区域
         outerCircle = outerCircle.subtracted(innerCircle);
         // 设置剪裁区域
         paint.setClipRegion(outerCircle);


        // 创建锥形渐变，指定中心点和起始角度
        QConicalGradient conicalGradient(width() / 2,height() / 2, m_curentAng);  // 0度开始

        // 设置颜色点
        if(0==m_direction){
            conicalGradient.setColorAt(0.0, QColor(0xa8,0xd5,0xd7,0xA0));      //
            conicalGradient.setColorAt(1.0, QColor(0xa8,0xd5,0xd7,0x00));      //
        }
        else{
            conicalGradient.setColorAt(1.0, QColor(0xa8,0xd5,0xd7,0xA0));      //
            conicalGradient.setColorAt(0.0, QColor(0xa8,0xd5,0xd7,0x00));      //
        }

        QBrush brush(conicalGradient);
        paint.setBrush(brush);
//        paint.setPen(Qt::NoPen);
        paint.setPen(QPen(conicalGradient,5.0));
//          paint.drawLine(0,0,width(),height());

//        QRectF rect(0,0,width(),height());
        // 绘制一个圆形区域

        paint.drawEllipse(po.x()-R,po.y()-R,2*R,2*R);

//         paint.drawEllipse(0,0,-100,-100);
     paint.restore();
    //在绘制前部线
          paint.save();
          paint.translate(po);
           paint.rotate(-m_curentAng);
           conicalGradient.setCenter(0,0);
           conicalGradient.setAngle(0);
           paint.setPen(QPen(conicalGradient,8.0));
           paint.setBrush(Qt::BrushStyle::NoBrush);
          if(0== m_direction){

              paint.drawLine(R-5,-4,radius+5,-4);
          }else{


              paint.drawLine(R-5,4,radius+5,4);

          }



          paint.restore();
}
