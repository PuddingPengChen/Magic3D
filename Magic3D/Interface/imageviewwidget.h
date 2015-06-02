/*******************************************************************************
*                                                                              *
* Author    :  Peng Chen                                                       *
* Version   :  0.0.1                                                           *
* Date      :  12 July 2014                                                    *
* Website   :  http://www.3green-tech.com                                      *
* Copyright :  3green-tech 2010-2014                                           *
*                                                                              *
* Attributions:                                                                *
* Used for show the layer image,show every slice layer image                   *                                                         *
*******************************************************************************/
#ifndef IMAGEVIEWWIDGET_H
#define IMAGEVIEWWIDGET_H

#include <QWidget>
#include "../SliceEngine/sliceDataStorage.h"
#include "painter.h"

namespace Ui {
class ImageViewWidget;
}

class ImageViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageViewWidget(QWidget *parent = 0);
    ~ImageViewWidget();
protected:
    void closeEvent(QCloseEvent *){emit Sig_SliderValue(-1);}
    void hideEvent(QHideEvent *){emit Sig_SliderValue(-1);}
public slots:


private slots:
    void on_LayerSlider_valueChanged(int value);
    void ReceiveStroage(SliceDataStorage *storage);

    void on_CloseButton_clicked();

private:
    Ui::ImageViewWidget *ui;
    SliceDataStorage *storg;
    Painter * m_painter;
//    int SliderValue;
signals:
    void Sig_printEditShow();
    void Sig_SliderValue(int);
};

#endif // IMAGEVIEWWIDGET_H
