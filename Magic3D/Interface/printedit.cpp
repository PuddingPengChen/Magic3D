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
    show = false;

    servPort = 3333;
    connected = false;
    Sliced = false;
    tcpSocket = new QTcpSocket();

    move_len = 100;
    Thickness_Config = THICK_HIGHT;
    Resin_Config = SPOT_G;
    init_comm();

//    myTimer = new QTimer(this);
//    connect(myTimer,SIGNAL(timeout()),this,SLOT(timerTask()));

//    HeartBeat = new QTimer(this);
//    connect(HeartBeat, SIGNAL(timeout()), this,SLOT(HeartBeatTask()));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(HostConnected()));  //if connected,tcpsocket will emin signal connected()
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(HostDisconnected()));
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(HostError()));
}


/***************************************/
FileTransmit_Thread::FileTransmit_Thread(QObject *parent)
    : QThread(parent)
{
}

FileTransmit_Thread::~FileTransmit_Thread()
{

}
void FileTransmit_Thread::cmd_send_2(cmd_t *cmd)
{
    if(file_tcpSocket->write((char *)cmd,sizeof(cmd_t))==-1)
    {
        perror("send cmd error\n");
        exit(1);
    }
}

void FileTransmit_Thread::status_recv_2(feedback_t *fback)
{
    int recvbytes;
    printf("wait feedback\n");
    file_tcpSocket->waitForReadyRead(-1);
    recvbytes = file_tcpSocket->read((char *)fback,sizeof(feedback_t));
    if(recvbytes == -1)
    {
        perror("recv feedback error \n");
        exit(1);
    }
}

u_int
FileTransmit_Thread::ssh_crc32_s(char *s, u_int len,u_int crc32val_temp)
{
    u_int i;
    u_int crc32val;

    crc32val = crc32val_temp;
    for (i = 0;  i < len;  i ++) {
    crc32val = crc32_tab[(crc32val ^ s[i]) & 0xff] ^ (crc32val >> 8);             }
    return crc32val;
}

void FileTransmit_Thread::run()
{
    FILE * fd;
//    QFile fle(for_threaduse_dic);
    int length;
    unsigned int crc32 = 0;
    int finish[2];
    int i = 0;
    char * f_char;
    char * filename;

    file_tcpSocket  = new QTcpSocket();
    file_IP = for_threaduse_IP;

    //printf("socket state = %d \n", file_tcpSocket->state());
    file_tcpSocket->connectToHost(file_IP, SERVPORT_FILE);

    QByteArray ba = for_threaduse_dic.toLatin1();
    filename = ba.data();

    QFile Qfile(for_threaduse_dic);
    if (!Qfile.open(QIODevice::ReadOnly))
    {
      return;
    }

    fd = fopen(filename,"rb");
    if(fd == NULL)
    {
        printf("open the file %s failed\n",filename);
    }
    Enable_User_Waiting_Cursor();

    LoadingBar loadbar(0,(int)(Qfile.size()/1024-1));
    loadbar.useCancelButton(false);
    loadbar.setDescription("Sending SVG file to server... " );
    while((length = fread(file_command.buf,1,MAXDATASIZE, fd))>0)
    {
        file_command.cmd = for_threaduse_cmd;
        file_command.buf_len = length;
        cmd_send_2(&file_command);

        status_recv_2(&file_fback);
        if(file_fback.status == WORK_NORMAL)
        {
            printf("%d send %d bytes\n",i++,length);
            loadbar.setValue(i);
        }

        crc32 = ssh_crc32_s(file_command.buf,length,crc32);
    }

    Disable_User_Waiting_Cursor();
    finish[0] = FINISH_MARK;
    finish[1] = crc32;
    printf("crc32 = %d\n",crc32);
    f_char = (char * ) finish;
    for(i=0;i<sizeof(int)*2;i++)
        file_command.buf[i] = f_char[i];
    file_command.buf_len = sizeof(int)*2;
    cmd_send_2(&file_command);
    fclose(fd);

    status_recv_2(&file_fback);
    if(file_fback.status)
    {
        printf("the file is sending success\n");
    }
    file_tcpSocket->disconnectFromHost();
    delete(file_tcpSocket);
}

PrintEdit::~PrintEdit()
{
    delete ui;
}
int PrintEdit::send_file_2(int cmd, QString str)
{
    mythread = new FileTransmit_Thread();
    mythread->for_threaduse_IP = this->IPstr;
    mythread->for_threaduse_cmd = cmd;
    mythread->for_threaduse_dic = str;
    mythread->start();
    return 1;
}
void PrintEdit::timerTask()
{
    if(connected)
    {
        get_layers_status(LAYERS_STATUS);
//        myTimer->start(10000);
    // printf("time out\n");
    }
}

