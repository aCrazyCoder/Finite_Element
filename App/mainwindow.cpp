#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QString::fromLocal8Bit("有限元融合模块"));
    setWindowIcon(QIcon(":/Image/Image/icon.png"));
    showWidget = new App_Main_Widget(this);
    setCentralWidget(showWidget);
    connect(this, SIGNAL(readDataFinished()), showWidget, SLOT(setOpenGLWindow()));
    connect(showWidget, SIGNAL(indexChanged(int)), this, SLOT(changeGridState(int)));

    createActions();
    createMenus();
    createToolBars();

    currentTimeLable = new QLabel;
    currentTime = new QTimer(this);
    currentTime->start(1000);
    connect(currentTime,SIGNAL(timeout()),this,SLOT(timeUpdate()));
    QMainWindow::statusBar()->addWidget(currentTimeLable);          //创建状态栏

    readSettings();
}

MainWindow::~MainWindow()
{
    delete []indices;
}

void MainWindow::createActions()
{
    openFileAction = new QAction(this);
    openFileAction->setIcon(QIcon(":/Image/Image/open.png"));
    openFileAction->setText(QString::fromLocal8Bit("打开"));
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(QString::fromLocal8Bit("打开一个文件"));

    exportAction = new QAction(QIcon(":/Image/Image/Export_64px.png"),QString::fromLocal8Bit("导出数据"),this);
    exportAction->setShortcut(QKeySequence(tr("Ctrl+E")));
    exportAction->setStatusTip(QString::fromLocal8Bit("导出所有计算结果"));

    printAction = new QAction(QIcon(":/Image/Image/print.png"),QString::fromLocal8Bit("打印"),this);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(QString::fromLocal8Bit("以图片形式打印文件"));

    exitAction = new QAction(QIcon(":/Image/Image/exit.png"),QString::fromLocal8Bit("退出"),this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(QString::fromLocal8Bit("退出软件"));

    zoomInAction = new QAction(QIcon(":/Image/Image/Zoom_in.png"),QString::fromLocal8Bit("缩小"),this);
    zoomInAction->setStatusTip(QString::fromLocal8Bit("缩小视图"));
    zoomOutAction = new QAction(QIcon(":/Image/Image/Zoom_out.png"),QString::fromLocal8Bit("放大"),this);
    zoomOutAction->setStatusTip(QString::fromLocal8Bit("放大视图"));

    moveAction = new QAction(QIcon(":/Image/Image/move.png"),QString::fromLocal8Bit("移动"),this);
    moveAction->setStatusTip(QString::fromLocal8Bit("移动视图"));

    upAction = new QAction(QIcon(":/Image/Image/up_arrow.png"),QString::fromLocal8Bit("向上移动"),this);
    upAction->setStatusTip(QString::fromLocal8Bit("向上移动视图"));
    downAction = new QAction(QIcon(":/Image/Image/down_arrow.png"),QString::fromLocal8Bit("向下移动"),this);
    downAction->setStatusTip(QString::fromLocal8Bit("向下移动视图"));
    leftAction = new QAction(QIcon(":/Image/Image/left_arrow.png"),QString::fromLocal8Bit("向左移动"),this);
    leftAction->setStatusTip(QString::fromLocal8Bit("向左移动视图"));
    rightAction = new QAction(QIcon(":/Image/Image/right_arrow.png"),QString::fromLocal8Bit("向右移动"),this);
    rightAction->setStatusTip(QString::fromLocal8Bit("向右移动视图"));
    middleAction = new QAction(QIcon(":/Image/Image/Middle.png"),QString::fromLocal8Bit("屏幕中心显示"),this);
    middleAction->setStatusTip(QString::fromLocal8Bit("模型位于窗口中心初始化显示"));
    showGridAction = new QAction(QIcon(":/Image/Image/Grid_48px.png"),QString::fromLocal8Bit("显示网格"),this);
    showGridAction->setStatusTip(QString::fromLocal8Bit("显示或关闭网格"));
    showGridAction->setCheckable(true);

    undoAction = new QAction(QIcon(":/Image/Image/back.png"),QString::fromLocal8Bit("撤销"),this);
    undoAction->setStatusTip(QString::fromLocal8Bit("撤销上一次操作"));
    redoAction = new QAction(QIcon(":/Image/Image/forward.png"),QString::fromLocal8Bit("恢复"),this);
    redoAction->setStatusTip(QString::fromLocal8Bit("恢复上一次操作"));

    informationAction = new QAction(QIcon(":/Image/Image/information.png"),QString::fromLocal8Bit("模型信息"),this);
    informationAction->setStatusTip(QString::fromLocal8Bit("有限元模型信息"));

    helpAction = new QAction(QIcon(":/Image/Image/help.png"),QString::fromLocal8Bit("帮助"),this);
    helpAction->setStatusTip(QString::fromLocal8Bit("软件使用说明"));
    aboutAction = new QAction(QIcon(":/Image/Image/about.png"),QString::fromLocal8Bit("关于"),this);
    aboutAction->setStatusTip(QString::fromLocal8Bit("关于软件"));

    ratioCalculate = new QAction(QIcon(":/Image/Image/division.png"),QString::fromLocal8Bit("计算比例值"),this);
    ratioCalculate->setStatusTip(QString::fromLocal8Bit("选择应变点和位移点，计算比例值"));

    unitConvertion = new QAction(QIcon(":/Image/Image/unit.png"),QString::fromLocal8Bit("单位切换"),this);
    unitConvertion->setStatusTip(QString::fromLocal8Bit("当前图形单位切换"));
    appSetting = new QAction(QIcon(":/Image/Image/settings.png"),QString::fromLocal8Bit("软件设置"),this);
    appSetting->setStatusTip(QString::fromLocal8Bit("软件设置"));
    weiyi_m = new QAction(QString::fromLocal8Bit("米_m"));
    weiyi_mm = new QAction(QString::fromLocal8Bit("毫米_mm"));
    weiyi_μm = new QAction(QString::fromLocal8Bit("微米_μm"));
    yingli_GPa = new QAction(QString::fromLocal8Bit("吉帕_GPa"));
    yingli_KPa = new QAction(QString::fromLocal8Bit("千帕_KGa"));
    yingli_MPa = new QAction(QString::fromLocal8Bit("兆帕_MPa"));
    yingbian_ε = new QAction(QString::fromLocal8Bit("应变_ε"));
    yingbian_με = new QAction(QString::fromLocal8Bit("应变_με"));
    weiyi_mm->setIcon(QIcon(":/Image/Image/correct.png"));
    yingli_MPa->setIcon(QIcon(":/Image/Image/correct.png"));
    yingbian_ε->setIcon(QIcon(":/Image/Image/correct.png"));

    connect(openFileAction,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(exportAction, SIGNAL(triggered(bool)),showWidget,SLOT(exportData()));
    connect(printAction,SIGNAL(triggered(bool)),this,SLOT(printFile()));
    connect(exitAction,SIGNAL(triggered(bool)),qApp,SLOT(closeAllWindows()));
    connect(informationAction,SIGNAL(triggered(bool)),this,SLOT(informationDialog()));
    connect(helpAction,SIGNAL(triggered(bool)),this,SLOT(openWord()));
    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(aboutApp()));
    connect(middleAction,SIGNAL(triggered(bool)),this,SLOT(linkSlot()));
    connect(showGridAction, &QAction::toggled, [=](bool checked){showWidget->demoOpenGL->gridDisplay = checked;});
    connect(ratioCalculate,SIGNAL(triggered(bool)),this,SLOT(linkSlot()));
    connect(appSetting,SIGNAL(triggered(bool)),this,SLOT(settingDialog()));
    connect(this,SIGNAL(slotNum(int)),showWidget,SLOT(linkSlot(int)));

    connect(weiyi_m,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(weiyi_mm,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(weiyi_μm,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(yingli_GPa,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(yingli_KPa,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(yingli_MPa,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(yingbian_ε,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));
    connect(yingbian_με,SIGNAL(triggered(bool)),this,SLOT(changeUnit()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(QString::fromLocal8Bit("文件"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exportAction);
    fileMenu->addAction(printAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(QString::fromLocal8Bit("编辑"));
    editMenu->addAction(zoomInAction);
    editMenu->addAction(zoomOutAction);
    editMenu->addSeparator();
    editMenu->addAction(moveAction);

    informationMenu = menuBar()->addMenu(QString::fromLocal8Bit("信息"));
    informationMenu->addAction(informationAction);

    settingMenu = menuBar()->addMenu(QString::fromLocal8Bit("设置"));
    QMenu *subMenu_1 = settingMenu->addMenu(QIcon(":/Image/Image/unit.png"),QString::fromLocal8Bit("单位设置"));
    QMenu *subMenu_2_1 = subMenu_1->addMenu(QString::fromLocal8Bit("应力单位"));
    QMenu *subMenu_2_2 = subMenu_1->addMenu(QString::fromLocal8Bit("应变单位"));
    QMenu *subMenu_2_3 = subMenu_1->addMenu(QString::fromLocal8Bit("位移单位"));
    subMenu_2_1->addAction(yingli_GPa);
    subMenu_2_1->addAction(yingli_MPa);
    subMenu_2_1->addAction(yingli_KPa);
    subMenu_2_2->addAction(yingbian_ε);
    subMenu_2_2->addAction(yingbian_με);
    subMenu_2_3->addAction(weiyi_m);
    subMenu_2_3->addAction(weiyi_mm);
    subMenu_2_3->addAction(weiyi_μm);
    settingMenu->addAction(appSetting);

    helpMenu = menuBar()->addMenu(QString::fromLocal8Bit("帮助"));
    helpMenu->addAction(helpAction);
    helpMenu->addAction(aboutAction);  

}

void MainWindow::createToolBars()
{
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(printAction);
    fileTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);

    editTool = addToolBar("Edit");
    editTool->addAction(zoomInAction);
    editTool->addAction(zoomOutAction);
    editTool->addSeparator();
    editTool->addAction(upAction);
    editTool->addAction(downAction);
    editTool->addAction(leftAction);
    editTool->addAction(rightAction);
    editTool->addSeparator();
    editTool->addAction(middleAction);
    editTool->addAction(showGridAction);
    editTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);

    doTool = addToolBar("Operation");
    doTool->addAction(undoAction);
    doTool->addAction(redoAction);
    doTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);

    ratioTool = addToolBar("Ratio");
    ratioTool->addAction(ratioCalculate);
    ratioTool->setAllowedAreas(Qt::TopToolBarArea|Qt::LeftToolBarArea);

}

void MainWindow::timeUpdate()
{
    QDateTime CurrentTime = QDateTime::currentDateTime();
    QString Timestr = CurrentTime.toString("  yyyy-MM-dd  hh:mm:ss  "); // 设置显示的格式
    currentTimeLable->setText(Timestr);
}

void MainWindow::openFile()
{
    /*
    *首先设置工程名称
    */
    projectName *set = new projectName(this);
    set->show();
    while(set->exec());

    /*
    *一次性导入四个文件
    */
    QStringList s = QFileDialog::getOpenFileNames(this,QString::fromLocal8Bit("打开文件"),"/","Txt files(*.txt)");
    if(s.isEmpty())
        return;
    else
    {
        if((s.length() != 4))
        {
            QMessageBox::warning(this, tr("Read File"), QString::fromLocal8Bit("导入文件数量不符，请重新导入"));
            return;
        }

        else
        {
            statusBar()->showMessage(QString::fromLocal8Bit("正在载入文件······"),2000);
            for(int i = 0; i<4; i++)
            {
                QString curFile = QFileInfo(s.at(i)).fileName();
                if(curFile == "geometry.txt")
                {
                    isGeomfileExist = true;
                    file.setFileName(s.at(i));
                    file.open(QIODevice::ReadOnly);
                    readGeometryFileData();
                    file.close();
                }
                else if(curFile == "weiyi.txt")
                {
                    isWeiyiFileExist = true;
                    file.setFileName(s.at(i));
                    file.open(QIODevice::ReadOnly);
                    readWeiyiFileData();
                    file.close();
                }
                else if(curFile == "yingbian.txt")
                {
                    isYingbianFileExist = true;
                    file.setFileName(s.at(i));
                    file.open(QIODevice::ReadOnly);
                    readYingbianFileData();
                    file.close();
                }
                else if(curFile == "yingli.txt")
                {
                    isYingliFileExist = true;
                    file.setFileName(s.at(i));
                    file.open(QIODevice::ReadOnly);
                    readYingliFileData();
                    file.close();
                }
                else
                    return;
            }
            emit readDataFinished();
        }
    }
}

void MainWindow::printFile()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(screenshot_Img.isNull())
    {
        QMessageBox::warning(this, tr("Print Image"),QString::fromLocal8Bit("打印失败：该图片不存在!\n请点击保存图片后重试。"));
        printDialog.close();
    }
    else
    {
        if(printDialog.exec())
        {
            QPainter painter(&printer);
            QRect rect = painter.viewport();
            QSize size = screenshot_Img.size();
            size.scale(rect.size(),Qt::KeepAspectRatio);
            painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
            painter.setWindow(screenshot_Img.rect());
            painter.drawImage(0,0,screenshot_Img);
        }
    }
}

void MainWindow::informationDialog()
{
    Dialog_ModelInformation *info = new Dialog_ModelInformation;
    info->show();
}

void MainWindow::openWord()
{
    QString doc_path = srcpath;
    doc_path.remove("/build-Finite_Element-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug");
    doc_path = doc_path+"/Finite_Element/Document/";       //路径待修改！！！！！
    QAxWidget *word = new QAxWidget("Word.Application");                       //调用word组件
    word->setProperty("Visible", true);
    QAxObject *documents = word->querySubObject("Documents");                  //获取所有工作的文档
    documents->dynamicCall("Open(QString)",doc_path.append("help.docx"));
}

void MainWindow::aboutApp()
{
    QMessageBox::about(this,QString::fromLocal8Bit("关于软件"),QString::fromLocal8Bit("<h2>有限元融合软件 1.0</h2>"
                                                                                  "<p>Copyright &copy; 2018 ShanCe Technology Inc."
                                                                                  "<p>有限元融合软件是一个有限元后处理程序，主要进行三维应力应变云图和位移云图的显示，"
                                                                                  "并进行相关的图形操作以及数据分析。"));
}

void MainWindow::writeSettings()
{
    QSettings settings("Shao Inc.",QString::fromLocal8Bit("有限元融合模块"));   //组织的名字，应用程序的名称
    settings.setValue("geometry",saveGeometry());
    settings.setValue("screenshot_Num",screenshot_Num);
}

void MainWindow::readSettings()
{
    QSettings settings("Shao Inc.",QString::fromLocal8Bit("有限元融合模块"));   //组织的名字，应用程序的名称
    restoreGeometry(settings.value("geometry").toByteArray());
    screenshot_Num = settings.value("screenshot_Num").toLongLong();
}

void MainWindow::readGeometryFileData()
{
    if(!file.isOpen())
    {
        QMessageBox::warning(this, tr("Read File"),tr("Cannot open file"));
        return;
    }
    else
    {
        QTextStream dataIn(&file);
        dataIn.setCodec(QTextCodec::codecForLocale());
        QStringList stringLine;
        int info = 0;                    //标志位，用来判断信息

        QString str;
        str = dataIn.readLine(0);   //先读取第一行，判断文件类型是否正确

        if(str == "      0. Coordinates of each node")
        {
            do
            {
                str = dataIn.readLine();
                if(!str.isEmpty())
                {
                    if(str == "      0. Nodes No. of each element")
                    {
                        info = 1;
                        continue;
                    }
                    else
                    {
                        if(info == 0)   //处理节点数据
                        {
                            stringLine = str.split(" ", QString::SkipEmptyParts);
                            if(stringLine.count() == 4)
                                for(int i = 1; i < 4; i++)
                                {
                                    bool ok;
                                    str = stringLine.value(i);
                                    nodeVector.append(str.toFloat(&ok));
                                }
                            else
                            {
                                QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("文件数据格式不正确，请更换文件重试"));
                                break;
                            }
                        }
                        else if(info == 1)  //处理元素数据
                        {
                            str.replace(QString("."), QString(" "));
                            stringLine = str.split(" ", QString::SkipEmptyParts);
                            if(stringLine.count() == 5)
                                for(int i = 1; i < 5; i++)
                                {
                                    bool ok;
                                    str = stringLine.value(i);
                                    elementVector.append(str.toInt(&ok)-1);
                                }
                            else
                            {
                                QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("文件数据格式不正确，请更换文件重试"));
                                break;
                            }
                        }
                    }
                }
            }while(!str.isEmpty());

            ModelInfo_AllNode = nodeVector.count() / 3;
            ModelInfo_AllElement = elementVector.count() / 4;

            indices = new int[elementVector.count() * 3];   //每四个数据对应十二个索引值
            int j = 0;
            for(int i = 0; i<elementVector.count(); i = i+4)
            {
                indices[j++] = elementVector[i];
                indices[j++] = elementVector[i+1];
                indices[j++] = elementVector[i+2];
                indices[j++] = elementVector[i];
                indices[j++] = elementVector[i+1];
                indices[j++] = elementVector[i+3];
                indices[j++] = elementVector[i];
                indices[j++] = elementVector[i+2];
                indices[j++] = elementVector[i+3];
                indices[j++] = elementVector[i+1];
                indices[j++] = elementVector[i+2];
                indices[j++] = elementVector[i+3];
            }
            float tempMax = nodeVector[0];
            float tempMin = nodeVector[0];
            for(int i = 1; i < nodeVector.length(); i++)
            {
                if(nodeVector[i] > tempMax)
                    tempMax = nodeVector[i];
                if(nodeVector[i] < tempMin)
                    tempMin = nodeVector[i];
            }
            coordinateRange_Up = tempMax;
            coordinateRange_Down = tempMin;
        }
        else
            QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("打开文件类型不符，请尝试更换文件"));
    }
}

void MainWindow::readWeiyiFileData()
{
    if(!file.isOpen())
    {
        QMessageBox::warning(this, tr("Read File"),tr("Cannot open file"));
        return;
    }
    else
    {
        QTextStream dataIn(&file);
        dataIn.setCodec(QTextCodec::codecForLocale());
        QStringList stringLine;

        QString str;
        str = dataIn.readLine(0);   //先读取第一行，判断文件类型是否正确

        if(str.contains("Node Number	Total Deformation"))
        {
            shiftUnit = str.remove("Node Number	Total Deformation ");
            do
            {
                str = dataIn.readLine();
                if(!str.isEmpty())
                {
                    stringLine = str.split('\t', QString::SkipEmptyParts);
                    if(stringLine.count() == 2)
                    {
                        bool ok;
                        str = stringLine.at(1);
                        shiftVector.append(str.toFloat(&ok));
                    }
                    else
                    {
                        QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("文件数据格式不正确，请更换文件重试"));
                        break;
                    }
                }
            }while(!str.isEmpty());
            float tempMax = shiftVector[0];
            float tempMin = shiftVector[0];
            for(int i = 1; i < shiftVector.length(); i++)
            {
                if(shiftVector[i] > tempMax)
                    tempMax = shiftVector[i];
                if(shiftVector[i] < tempMin)
                    tempMin = shiftVector[i];
            }
            ModelInfo_MaxShift = tempMax;
            ModelInfo_MinShift = tempMin;
        }
        else
            QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("打开文件类型不符，请尝试更换文件"));
    }
}

void MainWindow::readYingbianFileData()
{
    if(!file.isOpen())
    {
        QMessageBox::warning(this, tr("Read File"),tr("Cannot open file"));
        return;
    }
    else
    {
        QTextStream dataIn(&file);
        dataIn.setCodec(QTextCodec::codecForLocale());
        QStringList stringLine;

        QString str;
        str = dataIn.readLine(0);   //先读取第一行，判断文件类型是否正确

        if(str.contains("Node Number	Equivalent Elastic Strain"))
        {
            strainUnit = str.remove("Node Number	Equivalent Elastic Strain ");
            do
            {
                str = dataIn.readLine();
                if(!str.isEmpty())
                {
                    stringLine = str.split('\t', QString::SkipEmptyParts);
                    if(stringLine.count() == 2)
                    {
                        bool ok;
                        str = stringLine.at(1);
                        strainVector.append(str.toFloat(&ok));
                    }
                    else
                    {
                        QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("文件数据格式不正确，请更换文件重试"));
                        break;
                    }
                }
            }while(!str.isEmpty());
            float tempMax = strainVector[0];
            float tempMin = strainVector[0];
            for(int i = 1; i < strainVector.length(); i++)
            {
                if(strainVector[i] > tempMax)
                    tempMax = strainVector[i];
                if(strainVector[i] < tempMin)
                    tempMin = strainVector[i];
            }
            ModelInfo_MaxStrain = tempMax;
            ModelInfo_MinStrain = tempMin;
        }
        else
            QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("打开文件类型不符，请尝试更换文件"));
    }
}

