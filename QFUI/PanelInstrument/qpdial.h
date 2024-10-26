#ifndef QPDIAL_H
#define QPDIAL_H
/***
 * 声明本控件参考了大佬“飞扬青云“的样品展示
 * 意义：他本人的没有提供代码，因此本人复刻一个
 * 展示样品来源：https://pan.baidu.com/s/1A5Gd77kExm8Co5ckT51vvQ#list/path=%2F
 *
 *
 *
 * 授权使用，代码及工程都可以拿去随意使用和修改，但要求代码保留来源
 *
 *
*/
#include <QObject>
#include <QWidget>

class QPDial:public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);
public:
    QPDial(QWidget *parent);


private:
    void initVar();

    //表盘属性
     float m_dialFontHeight;//字体的高度
     float m_largeScaleHeight ;// 大的刻度高度
     float m_smallScaleHeight ;// 大的刻度高度
     float m_spaceRibbon;//刻度到导轨的空间带宽度
     float m_railRibbon;//导轨带的宽度
     qreal m_openAngle;//底下开口角度(角度制)
     float m_minV=0;// 仪表最小值
     float m_maxV=100;//仪表最大值
     float m_value=0;//当前值
     float m_TargeV =80;//目标值
    float m_scaleCount=10;//多少个 刻度
    QString m_unit="V";
    QString m_Title=" 电压表";
    int m_smallScaleCount=4;//小刻度数
    int m_fontSize=16;
    QString m_fontName="Arial";
    int m_titleFontSize=24;
    QString m_titleFontName="Arial";
    QColor m_strColor=QColor(0x03, 0xB7, 0xC9);//字符颜色
    QColor m_scaleColor=QColor(0x03, 0xB7, 0xC9);//刻度颜色
    QColor m_railColor=QColor(0x39,0x3f,0x4d,0xff);//轨道颜色
    QColor m_pointerColor=QColor(0x03, 0xB7, 0xC9);//指针颜色
    QTimer *timer;          //绘制定时器
    float m_stepRat=0.02;//动画延时步进比例，每次站总长度的大小
    bool m_isAnimation=true;


    void paintRail(QPainter&painter);
    void paintScaleW(QPainter&painter);
    void paintScale(QPainter&painter);
    void paintPointer(QPainter&painter);
    void paintTitle(QPainter&painter);



private slots:
    void __TimerEvent();
    signals:

public:
    //用户接口
    //设置刻度字符所用的空间高度，返回旧的高度
    float setFontHeight(float h);
    //设置大刻度的长度，返回旧的长度
    float setLargeScaleHeight(float h);
    //设置小刻度的长度，返回就的长度
    float setSmallScaleHeight(float h);
    //设置导轨和宽度之间的空间，返回旧的空间宽度
    float setSpaceRibbon(float h);
    //设置导轨的宽度，返回就的宽度
    float setRailRibbon(float h);
    //设置开口角度，返回旧的角度
    float setOpenAngle(float ang);
    //设置最小值。返回旧的最小值
    float setMinV(float v);
    //设置最大值。返回旧的最大值
    float setMaxV(float v);
    //设置当前值
     void setValue(float v);
     //获取当前值
      float getValue();
    //设置刻度数，返回旧的刻度数
    int setScaleCount(int count);
    //设置数值单位，返回旧的单位
    QString setUnit(const QString& u);
    //设置标识，返回旧的标识标题
    QString setTitle(const QString& t);
    //设置小的刻度数，返回旧的刻度数
    int setSmallScaleCount(int count);
    //设置刻度的字体大小，返回旧的字体大小
    int setFontSize(int size);
    //设置刻度的字体名称。返回旧的字体名称
    QString setFontName(QString name);
    //设置标题的字体大小。返回旧的字体大小
    int setTitleFontSize(int size);
    //设置标题的字体名称。返回旧的字体名称
    QString setTitleFontName(QString name);
    //设置字符的颜色，返回旧的颜色
    QColor setStrColor(QColor color);
    //设置刻度的颜色。返回旧的颜色
    QColor setScaleColor(QColor color);
    //设置轨道的颜色。返回旧的颜色
    QColor setRailColor(QColor color);
    //设置指针的颜色。返回旧的颜色
    QColor setPointerColor(QColor color);
    //设置动画每个周期前进比例（相对于 （最大值-最小值）的比例），返回旧的比例
    float setStepRatio(float rat);
    //是否开启动画，返回旧的状态
    bool isAnimation(bool flag);
};

#endif // QPDIAL_H
