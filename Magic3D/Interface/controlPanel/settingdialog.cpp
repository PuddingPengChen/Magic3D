#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    steps = 1.0;
    x_pos = 0;
    y_pos = 0;
    z_pos = 0;
    ui->frame->setEnabled(false);
    this->setWindowTitle(tr("打印机设置"));
    ui->cusplot->xAxis->setLabel(tr("时间轴"));
    ui->cusplot->yAxis->setLabel(tr("温度值℃"));
    ui->cusplot->yAxis->setRange(0, 100);

    ui->cusplot->addGraph(); // blue line
    ui->cusplot->graph(0)->setPen(QPen(Qt::blue));
    ui->cusplot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->cusplot->addGraph(); // red line
    ui->cusplot->graph(1)->setPen(QPen(Qt::red));

    ui->cusplot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->cusplot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->cusplot->xAxis->setAutoTickStep(false);
    ui->cusplot->xAxis->setTickStep(2);
    ui->cusplot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->cusplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->cusplot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->cusplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->cusplot->yAxis2, SLOT(setRange(QCPRange)));

    QSettings* psetting = new QSettings("printerConfig.ini",QSettings::IniFormat);
    psetting->beginGroup("preheart");
    ui->lineEdit_2->setText(psetting->value("preTime").toString());
    ui->lineEdit_3->setText(psetting->value("preTemp").toString());
    psetting->endGroup();
    QSettings* psetting1 = new QSettings("printerConfig.ini",QSettings::IniFormat);
    psetting1->beginGroup("slice");
    ui->filamentDiameter->setText(psetting1->value("diameter").toString());
    ui->extrusionWidth->setText(psetting1->value("widthE").toString());
    ui->printSpeed->setText(psetting1->value("printSpeed").toString());
    psetting1->endGroup();

    exculuerSpeed = 5000;
    exculuerSpeed = ui->excurdSpeed->text().toInt();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
void SettingDialog::upd()
{
   double iy = (double)(qrand()%100);
   emit Sig_updateTemp(35.0,iy);
}
void SettingDialog::realTimeSlot(double target,double real)
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    // add data to lines:
    // 目标温度
    // 实际温度
    ui->cusplot->graph(0)->addData(key, target);
    ui->cusplot->graph(1)->addData(key, real);

    // remove data of lines that's outside visible range:
    ui->cusplot->graph(0)->removeDataBefore(key-10);
    ui->cusplot->graph(1)->removeDataBefore(key-10);
    // rescale value (vertical) axis to fit the current data:
    ui->cusplot->graph(0)->rescaleValueAxis();
    ui->cusplot->graph(1)->rescaleValueAxis(true);

    ui->cusplot->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->cusplot->replot();
}
void SettingDialog::on_xHome_clicked()  //X home
{
    QString cmd;
    x_pos = 0;
    cmd = "G28 X \n";
    emit Sig_cmd(cmd);
}

void SettingDialog::on_yHome_clicked()  //Y home
{
    QString cmd = "G28 Y \n";
    y_pos = 0;
    emit Sig_cmd(cmd);
}

void SettingDialog::on_zHome_clicked()  //Z home
{
    QString cmd = "G28 Z \n";
    z_pos = 0;
    emit Sig_cmd(cmd);
}

void SettingDialog::on_xDele_2_clicked()    //Home
{
    QString cmd = "G28 F1000 \n";
    x_pos = 0;
    y_pos = 0;
    z_pos = 0;
    emit Sig_cmd(cmd);
}

void SettingDialog::on_xPlus_clicked()      //X plus
{
    x_pos = x_pos+steps;
    QString cmd = tr("G1 F1800 X%1 \n").arg(x_pos);
    emit Sig_cmd(cmd);
}

void SettingDialog::on_xDele_clicked()      //X dele
{
    x_pos = x_pos-steps;
    QString cmd = tr("G1 F1800 X%1 \n").arg(x_pos);
    emit Sig_cmd(cmd);
}

void SettingDialog::on_yDele_clicked()      //Y plus
{
    y_pos = y_pos+steps;
    QString cmd = tr("G1 F1800 Y%1 \n").arg(y_pos);
    emit Sig_cmd(cmd);
}

