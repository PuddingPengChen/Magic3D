#include "mainbutton.h"
#include "ui_mainbutton.h"

MainButton::MainButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainButton)
{
    ui->setupUi(this);
//    ui->ModelButton->setText(tr("Model"));
//    ui->SupportMode->setText(tr("Support"));
//    ui->PrintMode->setText(tr("Print"));
}

MainButton::~MainButton()
{
    delete ui;
}

void MainButton::on_ModelButton_clicked()
{
    emit Sig_ModelMode();
}

void MainButton::on_SupportMode_clicked()
{
    emit Sig_SupportMode();
}

void MainButton::on_PrintMode_clicked()
{
    emit Sig_PrintMode();
}
