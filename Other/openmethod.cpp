#include "openmethod.h"
#include "ui_openmethod.h"

openMethod::openMethod(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::openMethod)
{
    ui->setupUi(this);
}

openMethod::~openMethod()
{
    delete ui;
}
