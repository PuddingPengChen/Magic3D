/********************************************************************************
** Form generated from reading UI file 'imageviewwidget.ui'
**
** Created: Tue Jun 2 12:22:59 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWWIDGET_H
#define UI_IMAGEVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include <./Interface/painter.h>

QT_BEGIN_NAMESPACE

class Ui_ImageViewWidget
{
public:
    Painter *LayerShowWidget;
    QLabel *label;
    QSlider *LayerSlider;
    QFrame *shadowfram;
    QFrame *frame;
    QToolButton *CloseButton;

    void setupUi(QWidget *ImageViewWidget)
    {
        if (ImageViewWidget->objectName().isEmpty())
            ImageViewWidget->setObjectName(QString::fromUtf8("ImageViewWidget"));
        ImageViewWidget->resize(478, 337);
        ImageViewWidget->setStyleSheet(QString::fromUtf8("\n"
"QLabel\n"
"{\n"
"	font-family:\"Source Sans Pro\";\n"
"	 font-size: 16px;\n"
"    font-weight: regular;\n"
"	color:#FFF;\n"
"}\n"
"QWidget\n"
"{\n"
"	background-color: rgb(86, 86, 86);\n"
"}\n"
"QPushButton,QToolButton\n"
"{\n"
"    color: #424344;\n"
"    font-family: \"Source Sans Pro\";\n"
"    font-size: 11px;\n"
"    font-weight: regular;\n"
"}\n"
"\n"
"\n"
"QPushButton,QToolButton\n"
"{\n"
"    border: 1px solid yellow; /* dummy color -- is overridden below\n"
" */\n"
"	\n"
"}\n"
"\n"
"QPushButton,QToolButton\n"
"{\n"
"    border-radius: 4px;\n"
"    padding: 0px 15px;\n"
"   ;\n"
"    max-height: 100px;\n"
"    min-height: 16px;\n"
"}\n"
"\n"
"QPushButton,QToolButton\n"
"{\n"
"    border-color: #C0C1C3;\n"
"    background-color: #F6F7F9;\n"
"}\n"
"\n"
"QPushButton:hover,QToolButton:hover\n"
"{\n"
"    background-color: #FFF;\n"
"}\n"
"\n"
"QToolButton:pressed, QPushButton:pressed, QPushButton[btn-secondary=true]:pressed, QPushButton[btn-icon=true]:pressed\n"
"{\n"
"    background-color: qlineargrad"
                        "ient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E1E3, stop:.25 #F6F7F9);\n"
"}\n"
"\n"
"/*QToolButton:disabled,*/ \n"
"QPushButton:disabled\n"
"{\n"
"    background-color: #EAEBED;\n"
"    border-color: #E1E2E4;\n"
"    color: #C0C1C3;\n"
"}\n"
"QPushButton,QToolButton\n"
"{\n"
"    background-color: #2288C1;\n"
"    border-color: #006fa5;\n"
"    color: #fff;\n"
"}\n"
"\n"
"QPushButton:hover,QToolButton:hover\n"
"{\n"
"    background-color: #6C22E2;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0072a9, stop:.25 #2288C1);\n"
"}\n"
"\n"
"\n"
""));
        LayerShowWidget = new Painter(ImageViewWidget);
        LayerShowWidget->setObjectName(QString::fromUtf8("LayerShowWidget"));
        LayerShowWidget->setGeometry(QRect(71, 30, 391, 291));
        LayerShowWidget->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(ImageViewWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 299, 61, 31));
        label->setAlignment(Qt::AlignCenter);
        LayerSlider = new QSlider(ImageViewWidget);
        LayerSlider->setObjectName(QString::fromUtf8("LayerSlider"));
        LayerSlider->setGeometry(QRect(30, 29, 16, 255));
        LayerSlider->setStyleSheet(QString::fromUtf8("\n"
" QSlider::groove:vertical {\n"
"   /*  background: red;*/\n"
"   background-color:#2288C1;\n"
"	/*background-color: rgb(117, 195, 255);*/\n"
"     position: absolute; /* absolutely position 4px from the left and right of the widget. setting margins on the widget should work too... */\n"
"  border-radius: 5px;\n"
"     left: 4px; right: 4px;\n"
" }\n"
"\n"
" QSlider::handle:vertical {\n"
"     height: 10px;\n"
"    border-radius: 5px;\n"
"     background: green;\n"
"     margin: 0 -4px; /* expand outside the groove */\n"
" }\n"
"\n"
" QSlider::add-page:vertical\n"
" {\n"
"   /*  background: white;*/\n"
"     border-radius: 6px;\n"
"	background-color: rgb(21, 21, 225);\n"
" }\n"
"\n"
" QSlider::sub-page:vertical\n"
" {\n"
"    /* background: pink;*/  \n"
"   border-radius: 6px;\n"
"	background-color: rgb(97, 192, 255);\n"
" }"));
        LayerSlider->setOrientation(Qt::Vertical);
        shadowfram = new QFrame(ImageViewWidget);
        shadowfram->setObjectName(QString::fromUtf8("shadowfram"));
        shadowfram->setGeometry(QRect(0, 0, 478, 21));
        shadowfram->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(244, 244, 244);\n"
"}"));
        shadowfram->setFrameShape(QFrame::StyledPanel);
        shadowfram->setFrameShadow(QFrame::Raised);
        frame = new QFrame(shadowfram);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 478, 21));
        frame->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	border-top-left-radius:8px;\n"
"    border-top-right-radius: 8px;\n"
"	background-color: rgb(34, 136, 193);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        CloseButton = new QToolButton(frame);
        CloseButton->setObjectName(QString::fromUtf8("CloseButton"));
        CloseButton->setGeometry(QRect(450, 2, 18, 18));
        CloseButton->setMinimumSize(QSize(0, 18));
        CloseButton->setStyleSheet(QString::fromUtf8("QToolButton\n"
"{\n"
"	background:url(:/image/bitbug_favicon.ico);\n"
"}\n"
""));

        retranslateUi(ImageViewWidget);

        QMetaObject::connectSlotsByName(ImageViewWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageViewWidget)
    {
        ImageViewWidget->setWindowTitle(QApplication::translate("ImageViewWidget", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ImageViewWidget", "0", 0, QApplication::UnicodeUTF8));
        CloseButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageViewWidget: public Ui_ImageViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWWIDGET_H
