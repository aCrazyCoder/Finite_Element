#include "Dialog_ModelInformation.h"

Dialog_ModelInformation::Dialog_ModelInformation(QWidget *parent) : QWidget(parent)
{
    if(ModelInfo_class == 0)
        classification = new QLabel(QString::fromLocal8Bit("该模型属于结构静力学模型"));
    else
        classification = new QLabel(QString::fromLocal8Bit("该模型属于位移模型"));

    SegmentationUnit = new QLabel(QString::fromLocal8Bit("分割单元体为：%1顶点%2面体").arg(ModelInfo_segmentation_point).arg(ModelInfo_segmentation_body));
    ModelInfo = new QLabel(QString::fromLocal8Bit("节点总数为：%1  元素总数为：%2").arg(ModelInfo_AllNode).arg(ModelInfo_AllElement));

    MaxStrain = new QLabel(QString::fromLocal8Bit("最大应变为："));
    MaxStrainInfo = new QLabel(QString("%1").arg(ModelInfo_MaxStrain).append(strainUnit));
    MaxStrainInfo->setFrameStyle(QFrame::Sunken|QFrame::Panel);

    MinStrain = new QLabel(QString::fromLocal8Bit("最小应变为："));
    MinStrainInfo = new QLabel(QString("%1").arg(ModelInfo_MinStrain).append(strainUnit));
    MinStrainInfo->setFrameStyle(QFrame::Sunken|QFrame::Panel);

    MaxStress = new QLabel(QString::fromLocal8Bit("最大应力为："));
    MaxStressInfo = new QLabel(QString("%1").arg(ModelInfo_MaxStress).append(stressUnit));
    MaxStressInfo->setFrameStyle(QFrame::Sunken|QFrame::Panel);

    MinStress = new QLabel(QString::fromLocal8Bit("最小应力为："));
    MinStressInfo = new QLabel(QString("%1").arg(ModelInfo_MinStress).append(stressUnit));
    MinStressInfo->setFrameStyle(QFrame::Sunken|QFrame::Panel);

    MaxShift = new QLabel(QString::fromLocal8Bit("最大位移为："));
    MaxShiftInfo = new QLabel(QString("%1").arg(ModelInfo_MaxShift).append(shiftUnit));
    MaxShiftInfo->setFrameStyle(QFrame::Sunken|QFrame::Panel);

    MinShift = new QLabel(QString::fromLocal8Bit("最小位移为："));
    MinShiftInfo = new QLabel(QString("%1").arg(ModelInfo_MinShift).append(shiftUnit));
    MinShiftInfo->setFrameStyle(QFrame::Sunken|QFrame::Panel);

    sureBtn = new QPushButton(QString::fromLocal8Bit("确定"));
    connect(sureBtn,SIGNAL(clicked(bool)),this,SLOT(close()));

    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(classification,0,0,1,2);
    mainLayout->addWidget(SegmentationUnit,1,0,1,2);
    mainLayout->addWidget(ModelInfo,2,0,1,2);
    mainLayout->addWidget(MaxStrain,3,0);
    mainLayout->addWidget(MaxStrainInfo,3,1);
    mainLayout->addWidget(MinStrain,4,0);
    mainLayout->addWidget(MinStrainInfo,4,1);
    mainLayout->addWidget(MaxStress,5,0);
    mainLayout->addWidget(MaxStressInfo,5,1);
    mainLayout->addWidget(MinStress,6,0);
    mainLayout->addWidget(MinStressInfo,6,1);
    mainLayout->addWidget(MaxShift,7,0);
    mainLayout->addWidget(MaxShiftInfo,7,1);
    mainLayout->addWidget(MinShift,8,0);
    mainLayout->addWidget(MinShiftInfo,8,1);
    mainLayout->addWidget(sureBtn,9,1,Qt::AlignRight);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    setWindowTitle(QString::fromLocal8Bit("模型信息"));
    setWindowIcon(QIcon(":/Image/Image/icon.png"));
    setWindowFlags(Qt::Window);
    setWindowModality(Qt::WindowModal);
    setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
    setFont(QFont("Microsoft YaHei",18));

}

Dialog_ModelInformation::~Dialog_ModelInformation()
{

}