void SettingDialog::on_yPlus_clicked()      //Y dele
{
    y_pos = y_pos-steps;
    QString cmd = tr("G1 F1800 Y%1 \n").arg(y_pos);
    emit Sig_cmd(cmd);
}
void SettingDialog::on_zPlus_clicked()      //Z plus
{
    z_pos = z_pos+steps;

    QString cmd = tr("G1 F200 Z%1 \n").arg(z_pos);
    emit Sig_cmd(cmd);
}

void SettingDialog::on_zDele_clicked()      //Z dele
{
    z_pos = z_pos-steps;
    QString cmd = tr("G1 F200 Z%1 \n").arg(z_pos);
    emit Sig_cmd(cmd);
}
void SettingDialog::showMessage(QString str)
{
    ui->textBrowser->append(str);
}
void SettingDialog::on_tempture_clicked()   //tempture
{
    QString cmd = "M105 \n";
    emit Sig_cmd(cmd);
}
void SettingDialog::setControl(bool t)
{
    ui->frame->setEnabled(t);
}
void SettingDialog::on_lineEdit_returnPressed()     //command send
{
    QString cmd = ui->lineEdit->text();
    ui->textBrowser->append(QObject::tr("发送指令:%1").arg(cmd));
    emit Sig_cmd(tr("%1\n").arg(cmd));
}

void SettingDialog::on_radioButton_clicked()        //step = 1
{
    steps = 0.1;
}

void SettingDialog::on_radioButton_2_clicked()      //step = 10
{
    steps = 1.0;
}


void SettingDialog::on_radioButton_3_clicked()      //step = 100
{
    steps = 10.0;
}

void SettingDialog::on_ePlus_clicked()      //E excluder
{
    emit Sig_cmd("G91 \n");
    emit Sig_cmd(tr("G1 E%1 F%2 \n").arg(ui->outlong->text().toInt()).arg(exculuerSpeed));
    emit Sig_cmd("G90 \n");
}

void SettingDialog::on_eDele_clicked()      //E recation
{
    emit Sig_cmd("G91 \n");
    emit Sig_cmd(tr("G1 E-%1 F%2 \n").arg(ui->outlong->text().toInt()).arg(exculuerSpeed));
    emit Sig_cmd("G90 \n");
}
void SettingDialog::on_lineEdit_2_returnPressed()       //preheart time
{
    int time = ui->lineEdit_2->text().toInt();
    QSettings *settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("preheart");
    settings->setValue("preTime",QVariant(time));
    settings->endGroup();
}

void SettingDialog::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{
    int temp = ui->lineEdit_3->text().toInt();
    QSettings* settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("preheart");
    settings->setValue("preTemp",QVariant(temp));
    settings->endGroup();
}
void SettingDialog::on_lineEdit_3_returnPressed()   //
{
    int temp = ui->lineEdit_3->text().toInt();
    QSettings* settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("preheart");
    settings->setValue("preTemp",QVariant(temp));
    settings->endGroup();
}

void SettingDialog::on_pushButton_clicked()
{
    this->close();
}

void SettingDialog::on_outlong_returnPressed()
{

}

void SettingDialog::on_sendGcode_clicked()  //发送Gcode的按键
{
    QString cmd = ui->lineEdit->text();
    ui->textBrowser->append(QObject::tr("发送指令:%1").arg(cmd));
    emit Sig_cmd(tr("%1").arg(cmd));
}

void SettingDialog::on_excurdSpeed_returnPressed()      //回抽速度
{
    exculuerSpeed = ui->excurdSpeed->text().toInt();
}

void SettingDialog::on_filamentDiameter_returnPressed() //耗材直径
{
    int temp = ui->filamentDiameter->text().toInt();
    QSettings* settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("slice");
    settings->setValue("diameter",QVariant(temp));
    settings->endGroup();
}

void SettingDialog::on_extrusionWidth_returnPressed()   //挤出宽度
{
    int temp = ui->extrusionWidth->text().toInt();
    QSettings* settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("slice");
    settings->setValue("widthE",QVariant(temp));
    settings->endGroup();
}

void SettingDialog::on_printSpeed_returnPressed()       //打印速度
{
    int temp = ui->printSpeed->text().toInt();
    QSettings* settings = new QSettings("printerConfig.ini",QSettings::IniFormat);
    settings->beginGroup("slice");
    settings->setValue("printSpeed",QVariant(temp));
    settings->endGroup();
}
void SettingDialog::slot_close()
{
    this->close();
}
