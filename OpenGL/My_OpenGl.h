#ifndef MY_OPENGL_H
#define MY_OPENGL_H

/*
 * brief:   OpenGL画图程序
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月14日
 * note：
 */

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QPainter>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QEvent>
#include <QMatrix4x4>
#include <QWindow>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QCursor>
#include <QDebug>
#include <QImage>
#include <QDateTime>
#include <QLinearGradient>
#include <QBrush>
#include <QMessageBox>
#include <QTextCodec>

#include "Lib\freeglut\freeglut.h"
#include "Global/Global_Variable.h"
#include "Information_OpenGL.h"
#include "Tools/arcball.h"

class my_OpenGL : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    explicit my_OpenGL(int width, int height, QWidget *parent = 0);
    ~my_OpenGL();

    void initializeGL()override;
    void resizeGL(int w,int h)override;
    void paintGL()override;

    void mouseMoveEvent(QMouseEvent *event)override;
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void keyPressEvent(QKeyEvent *event)override;
    void wheelEvent(QWheelEvent *event)override;

    void initialize_recovery(); //初始化恢复居中显示

    //网格显示设置
    bool gridDisplay;

    //控制图形显示总开关，只有在打开文件时变为true
    bool graphDisplay;

signals:
    void numChanged();

private:

    //设置OpenGL各种参数
    QOpenGLShader *m_vertex_shader;
    QOpenGLShader *m_fragment_shader;
    QOpenGLShaderProgram *m_program;

    unsigned int VBO[3];
    unsigned int VAO;
    unsigned int EBO;

    //model负责旋转，view负责平移和缩放
    QMatrix4x4 model;
    QMatrix4x4 view;
    QMatrix4x4 projection;

    //计算帧数
    quint64 m_frame;

    //设置参数
    float lastX;   //设置初始化位置
    float lastY;
    bool firstMouse;         //记录是否第一次移动鼠标，防止抖动
    float deltaTime;	        //记录当前帧与上一帧的时间差
    float lastFrame;          //记录上一次运行时间

    //记录光标形状
    QCursor cursor;

    //设置图形平移，旋转，缩放参数
    float x_translation;
    float y_translation;
    float scaleNum;
    float scaleAll_xAndy;

    //信息框
    Information_OpenGL *m_information;
    QString m_dataType;
    QString m_dataUnit;
    float m_iconPara;
    float m_iconParaLow;
    bool m_showIcon;

    //小坐标系
    enum{x_axis, y_axis, z_axis};
    void drawCylinder(int flag, float length, float radius);
    void drawCone(int flag, float position, float length, float radius);
    void drawCircle(int flag, float position, float radius);
    void drawCoordinate(float position, float length, float radius, float ratio);
    void drawSphere(float x_center, float y_center, float z_center, float radius, float M, float N);   //M，N分别表示球体的横纵向被分成多少份

    /*↓↓↓↓↓↓↓↓↓↓↓↓↓↓该版本中采用ArcBall方法↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/
    //上一次旋转矩阵
    QMatrix3x3 LastRot;
    //这次的旋转矩阵
    QMatrix3x3 ThisRot;
    //初始化
    ArcBall *m_arcball;
    bool isDragging = false;
    /*↑↑↑↑↑↑↑↑↑↑↑↑↑↑该版本中采用ArcBall方法↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑*/

    /*↓↓↓↓↓↓↓↓↓↓↓↓↓↓待传输数据↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓*/
    int *m_indices;
    QVector<float> m_nodeVector;
    QVector<float> m_colorVector;

    int windowHeight;
    int windowWidth;
    float coordinateSize;
    /*↑↑↑↑↑↑↑↑↑↑↑↑↑↑待传输数据↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑*/

    //显示线框设置
    QVector<float> m_lineVector;
    bool useLine;

public slots:

};



#endif // MY_OPENGL_H
