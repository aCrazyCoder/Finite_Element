#ifndef DIALOG_MODELINFORMATION_H
#define DIALOG_MODELINFORMATION_H

/*
 * brief:   模型信息对话框
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLayout>
#include <QString>
#include <QIcon>

#include "Global/Global_Variable.h"

class Dialog_ModelInformation : public QWidget
{
    Q_OBJECT
public:
    explicit Dialog_ModelInformation(QWidget *parent = nullptr);
    ~Dialog_ModelInformation();

signals:

public slots:

private:
    QLabel *classification;
    QLabel *SegmentationUnit;
    QLabel *ModelInfo;
    QLabel *MaxStrain;
    QLabel *MaxStrainInfo;
    QLabel *MinStrain;
    QLabel *MinStrainInfo;
    QLabel *MaxStress;
    QLabel *MaxStressInfo;
    QLabel *MinStress;
    QLabel *MinStressInfo;
    QLabel *MaxShift;
    QLabel *MaxShiftInfo;
    QLabel *MinShift;
    QLabel *MinShiftInfo;
    QPushButton *sureBtn;
    QGridLayout *mainLayout;
};

#endif // DIALOG_MODELINFORMATION_H
