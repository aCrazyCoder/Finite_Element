#include "App_Main_Widget.h"

App_Main_Widget::App_Main_Widget(QWidget *parent) : QWidget(parent)
{
    RatioLab = new QLabel(QString::fromLocal8Bit("R<sub>应变/位移</sub>(με/μm):"));
    RatioLab->setFont(QFont("Microsoft YaHei",12));
    RatioData = new QLabel(QString::number(Ratio_Data, 'f', 3));
    RatioData->setFont(QFont("Microsoft YaHei",16));
    RatioData->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    m_table = new QTableWidget;
    m_table->setColumnCount(4);
    QStringList header;
    header<<QString::fromLocal8Bit("比例")<<QString::fromLocal8Bit("应变")<<QString::fromLocal8Bit("位移")<<QString::fromLocal8Bit("时间");
    m_table->setHorizontalHeaderLabels(header);
    m_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_table->verticalHeader()->setVisible(false);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setStyleSheet("selection-background-color:lightblue;");
    m_table->horizontalHeader()->resizeSection(0,80);
    m_table->horizontalHeader()->resizeSection(1,80);
    m_table->horizontalHeader()->resizeSection(2,80);
    m_table->horizontalHeader()->resizeSection(3,180);
    m_table->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
    m_table->horizontalHeader()->setSortIndicatorShown(true);
    m_table->horizontalHeader()->setSectionsClickable(true);
    connect(m_table->horizontalHeader(), SIGNAL(sectionClicked(int)), m_table, SLOT(sortByColumn(int)));
    m_table->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(240,240,240);}");
    m_table->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                                                  "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                  "QScrollBar::handle:hover{background:gray;}"
                                                  "QScrollBar::sub-line{background:transparent;}"
                                                  "QScrollBar::add-line{background:transparent;}");
    m_table->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                                                "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                                "QScrollBar::handle:hover{background:gray;}"
                                                "QScrollBar::sub-line{background:transparent;}"
                                                "QScrollBar::add-line{background:transparent;}");

    m_GroupBox_CalculationResults = new QGroupBox(QString::fromLocal8Bit("计算结果"));
    m_GroupBox_CalculationResults->setFont(QFont("Microsoft YaHei",10));
    CalculationResults_Layout = new QGridLayout;
    CalculationResults_Layout->addWidget(RatioLab,0,0,1,1);
    CalculationResults_Layout->addWidget(RatioData,0,1,1,1);
    CalculationResults_Layout->addWidget(m_table,1,0,1,2);
    m_GroupBox_CalculationResults->setLayout(CalculationResults_Layout);

    point_Lab = new QLabel(QString::fromLocal8Bit("当前点位置坐标："));
    point_Lab->setFont(QFont("Microsoft YaHei",12));

    QString num = "<font color=red size='+1' face='Microsoft YaHei'><u>%1</u></font>";

    point_info_Lab_X = new QLabel(QString("x:   ").append(num).arg(QString::number(World_x, 'f', 3)));
    point_info_Lab_Y = new QLabel(QString("Y:   ").append(num).arg(QString::number(World_y, 'f', 3)));
    point_info_Lab_Z = new QLabel(QString("Z:   ").append(num).arg(QString::number(World_z, 'f', 3)));
    point_strain_Lab = new QLabel(QString::fromLocal8Bit("当前点应变大小:"));
    point_strain_Lab->setFont(QFont("Microsoft YaHei",12));
    QString num_Strain;
    point_strain_info_Lab = new QLabel(num_Strain.setNum(current_Strain,'f',3));
    point_strain_info_Lab->setFont(QFont("Microsoft YaHei",16));
    point_strain_info_Lab->setMaximumHeight(30);
    point_strain_info_Lab->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    point_shift_Lab = new QLabel(QString::fromLocal8Bit("当前点位移大小:"));
    point_shift_Lab->setFont(QFont("Microsoft YaHei",12));
    QString num_Shift;
    point_shift_info_Lab = new QLabel(num_Shift.setNum(current_Shift,'f',3));
    point_shift_info_Lab->setFont(QFont("Microsoft YaHei",16));
    point_shift_info_Lab->setMaximumHeight(30);
    point_shift_info_Lab->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    point_stress_Lab = new QLabel(QString::fromLocal8Bit("当前点应力大小:"));
    point_stress_Lab->setFont(QFont("Microsoft YaHei",12));
    QString num_Stress;
    point_stress_info_Lab = new QLabel(num_Stress.setNum(current_Stress,'f',3));
    point_stress_info_Lab->setFont(QFont("Microsoft YaHei",16));
    point_stress_info_Lab->setMaximumHeight(30);
    point_stress_info_Lab->setFrameStyle(QFrame::Panel|QFrame::Sunken);

    m_GroupBox_PointInformation = new QGroupBox(QString::fromLocal8Bit("当前点信息"));
    m_GroupBox_PointInformation->setFont(QFont("Microsoft YaHei",10));
    PointInformation_Layout = new QGridLayout;
    PointInformation_Layout->addWidget(point_Lab,0,0,1,2);
    PointInformation_Layout->addWidget(point_info_Lab_X,1,0,1,2);
    PointInformation_Layout->addWidget(point_info_Lab_Y,2,0,1,2);
    PointInformation_Layout->addWidget(point_info_Lab_Z,3,0,1,2);

    PointInformation_Layout->addWidget(point_strain_Lab,4,0);
    PointInformation_Layout->addWidget(point_strain_info_Lab,4,1);
    PointInformation_Layout->addWidget(point_shift_Lab,6,0);
    PointInformation_Layout->addWidget(point_shift_info_Lab,6,1);
    PointInformation_Layout->addWidget(point_stress_Lab,5,0);
    PointInformation_Layout->addWidget(point_stress_info_Lab,5,1);
    m_GroupBox_PointInformation->setLayout(PointInformation_Layout);

    screenshotBtn = new QPushButton(QString::fromLocal8Bit("保存截图"));
    screenshotBtn->setFont(QFont("Microsoft YaHei",12));
    screenPic = new QLabel;
    screenPic->setMaximumSize(180,180);
    screenPic->setMinimumSize(180,180);
    screenPic->setFrameStyle(QFrame::Panel|QFrame::Sunken);
    QPixmap pic(":/Image/Image/finite.png");   //默认显示图片，保存截图时需要更新
    pic = pic.scaled(180,180,Qt::KeepAspectRatio);
    screenPic->setPixmap(pic);

    m_GroupBox_ScreenShot = new QGroupBox(QString::fromLocal8Bit("截图"));
    m_GroupBox_ScreenShot->setFont(QFont("Microsoft YaHei",10));
    ScreenShot_Layout = new QVBoxLayout;
    ScreenShot_Layout->addWidget(screenPic,0,Qt::AlignCenter);
    ScreenShot_Layout->addWidget(screenshotBtn,0,Qt::AlignRight);
    m_GroupBox_ScreenShot->setLayout(ScreenShot_Layout);

    m_openMethod = new openMethod;
    main_3D_window = new QTabWidget;
    main_3D_window->setTabsClosable(true);
    main_3D_window->addTab(m_openMethod,QIcon(":/Image/Image/start.png"),QString::fromLocal8Bit("开始"));
    connect(main_3D_window,SIGNAL(tabCloseRequested(int)),this,SLOT(removeSubTab(int)));
    connect(main_3D_window, SIGNAL(currentChanged(int)), this, SLOT(switchOpenGL(int)));

    right_Layout = new QVBoxLayout;
    right_Layout->addWidget(m_GroupBox_PointInformation);
    right_Layout->addStretch();
    right_Layout->addWidget(m_GroupBox_CalculationResults);
    right_Layout->addStretch();
    right_Layout->addWidget(m_GroupBox_ScreenShot);

    main_Layout = new QHBoxLayout(this);
    main_Layout->addWidget(main_3D_window);
    main_Layout->addLayout(right_Layout);
    main_Layout->setStretchFactor(main_3D_window,5);
    main_Layout->setStretchFactor(right_Layout,1);
    main_Layout->setMargin(10);
    main_Layout->setSpacing(10);

    connect(screenshotBtn,SIGNAL(clicked(bool)),this,SLOT(screenShot()));

    demoOpenGL = new my_OpenGL(1569,907);
