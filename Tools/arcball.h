#ifndef ARCBALL_H
#define ARCBALL_H

#include "assert.h"
#include <QVector3D>
#include <QPointF>
#include <QQuaternion>

# define Epsilon 1.0e-5

class ArcBall
{
public:
    ArcBall(float width, float height);
    ~ArcBall();

    void setBounds(float NewWidth, float NewHeight)
    {
        assert((NewWidth > 1.0f) && (NewHeight > 1.f));
        this->AdjustWidth = 1.0f / ((NewWidth - 1.0f) * 0.5f);
        this->AdjustHeight = 1.0f / ((NewHeight - 1.0f) * 0.5f);
    }

    void click(const QPointF NewPt);
    void drag(const QPointF NewPt, QQuaternion *NewRot);

protected:
    void mapToSphere(const QPointF NewPt, QVector3D *NewVec);
    QVector3D StVec;
    QVector3D EnVec;
    float AdjustWidth;
    float AdjustHeight;
};

#endif // ARCBALL_H
