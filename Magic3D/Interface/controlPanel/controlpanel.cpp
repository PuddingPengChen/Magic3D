#include "controlpanel.h"
#include "ui_controlpanel.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

controlPanel::controlPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controlPanel)
{
    ui->setupUi(this);
    printer = new PrintThread();
    machineControl = new SettingDialog();
    connected = false;
    stoped = true;

    if(printer->getCom().count()>0)
    ui->IP1->addItems(printer->getCom());

    //printer ---->   this
    connect(printer,SIGNAL(Sig_consucceful(bool)),this,SLOT(slotConnect(bool)));
    connect(printer,SIGNAL(Sig_okmount(unsigned int)),this,SLOT(updateProgressBar(unsigned int)));
    connect(printer,SIGNAL(Sig_temp(float)),this,SLOT(updateTemp(float)));
    connect(printer,SIGNAL(Sig_oktalmount(uint)),this,SLOT(setTotalProgressBar(unsigned int)));
    connect(printer,SIGNAL(Sig_detectcoms()),this,SLOT(hasCom()));

    //this ---->  printer
    connect(this,SIGNAL(Sig_stopRecover(bool)),printer,SLOT(stopPrint(bool)));
    connect(this,SIGNAL(Sig_canclePrint()),printer,SLOT(canclePrint()));
    connect(this,SIGNAL(Sig_disconnectPrinter()),printer,SLOT(disconnectCom()));

    //machineControl ----> printer
    connect(machineControl,SIGNAL(Sig_cmd(QString)),printer,SLOT(controlPan(QString)));

    //printer ----> machineControl
    connect(printer,SIGNAL(Sig_recvCom(QString)),machineControl,SLOT(showMessage(QString)));
    connect(printer,SIGNAL(Sig_tempUpdate(double,double)),machineControl,SLOT(realTimeSlot(double,double)));
}

void controlPanel::slotConnect(bool con)      //串口连接成功后使能界面
{
    if(con)
    {
        QMessageBox::information(NULL, tr("通知"), tr("成功链接串口"));
        ui->Stop->setEnabled(true);
        ui->Cancle1->setEnabled(true);
        ui->Recovery->setEnabled(true);
        ui->Print1->setEnabled(true);
        machineControl->setControl(true);
        ui->connect->setText(tr("单击断开"));
    }
    else
    {
        ui->connect->setText(tr("建立连接"));
    }

}
void controlPanel::updateProgressBar(unsigned int val)
{
    ui->Prog1->setValue(val);
    qDebug()<<tr("current progress value:%1").arg(val);
}
void controlPanel::updateTemp(float temp)
{
    ui->Temp1->setText(QString::number(temp));
    qDebug()<<tr("current temp is : %1").arg(temp);
}

void controlPanel::setTotalProgressBar(unsigned int val)
{
   qDebug()<<tr("set total progress:").arg(val);
   ui->Prog1->setRange(0,val);
   ui->State1->setText(tr("加热完成"));
}
/**************************************************/
void controlPanel::hasCom()
{
   // ui->IP1->setText(printer->getCom().at(0));
}

controlPanel::~controlPanel()
{
    delete ui;
}

void controlPanel::on_connect_clicked()     //连接串口
{
    QString port = ui->IP1->currentText();
    if(port=="")
    {
        QMessageBox::information(this,tr("警告"),tr("未选择串口！！"));
    }
    else
    {
        if(connected)
        {
           printer->disconnectCom();
           ui->connect->setText(tr("连接"));
           connected = false;
           machineControl->setControl(false);
           ui->Stop->setEnabled(false);
           ui->Cancle1->setEnabled(false);
           ui->Recovery->setEnabled(false);
           ui->Print1->setEnabled(false);
        }
        else
        {
            ui->connect->setText(tr("正在连接.."));
            connected = printer->connectCom(port);
        }
    }
}

void controlPanel::on_Setting_clicked()     //显示控制面板
{
    machineControl->show();
    machineControl->raise();
}

void controlPanel::on_loadfile_clicked()     //添加可打印的gcode
{
    QString openFile = QFileDialog::getOpenFileName(this,tr("选择打印文件"),".",tr("模型文件( *.gcode)"));
    ui->State1->setText(tr("已装载文件%1").arg(QFileInfo(openFile).fileName()));
    printableList.clear();
    if(!openFile.isEmpty())
    printableList.append(openFile);
}

void controlPanel::on_Print1_clicked()      //打印按钮
{
    if(connected)
    {

        if(printableList.count()>0)
        {
            printer->beginPrint(printableList);
        }
        else
        {
            QMessageBox::information(this,tr("提示"),tr("没有装载打印文件"));
        }
        ui->State1->setText(tr("正在打印"));
    }
    else
    {
        QMessageBox::information(this,tr("警告"),tr("没有链接打印机！"));
        qDebug()<<tr("没有连接打印机！");
    }
}

void controlPanel::on_Stop_clicked()        //打印暂停
{
    if(stoped)
    {
        ui->State1->setText(tr("打印暂停"));
        stoped = true;
    }
    emit Sig_stopRecover(false);
}

void controlPanel::on_Recovery_clicked()    //恢复打印
{
    if(stoped)
    {
        stoped = false;
        ui->State1->setText(tr("打印恢复"));
    }
    emit Sig_stopRecover(true);
}

void controlPanel::on_Cancle1_clicked()     //取消打印
{
    stoped = true;

    emit Sig_canclePrint();
    ui->Temp1->setText("0");
    ui->Prog1->setValue(0);

    ui->State1->setText(tr("空闲"));
}
