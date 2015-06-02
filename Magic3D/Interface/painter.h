/*******************************************************************************
*                                                                              *
* Author    :  Peng Chen                                                       *
* Version   :  0.0.1                                                           *
* Date      :  12 July 2014                                                    *
* Website   :  http://www.3green-tech.com                                      *
* Copyright :  3green-tech 2010-2014                                           *
*                                                                              *
* Attributions:                                                                *
* Painter was used for paint the slice layer.                                  *
*******************************************************************************/
#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include "../SliceEngine/sliceDataStorage.h"
namespace Ui {
class Painter;
}

class Painter : public QWidget
{
    Q_OBJECT
    
public:
    explicit Painter(QWidget *parent = 0);
    ~Painter();
    
    void paintEvent(QPaintEvent *);
    void show_layer(SliceDataStorage * storage,int layers_n);

    QPixmap pix;

    SliceDataStorage *storage;
    int layers_n;
private:
    Ui::Painter *ui;
};

#endif // PAINTER_H
