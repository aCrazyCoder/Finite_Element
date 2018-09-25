#ifndef OPENMETHOD_H
#define OPENMETHOD_H

#include <QWidget>

namespace Ui {
class openMethod;
}

class openMethod : public QWidget
{
    Q_OBJECT

public:
    explicit openMethod(QWidget *parent = 0);
    ~openMethod();

private:
    Ui::openMethod *ui;
};

#endif // OPENMETHOD_H
