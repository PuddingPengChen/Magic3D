#include "printthread.h"
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

PrintThread::PrintThread(QObject *parent) :
    QThread(parent)
{
    isPrinting = false;
    isStop = true;
    ok_mount = 0;
    temperature = 0;
    gcode = new readGcode();
    checkTimer = new QTimer();
    checkTemp = new QTimer();
    settings = new QSettings("printerConfig.ini",QSettings::IniFormat);

    connect(checkTimer,SIGNAL(timeout()),this,SLOT(init_comm()));
    connect(checkTemp,SIGNAL(timeout()),this,SLOT(getTemp()));

//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(readArduino()));
    init_comm();
    checkCom();
}

PrintThread::~PrintThread()
{

}
void PrintThread::checkCom()
{
    //如果软件打开没有检测到可用的串口，则每隔2秒更新一次串口列表
    if(comlist.count()==0)
    {
        checkTimer->start(2000);
    }
}
//get the windows' key value
void PrintThread::init_comm()
{
    QString path = "HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM";
    QSettings *settings = new QSettings(path, QSettings::NativeFormat);
    QStringList key = settings->allKeys();
    comlist.clear();

    /* 取串口名 */
    for (int i=0; i<key.size(); i++)
    {
        comlist << getcomm(i, "value");
        qDebug()<<"available uart com:"<<comlist[i];
    }
    if(comlist.count()>0)
    {
        checkTimer->stop();
        //告诉打印机，检测到了串口
        emit Sig_detectcoms();
    }

//    ui->comboBox->addItems(comlist);
}
void PrintThread::disconnectCom()
{
    Arcom->close();
    delete Arcom;
    //如果断开连接，重新开启
    checkTimer->start(2000);
    checkTemp->stop();
//    timer->stop();
}
QString PrintThread::getcomm(int index, QString keyorvalue)
{
    QString commresult;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_READ, &hKey) != 0) {
            QString error="Cannot open regedit!";//无法打开注册表时返回error
            qDebug()<<"Cannot open regdit!!";
            return error;
        }//if(::RegOpenKeyEx(HKEY_LOCAL_MACHINE,subkey,0,KEY_READ,&hKey)!=0)

        QString keymessage;//键名
        QString message;
        QString valuemessage;//键值
        indexnum = index;//要读取键值的索引号
        keysize = sizeof(keyname);
        valuesize = sizeof(keyvalue);

        if (RegEnumValue(hKey, indexnum, keyname, &keysize, 0, &type, (BYTE*)keyvalue, &valuesize) == 0) { //列举键名和值
            for (int i=0; i<(int)keysize; i++) {
                message = keyname[i];
                keymessage.append(message);
            }

            for (int j=0; j<(int)valuesize; j++) {
                 if (keyvalue[j] != 0x00) {
                     valuemessage.append(keyvalue[j]);
                 }
            }

            if (keyorvalue == "key") {
                 commresult = keymessage;
            }

            if (keyorvalue == "value") {
                 commresult=valuemessage;
            }
        } else {
             commresult = "nokey";
        }
        RegCloseKey(hKey);//关闭注册表
        return commresult;
}
//struct PortSettings
//{
//    BaudRateType BaudRate;
//    DataBitsType DataBits;
//    ParityType Parity;
//    StopBitsType StopBits;
//    FlowType FlowControl;
//    long Timeout_Millisec;
//};
bool PrintThread::connectCom(QString port)
{
//    struct PortSettings myComSetting = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,25};
    bool coned = false;
    QRegExp re("COM([0-9]*)");
    int pos = port.indexOf(re);
    if(re.cap(1).toInt()>=10)
    {
        qDebug()<<"fuck"<<re.cap(1);
        port = "\\\\.\\"+port;
    }
    QString portName = port; //获取串口名
    qDebug()<<"before connect the printer:"<<portName;
    //QextSerialBase::Polling
    Arcom = new Win_QextSerialPort(portName,QextSerialBase::EventDriven);
//    Arcom = new Win_QextSerialPort(portName,QextSerialBase::Polling);

    if(Arcom->open(QIODevice::ReadWrite))
    {
        QObject::connect(Arcom,SIGNAL(readyRead()),this,SLOT(readArduino()));
        coned = true;
        qDebug()<<"helloworld!!";
        checkTemp->start(5000);
//        timer->start(200);
        checkTimer->stop();
    }
    else
    {
       QMessageBox::information(NULL, tr("通知"), tr("链接串口失败"));
       emit Sig_consucceful(false);
       coned = false;
    }
    //设置波特率
    Arcom->setBaudRate(BAUD115200);
    //设置数据位
    Arcom->setDataBits(DATA_8);
    //设置校验
    Arcom->setParity(PAR_NONE);
    //设置停止位
    Arcom->setStopBits(STOP_1);
    Arcom->setFlowControl(FLOW_OFF);
    return coned;
}
void PrintThread::getTemp()
{
   sendToArduino("M105 \n");
}
void PrintThread::controlPan(QString cmd)
{
    sendToArduino(cmd);
}
void PrintThread::readArduino()
{
     QByteArray ba = Arcom->readAll();
    if(!ba.isEmpty())
    {
//        QByteArray ba = Arcom->readAll();
        QString le = ba;
//        le.startsWith("ok")
        qDebug()<<"SerialCom receive:"<<le;
        emit Sig_recvCom(le);
        QRegExp reg(QString("T: *([0-9]*\.[0-9]*)"));
//        QRegExp reg2(QString("B: *([0-9\.]*)"));
        QRegExp regOK(QString("ok"));

        if(le.contains(reg))        //获取温度
        {
            int pos = le.indexOf(reg);
            pos = le.indexOf(reg);
            if(pos>=0)
            {
                qDebug()<<reg.matchedLength();
                qDebug()<<reg.cap(0);
                qDebug()<<"Flagment:"<<reg.cap(1);
//                qDebug()<<reg2.cap(0);
//                qDebug()<<"Bed:"<<reg2.cap(1);
                temperature = reg.cap(1).toFloat();
                settings->beginGroup("preheart");
                double target = settings->value("preTemp").toFloat();
                settings->endGroup();

                qDebug()<<tr("temp = %1").arg(temperature);
                emit Sig_temp(temperature);
                emit Sig_tempUpdate(target,temperature);
            }
        }
        if(((!le.contains(reg))&&(le.contains(regOK))||isPrinting))
        {
            if(!isStop)
            {
                ok_mount++;
                addToSender();
                sendToArduino(tosend);
                emit Sig_okmount(ok_mount);
            }

        }
        else if(le.startsWith("start"))
        {
            qDebug()<<"The printer has connected!!";
            emit Sig_consucceful(true);
        }
        else
        {
            sendToArduino("G4 P20 \n");
        }
    }
}

