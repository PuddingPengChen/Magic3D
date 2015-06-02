#include "imageviewwidget.h"
#include "ui_imageviewwidget.h"

ImageViewWidget::ImageViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageViewWidget)
{
    ui->setupUi(this);
    m_painter = ui->LayerShowWidget;
//    SliderValue = -1;
}

ImageViewWidget::~ImageViewWidget()
{
    delete ui;
}

void ImageViewWidget::on_LayerSlider_valueChanged(int value)
{
    m_painter->show_layer(storg,value);
    m_painter->update();
    ui->label->setText(tr("%1").arg(value));
    emit Sig_SliderValue(value);
//    SliderValue = value;

}
void ImageViewWidget::ReceiveStroage(SliceDataStorage *sto)
{
    storg = sto;
    ui->LayerSlider->setRange(0,(storg->volumes[0].layers.size())-1);
}

void ImageViewWidget::on_CloseButton_clicked()
{
    this->close();
    emit Sig_printEditShow();
}
