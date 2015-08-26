#ifndef PRINTEDIT_H
#define PRINTEDIT_H

#include <QWidget>
#include <QTcpSocket>
#include "cilent.h"
#include <QTimer>
#include <QThread>
#include <winsock2.h>
#include "worldview.h"
#include "uart/qextserialenumerator.h"
#include "./uart/win_qextserialport.h"
#include <QSettings>
#include <qt_windows.h>

class WorldView;
class GreenTech;


namespace Ui {
class PrintEdit;
}

class PrintEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrintEdit(QWidget *parent = 0);
    ~PrintEdit();
    WorldView *pworld;
    void DisableSome();

private slots:
    void on_ImageButton_clicked();
    void on_SliceButton_clicked();
    void on_ConnectButton_clicked();
    void on_PrintButton_clicked();
    void on_StopPrintButton_clicked();
    void on_RecoverButton_clicked();
    void on_ResetButton_clicked();
    void on_toolButton_clicked();

    bool IsIPaddress(QString ip);
    void HostConnected();
    void HostDisconnected();
    void HostError();

    //get the serialcom list
    QString getcomm(int index, QString keyorvalue);
    void init_comm();
    void on_radioButton_clicked(bool checked);

private:
    Ui::PrintEdit *ui;
    //获取windows的串口
    HKEY hKey;
    LPCWSTR subkey;
    wchar_t keyname[256]; //键名数组
    char keyvalue[256];  //键值数组
    DWORD keysize,type,valuesize;
    int indexnum;

    bool connected;
    bool Sliced;
    int servPort;


    //串口数字
    Win_QextSerialPort* Arcom;
    QList<QextPortInfo> pPorts;

    void timerTask();


signals:
    void Sig_ImageShow(bool show);
    void Sig_Slice();
    void Sig_Thickness(int);
    void Sig_ComError(QString);
    void Sig_curaSupport(bool);
};

#endif // PRINTEDIT_H
