#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * brief:   主窗口布局
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include <QMainWindow>
#include <QLabel>
#include <QAction>
#include <QIcon>
#include <QString>
#include <QMenu>
#include <QToolBar>
#include <QMenuBar>
#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QApplication>
#include <QAxWidget>
#include <QAxObject>
#include <QStringListIterator>
#include <QSettings>
#include <QTextCodec>

#include "App/App_Main_Widget.h"
#include "Dialog/Dialog_ModelInformation.h"
#include "Dialog/Dialog_AppSetting.h"
#include "Global/Global_Variable.h"
#include "Other/projectname.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();    //创建动作
    void createMenus();      //创建菜单
    void createToolBars();    //创建工具栏
    void closeEvent(QCloseEvent *event);

public slots:
    void timeUpdate();
    void openFile();
    void printFile();
    void informationDialog();
    void openWord();
    void aboutApp();
    void settingDialog();
    void changeUnit();
    void changeGridState(int index);

private slots:
    void linkSlot();

signals:
    void slotNum(int a);
    void updateData();
    void readDataFinished();

protected:

private:
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *informationMenu;
    QMenu *helpMenu;
    QMenu *settingMenu;

    App_Main_Widget *showWidget;

    QAction *openFileAction;  //文件菜单项
    QAction *printAction;
    QAction *exportAction;
    QAction *exitAction;

    QAction *zoomInAction;    //编辑菜单项
    QAction *zoomOutAction;
    QAction *moveAction;
    QAction *undoAction;
    QAction *redoAction;

    QAction *upAction;
    QAction *downAction;
    QAction *leftAction;
    QAction *rightAction;
    QAction *middleAction;
    QAction *showGridAction;

    QAction *informationAction;  //模型信息菜单项

    QAction *helpAction;   //帮助菜单项
    QAction *aboutAction;

    QToolBar *fileTool;
    QToolBar *editTool;
    QToolBar *doTool;
    QToolBar *ratioTool;

    QLabel *currentTimeLable;
    QTimer *currentTime;

    QAction *ratioCalculate;

    QAction *unitConvertion;
    QAction *appSetting;
    QAction *weiyi_m;
    QAction *weiyi_mm;
    QAction *weiyi_μm;
    QAction *yingli_GPa;
    QAction *yingli_MPa;
    QAction *yingli_KPa;
    QAction *yingbian_ε;
    QAction *yingbian_με;

    void writeSettings();
    void readSettings();

    void readGeometryFileData();
    void readWeiyiFileData();
    void readYingbianFileData();
    void readYingliFileData();
    QFile file;
};

#endif // MAINWINDOW_H
