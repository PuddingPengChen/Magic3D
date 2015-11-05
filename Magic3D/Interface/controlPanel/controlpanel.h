#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>
#include "printthread.h"
#include "readgcode.h"
#include "settingdialog.h"

namespace Ui {
class controlPanel;
}

class controlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit controlPanel(QWidget *parent = 0);
    ~controlPanel();
signals:
    void Sig_stopRecover(bool);
    void Sig_canclePrint();
    void Sig_disconnectPrinter();

public slots:
    void slotConnect(bool);
    void updateProgressBar(unsigned int);
    void updateTemp(float);
    void setTotalProgressBar(unsigned int val);
    void hasCom();

private slots:
    void on_connect_clicked();

    void on_Setting_clicked();

    void on_loadfile_clicked();

    void on_Print1_clicked();

    void on_Stop_clicked();

    void on_Recovery_clicked();

    void on_Cancle1_clicked();

private:
    bool connected;
    bool stoped;
    QStringList printableList;
    PrintThread* printer;
    SettingDialog* machineControl;

    Ui::controlPanel *ui;
};

#endif // CONTROLPANEL_H
