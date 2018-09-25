#include "Dialog_SerialPort.h"

Dialog_SerialPort::Dialog_SerialPort()
{
    SerialPortNum_Lab = new QLabel(QString::fromLocal8Bit("端口"));
    SerialPortNum_Lab->setAlignment(Qt::AlignJustify);
    SerialPortNum_CB = new QComboBox;
    BaudRate_Lab = new QLabel(QString::fromLocal8Bit("波特率"));
    BaudRate_Lab->setAlignment(Qt::AlignJustify);
    BaudRate_CB = new QComboBox;
    DataBits_Lab = new QLabel(QString::fromLocal8Bit("数据位"));
    DataBits_Lab->setAlignment(Qt::AlignJustify);
    DataBits_CB = new QComboBox;
    Parity_Lab = new QLabel(QString::fromLocal8Bit("校验位"));
    Parity_Lab->setAlignment(Qt::AlignJustify);
    Parity_CB = new QComboBox;
    StopBits_Lab = new QLabel(QString::fromLocal8Bit("停止位"));
    StopBits_Lab->setAlignment(Qt::AlignJustify);
    StopBits_CB = new QComboBox;
    FlowControl_Lab = new QLabel(QString::fromLocal8Bit("流控"));
    FlowControl_Lab->setAlignment(Qt::AlignJustify);
    FlowControl_CB = new QComboBox;
    SerialPort_Btn = new QPushButton(QString::fromLocal8Bit("打开串口"));
    cancelOpen = new QPushButton(QString::fromLocal8Bit("取消"));
    notifications = new QLabel;
    m_timer = new QTimer;
    m_timer->setInterval(3000);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(close()));
    connect(m_timer,SIGNAL(timeout()),m_timer,SLOT(stop()));

    BaudRate_CB->insertItem(0,tr("9600"));
    BaudRate_CB->insertItem(1,tr("19200"));
    BaudRate_CB->insertItem(2,tr("38400"));
    BaudRate_CB->insertItem(3,tr("57600"));
    BaudRate_CB->insertItem(4,tr("115200"));

    DataBits_CB->insertItem(5,tr("5"));
    DataBits_CB->insertItem(6,tr("6"));
    DataBits_CB->insertItem(7,tr("7"));
    DataBits_CB->insertItem(8,tr("8"));

    Parity_CB->insertItem(0,tr("None"));
    Parity_CB->insertItem(1,tr("Even"));
    Parity_CB->insertItem(2,tr("Odd"));
    Parity_CB->insertItem(3,tr("Space"));
    Parity_CB->insertItem(4,tr("Mark"));

    StopBits_CB->insertItem(0,tr("1"));
    StopBits_CB->insertItem(1,tr("1.5"));
    StopBits_CB->insertItem(2,tr("2"));

    FlowControl_CB->insertItem(0,tr("None"));
    FlowControl_CB->insertItem(1,tr("RTS/CTS"));
    FlowControl_CB->insertItem(2,tr("XON/XOFF"));

    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            SerialPortNum_CB->addItem(serial.portName());
        }
        serial.close();
    }
    //设置波特率下拉菜单默认显示第三项
    BaudRate_CB->setCurrentIndex(4);
    notifications->setStyleSheet("color:red");
    notifications->setText(SerialPortNum_CB->currentText().append(" CLOSED"));

    up_Layout = new QGridLayout;
    up_Layout->addWidget(SerialPortNum_Lab,0,0,1,1,Qt::AlignLeft);
    up_Layout->addWidget(SerialPortNum_CB,0,1,1,1,Qt::AlignRight);
    up_Layout->addWidget(BaudRate_Lab,1,0,1,1,Qt::AlignLeft);
    up_Layout->addWidget(BaudRate_CB,1,1,1,1,Qt::AlignRight);
    up_Layout->addWidget(DataBits_Lab,2,0,1,1,Qt::AlignLeft);
    up_Layout->addWidget(DataBits_CB,2,1,1,1,Qt::AlignRight);
    up_Layout->addWidget(Parity_Lab,3,0,1,1,Qt::AlignLeft);
    up_Layout->addWidget(Parity_CB,3,1,1,1,Qt::AlignRight);
    up_Layout->addWidget(StopBits_Lab,4,0,1,1,Qt::AlignLeft);
    up_Layout->addWidget(StopBits_CB,4,1,1,1,Qt::AlignRight);
    up_Layout->addWidget(FlowControl_Lab,5,0,1,1,Qt::AlignLeft);
    up_Layout->addWidget(FlowControl_CB,5,1,1,1,Qt::AlignRight);

    main_Layout = new QGridLayout(this);
    main_Layout->addLayout(up_Layout,0,0,1,2,Qt::AlignCenter);
    main_Layout->addWidget(SerialPort_Btn,1,0,1,1,Qt::AlignCenter);
    main_Layout->addWidget(cancelOpen,1,1,1,1,Qt::AlignCenter);
    main_Layout->addWidget(notifications,2,0,1,2,Qt::AlignLeft);
    main_Layout->setColumnStretch(0,2);
    main_Layout->setColumnStretch(1,1);
    main_Layout->setMargin(10);

    setLayout(main_Layout);
    setModal(true);  //设置为模态对话框
    setFont(QFont("Microsoft YaHei",12));

    setWindowIcon(QIcon(":/Image/Image/icon.png"));
    setWindowTitle(QString::fromLocal8Bit("串口设置"));

    connect(cancelOpen,SIGNAL(clicked(bool)),this,SLOT(reject()));
    connect(SerialPort_Btn,SIGNAL(clicked(bool)),this,SLOT(on_openButton_clicked()));
    connect(SerialPortNum_CB, SIGNAL(currentIndexChanged(int)), this, SLOT(changeNotifications()));

}

