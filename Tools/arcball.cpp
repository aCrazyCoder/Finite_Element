#include "arcball.h"

ArcBall::ArcBall(float width, float height)
{
    this->StVec = QVector3D(0.0f,0.0f,0.0f);
    this->EnVec = QVector3D(0.0f,0.0f,0.0f);
    this->setBounds(width, height);
}

void ArcBall::click(const QPointF NewPt)
{
    this->mapToSphere(NewPt, &this->StVec);
}

void ArcBall::drag(const QPointF NewPt, QQuaternion* NewRot)
{
    this->mapToSphere(NewPt, &this->EnVec);

    if(NewRot)
    {
        QVector3D Perp;
        Perp = QVector3D::crossProduct(this->StVec, this->EnVec);

        if(Perp.length() > Epsilon)
        {
            NewRot->setX(Perp.x());
            NewRot->setY(Perp.y());
            NewRot->setZ(Perp.z());
            NewRot->setScalar(QVector3D::dotProduct(this->StVec, this->EnVec));
        }
        else
        {
            NewRot->setX(0.0f);
            NewRot->setY(0.0f);
            NewRot->setZ(0.0f);
            NewRot->setScalar(0.0f);
        }
    }
}

void ArcBall::mapToSphere(const QPointF NewPt, QVector3D* NewVec)
{
    QPointF TempPt;
    float length;
    TempPt = NewPt;

    TempPt.setX((TempPt.x() * this->AdjustWidth) - 1.0f);
    TempPt.setY(1.0f - (TempPt.y() * this->AdjustHeight));

    length = (TempPt.x() * TempPt.x()) + (TempPt.y() * TempPt.y());

    if(length > 1.0f)
    {
        float norm;
        norm = 1.0f / sqrtf(length);

        NewVec->setX(TempPt.x() * norm);
        NewVec->setY(TempPt.y() * norm);
        NewVec->setZ(0.0f);
    }
    else
    {
        NewVec->setX(TempPt.x());
        NewVec->setY(TempPt.y());
        NewVec->setZ(sqrtf(1.0f - length));
    }
}
