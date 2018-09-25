#ifndef HLED_H
#define HLED_H

/*
 * brief:   LED工具
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月10日
 * note：
 */

#include <QWidget>
#include <QSize>

class QColor;

class HLed : public QWidget
{
    Q_OBJECT
public:
    HLed(QWidget *parent = 0);
    ~HLed();

    QColor color() const;
    bool on() const;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

public slots:
    void setColor(const QColor &color);
    void toggle();
    void turnOn(bool on=true);
    void turnOff(bool off=true);

protected:
    void paintEvent(QPaintEvent*);
    int ledWidth() const;

private:
    struct Private;
    Private * const m_d;
};

#endif // HLED_H
