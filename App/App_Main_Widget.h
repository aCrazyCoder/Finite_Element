#ifndef APP_MAIN_WIDGET_H
#define APP_MAIN_WIDGET_H

/*
 * brief:   主控件布局
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月10日
 * note：
 */

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QStatusBar>
#include <QPushButton>
#include <QSpacerItem>
#include <QImage>
#include <QSizePolicy>
#include <QRect>
#include <QMessageBox>
#include <QDir>
#include <QDateTime>
#include <QTimer>
#include <QAction>
#include <QTabWidget>
#include <QGroupBox>
#include <QIcon>
#include <QPalette>
#include <QColor>
#include <QTableWidget>
#include <QHeaderView>
#include <QScrollBar>
#include <QSize>
#include <QFileDialog>

#include "OpenGL/My_OpenGl.h"
#include "Global/Global_Variable.h"
#include "Other/openmethod.h"

class App_Main_Widget : public QWidget
{
    Q_OBJECT
public:
    explicit App_Main_Widget(QWidget *parent = nullptr);
    ~App_Main_Widget();

    //主tab窗口
    QTabWidget *main_3D_window;

    QLabel *point_strain_Lab;
    QLabel *point_stress_Lab;
    QLabel *point_shift_Lab;

    my_OpenGL *demoOpenGL;
    my_OpenGL *gemoOpenGL;
    my_OpenGL *shiftOpenGL;
    my_OpenGL *strainOpenGL;
    my_OpenGL *stressOpenGL;

signals:
    void indexChanged(int index);

public slots:
    void screenShot();
    void numUpdate();
    void linkSlot(int a);
    void removeSubTab(int a);
    void setOpenGLWindow();
    void switchOpenGL(int index);
    void exportData();

private:
    QGroupBox *m_GroupBox_CalculationResults;
    QLabel *RatioLab;
    QLabel *RatioData;
    QTableWidget *m_table;

    QGroupBox *m_GroupBox_ScreenShot;
    QPushButton *screenshotBtn;
    QLabel *screenPic;

    QGroupBox *m_GroupBox_PointInformation;
    QLabel *point_Lab;
    QLabel *point_info_Lab_X;
    QLabel *point_info_Lab_Y;
    QLabel *point_info_Lab_Z;
    QLabel *point_strain_info_Lab;
    QLabel *point_shift_info_Lab;
    QLabel *point_stress_info_Lab;

    QHBoxLayout *main_Layout;
    QVBoxLayout *right_Layout;
    QGridLayout *CalculationResults_Layout;
    QGridLayout *PointInformation_Layout;
    QVBoxLayout *ScreenShot_Layout;

    openMethod *m_openMethod;

    void calculateRatio();

};

#endif // APP_MAIN_WIDGET_H
