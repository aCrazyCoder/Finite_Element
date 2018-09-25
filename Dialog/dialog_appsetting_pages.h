#ifndef DIALOG_APPSETTING_PAGES_H
#define DIALOG_APPSETTING_PAGES_H

/*
 * brief:   软件设置对话框各页内容
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include <QWidget>
#include <QtWidgets>
#include "Global/Global_Variable.h"

class ConfigurationPage : public QWidget
{
    Q_OBJECT
public:
    ConfigurationPage(QWidget *parent = 0);
    void cancelSettings();

public slots:
    void changeValue(int value);
    void updateFilePath();
    void restoreDefaultSettings();

private:
  QSlider *Mouse_Move_Slider;
  QLabel *Mouse_Move_Slider_Value;
  QSlider *Wheel_Move_Slider;
  QLabel *Wheel_Move_Slider_Value;
  QSlider *Keyboard_Move_Slider;
  QLabel *Keyboard_Move_Slider_Value;

  QComboBox *directoryComboBox;
  QPushButton *toolButton;

  QPushButton *defaultSettings;

  double mouseMoveSensitivity_temp;
  double mouseWheelSensitivity_temp;
  double keyboardMoveSensitivity_temp;
  int index;
};

class QueryPage : public QWidget
{
public:
  QueryPage(QWidget *parent = 0);
};

class UpdatePage : public QWidget
{
public:
  UpdatePage(QWidget *parent = 0);
};

#endif // DIALOG_APPSETTING_PAGES_H