void PrintEdit::HeartBeatTask()
{
    printf("execut heartbeat!\n");
    if(connected)
    {
        command.cmd = HEARTBEAT;
        command.buf_len = 0;
        cmd_send(&command);
        printf("Heartbeat--%d\n",beatcnt);
        log_out("Heartbeat--");
//        HeartBeat->start(3000);//3000ms 3s
        beatcnt++;

        status_recv(&fback); //waiting
        if(fback.status)
        {
            printf("Server:Beat normal\n");
            log_out("Server:Beat normal");
        }
    }
}
/**************************************************/
/**********该函数为显示剖面按键按下时触发的函数*********/
/**************************************************/
void PrintEdit::on_ImageButton_clicked()
{
    show = true;
    emit Sig_ImageShow(show);
}
/**************************************************/
/************该函数为Slice按键按下时触发的函数*********/
/**************************************************/
void PrintEdit::on_SliceButton_clicked()
{
    log_out("Slicing......");
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
//    IPstr = ui->lineEdit->text();
//        if((!connected)&&(IsIPaddress(IPstr)==true))
//        {
//               tcpSocket->connectToHost(IPstr, servPort);
//        }
//        else if((!connected)&&((IsIPaddress(IPstr))==false))
//        {
//            ui->IP_label->setText("IP error!!");
//            ui->lineEdit->clear();
//        }
//        else if(connected)
//        {
//            close_server(); //send WORKOVER cmd
//            tcpSocket->disconnectFromHost();

//        }
}
void PrintEdit::HostConnected()
{
    printf("socket state = %d \n", tcpSocket->state());
    ui->ConnectButton->setText("DisConnect");
    ui->IP_label->setText("3D printer has connected");
    status=hand_server();
    if(ONLINE == status)
    {
        log_out("3D priter is bussy\n");
    }
    else if(OFFLINE == status)
    {
        log_out("you can use 3D printer\n");
        connected =true;
    }
    if(Sliced&connected)
    {
        ui->PrintButton->setEnabled(true);
        ui->StopPrintButton->setEnabled(true);
        ui->RecoverButton->setEnabled(true);
        ui->ResetButton->setEnabled(true);
    }
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
    ui->IP_label->setText("Connect error!Please check the printer");
}

/*base founction*/
void PrintEdit::cmd_send(cmd_t *cmd)
{
    if(tcpSocket->write((char *)cmd,sizeof(cmd_t))==-1)
    {
        perror("send cmd error\n");
        exit(1);
    }
}

void PrintEdit::status_recv(feedback_t *fback)
{
    int recvbytes;
    printf("wait feedback\n");
    tcpSocket->waitForReadyRead(3000);//timeout = 3000 ms
    recvbytes = tcpSocket->read((char *)fback,sizeof(feedback_t));
    if(recvbytes == -1)
    {
        perror("recv feedback error \n");
        exit(1);
    }
    printf("server have feedback!：%s\n",fback->buf);
}
int PrintEdit::hand_server()
{
    command.cmd = HANDSHAKE;
    command.buf_len= sizeof(int);

    cmd_send(&command);
    printf("send command\n");
    status_recv(&fback);
    return (fback.status);
}
int PrintEdit::close_server()
{
    command.cmd = WORK_OVER;
    command.buf_len = 0;

    cmd_send(&command);
}
void PrintEdit::get_info(int cmd)
{
    info_t * info_temp;
    command.cmd = GET_INFO;
    command.buf_len = 0;

    cmd_send(&command);
    status_recv(&fback);

    info_temp = (info_t *)(fback.buf);

    printf("the version is %d\n",info_temp->version);

    QString ver = QString::number(info_temp->version,10);
    log_out("the version is "+ver);
}
int PrintEdit::send_para(int cmd,int Thickness, int Resin)
{
    char * para;
    int i;
    para_t parameter;
    parameter.Resin_config = Resin;
    parameter.Thick_config = Thickness;

    command.cmd = cmd;
    command.buf_len = sizeof(para_t);
    para = (char *)(&parameter);
    for(i=0;i<command.buf_len;i++)
        command.buf[i] = para[i];

    cmd_send(&command);
    status_recv(&fback);

    if(fback.status)
    {
        printf("the parameters is sending success\n");
        log_out("the parameters is sending success");
    }
}

int PrintEdit::start_print(int cmd)
{
    command.cmd = cmd;
    command.buf_len = 0;
    cmd_send(&command);

    status_recv(&fback);
    if(fback.status)
    {
        printf("the printer is start working\n");
        log_out("teh printer is start working");
    }
    return 1;
}
int PrintEdit::send_motor_len(int cmd, int direction, int len)
{
    char *temp;
    int i =0;
    command.cmd = cmd;
    command.buf_len = sizeof(int)*2;

    temp = (char *)&direction;
    for(i=0;i<sizeof(int);i++)
        command.buf[i] = temp[i];
    temp = (char *)&len;
    for(i=0;i<sizeof(int);i++)
        command.buf[i+4] = temp[i];

    cmd_send(&command);

    status_recv(&fback);
    if(fback.status)
    {
        printf("the motor move normal\n");
        log_out("the motor move normal");
    }
}

