/*
 * brief:   主函数
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include "App\mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include "Global/Global_Function.h"
#include "Global/Global_Variable.h"
//#include "D:\Visual Leak Detector\include\vld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glutInit(&argc,argv);
    a.connect(&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));   //关闭主程序时，关闭所有子窗口

    QSplashScreen *m_splash = new QSplashScreen;                //设置启动界面
    m_splash->setPixmap(QPixmap(":/Image/Image/qidong.png"));
    m_splash->show();
    Qt::Alignment bottomleft = Qt::AlignBottom|Qt::AlignLeft;
    m_splash->showMessage("Loaded modules......",bottomleft,Qt::red);

    a.processEvents();

    MainWindow w;
    w.setMinimumSize(1680,1050);
    w.showMaximized();

    m_splash->finish(&w);
    delete m_splash;

    return a.exec();
}
