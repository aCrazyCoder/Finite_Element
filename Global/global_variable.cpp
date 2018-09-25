#include "Global_Variable.h"

QDir dir;
QString srcpath = dir.currentPath();

int ModelInfo_class = 0;
int ModelInfo_segmentation_point = 4;
int ModelInfo_segmentation_body = 4;
int ModelInfo_AllNode = 0;
int ModelInfo_AllElement = 0;
float ModelInfo_MaxStrain = 0.00;       //应变
float ModelInfo_MinStrain = 0.00;
float ModelInfo_MaxShift = 0.00;        //位移
float ModelInfo_MinShift = 0.00;
float ModelInfo_MaxStress = 0.00;       //应力
float ModelInfo_MinStress = 0.00;

qint64 screenshot_Num = 0;
QImage screenshot_Img;

double World_x = 0.000;
double World_y = 0.000;
double World_z = 0.000;

float current_Strain = 0.0;
float current_Shift = 0.0;
float current_Stress = 0.0;

double Strain_Data = 0.00;
double Amp_Data = 0.00;
double Ratio_Data = 0.00;

int rxData = 0;

double mouseMoveSensitivity = 0.5;
double mouseWheelSensitivity = 90.0;
double keyboardMoveSensitivity = 2.50;

QStringList list;
int listIndex = 0;

QVector<float> nodeVector;     //节点容器
QVector<int> elementVector;     //元素容器
int *indices = new int[1];  //初始化;
QVector<float> shiftVector;
QVector<float> strainVector; //应变数据
QVector<float> stressVector; //应变数据
int dataType = 0;
unsigned int color[] = {
    255, 0,   0,                //颜色索引，由红到蓝
    255, 178, 0,
    255, 255, 0,
    178, 255, 0,
    0,   255, 0,
    0,   255, 178,
    0,   255, 255,
    0,   178, 255,
    0,   0,   255
};

bool isGeomfileExist = false;
bool isWeiyiFileExist = false;
bool isYingbianFileExist = false;
bool isYingliFileExist = false;

float coordinateRange_Down = 0.0f;
float coordinateRange_Up = 0.0f;

QString shiftUnit;
QString strainUnit;
QString stressUnit;

QString ProjectName = QString::fromLocal8Bit("新工程");
