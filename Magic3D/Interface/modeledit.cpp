#include "modeledit.h"
#include "ui_modeledit.h"
#include <QColorDialog>

ModelEdit::ModelEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModelEdit)
{
    ui->setupUi(this);
    selected = false;
}
ModelEdit::~ModelEdit()
{
    delete ui;
}
void ModelEdit::AddModelItem(QListWidgetItem* item)
{
    ui->ModelList->addItem(item);
}
QListWidget* ModelEdit::GetModelList()
{
    return ui->ModelList;
}
QLineEdit* ModelEdit::GetLineEdit()
{
    return ui->lineEdit_scale;
}

void ModelEdit::on_AddModelButton_clicked()
{
    emit Sig_AddModel();
    UI_control(true);
}

void ModelEdit::on_DuplicateModeButton_clicked()
{
    emit Sig_DuplicateModel();
}

void ModelEdit::on_RemoveModelButton_clicked()
{
    emit Sig_RemoveModel();
}

void ModelEdit::on_ModelScaleButton_clicked()
{
    double scale_value = ui->lineEdit_scale->text().toDouble();
    emit  Sig_ScaleModel(scale_value);
}

void ModelEdit::on_ModelSelectedButton_clicked()
{
    emit Sig_SelectedModel();
}

void ModelEdit::on_RestRotButton_clicked()
{
    emit Sig_ResetRotModel();
//    ui->dial_x->setValue(0);
//    ui->dial_y->setValue(0);
//    ui->dial_z->setValue(0);
}

void ModelEdit::on_ModelRotButton_clicked()
{
    emit Sig_RotModel();
}


void ModelEdit::on_ModelSnapButton_clicked()
{
    emit Sig_SnapModel();
}

void ModelEdit::on_ModelMoveButton_clicked()
{
    emit Sig_MoveModel();
}

void ModelEdit::on_ModelExportButton_clicked()
{
    emit Sig_ExportModel();
}

//void ModelEdit::on_ScaleLineEdit_returnPressed()
//{
//    QString mm = ui->ScaleLineEdit->text();
//    double scale_value = mm.toDouble();
//    emit  Sig_ScaleModel(scale_value);
//}


//void ModelEdit::on_dial_x_valueChanged(int value)
//{
//    emit Sig_RotX(value/10.0);
//}

//void ModelEdit::on_dial_y_valueChanged(int value)
//{
//    emit Sig_RotY(value/10.0);
//}

//void ModelEdit::on_dial_z_valueChanged(int value)
//{
//    emit Sig_RotZ(value/10.0);
//}
void ModelEdit::SetZ_value(double m)
{
    QString pp = QString(tr("%1").arg(m));
    ui->SupZ_linedit->setText(pp);
}
void ModelEdit::SetPosText(QVector3D m)
{
//    ui->label_sizex->setText(QString().number(m.x()));
    ui->label_sizex->setText(QString("%1").arg(m.x()));
    ui->label_sizey->setText(QString().number(m.y()));
    ui->label_sizez->setText(QString().number(m.z()));
}
void ModelEdit::SetRotText(QVector3D m)
{
    ui->lineEdit_rotx->setText(QString("%1").arg(m.x()));
//    ui->label_rotVx->setText(QString().number(m.x()));
    ui->lineEdit_roty->setText(QString().number(m.y()));
    ui->lineEdit_rotz->setText(QString().number(m.z()));



}

//void ModelEdit::on_doubleSpinBox_valueChanged(double arg1)
//{
//   emit  Sig_ScaleModel(arg1);
//}


void ModelEdit::on_ColorButton_clicked()
{
    emit Sig_ModelColor();
}

void ModelEdit::on_lineEdit_scale_returnPressed()
{
    QString scale = ui->lineEdit_scale->text();
    emit Sig_ScaleModel(scale.toDouble());
}

void ModelEdit::on_lineEdit_rotx_returnPressed()
{
    float rot_x = ui->lineEdit_rotx->text().toDouble();

    emit Sig_RotX(rot_x);
}

void ModelEdit::on_lineEdit_roty_returnPressed()
{
    float rot_y = ui->lineEdit_roty->text().toDouble();
//    ui->dial_x->setValue(rot_y*10);
    emit Sig_RotY(rot_y);
}

void ModelEdit::on_lineEdit_rotz_returnPressed()
{
    float rot_z = ui->lineEdit_rotz->text().toDouble();
//    ui->dial_x->setValue(rot_z*10);
    emit Sig_RotZ(rot_z);
}

void ModelEdit::IsModelSelected(bool selecte)
{
    selected = selecte;
    UI_control(selected);

}
void ModelEdit::UI_control(bool hp)
{
    if(hp)
    {

        ui->ColorButton->setEnabled(true);
        ui->DuplicateModeButton->setEnabled(true);
        ui->lineEdit_rotx->setEnabled(true);
        ui->lineEdit_roty->setEnabled(true);
        ui->lineEdit_rotz->setEnabled(true);
        ui->lineEdit_scale->setEnabled(true);
        ui->ModelExportButton->setEnabled(true);
        ui->ModelMoveButton->setEnabled(true);
        ui->ModelRotButton->setEnabled(true);
        ui->ModelSelectedButton->setEnabled(true);
        ui->ModelSnapButton->setEnabled(true);
        ui->RemoveModelButton->setEnabled(true);
        ui->RestRotButton->setEnabled(true);
        ui->SupZ->setEnabled(true);
        ui->SupZ_linedit->setEnabled(true);
    }
    else
    {
        ui->ColorButton->setEnabled(false);
        ui->DuplicateModeButton->setEnabled(false);
        ui->lineEdit_rotx->setEnabled(false);
        ui->lineEdit_roty->setEnabled(false);
        ui->lineEdit_rotz->setEnabled(false);
        ui->lineEdit_scale->setEnabled(false);
        ui->ModelExportButton->setEnabled(false);
        ui->ModelMoveButton->setEnabled(false);
        ui->ModelRotButton->setEnabled(false);
        ui->ModelSelectedButton->setEnabled(false);
        ui->ModelSnapButton->setEnabled(false);
        ui->RemoveModelButton->setEnabled(false);
        ui->RestRotButton->setEnabled(false);
        ui->SupZ->setEnabled(false);
        ui->SupZ_linedit->setEnabled(false);
    }
}

void ModelEdit::on_SupZ_linedit_returnPressed()
{
    qreal Sup_Z = ui->SupZ_linedit->text().toDouble();
    QVector3D Rect = QVector3D(0,0,Sup_Z);
    emit Sig_SupZ(Rect);
}

void ModelEdit::on_SupZ_clicked()
{
    qreal Sup_Z = ui->SupZ_linedit->text().toDouble();
    QVector3D Rect = QVector3D(0,0,Sup_Z);
    emit Sig_SupZ(Rect);
}