void MainWindow::readYingliFileData()
{
    if(!file.isOpen())
    {
        QMessageBox::warning(this, tr("Read File"),tr("Cannot open file"));
        return;
    }
    else
    {
        QTextStream dataIn(&file);
        dataIn.setCodec(QTextCodec::codecForLocale());
        QStringList stringLine;

        QString str;
        str = dataIn.readLine(0);   //先读取第一行，判断文件类型是否正确

        if(str.contains("Node Number	Equivalent (von-Mises) Stress"))
        {
            stressUnit = str.remove("Node Number	Equivalent (von-Mises) Stress ");
            do
            {
                str = dataIn.readLine();
                if(!str.isEmpty())
                {
                    stringLine = str.split('\t', QString::SkipEmptyParts);
                    if(stringLine.count() == 2)
                    {
                        bool ok;
                        str = stringLine.at(1);
                        stressVector.append(str.toFloat(&ok));
                    }
                    else
                    {
                        QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("文件数据格式不正确，请更换文件重试"));
                        break;
                    }
                }
            }while(!str.isEmpty());
            float tempMax = stressVector[0];
            float tempMin = stressVector[0];
            for(int i = 1; i < stressVector.length(); i++)
            {
                if(stressVector[i] > tempMax)
                    tempMax = stressVector[i];
                if(stressVector[i] < tempMin)
                    tempMin = stressVector[i];
            }
            ModelInfo_MaxStress = tempMax;
            ModelInfo_MinStress = tempMin;
        }
        else
            QMessageBox::warning(this, QString::fromLocal8Bit("打开文件"), QString::fromLocal8Bit("打开文件类型不符，请尝试更换文件"));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button = QMessageBox::question(this, QString::fromLocal8Bit("退出程序"),
                                   QString::fromLocal8Bit("确认退出程序?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if (button == QMessageBox::No)
    {
        event->ignore();  //忽略退出信号，程序继续运行
    }
    else if (button == QMessageBox::Yes)
    {
        writeSettings();
        qApp->closeAllWindows();
        event->accept();  //接受退出信号，程序退出
    }
}

//连接槽函数
void MainWindow::linkSlot()
{
    QAction *action = dynamic_cast<QAction*>(sender());
    if(action == middleAction)
        emit slotNum(1);
    else if(action == ratioCalculate)
        emit slotNum(2);
    else return;
}

void MainWindow::settingDialog()
{
    Dialog_AppSetting *appsetting = new Dialog_AppSetting;
    appsetting->show();
}

void MainWindow::changeUnit()
{
    QAction *action = (QAction*)sender();
    if(QString::fromLocal8Bit("米_m") == action->text())
    {
        weiyi_m->setIcon(QIcon(":/Image/Image/correct.png"));
        weiyi_mm->setIcon(QIcon());
        weiyi_μm->setIcon(QIcon());
    }
    else if(QString::fromLocal8Bit("毫米_mm") == action->text())
    {
        weiyi_m->setIcon(QIcon());
        weiyi_mm->setIcon(QIcon(":/Image/Image/correct.png"));
        weiyi_μm->setIcon(QIcon());
    }
    else if(QString::fromLocal8Bit("微米_μm") == action->text())
    {
        weiyi_m->setIcon(QIcon());
        weiyi_mm->setIcon(QIcon());
        weiyi_μm->setIcon(QIcon(":/Image/Image/correct.png"));
    }
    else if(QString::fromLocal8Bit("吉帕_GPa") == action->text())
    {
        yingli_GPa->setIcon(QIcon(":/Image/Image/correct.png"));
        yingli_MPa->setIcon(QIcon());
        yingli_KPa->setIcon(QIcon());
    }
    else if(QString::fromLocal8Bit("兆帕_MPa") == action->text())
    {
        yingli_GPa->setIcon(QIcon());
        yingli_MPa->setIcon(QIcon(":/Image/Image/correct.png"));
        yingli_KPa->setIcon(QIcon());
    }
    else if(QString::fromLocal8Bit("千帕_KGa") == action->text())
    {
        yingli_GPa->setIcon(QIcon());
        yingli_MPa->setIcon(QIcon());
        yingli_KPa->setIcon(QIcon(":/Image/Image/correct.png"));
    }
    else if(QString::fromLocal8Bit("应变_ε") == action->text())
    {
        yingbian_ε->setIcon(QIcon(":/Image/Image/correct.png"));
        yingbian_με->setIcon(QIcon());
    }
    else if(QString::fromLocal8Bit("应变_με") == action->text())
    {
        yingbian_ε->setIcon(QIcon());
        yingbian_με->setIcon(QIcon(":/Image/Image/correct.png"));
    }
    else return;
}

void MainWindow::changeGridState(int index)
{
    if(index == 0)
        showGridAction->setChecked(showWidget->demoOpenGL->gridDisplay);
    else
        showGridAction->setChecked(showWidget->demoOpenGL->gridDisplay);
}
