#include "projectname.h"
#include "ui_projectname.h"

projectName::projectName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::projectName)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/Image/Image/icon.png"));
    setWindowTitle(QString::fromLocal8Bit("设置工程名称"));
    setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
    setModal(true);
}

projectName::~projectName()
{
    delete ui;
}

void projectName::on_pushButton_clicked()
{
    ProjectName = ui->textEdit->toPlainText();
    close();
}
