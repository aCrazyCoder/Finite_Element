#ifndef DIALOG_SERIALPORT_H
#define DIALOG_SERIALPORT_H

/*
 * brief:   打开串口对话框
 * auther:  Shao Xingchen
 * version: v1.0
 * date:    2018年1月11日
 * note：
 */

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLayout>
#include <QTextEdit>
#include <QStatusBar>
#include <QMessageBox>
#include <QTimer>
#include "Global/Global_Variable.h"

class Dialog_SerialPort : public QDialog
{
    Q_OBJECT
public:
    Dialog_SerialPort();
    ~Dialog_SerialPort();

public slots:
    void on_openButton_clicked();
    void Read_Data();
    void changeNotifications();
    void closeSerialPort();

signals:
    void openSerialPort();
    void serialportdataUpdate();

private:
    QLabel *SerialPortNum_Lab;
    QComboBox *SerialPortNum_CB;
    QLabel *BaudRate_Lab;
    QComboBox *BaudRate_CB;
    QLabel *DataBits_Lab;
    QComboBox *DataBits_CB;
    QLabel *Parity_Lab;
    QComboBox *Parity_CB;
    QLabel *StopBits_Lab;
    QComboBox *StopBits_CB;
    QLabel *FlowControl_Lab;
    QComboBox *FlowControl_CB;
    QPushButton *SerialPort_Btn;
    QPushButton *cancelOpen;
    QLabel *notifications;
    QTimer *m_timer;
    QGridLayout *main_Layout;
    QGridLayout *up_Layout;

    QSerialPort *serial;
};

#endif // DIALOG_SERIALPORT_H
