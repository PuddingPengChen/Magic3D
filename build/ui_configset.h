/********************************************************************************
** Form generated from reading UI file 'configset.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGSET_H
#define UI_CONFIGSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_ConfigSet
{
public:
    QFrame *frame_title;
    QFrame *frame_title_2;
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *OK_pushButton;

    void setupUi(QDialog *ConfigSet)
    {
        if (ConfigSet->objectName().isEmpty())
            ConfigSet->setObjectName(QStringLiteral("ConfigSet"));
        ConfigSet->resize(400, 251);
        ConfigSet->setStyleSheet(QLatin1String("QRadioButton\n"
"{\n"
"font-family:\"Source Sans Pro\";\n"
"	 font-size: 16px;\n"
"    font-weight: regular;\n"
"	color:#FFF;\n"
"}\n"
"QLineEdit\n"
"{	\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
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
"    border: 1px solid yellow; /* dummy color -- is overridden below */\n"
"}\n"
"\n"
"QPushButton,QToolButton\n"
"{\n"
"    border-radius: 4px;\n"
"    padding: 0px 15px;\n"
"   ;\n"
"    max-height: 100px;\n"
"    min-height: 25px;\n"
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
"    background-color: #FF"
                        "F;\n"
"}\n"
"\n"
"QToolButton:pressed, QPushButton:pressed, QPushButton[btn-secondary=true]:pressed, QPushButton[btn-icon=true]:pressed\n"
"{\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E1E3, stop:.25 #F6F7F9);\n"
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
        frame_title = new QFrame(ConfigSet);
        frame_title->setObjectName(QStringLiteral("frame_title"));
        frame_title->setGeometry(QRect(1, -1, 400, 21));
        frame_title->setStyleSheet(QLatin1String("QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(244, 244, 244);\n"
"}"));
        frame_title->setFrameShape(QFrame::StyledPanel);
        frame_title->setFrameShadow(QFrame::Raised);
        frame_title_2 = new QFrame(frame_title);
        frame_title_2->setObjectName(QStringLiteral("frame_title_2"));
        frame_title_2->setGeometry(QRect(-1, 1, 402, 21));
        frame_title_2->setStyleSheet(QLatin1String("QFrame\n"
"{\n"
"	border-top-left-radius:8px;\n"
"    border-top-right-radius: 8px;\n"
"	background-color: rgb(34, 136, 193);\n"
"}"));
        frame_title_2->setFrameShape(QFrame::StyledPanel);
        frame_title_2->setFrameShadow(QFrame::Raised);
        label = new QLabel(ConfigSet);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 50, 221, 41));
        radioButton = new QRadioButton(ConfigSet);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(110, 110, 201, 16));
        radioButton_2 = new QRadioButton(ConfigSet);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(110, 150, 171, 21));
        OK_pushButton = new QPushButton(ConfigSet);
        OK_pushButton->setObjectName(QStringLiteral("OK_pushButton"));
        OK_pushButton->setGeometry(QRect(150, 196, 75, 31));

        retranslateUi(ConfigSet);
        QObject::connect(OK_pushButton, SIGNAL(clicked()), ConfigSet, SLOT(accept()));

        QMetaObject::connectSlotsByName(ConfigSet);
    } // setupUi

    void retranslateUi(QDialog *ConfigSet)
    {
        ConfigSet->setWindowTitle(QApplication::translate("ConfigSet", "Dialog", 0));
        label->setText(QApplication::translate("ConfigSet", "Please choose your machine:", 0));
        radioButton->setText(QApplication::translate("ConfigSet", "GuangSu-1024x768", 0));
        radioButton_2->setText(QApplication::translate("ConfigSet", "GuangSu-1920x1080", 0));
        OK_pushButton->setText(QApplication::translate("ConfigSet", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigSet: public Ui_ConfigSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGSET_H
