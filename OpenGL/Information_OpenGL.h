#ifndef INFORMATION_OPENGL_H
#define INFORMATION_OPENGL_H

/*
 * brief:   OpenGL图形信息
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年3月23日
 * note：
 */

#include <QWidget>
#include <QBrush>
#include <QMessageBox>
#include <QPainter>
#include <QDate>
#include <QStyleOption>
#include <QBitmap>
#include <QPalette>
#include <QDebug>

class Information_OpenGL : public QWidget
{
    Q_OBJECT
public:
    explicit Information_OpenGL(int h, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *)override;

    void setPara(float iconData, float iconDataLow, QString dataType, QString dataUnit, bool Icon);

    float m_FPS;

private:
    //二维平面背景画笔画刷
    QFont textFont;
    QPen textPen;
    QBrush backgroundBrush;
    QPen backgroundPen;
    QBrush iconBrush;
    QPen iconPen;
    QFont iconFont;

    //二维画图参数
    double iconPara;
    double iconParaLow;

    //定义信息框的高度
    int height;

    //定义显示内容
    QString type;
    QString unit;
    bool showIcon;


signals:

public slots:
};

#endif // INFORMATION_OPENGL_H
