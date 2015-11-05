#ifndef PRINTTHREAD_H
#define PRINTTHREAD_H
#include <QThread>
#include "../../Uart/qextserialenumerator.h"
#include "../../Uart/win_qextserialport.h"
#include <QSettings>
#include <qt_windows.h>
#include <QTimer>
#include "readgcode.h"


class PrintThread : public QThread
{
    Q_OBJECT
public:
    explicit PrintThread(QObject *parent = 0);
    ~PrintThread();
     void run();
     bool connectCom(QString port);
     void beginPrint(QStringList);
     void debugFunction();

     int getTotalLay();
     int getTime();
     int getTotalGmd();
     QStringList getCom(){return comlist;}

public slots:
     void readArduino();
     void stopPrint(bool);
     void canclePrint();
     void disconnectCom();
     void init_comm();
     void controlPan(QString);
     void getTemp();
     void preHeartFinish();
     void preHeart();

signals:
     void Sig_consucceful(bool);
     void Sig_okmount(unsigned int);
     void Sig_oktalmount(unsigned int);
     void Sig_temp(float);
     void Sig_detectcoms();
     void Sig_warmPre();
     void Sig_recvCom(QString);
     void Sig_tempUpdate(double ,double);
     void Sig_startTimer();

private:
     //获取windows的串口
     HKEY hKey;
     LPCWSTR subkey;
     wchar_t keyname[256]; //键名数组
     char keyvalue[256];  //键值数组
     DWORD keysize,type,valuesize;
     int indexnum;

     QStringList comlist;
     QTimer* checkTimer;
     QTimer* checkTemp;

     QString getcomm(int index, QString keyorvalue);
     void checkCom();


     //串口数字
     Win_QextSerialPort* Arcom;
     QList<QextPortInfo> pPorts;

     QTimer *timer;

     void sendToArduino(QString str);
     void addToSender();
     readGcode* gcode;
     QSettings * settings;
     QString tosend;
     bool isPrinting;
     bool isStop;
     int ok_mount;  //  统计ok的数量
     float temperature;

};

#endif // PRINTTHREAD_H
