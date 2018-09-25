#ifndef PROJECTNAME_H
#define PROJECTNAME_H

#include <QDialog>
#include "Global/Global_Variable.h"

namespace Ui {
class projectName;
}

class projectName : public QDialog
{
    Q_OBJECT

public:
    explicit projectName(QWidget *parent = 0);
    ~projectName();

private slots:
    void on_pushButton_clicked();

private:
    Ui::projectName *ui;
};

#endif // PROJECTNAME_H