Dialog_SerialPort::~Dialog_SerialPort()
{

}

void Dialog_SerialPort::on_openButton_clicked()
{
    serial = new QSerialPort(this);
    //设置串口名
    serial->setPortName(SerialPortNum_CB->currentText());
    //打开串口
    serial->open(QIODevice::ReadWrite);
    if(!serial->isOpen())
    {
        QMessageBox::warning(this, tr("SerialPort"), QString::fromLocal8Bit("串口打开失败！"));
        return;
    }
    else
    {
        notifications->setStyleSheet("color: green");
        notifications->setText(SerialPortNum_CB->currentText().append(" OPEN"));
        m_timer->start();
        emit openSerialPort();
    }
    //设置波特率
    serial->setBaudRate(BaudRate_CB->currentText().toInt());
    //设置数据位数
    switch(DataBits_CB->currentIndex())
    {
    case 5: serial->setDataBits(QSerialPort::Data5); break;
    case 6: serial->setDataBits(QSerialPort::Data6); break;
    case 7: serial->setDataBits(QSerialPort::Data7); break;
    case 8: serial->setDataBits(QSerialPort::Data8); break;
    default: break;
    }
    //设置奇偶校验
    switch(Parity_CB->currentIndex())
    {
    case 0: serial->setParity(QSerialPort::NoParity); break;
    case 1: serial->setParity(QSerialPort::EvenParity); break;
    case 2: serial->setParity(QSerialPort::OddParity); break;
    case 3: serial->setParity(QSerialPort::SpaceParity); break;
    case 4: serial->setParity(QSerialPort::MarkParity); break;
    default: break;
    }
    //设置停止位
    switch(StopBits_CB->currentIndex())
    {
    case 0: serial->setStopBits(QSerialPort::OneStop); break;
    case 1: serial->setStopBits(QSerialPort::OneAndHalfStop); break;
    case 2: serial->setStopBits(QSerialPort::TwoStop); break;
    default: break;
    }
    //设置流控制
    switch(FlowControl_CB->currentIndex())
    {
    case 0: serial->setFlowControl(QSerialPort::NoFlowControl); break;
    case 1: serial->setFlowControl(QSerialPort::HardwareControl); break;
    case 2: serial->setFlowControl(QSerialPort::SoftwareControl); break;
    default: break;
    }

    //连接信号槽
    QObject::connect(serial, &QSerialPort::readyRead, this, &Dialog_SerialPort::Read_Data);

}

//读取接收到的数据
void Dialog_SerialPort::Read_Data()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
        bool ok;
        rxData = buf.toInt(&ok, 16);     //将16进制数字转换为十进制数字
        emit serialportdataUpdate();
    }
    else
        QMessageBox::warning(this, tr("SerialPort"), QString::fromLocal8Bit("串口传输中断！请检查串口连接和串口设置！"));
    buf.clear();
}

void Dialog_SerialPort::changeNotifications()
{
    notifications->setStyleSheet("color: red");
    notifications->setText(SerialPortNum_CB->currentText().append(" CLOSED"));
}

void Dialog_SerialPort::closeSerialPort()
{
    serial->clear();
    serial->close();
    serial->deleteLater();
}




