#include "Global_Function.h"

//角度转为弧度
float radians(float x)
{
    return x/180*3.1415926;
}

//弧度转为角度
float degree(float x)
{
    return x*180/3.1415926;
}

//计算向量vec绕任意轴axis逆时针旋转角度angle后的表达
QVector3D vec_rotate(QVector3D vec, QVector3D axis, float angle)
{
    axis.normalize();
    QVector3D result;
    float px = vec.x();
    float py = vec.y();
    float pz = vec.z();
    float ax = axis.x();
    float ay = axis.y();
    float az = axis.z();
    result.setX(px*cos(radians(angle)) + (ay*pz-az*py)*sin(radians(angle)) + ax*(ax*px+ay*py+az*pz)*(1-cos(radians(angle))));
    result.setY(py*cos(radians(angle)) + (az*px-ax*pz)*sin(radians(angle)) + ay*(ax*px+ay*py+az*pz)*(1-cos(radians(angle))));
    result.setZ(pz*cos(radians(angle)) + (ax*py-ay*px)*sin(radians(angle)) + az*(ax*px+ay*py+az*pz)*(1-cos(radians(angle))));
    return result;
}
