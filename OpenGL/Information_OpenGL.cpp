#include "Information_OpenGL.h"

Information_OpenGL::Information_OpenGL(int h, QWidget *parent) : QWidget(parent)
{
    height = h;
    setAttribute(Qt::WA_TranslucentBackground, true);
    resize(290, height);
    setWindowFlag(Qt::FramelessWindowHint);      //隐藏窗口标题栏

    iconPara = 0.0f;
    showIcon = false;
    m_FPS = 0.0;
}

void Information_OpenGL::paintEvent(QPaintEvent *)
{

    QPainter m_paint;
    m_paint.begin(this);
    m_paint.setRenderHint(QPainter::Antialiasing);
    textFont.setPixelSize(30);
    textFont.setWeight(QFont::Bold);
    textPen = QPen(Qt::black);
    m_paint.setPen(textPen);
    m_paint.setFont(textFont);
    m_paint.drawText(20,30,QString("Static Structural"));

    textFont.setPixelSize(20);
    textFont.setWeight(QFont::Medium);
    m_paint.setPen(textPen);
    m_paint.setFont(textFont);
    m_paint.drawText(20,50,QString("Type:%1").arg(type));
    m_paint.drawText(20,70,QString("Unit:%1").arg(unit));
    m_paint.drawText(20,90,QString("Time:1"));
    m_paint.drawText(20,110,QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm"));

    if(showIcon)
    {
        iconPen = QPen(Qt::black);
        iconPen.setWidth(2);
        m_paint.setPen(iconPen);
        iconFont.setPixelSize(20);
        iconFont.setWeight(QFont::Bold);
        m_paint.setFont(iconFont);
        iconBrush = QBrush(QColor(255, 0, 0));

        m_paint.fillRect(QRect( 20, 150, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 150, 30, 30));
        m_paint.drawText( 60, 155,QString("%1 Max").arg(iconPara));

        iconBrush.setColor(QColor(255, 178, 0));
        iconFont.setWeight(QFont::Medium);
        m_paint.setFont(iconFont);
        m_paint.fillRect(QRect( 20, 180, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 180, 30, 30));
        m_paint.drawText( 60, 185,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*1.0));

        iconBrush.setColor(QColor(255, 255, 0));
        m_paint.fillRect(QRect( 20, 210, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 210, 30, 30));
        m_paint.drawText( 60, 215,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*2.0));

        iconBrush.setColor(QColor(178, 255, 0));
        m_paint.fillRect(QRect( 20, 240, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 240, 30, 30));
        m_paint.drawText( 60, 245,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*3.0));

        iconBrush.setColor(QColor(0, 255, 0));
        m_paint.fillRect(QRect( 20, 270, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 270, 30, 30));
        m_paint.drawText( 60, 275,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*4.0));

        iconBrush.setColor(QColor(0, 255, 178));
        m_paint.fillRect(QRect( 20, 300, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 300, 30, 30));
        m_paint.drawText( 60, 305,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*5.0));

        iconBrush.setColor(QColor(0, 255, 255));
        m_paint.fillRect(QRect( 20, 330, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 330, 30, 30));
        m_paint.drawText( 60, 335,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*6.0));

        iconBrush.setColor(QColor(0, 178, 255));
        m_paint.fillRect(QRect( 20, 360, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 360, 30, 30));
        m_paint.drawText( 60, 365,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*7.0));

        iconBrush.setColor(QColor(0, 0, 255));
        m_paint.fillRect(QRect( 20, 390, 30, 30), iconBrush);
        m_paint.drawRect(QRect( 20, 390, 30, 30));
        m_paint.drawText( 60, 395,QString("%1").arg(iconPara-(iconPara-iconParaLow)/9.0*8.0));

        iconFont.setWeight(QFont::Bold);
        m_paint.setFont(iconFont);
        m_paint.drawText( 60, 425,QString("%1 Min").arg(iconParaLow));

        m_paint.drawText(20, 460, QString("FPS:%1").arg(m_FPS, 0, 'f', 2, 0));

        m_paint.end();
    }
    else
    {
        m_paint.drawText(20, 145, QString("FPS:%1").arg(m_FPS, 0, 'f', 2, 0));

        m_paint.end();
    }


    update();
}

void Information_OpenGL::setPara(float iconData, float iconDataLow, QString dataType, QString dataUnit, bool Icon)
{
    iconPara = (double)iconData;
    iconParaLow = (double)iconDataLow;
    type = dataType;
    unit = dataUnit;
    showIcon = Icon;
}
