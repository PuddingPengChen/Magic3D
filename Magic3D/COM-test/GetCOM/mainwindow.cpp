#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_comm();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init_comm()
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
QString MainWindow::getcomm(int index, QString keyorvalue)
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
