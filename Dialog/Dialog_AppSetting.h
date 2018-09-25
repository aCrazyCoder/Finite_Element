#ifndef DIALOG_APPSETTING_H
#define DIALOG_APPSETTING_H

/*
 * brief:   软件设置对话框
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月4日
 * note：
 */

#include <QDialog>
#include <QDialogButtonBox>
#include <QLayout>
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
#include "Dialog_AppSetting_Pages.h"

class Dialog_AppSetting : public QDialog
{
    Q_OBJECT

public:
    Dialog_AppSetting();

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void cancelSettings();

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    ConfigurationPage *configurationPage;
};

#endif // DIALOG_APPSETTING_H
