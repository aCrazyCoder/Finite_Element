#include "dialog_appsetting_pages.h"

ConfigurationPage::ConfigurationPage(QWidget *parent)
      : QWidget(parent)
{
    QGroupBox *Mouse_Keyboard_Configuration = new QGroupBox(QString::fromLocal8Bit("鼠标键盘灵敏度设置"));
    QLabel *Mouse_Move_Sensitivity = new QLabel(QString::fromLocal8Bit("鼠标移动灵敏度"));
    QLabel *Wheel_Move_Sensitivity = new QLabel(QString::fromLocal8Bit("滚轮移动灵敏度"));
    QLabel *Keyboard_Move_Sensitivity = new QLabel(QString::fromLocal8Bit("键盘移动灵敏度"));

    Mouse_Move_Slider = new QSlider(Qt::Horizontal);
    Mouse_Move_Slider->setMinimum(0);
    Mouse_Move_Slider->setMaximum(100);  //100对应0.05
    Mouse_Move_Slider->setValue((int)(mouseMoveSensitivity * 2000));
    Mouse_Move_Slider_Value = new QLabel;
    Mouse_Move_Slider_Value->setMaximumWidth(50);
    Mouse_Move_Slider_Value->setMinimumWidth(50);
    Mouse_Move_Slider_Value->setNum(mouseMoveSensitivity);
    Mouse_Move_Slider->setStyleSheet("QSlider::groove:horizontal{"
                                     " border: 1px solid #999999;"
                                     " height: 5px; "
                                     "position: absolute;"
                                     "border-radius :3px;"
                                     " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                                     " margin: 1px 0;"
                                     " left: 3px; right: 3px;"
                                     "}"
                                     "QSlider::handle:horizontal {"
                                     " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                                     "border: 1px solid #5c5c5c;"
                                     "width: 12px;"
                                     " height: 12px; "
                                     "margin: -2px -1; "/* handle is placed by default on the contents rect of the groove. Expand outside the groove */
                                     "  border-radius: 4px;"
                                     "}"
                                     " QSlider::add-page:horizontal {"
                                     "border-radius :2px;"
                                     " margin: 1px 1;"
                                     "background: white;"
                                     //  "position: absolute;"
                                     //  " left: 2px; right: 2px;"
                                     "}"
                                     "QSlider::sub-page:horizontal {"
                                     "border-radius :2px;"
                                     " margin: 1px 1;"//
                                     "  background-color:#86dfc6;"
                                     // "position: absolute;"
                                     // " left: 2px; right: 2px;"
                                     "}");

    Wheel_Move_Slider = new QSlider(Qt::Horizontal);
    Wheel_Move_Slider->setMinimum(0);
    Wheel_Move_Slider->setMaximum(100);  //范围75-95
    Wheel_Move_Slider->setValue((int)((mouseWheelSensitivity - 75) * 5));
    Wheel_Move_Slider_Value = new QLabel;
    Wheel_Move_Slider_Value->setMinimumWidth(50);
    Wheel_Move_Slider_Value->setMaximumWidth(50);
    Wheel_Move_Slider_Value->setNum(mouseWheelSensitivity);
    Wheel_Move_Slider->setStyleSheet(//滑条
                                     "QSlider::groove:horizontal{"
                                     " border: 1px solid #999999;"
                                     " height: 5px; "

                                     "position: absolute;"
                                     "border-radius :3px;"
                                     " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                                     " margin: 1px 0;"
                                     " left: 3px; right: 3px;"
                                     "}"
                                     //小滑块
                                     "QSlider::handle:horizontal {"
                                     " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                                     "border: 1px solid #5c5c5c;"
                                     "width: 12px;"
                                     " height: 12px; "
                                     "margin: -2px -1; "/* handle is placed by default on the contents rect of the groove. Expand outside the groove */
                                     "  border-radius: 4px;"
                                     "}"
                                     //滑块滑过改变样式
                                     " QSlider::add-page:horizontal {"
                                     "border-radius :2px;"
                                     " margin: 1px 1;"
                                     "background: white;"
                                     //  "position: absolute;"
                                     //  " left: 2px; right: 2px;"
                                     "}"
                                     "QSlider::sub-page:horizontal {"
                                     "border-radius :2px;"
                                     " margin: 1px 1;"//
                                     "  background-color:#86dfc6;"
                                     // "position: absolute;"
                                     // " left: 2px; right: 2px;"
                                     "}");

    Keyboard_Move_Slider = new QSlider(Qt::Horizontal);
    Keyboard_Move_Slider->setMinimum(0);
    Keyboard_Move_Slider->setMaximum(100);  //100对应5.0
    Keyboard_Move_Slider->setValue((int)(keyboardMoveSensitivity * 20));
    Keyboard_Move_Slider_Value = new QLabel;
    Keyboard_Move_Slider_Value->setMinimumWidth(50);
    Keyboard_Move_Slider_Value->setMaximumWidth(50);
    Keyboard_Move_Slider_Value->setNum(keyboardMoveSensitivity);
    Keyboard_Move_Slider->setStyleSheet(//滑条
                                     "QSlider::groove:horizontal{"
                                     " border: 1px solid #999999;"
                                     " height: 5px; "

                                     "position: absolute;"
                                     "border-radius :3px;"
                                     " background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                                     " margin: 1px 0;"
                                     " left: 3px; right: 3px;"
                                     "}"
                                     //小滑块
                                     "QSlider::handle:horizontal {"
                                     " background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);"
                                     "border: 1px solid #5c5c5c;"
                                     "width: 12px;"
                                     " height: 12px; "
                                     "margin: -2px -1; "/* handle is placed by default on the contents rect of the groove. Expand outside the groove */
                                     "  border-radius: 4px;"
                                     "}"
                                     //滑块滑过改变样式
                                     " QSlider::add-page:horizontal {"
                                     "border-radius :2px;"
                                     " margin: 1px 1;"
                                     "background: white;"
                                     //  "position: absolute;"
                                     //  " left: 2px; right: 2px;"
                                     "}"
                                     "QSlider::sub-page:horizontal {"
                                     "border-radius :2px;"
                                     " margin: 1px 1;"//
                                     "  background-color:#86dfc6;"
                                     // "position: absolute;"
                                     // " left: 2px; right: 2px;"
                                     "}");

    QGridLayout *Mouse_Keyboard_Configuration_Layout = new QGridLayout;
    Mouse_Keyboard_Configuration_Layout->addWidget(Mouse_Move_Sensitivity, 0, 0, 1, 1);
    Mouse_Keyboard_Configuration_Layout->addWidget(Mouse_Move_Slider, 0, 1, 1, 1);
    Mouse_Keyboard_Configuration_Layout->addWidget(Mouse_Move_Slider_Value , 0, 2, 1, 1, Qt::AlignHCenter);
    Mouse_Keyboard_Configuration_Layout->addWidget(Wheel_Move_Sensitivity, 1, 0, 1, 1);
    Mouse_Keyboard_Configuration_Layout->addWidget(Wheel_Move_Slider, 1, 1, 1, 1);
    Mouse_Keyboard_Configuration_Layout->addWidget(Wheel_Move_Slider_Value , 1, 2, 1, 1, Qt::AlignHCenter);
    Mouse_Keyboard_Configuration_Layout->addWidget(Keyboard_Move_Sensitivity, 2, 0, 1, 1);
    Mouse_Keyboard_Configuration_Layout->addWidget(Keyboard_Move_Slider, 2, 1, 1, 1);
    Mouse_Keyboard_Configuration_Layout->addWidget(Keyboard_Move_Slider_Value, 2, 2, 1, 1, Qt::AlignHCenter);
//    Mouse_Keyboard_Configuration_Layout->setColumnStretch(1, 1);
    Mouse_Keyboard_Configuration->setLayout(Mouse_Keyboard_Configuration_Layout);

    QGroupBox *File_Path = new QGroupBox(QString::fromLocal8Bit("文件保存路径"));
    QLabel *fileLab = new QLabel(QString::fromLocal8Bit("存储路径"));
    directoryComboBox = new QComboBox;
    directoryComboBox->setMaximumWidth(348);
    directoryComboBox->addItem(srcpath);
    for(int i = 0; i<list.size(); ++i)
    {
        directoryComboBox->addItem(list.at(i));
    }
    directoryComboBox->setCurrentIndex(listIndex);
    toolButton = new QPushButton("...");
    toolButton->setMaximumWidth(50);
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(fileLab);
    lay->addWidget(directoryComboBox);
    lay->addWidget(toolButton);
    File_Path->setLayout(lay);
    //Qt5中connect新用法，信号直接连接lamda表达式，省去声明slot函数，注意这里currentIndexChanged存在重载，故应做static_cast转换。
    QObject::connect(directoryComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int a){listIndex = a;});

    defaultSettings = new QPushButton(QString::fromLocal8Bit("恢复默认设置"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(Mouse_Keyboard_Configuration);
    mainLayout->addWidget(File_Path);
    mainLayout->addWidget(defaultSettings, 0, Qt::AlignRight);
    mainLayout->addStretch(1);

    setLayout(mainLayout);

    connect(Mouse_Move_Slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    connect(Wheel_Move_Slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    connect(Keyboard_Move_Slider, SIGNAL(valueChanged(int)), this, SLOT(changeValue(int)));
    connect(toolButton, SIGNAL(clicked(bool)), this, SLOT(updateFilePath()));
    connect(defaultSettings, SIGNAL(clicked(bool)), this, SLOT(restoreDefaultSettings()));

    //每次打开对话框均保存临时变量，供用户取消操作使用
    mouseMoveSensitivity_temp = mouseMoveSensitivity;
    mouseWheelSensitivity_temp = mouseWheelSensitivity;
    keyboardMoveSensitivity_temp = keyboardMoveSensitivity;
    index = directoryComboBox->currentIndex();
}

UpdatePage::UpdatePage(QWidget *parent)
  : QWidget(parent)
{
  QGroupBox *updateGroup = new QGroupBox(tr("Package selection"));
  QCheckBox *systemCheckBox = new QCheckBox(tr("Update system"));
  QCheckBox *appsCheckBox = new QCheckBox(tr("Update applications"));
  QCheckBox *docsCheckBox = new QCheckBox(tr("Update documentation"));

  QGroupBox *packageGroup = new QGroupBox(tr("Existing packages"));

  QListWidget *packageList = new QListWidget;
  QListWidgetItem *qtItem = new QListWidgetItem(packageList);
  qtItem->setText(tr("Qt"));
  QListWidgetItem *qsaItem = new QListWidgetItem(packageList);
  qsaItem->setText(tr("QSA"));
  QListWidgetItem *teamBuilderItem = new QListWidgetItem(packageList);
  teamBuilderItem->setText(tr("Teambuilder"));

  QPushButton *startUpdateButton = new QPushButton(tr("Start update"));

  QVBoxLayout *updateLayout = new QVBoxLayout;
  updateLayout->addWidget(systemCheckBox);
  updateLayout->addWidget(appsCheckBox);
  updateLayout->addWidget(docsCheckBox);
  updateGroup->setLayout(updateLayout);

  QVBoxLayout *packageLayout = new QVBoxLayout;
  packageLayout->addWidget(packageList);
  packageGroup->setLayout(packageLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(updateGroup);
  mainLayout->addWidget(packageGroup);
  mainLayout->addSpacing(12);
  mainLayout->addWidget(startUpdateButton);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

QueryPage::QueryPage(QWidget *parent)
  : QWidget(parent)
{
  QGroupBox *packagesGroup = new QGroupBox(tr("Look for packages"));

  QLabel *nameLabel = new QLabel(tr("Name:"));
  QLineEdit *nameEdit = new QLineEdit;

  QLabel *dateLabel = new QLabel(tr("Released after:"));
  QDateTimeEdit *dateEdit = new QDateTimeEdit(QDate::currentDate());

  QCheckBox *releasesCheckBox = new QCheckBox(tr("Releases"));
  QCheckBox *upgradesCheckBox = new QCheckBox(tr("Upgrades"));

  QSpinBox *hitsSpinBox = new QSpinBox;
  hitsSpinBox->setPrefix(tr("Return up to "));
  hitsSpinBox->setSuffix(tr(" results"));
  hitsSpinBox->setSpecialValueText(tr("Return only the first result"));
  hitsSpinBox->setMinimum(1);
  hitsSpinBox->setMaximum(100);
  hitsSpinBox->setSingleStep(10);

  QPushButton *startQueryButton = new QPushButton(tr("Start query"));

  QGridLayout *packagesLayout = new QGridLayout;
  packagesLayout->addWidget(nameLabel, 0, 0);
  packagesLayout->addWidget(nameEdit, 0, 1);
  packagesLayout->addWidget(dateLabel, 1, 0);
  packagesLayout->addWidget(dateEdit, 1, 1);
  packagesLayout->addWidget(releasesCheckBox, 2, 0);
  packagesLayout->addWidget(upgradesCheckBox, 3, 0);
  packagesLayout->addWidget(hitsSpinBox, 4, 0, 1, 2);
  packagesGroup->setLayout(packagesLayout);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(packagesGroup);
  mainLayout->addSpacing(12);
  mainLayout->addWidget(startQueryButton);
  mainLayout->addStretch(1);
  setLayout(mainLayout);
}

void ConfigurationPage::changeValue(int value)
{
    QSlider *slider = (QSlider*)sender();

    if(Mouse_Move_Slider == slider)
    {
        Mouse_Move_Slider_Value->setNum((double)(value / 2000.00));
        mouseMoveSensitivity = (float)(value / 2000.00);
    }

    else if(Wheel_Move_Slider == slider)
    {
        Wheel_Move_Slider_Value->setNum((double)(75.00 + value / 5.00));
        mouseWheelSensitivity = (float)(75.00 + value / 5.00);
    }

    else if(Keyboard_Move_Slider == slider)
    {
        Keyboard_Move_Slider_Value->setNum((double)(value * 0.05));
        keyboardMoveSensitivity = (float)(value * 0.05);
    }

    else return;
}

void ConfigurationPage::updateFilePath()  //仅改变现实路径，尚未完成函数功能
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Save Path"), QDir::currentPath()));

    if(!directory.isEmpty())
    {
        if(directoryComboBox->findText(directory) == -1)
        {
            directoryComboBox->addItem(directory);
            list.append(directory);
        }
        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
    }
}

void ConfigurationPage::restoreDefaultSettings()
{
    Mouse_Move_Slider->setValue(20);
    Mouse_Move_Slider_Value->setNum((double)(Mouse_Move_Slider->value() / 2000.00));
    mouseMoveSensitivity = 0.01;

    Wheel_Move_Slider->setValue(75);
    Wheel_Move_Slider_Value->setNum((double)(75.00 + Wheel_Move_Slider->value() / 5.00));
    mouseWheelSensitivity = 90.0;

    Keyboard_Move_Slider->setValue(50);
    Keyboard_Move_Slider_Value->setNum((double)(Keyboard_Move_Slider->value() * 0.05));
    keyboardMoveSensitivity = 2.5;

    directoryComboBox->setCurrentIndex(0);
}

void ConfigurationPage::cancelSettings()
{
    mouseMoveSensitivity = mouseMoveSensitivity_temp;
    Mouse_Move_Slider->setValue((int)(mouseMoveSensitivity * 2000));
    Mouse_Move_Slider_Value->setNum(mouseMoveSensitivity);

    mouseWheelSensitivity = mouseWheelSensitivity_temp;
    Wheel_Move_Slider->setValue((int)((mouseWheelSensitivity - 75) * 5));
    Wheel_Move_Slider_Value->setNum(mouseWheelSensitivity);

    keyboardMoveSensitivity = keyboardMoveSensitivity_temp;
    Keyboard_Move_Slider->setValue((int)(keyboardMoveSensitivity * 20));
    Keyboard_Move_Slider_Value->setNum(keyboardMoveSensitivity);

    directoryComboBox->setCurrentIndex(index);
}