//    QTimer::singleShot(0,demoOpenGL,SLOT(setFocus()));  //设置图形显示窗口为默认焦点
}

App_Main_Widget::~App_Main_Widget()
{

}

void App_Main_Widget::screenShot()
{

    QPixmap p = demoOpenGL->grab(QRect(demoOpenGL->x(),demoOpenGL->y(),demoOpenGL->x()+demoOpenGL->width(),demoOpenGL->y()-demoOpenGL->height()));
    if(!p)
    {
        QMessageBox::warning(this,tr("ScreenShot"),QString::fromLocal8Bit("保存截图失败！"));
    }
    else
    {
        QMessageBox::information(this,tr("ScreenShot"),QString::fromLocal8Bit("保存截图成功！"));
        screenshot_Img = p.toImage();
        screenshot_Num++;
        srcpath.remove("/build-Finite_Element-Desktop_Qt_5_9_1_MSVC2015_64bit-Debug");
       //路径待修改！！！！！
        QDateTime time = QDateTime::currentDateTime();
        QString name = "ScreenShot_%1";
        screenshot_Img.save(srcpath+"/Finite_Element/ScreenShot/"+name.arg(screenshot_Num)+time.toString("(yyyy_MM_dd)")+".png");
        p = p.scaled(180,180,Qt::KeepAspectRatio);
        screenPic->setPixmap(p);
    }
}

