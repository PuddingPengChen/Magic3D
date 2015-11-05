#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
    void setControl(bool t);
signals:
    void Sig_cmd(QString);
    void Sig_updateTemp(double,double);
private slots:
    void on_xHome_clicked();
    void on_yHome_clicked();
    void on_zHome_clicked();
    void on_xDele_2_clicked();
    void on_xPlus_clicked();
    void on_xDele_clicked();
    void on_yDele_clicked();
    void on_yPlus_clicked();
    void on_zPlus_clicked();
    void on_zDele_clicked();
    void on_tempture_clicked();
    void on_lineEdit_returnPressed();
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_lineEdit_2_returnPressed();

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

    void on_ePlus_clicked();

    void on_eDele_clicked();
    void on_pushButton_clicked();
    void realTimeSlot(double,double);
    void upd();

    void on_lineEdit_3_returnPressed();

    void on_outlong_returnPressed();

    void on_sendGcode_clicked();

    void on_excurdSpeed_returnPressed();

    void on_filamentDiameter_returnPressed();

    void on_extrusionWidth_returnPressed();

    void on_printSpeed_returnPressed();

public slots:
    void showMessage(QString);
    void slot_close();
private:
    Ui::SettingDialog *ui;
    float steps;
    float x_pos;
    float y_pos;
    float z_pos;
    QTimer* timers;
    int exculuerSpeed;
};

#endif // SETTINGDIALOG_H