void PrintThread::addToSender()
{
//    QRegExp regG(QString("G[0-9]*"));
    tosend = gcode->readOneLine();
    if(tosend=="end")
    {
        tosend = "G28 \n";
        isStop = true;
        ok_mount = 0;
        emit Sig_okmount(ok_mount);
    }
    else
    {
//        if(tosend.contains(regG))
        if(!tosend.startsWith(";"))
        {
            isPrinting = true;
        }
        else
        {
            isPrinting = false;
        }
    }
    qDebug()<<"add to sender:"<<tosend;
}
void PrintThread::sendToArduino(QString str)    //send command to the arduino
{
    char *pt ;
    int write_nu = 0;
    QByteArray ba = str.toLatin1();
    pt = ba.data();
//    int buflen=str.length();
    write_nu = Arcom->write(ba);
//  qDebug()<<QObject::tr("write succefful :%1 ").arg(str);
}
//预加热处理
void PrintThread::preHeart()
{
    settings->beginGroup("preheart");
    int temp = settings->value("preTemp").toInt();
    int times = settings->value("preTime").toInt();
    settings->endGroup();

    QString heart = QString(tr("M104 S%1 \n").arg(temp));
    sendToArduino(heart);
    QTimer::singleShot((times*60*1000),this,SLOT(preHeartFinish()));
    qDebug()<<"pre heart the printer choolate";

}
void PrintThread::preHeartFinish()
{
    settings->beginGroup("preheart");
    int temp = settings->value("preTemp").toInt();
    settings->endGroup();
    if(temperature>temp)
    {
//        isStop = true;
//        isPrinting = false;
//        qDebug()<<"pre heart finish!!";
        QMessageBox::information(NULL,tr("提示"),tr("预加热已完成！可开始打印"));
    }
}

void PrintThread::beginPrint(QStringList file)
{
    settings->beginGroup("preheart");
    int temp = settings->value("preTemp").toInt();
    settings->endGroup();
//    if(temperature>temp)
    {
        gcode->setTargetFile(file.at(0));
        unsigned int po = gcode->getTotalGcmd();
        emit Sig_oktalmount(po);
        addToSender();
        sendToArduino("G28 \n");
        isStop = false;
        qDebug()<<tosend;
        emit Sig_startTimer();

    }
//    else
//    {
//        emit Sig_warmPre(); //发出未预热警告
//    }
}


int PrintThread::getTotalLay()
{
    gcode->getTotalLayer();
}
int PrintThread::getTime()
{
    gcode->getTotalTime();
}
int PrintThread::getTotalGmd()
{
    gcode->getTotalGcmd();
}


void PrintThread::debugFunction()
{

}

void PrintThread::stopPrint(bool print)
{
    if(isStop&&print)   //进行恢复
    {
        isStop = false;
        sendToArduino("G1 Z-15.0 F1000 \n");
        addToSender();
        sendToArduino(tosend);
    }
    else if((!print)&&(!isStop))
    {
        isStop = true;
        sendToArduino("G1 Z15.0 F1000 \n");

    }
}
void PrintThread::canclePrint()
{
    isStop = true;
    ok_mount = 0;
    sendToArduino("G28 \n");
//    sendToArduino("M1 \n");
    gcode->reset();
}
void PrintThread::run()
{

}