int PrintEdit::get_layers_status(int cmd)
{
    int *layer;
    command.cmd = cmd;
    command.buf_len = 0;

    cmd_send(&command);
    status_recv(&fback);
    layer = (int *)fback.buf;
    if(fback.status)
    {
        if(*layer == -1)
            log_out("the 3D printer is not printing\n");
        else
        {
            pworld->setLayerValue(*layer);
            QString layers = QString::number(*layer,10);
            log_out("the 3D printer is printing at layers"+layers);
         }
    }
    return 1;
}

int PrintEdit::send_hung_cmd(int cmd)
{
    command.cmd = cmd;
    command.buf_len = 0;

    cmd_send(&command);
    status_recv(&fback);
    if(fback.status)
    {
        printf("the 3D printer is hung\n");
        log_out("the 3D printer is hung");
    }
    return 1;
}

int PrintEdit::send_recover_cmd(int cmd)
{
    command.cmd = cmd;
    command.buf_len = 0;

    cmd_send(&command);
    status_recv(&fback);
    if(fback.status)
    {
        printf("the 3D printer is recovering\n");
        log_out("the 3D printer is recovering");
    }
    return 1;
}

int PrintEdit::init_motor(int cmd, int up_down)
{
    char *temp;
    int i =0;
    command.cmd = cmd;
    command.buf_len = sizeof(int)*3;

    temp = (char *)&up_down;
    for(i=0;i<sizeof(int);i++)
        command.buf[i+8] = temp[i];

    cmd_send(&command);

    status_recv(&fback);
    if(fback.status)
    {
        printf("init motor move normal\n");
        log_out("init motor move normal");
    }
}

void PrintEdit::log_out(QString str)
{
    ui->InforBrowser->append(str);
}

void PrintEdit::on_PrintButton_clicked()        //print button
{
    QString directory = "./test.svg";
    if(connected)
    {
        command.cmd = SEND_FILE;
        command.buf_len = 0;
        cmd_send(&command);

        status_recv(&fback);
        if(fback.status == COMMAND_VALID)
        {
            printf("start to transmit file...\n");
            log_out("start to transmit file...");
        }
        Sleep(2);
        send_file_2(FILE_PACKAGE,directory);
        log_out("Transmit finish.");
        send_para(SEND_PARA,Thickness_Config,Resin_Config);
        log_out("Now start print job...");
        start_print(START_PRINT);

    }
}
/********************************************************************/
/****************The following function is just for debug************/
/********************************************************************/
void PrintEdit::on_StopPrintButton_clicked()        //stop button
{
    if( connected)
    {
        send_hung_cmd(HUNG_CMD);
//        myTimer->stop();
    }
}
void PrintEdit::on_RecoverButton_clicked()      //recover button
{
    if(connected)
    {
        send_recover_cmd(RECOVER);
    }
}

void PrintEdit::on_ResetButton_clicked()        //reset button
{
    if(connected)
    {
        send_recover_cmd(RESET_PRINTER);
    }
}

void PrintEdit::on_toolButton_clicked()
{
    ui->InforBrowser->clear();
}

//void PrintEdit::on_Hight_radioButton_clicked()      //100um radiobutton
//{
//    emit Sig_Thickness(100);
//    Thickness_Config = THICK_HIGHT;
//}

//void PrintEdit::on_Mid_radioButton_clicked()        //50mm radiobutton
//{
//    emit Sig_Thickness(50);
//    Thickness_Config = THICK_MID;
//}

//void PrintEdit::on_Low_radioButton_clicked()        //25mm radiobutton
//{
//    emit Sig_Thickness(25);
//    Thickness_Config = THICK_LOW;
//}
/**********************************************/
/******************选择树脂的种类****************/
/*********************************************/
//void PrintEdit::on_SpG_radioButton_clicked()        //Spot-G resin
//{
//    Resin_Config = SPOT_G;
//}

//void PrintEdit::on_SpH_radioButton_5_clicked()      //Spot-Ht
//{
//    Resin_Config = SPOT_HT;
//}
//void PrintEdit::on_MjG_radioButton_6_clicked()      //MakerJuice-G+
//{
//    Resin_Config = MAKERJUICE_G;
//}
//void PrintEdit::on_MjS_radioButton_7_clicked()      //MakerJuice-SF
//{
//    Resin_Config = MAKERJUICE_SF;
//}
