#include "printedit.h"
#include "iostream"
#include "ui_printedit.h"
#include "loadingbar.h"
#include "cilent.h"
#include <QFile>
#include <QMessageBox>
#include <QRegExp>
#include "OS_Function.h"

PrintEdit::PrintEdit(QWidget *parent):
    QWidget(parent),
    ui(new Ui::PrintEdit)
{
    ui->setupUi(this);

    init_comm();

}


PrintEdit::~PrintEdit()
{
    delete ui;
}

void PrintEdit::timerTask()
{

}

/**************************************************/
/**********该函数为显示剖面按键按下时触发的函数*********/
/**************************************************/
void PrintEdit::on_ImageButton_clicked()
{
}
/**************************************************/
/************该函数为Slice按键按下时触发的函数*********/
/**************************************************/
void PrintEdit::on_SliceButton_clicked()
{

    emit Sig_Slice();
    Sliced = true;

    ui->ImageButton->setEnabled(true);
    if(Sliced&connected)
    {
        ui->PrintButton->setEnabled(true);
        ui->StopPrintButton->setEnabled(true);
        ui->RecoverButton->setEnabled(true);
        ui->ResetButton->setEnabled(true);
    }
}

void PrintEdit::DisableSome()
{
    ui->ImageButton->setEnabled(false);
//    ui->PrintButton->setEnabled(false);
}
bool PrintEdit::IsIPaddress(QString ip)
{
    bool flag;
    QRegExp reg("(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
       if(reg.exactMatch(ip))
       {
           flag = true;
       }
       else
       {
           flag  = false;
       }
       return flag;
}
//get the windows' key value
void PrintEdit::init_comm()
{
    QString path = "HKEY_LOCAL_MACHINE\\HARDWARE\\DEVICEMAP\\SERIALCOMM";
    QSettings *settings = new QSettings(path, QSettings::NativeFormat);
    QStringList key = settings->allKeys();
    qDebug()<<tr("key size = %1").arg(key.size());
    QStringList comlist ;
    QStringList Baudlist ;

    comlist.clear();

    /* 取串口名 */
    for (int i=0; i<key.size(); i++) {
        comlist << getcomm(i, "value");
    }
    ui->comboBox->addItems(comlist);
}

/*
    读取键值
*/
QString PrintEdit::getcomm(int index, QString keyorvalue)
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

void PrintEdit::on_ConnectButton_clicked()          //connect button
{
    struct PortSettings myComSetting = {BAUD9600,DATA_8,PAR_NONE,STOP_1,FLOW_OFF,500};
    QString portName = ui->comboBox->currentText(); //获取串口名
    Arcom = new Win_QextSerialPort(portName,myComSetting,QextSerialBase::EventDriven);

    if(Arcom->open(QIODevice::ReadWrite))
    {
        emit Sig_ComError("NO1");
    }
    else
    {
       emit Sig_ComError("NO2");
        return;
    }

    connect(Arcom,SIGNAL(readyRead()),this,SLOT(readArduino()));
}
void PrintEdit::HostConnected()
{

}
void PrintEdit::HostDisconnected()
{
    ui->ConnectButton->setText("Connect");
    ui->IP_label->setText("3D printer disconnected!");
    connected = false;
    ui->PrintButton->setEnabled(false);
    ui->StopPrintButton->setEnabled(false);
    ui->RecoverButton->setEnabled(false);
    ui->ResetButton->setEnabled(false);
}
void PrintEdit::HostError()
{

}


void PrintEdit::on_PrintButton_clicked()        //print button
{

}
/********************************************************************/
/****************The following function is just for debug************/
/********************************************************************/
void PrintEdit::on_StopPrintButton_clicked()        //stop button
{

}
void PrintEdit::on_RecoverButton_clicked()      //recover button
{

}

void PrintEdit::on_ResetButton_clicked()        //reset button
{

}

void PrintEdit::on_toolButton_clicked()
{
    ui->InforBrowser->clear();
}




void PrintEdit::on_radioButton_clicked(bool checked)    //开启cura的支撑结构
{
    if(checked)
    {
        emit Sig_curaSupport(true);
    }
    else
    {
        emit Sig_curaSupport(false);
    }
}
