#ifndef GLOBAL_FUNCTION_H
#define GLOBAL_FUNCTION_H

/*
 * brief:   全局函数的声明文件
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include <QVector3D>

float radians(float x);
float degree(float x);
QVector3D vec_rotate(QVector3D vec, QVector3D axis, float angle);

#endif // GLOBAL_FUNCTION_H