//更新数据
void App_Main_Widget::numUpdate()
{
    QString num = "<font color=red size='+1' face='Microsoft YaHei'><u>%1</u></font>";
    point_info_Lab_X->setText(QString("x:   ").append(num).arg(QString::number(World_x, 'f', 3)));
    point_info_Lab_Y->setText(QString("y:   ").append(num).arg(QString::number(World_y, 'f', 3)));
    point_info_Lab_Z->setText(QString("z:   ").append(num).arg(QString::number(World_z, 'f', 3)));

    point_strain_info_Lab->setText(QString::number(current_Strain, 'g', 5));
    point_shift_info_Lab->setText(QString::number(current_Shift, 'f', 5));
    point_stress_info_Lab->setText(QString::number(current_Stress, 'f', 5));
}

//链接槽函数
void App_Main_Widget::linkSlot(int a)
{
    if(a == 1)                                      //居中操作
        demoOpenGL->initialize_recovery();
    else if(a == 2)                                 //闪烁标签，提示输入
        calculateRatio();
    else
        return;
}

//移除子标签
void App_Main_Widget::removeSubTab(int a)
{
    main_3D_window->removeTab(a);
}

void App_Main_Widget::setOpenGLWindow()
{
    QSize openglWindowSize = m_openMethod->size();
    if(main_3D_window->tabText(0) == QString::fromLocal8Bit("开始"))
        main_3D_window->removeTab(0);

    dataType = 0;
    gemoOpenGL = new my_OpenGL(openglWindowSize.width(), openglWindowSize.height());
    main_3D_window->addTab(gemoOpenGL, QIcon(":/Image/Image/newTab.ico"), ProjectName+":geometry.txt");
    connect(gemoOpenGL, SIGNAL(numChanged()), this, SLOT(numUpdate()));

    dataType = 1;
    shiftOpenGL = new my_OpenGL(openglWindowSize.width(), openglWindowSize.height());
    main_3D_window->addTab(shiftOpenGL, QIcon(":/Image/Image/newTab.ico"), ProjectName+":weiyi.txt");
    connect(shiftOpenGL, SIGNAL(numChanged()), this, SLOT(numUpdate()));

    dataType = 2;
    strainOpenGL = new my_OpenGL(openglWindowSize.width(), openglWindowSize.height());
    main_3D_window->addTab(strainOpenGL, QIcon(":/Image/Image/newTab.ico"), ProjectName+":yingbian.txt");
    connect(strainOpenGL, SIGNAL(numChanged()), this, SLOT(numUpdate()));

    dataType = 3;
    stressOpenGL = new my_OpenGL(openglWindowSize.width(), openglWindowSize.height());
    main_3D_window->addTab(stressOpenGL, QIcon(":/Image/Image/newTab.ico"), ProjectName+":yingli.txt");
    connect(stressOpenGL, SIGNAL(numChanged()), this, SLOT(numUpdate()));

}

