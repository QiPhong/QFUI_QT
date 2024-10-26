#ifndef QBATTERY_H
#define QBATTERY_H

/***
 * 声明本控件参考了大佬“飞扬青云“的代码
 * 意义：他本人的没有竖着的电池，顾本人做了一个
 * 参考代码来源：https://github.com/feiyangqingyun/QWidgetDemo
 *
 *
 *
 * 授权使用，代码及工程都可以拿去随意使用和修改，但要求代码保留来源
 *
 *
*/






#include <QWidget>


class QBattery : public QWidget
{
    Q_PROPERTY(float minValue READ getMinValue WRITE setMinValue)
    Q_PROPERTY(float maxValue READ getMaxValue WRITE setMaxValue)
     Q_PROPERTY(float m_TargeV READ getValue WRITE setValue)
public:
    explicit QBattery(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);

public Q_SLOTS:
    void setValue(int value);
private slots:
    void __TimerEvent();

private:
//属性控制
    //#1 边框属性
    float m_borderLineW=5;//边框的线宽
    float m_borderRadius=8;// 圆角矩形的半径
    QColor m_borderColor=QColor(0xA0,0XB1,0XB2,0xFF);
    //#1.2 电池顶部属性
    float m_Proportion_H=0.05;//顶端正极头占比
    float m_Proportion_W=0.3;//电池头部宽度占比
    float m_borderTRadius=5;// 圆角矩形的半径


//公共属性

    float m_maxV=100;    //最大值
    float m_minV = 0;    //最小值
    float m_cerrentV=0;//当前值
    float m_TargeV=100;
    QTimer *timer;          //绘制定时器
    float m_stepRat=0.01;//动画延时步进比例，每次站总长度的大小
    bool m_isAnimation=true;


    //内部属性
    //#1.1背景颜色
    QColor m_internalColor1=QColor(0x00,0X70,0X00,0xFF);
    QColor m_internalColor2=QColor(0x00,0XE1,0X00,0xFF);
     float m_capRadius=5;// 圆角矩形的半径
    float m_capCollapse= m_borderRadius;//向内坍缩




public:
//对外接口


    //获取和设置最小值
    float getMinValue() const;
    void setMinValue(float minValue);

    //获取和设置最大值
    float getMaxValue() const;
    void setMaxValue(float maxValue);

    //获取和设置电池电量值
    float getValue() const;
    void setValue(float value);
    //设置外框线宽（返回旧的线宽）
    float setBorderLineWidth(float w);
    //设置外框圆角矩形 半径（返回旧的半径）
    float setBorderRadius(float r);
    //设置外框颜色 半径（返回旧的颜色）
    QColor setBorderColor(QColor color);
    //设置电池头部高度占比（返回旧的比例）
    float setProportionHeightRatio(float ato);
    //设置电池头部宽度占比（返回旧的比例）
    float setProportionWidthRatio(float ato);
    //设置外框头部圆角矩形 半径（返回旧的半径）
    float setBorderTRadius(float r);
    //设置动画每个周期前进比例（相对于 （最大值-最小值）的比例），返回旧的比例
    float setStepRatio(float rat);
    //是否开启动画，返回旧的状态
    bool isAnimation(bool flag);
    //设置内部渐变颜色
    void setInternalColor(QColor c1,QColor c2);
    //设置内部圆角矩形 半径（返回旧的半径）
    float setCapRadius(float r);
    //设置内部坍缩大小,返回旧的坍缩值
    float setCapCollapse(float cc);

Q_SIGNALS:
    void valueChanged(float value);


    signals:
};

#endif // QBATTERY_H
