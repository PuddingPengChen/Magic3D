#include "configset.h"
#include "ui_configset.h"

int MachineSetting=0;

ConfigSet::ConfigSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigSet)
{
    Revolution = 0;
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
}

ConfigSet::~ConfigSet()
{
    delete ui;
}

void ConfigSet::on_radioButton_clicked()
{
    Revolution = GuangI;
    MachineSetting = Revolution;
}

void ConfigSet::on_radioButton_2_clicked()
{
    Revolution = GuangII;
    MachineSetting = Revolution;
}