void App_Main_Widget::switchOpenGL(int index)
{
    switch (index)
    {
    case 0:
        demoOpenGL = gemoOpenGL;
        emit indexChanged(0);
        break;
    case 1:
        demoOpenGL = shiftOpenGL;
        emit indexChanged(1);
        break;
    case 2:
        demoOpenGL = strainOpenGL;
        emit indexChanged(2);
        break;
    case 3:
        demoOpenGL = stressOpenGL;
        emit indexChanged(3);
        break;
    default:
        break;
    }
}

void App_Main_Widget::exportData()
{
    QString directory = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("导出文件保存路径"), QDir::currentPath());
    if(directory.isEmpty())
        return;
    else
    {
        QFile file;
        QString currentOpenTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
        QString fileUrl = directory.append("/").append(currentOpenTime).append(ProjectName).append(".txt");
        file.setFileName(fileUrl);
        file.open(QIODevice::Text | QIODevice::ReadWrite);

        if(file.isOpen())
        {
            QTextStream out(&file);
            out << "****************************************"<<endl;
            out << ProjectName << endl;
            out << currentOpenTime << endl;
            out << "****************************************"<<endl;
            out << QString::fromLocal8Bit("时间") << '\t' << QString::fromLocal8Bit("比例系数(%1)").arg(QString::fromLocal8Bit("με/μm")) << '\t' << QString::fromLocal8Bit("应变%1").arg(strainUnit) << '\t' << QString::fromLocal8Bit("位移%1").arg(shiftUnit) << endl;
            for(int i = 0; i < m_table->rowCount(); i++)
            {
                out << m_table->item(i, 3)->text() << '\t' << m_table->item(i, 0)->text() << '\t' << m_table->item(i, 1)->text() << '\t' << m_table->item(i, 2)->text() << endl;
            }
            file.close();
            QMessageBox::information(this, "Finite Element", QString::fromLocal8Bit("<font size='+1'>导出数据成功。</font>").append(QString::fromLocal8Bit("<br>文件路径：")).append(fileUrl));
        }
        else
            QMessageBox::warning(this, tr("Error"), QString::fromLocal8Bit("导出数据失败"));
    }
}

void App_Main_Widget::calculateRatio()
{
    if((current_Strain == 0.0f) | (current_Shift == 0.0f))
        QMessageBox::warning(this, QString::fromLocal8Bit("计算比例值"), QString::fromLocal8Bit("Error: 尚未选择所需参数或所需参数存在计算未定性"));
    else
    {
        Ratio_Data = current_Strain / current_Shift * 1000.0f;
        RatioData->setText(QString::number(Ratio_Data, 'f', 4));
        m_table->setSortingEnabled(false);
        m_table->insertRow(0);
        m_table->setItem(0, 0, new QTableWidgetItem(QString::number(Ratio_Data)));
        m_table->setItem(0, 1, new QTableWidgetItem(QString::number(current_Strain)));
        m_table->setItem(0, 2, new QTableWidgetItem(QString::number(current_Shift)));
        m_table->setItem(0, 3, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd  hh:mm:ss")));
        m_table->setSortingEnabled(true);
    }
}








