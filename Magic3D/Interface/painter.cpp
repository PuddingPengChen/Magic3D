#include "painter.h"
#include "ui_painter.h"
#include <QPainter>
#include <QPolygon>
#include <QDebug>
#include "../SliceEngine/utils/intpoint.h"
Painter::Painter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Painter)
{
    ui->setupUi(this);
    pix = QPixmap(this->width(),this->height());
//    pix.fill(QColor(126,19,18,128));
    pix.fill(Qt::white);
}

Painter::~Painter()
{
    delete ui;
}
void Painter::paintEvent(QPaintEvent *)
{
    QPainter pp(this);
    pp.drawPixmap(0,0,pix);
    pix.fill(Qt::lightGray);
//    qDebug()<<"Paining...";

}
void Painter::show_layer(SliceDataStorage * storage, int layers_n)
{
    QPainter pt(&pix);
  //  qDebug()<<"in the show layer dialog";
    Point3 modelSize = storage->modelSize;
    Point3 modelMin = storage->modelMin;

    for(unsigned int volumeIdx=0; volumeIdx<storage->volumes.size(); volumeIdx++)
    {
            SliceLayer* layer = &storage->volumes[volumeIdx].layers[layers_n];
            for(unsigned int i=0;i<layer->parts.size();i++)
            {

                SliceLayerPart* part = &layer->parts[i];
                for(unsigned int j=0;j<part->outline.size();j++)
                {   
                    QPolygon poly;
                    for(unsigned int k=0;k<part->outline[j].size();k++)
                    {
                        QPoint one;
                        //qDebug()<<tr("x=%1,y=%2").arg(float(part->outline[j][k].X-modelMin.x)/modelSize.vSize()*100).arg(float(part->outline[j][k].Y-modelMin.y)/modelSize.vSize()*100);
                        one.setX(this->width()/2-100+float(part->outline[j][k].X-modelMin.x)/modelSize.vSize()*300);
                        one.setY(this->height()/2-100+float(part->outline[j][k].Y-modelMin.y)/modelSize.vSize()*300);
                        poly<<one;
                    }
                    //glEnd();
                    if(j==0)
                        pt.setBrush(Qt::darkGray);
                    else
                        pt.setBrush(Qt::lightGray);
                    pt.drawPolygon(poly,Qt::OddEvenFill);
                }
            }

    }
}
