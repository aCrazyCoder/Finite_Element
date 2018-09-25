#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

/*
 * brief:   全局变量的声明文件
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include "qglobal.h"
#include <QImage>
#include <QVector3D>
#include <QDir>
#include <QString>

//宏定义
#ifndef PI
#define PI        3.1415926
#endif
#ifndef MAX_CHAR
#define MAX_CHAR  128
#endif

//当前工程目录
extern QString srcpath;

//应力位移等模型参数列表
extern int ModelInfo_class;
extern int ModelInfo_segmentation_point;
extern int ModelInfo_segmentation_body;
extern int ModelInfo_AllNode;
extern int ModelInfo_AllElement;
extern float ModelInfo_MaxStrain;       //应变
extern float ModelInfo_MinStrain;
extern float ModelInfo_MaxShift;        //位移
extern float ModelInfo_MinShift;
extern float ModelInfo_MaxStress;       //应力
extern float ModelInfo_MinStress;

//截图顺序号
extern qint64 screenshot_Num;
//截图图片
extern QImage screenshot_Img;

//定义三维图形中的世界坐标
extern double World_x;
extern double World_y;
extern double World_z;

//定义当前点位移与应力应变大小
extern float current_Strain; //应变
extern float current_Shift;  //位移
extern float current_Stress; //应力

//定义实时叶尖振幅和叶片应力，比例系数
extern double Strain_Data;
extern double Amp_Data;
extern double Ratio_Data;

//串口接受数据
extern int rxData;

//鼠标参数设置
extern double mouseMoveSensitivity;
extern double mouseWheelSensitivity;
extern double keyboardMoveSensitivity;

//文件保存路径列表和列表索引
extern QStringList list;
extern int listIndex;

//导入数据容器
extern QVector<float> nodeVector;  //节点容器
extern QVector<int> elementVector;  //元素容器
extern int *indices;
extern unsigned int color[];        //颜色存储
extern QVector<float> shiftVector;  //位移数据
extern QVector<float> strainVector; //应变数据
extern QVector<float> stressVector; //应变数据
extern int dataType;  //数据类型

//文件标签
extern bool isGeomfileExist;
extern bool isWeiyiFileExist;
extern bool isYingbianFileExist;
extern bool isYingliFileExist;

/*
*根据数据应获取的一些基本信息
*/
//几何形状数据的范围，已确定OpenGL中画布的大小，与视野的大小
extern float coordinateRange_Up;
extern float coordinateRange_Down;
//数据单位
extern QString shiftUnit;
extern QString strainUnit;
extern QString stressUnit;

//工程名称
extern QString ProjectName;

#endif // GLOBAL_VARIABLE_H
