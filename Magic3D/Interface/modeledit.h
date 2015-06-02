/*******************************************************************************
*                                                                              *
* Author    :  Peng Chen                                                       *
* Version   :  0.0.1                                                           *
* Date      :  12 July 2014                                                    *
* Website   :  http://www.3green-tech.com                                      *
* Copyright :  3green-tech 2010-2014                                           *
*                                                                              *
* Attributions:                                                                *
* When press the Modeledit button,a modeledit widget will be created.This      *
* widget implentment the scale,move and rotation the ModelEdit                 *
*******************************************************************************/
#ifndef MODELEDIT_H
#define MODELEDIT_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QDoubleSpinBox>
#include <QColor>
#include <QVector3D>

namespace Ui {
class ModelEdit;
}

class ModelEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit ModelEdit(QWidget *parent = 0);
    ~ModelEdit();
    void AddModelItem(QListWidgetItem* item);
    QListWidget* GetModelList();
    QLineEdit* GetLineEdit();
    void SetPosText(QVector3D m);
    void SetZ_value(double m);
    void SetRotText(QVector3D m);
    void UI_control(bool hp);
    bool selected;
public slots:
    void IsModelSelected(bool);
    
private:
    Ui::ModelEdit *ui;
signals:
    void Sig_AddModel();
    void Sig_DuplicateModel();
    void Sig_RemoveModel();
    void Sig_ScaleModel(double scale);
    void Sig_SelectedModel();
    void Sig_RotModel();
    void Sig_ResetRotModel();
    void Sig_SnapModel();
    void Sig_MoveModel();
    void Sig_ExportModel();
    void Sig_ModelColor();
    void Sig_SupZ(QVector3D);

    void Sig_RotX(float);
    void Sig_RotY(float);
    void Sig_RotZ(float);
private slots:
    void on_AddModelButton_clicked();
    void on_DuplicateModeButton_clicked();
    void on_RemoveModelButton_clicked();
    void on_ModelScaleButton_clicked();
    void on_ModelSelectedButton_clicked();
    void on_RestRotButton_clicked();
    void on_ModelRotButton_clicked();
    void on_ModelSnapButton_clicked();
    void on_ModelMoveButton_clicked();
    void on_ModelExportButton_clicked();
//    void on_ScaleLineEdit_returnPressed();
//    void on_dial_x_valueChanged(int value);
//    void on_dial_y_valueChanged(int value);
//    void on_dial_z_valueChanged(int value);
//    void on_doubleSpinBox_valueChanged(double arg1);
//    void on_doubleSpinBox_valueChanged(const QString &arg1);
    void on_ColorButton_clicked();
    void on_lineEdit_scale_returnPressed();
    void on_lineEdit_rotx_returnPressed();
    void on_lineEdit_roty_returnPressed();
    void on_lineEdit_rotz_returnPressed();
    void on_SupZ_linedit_returnPressed();
    void on_SupZ_clicked();
};

#endif // MODELEDIT_H
