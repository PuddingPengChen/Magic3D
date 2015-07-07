/********************************************************************************
** Form generated from reading UI file 'printedit.ui'
**
** Created: Tue Jun 2 14:04:50 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRINTEDIT_H
#define UI_PRINTEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PrintEdit
{
public:
    QFrame *frame;
    QTextBrowser *InforBrowser;
    QToolButton *toolButton;
    QPushButton *PrintButton;
    QPushButton *StopPrintButton;
    QPushButton *RecoverButton;
    QPushButton *ResetButton;
    QGroupBox *IPGroup;
    QPushButton *ConnectButton;
    QLabel *IP_label;
    QComboBox *comboBox;
    QPushButton *ImageButton;
    QPushButton *SliceButton;

    void setupUi(QWidget *PrintEdit)
    {
        if (PrintEdit->objectName().isEmpty())
            PrintEdit->setObjectName(QString::fromUtf8("PrintEdit"));
        PrintEdit->setWindowModality(Qt::WindowModal);
        PrintEdit->resize(300, 292);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/logo2.PNG"), QSize(), QIcon::Normal, QIcon::Off);
        PrintEdit->setWindowIcon(icon);
        PrintEdit->setStyleSheet(QString::fromUtf8("\n"
"QWidget\n"
"{\n"
"	background-color: rgb(244, 244, 244);\n"
"}\n"
"\n"
""));
        frame = new QFrame(PrintEdit);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(3, 10, 291, 271));
        frame->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color: rgb(116, 126, 146);\n"
"	border-radius: 12px;\n"
"}\n"
"QComboBox\n"
"{\n"
"	border-radius: 4px;\n"
"	background-color: rgb(155, 156, 155);\n"
"	color:rgb(255,255,255);\n"
"}\n"
"/*QComboBox::drop-down\n"
"{\n"
"	\n"
"	subcontrol-origin: margin;\n"
"}*/\n"
"QLineEdit\n"
"{	\n"
"	color: rgb(255, 255, 255);\n"
"	border-radius: 4px;\n"
"	border: 1px solid rgb(255,250,250);\n"
"	background-color: rgb(116, 126, 146);\n"
"}\n"
"QLabel\n"
"{\n"
"	font-family:\"Source Sans Pro\";\n"
"	font-size: 12px;\n"
"    font-weight: regular;\n"
"	color:#FFF;\n"
"}\n"
"\n"
"QPushButton,QToolButton\n"
"{\n"
"   /* color: #424344;*/\n"
"    font-family: \"Source Sans Pro\";\n"
"    font-size: 11px;\n"
"    font-weight: regular;\n"
" 	border: 1px solid yellow;\n"
" 	border-radius: 4px;\n"
"    padding: 0px 15px;   \n"
"    max-height: 100px;\n"
"    min-height: 25px;\n"
"	min-weight:52px;\n"
"\n"
" 	/*background-color: #2288C1;*/\n"
"	background-color: rgb(155,155,155);\n"
"    border-color: rgb(1"
                        "55,155,155);\n"
"    color: #fff;\n"
"}\n"
"\n"
"QToolButton:pressed, QPushButton:pressed, QPushButton[btn-secondary=true]:pressed, QPushButton[btn-icon=true]:pressed\n"
"{\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E1E3, stop:.25 #F6F7F9);\n"
"}\n"
"\n"
"QPushButton:disabled\n"
"{\n"
"    background-color: #EAEBED;\n"
"    border-color: #E1E2E4;\n"
"    color: #C0C1C3;\n"
"}\n"
"\n"
"QPushButton:pressed,QToolButton:pressed\n"
"{\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0072a9, stop:.25 #2288C1);\n"
"}\n"
"QPushButton:hover,QToolButton:hover\n"
"{\n"
"    background-color: #6C22E2;\n"
"}\n"
"\n"
"QRadioButton{\n"
"	color:#fff;\n"
"}\n"
"QGroupBox\n"
"{\n"
"  border: 1px solid #ffffff;\n"
"  border-radius:3px;\n"
"  color: #FFF;\n"
"  background-color: rgb(116, 126, 146);\n"
"\n"
"}\n"
"\n"
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        InforBrowser = new QTextBrowser(frame);
        InforBrowser->setObjectName(QString::fromUtf8("InforBrowser"));
        InforBrowser->setGeometry(QRect(140, 110, 131, 121));
        InforBrowser->setStyleSheet(QString::fromUtf8("QTextBrowser\n"
"{\n"
"	color: rgb(255, 255, 255);	\n"
"	background-color: rgb(115, 115, 115);\n"
"    font-family: \"Source Sans Pro\";\n"
"    font-size: 14px;\n"
"    font-weight: regular;\n"
"}"));
        toolButton = new QToolButton(frame);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(20, 220, 52, 27));
        QFont font;
        font.setFamily(QString::fromUtf8("Source Sans Pro"));
        toolButton->setFont(font);
        toolButton->setFocusPolicy(Qt::NoFocus);
        PrintButton = new QPushButton(frame);
        PrintButton->setObjectName(QString::fromUtf8("PrintButton"));
        PrintButton->setEnabled(false);
        PrintButton->setGeometry(QRect(19, 143, 52, 27));
        PrintButton->setFont(font);
        StopPrintButton = new QPushButton(frame);
        StopPrintButton->setObjectName(QString::fromUtf8("StopPrintButton"));
        StopPrintButton->setEnabled(false);
        StopPrintButton->setGeometry(QRect(78, 144, 52, 27));
        StopPrintButton->setFont(font);
        StopPrintButton->setFocusPolicy(Qt::NoFocus);
        RecoverButton = new QPushButton(frame);
        RecoverButton->setObjectName(QString::fromUtf8("RecoverButton"));
        RecoverButton->setEnabled(false);
        RecoverButton->setGeometry(QRect(77, 177, 52, 27));
        RecoverButton->setFont(font);
        RecoverButton->setFocusPolicy(Qt::NoFocus);
        ResetButton = new QPushButton(frame);
        ResetButton->setObjectName(QString::fromUtf8("ResetButton"));
        ResetButton->setEnabled(false);
        ResetButton->setGeometry(QRect(19, 176, 52, 27));
        ResetButton->setFont(font);
        ResetButton->setFocusPolicy(Qt::NoFocus);
        IPGroup = new QGroupBox(frame);
        IPGroup->setObjectName(QString::fromUtf8("IPGroup"));
        IPGroup->setGeometry(QRect(20, 10, 251, 91));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        IPGroup->setFont(font1);
        IPGroup->setStyleSheet(QString::fromUtf8(""));
        IPGroup->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        ConnectButton = new QPushButton(IPGroup);
        ConnectButton->setObjectName(QString::fromUtf8("ConnectButton"));
        ConnectButton->setGeometry(QRect(8, 50, 52, 27));
        ConnectButton->setFont(font);
        ConnectButton->setFocusPolicy(Qt::NoFocus);
        IP_label = new QLabel(IPGroup);
        IP_label->setObjectName(QString::fromUtf8("IP_label"));
        IP_label->setGeometry(QRect(9, 19, 231, 21));
        comboBox = new QComboBox(IPGroup);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(70, 50, 69, 27));
        comboBox->setFocusPolicy(Qt::NoFocus);
        comboBox->setContextMenuPolicy(Qt::NoContextMenu);
        ImageButton = new QPushButton(frame);
        ImageButton->setObjectName(QString::fromUtf8("ImageButton"));
        ImageButton->setEnabled(false);
        ImageButton->setGeometry(QRect(79, 110, 52, 27));
        ImageButton->setFont(font);
        ImageButton->setFocusPolicy(Qt::NoFocus);
        SliceButton = new QPushButton(frame);
        SliceButton->setObjectName(QString::fromUtf8("SliceButton"));
        SliceButton->setGeometry(QRect(19, 110, 52, 27));
        SliceButton->setFont(font);
        SliceButton->setFocusPolicy(Qt::NoFocus);

        retranslateUi(PrintEdit);

        QMetaObject::connectSlotsByName(PrintEdit);
    } // setupUi

    void retranslateUi(QWidget *PrintEdit)
    {
        PrintEdit->setWindowTitle(QApplication::translate("PrintEdit", "Form", 0, QApplication::UnicodeUTF8));
        InforBrowser->setHtml(QApplication::translate("PrintEdit", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Source Sans Pro'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButton->setToolTip(QApplication::translate("PrintEdit", "Clean the infor browser", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButton->setText(QApplication::translate("PrintEdit", "\346\270\205\345\261\217", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        PrintButton->setToolTip(QApplication::translate("PrintEdit", "Begin print", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        PrintButton->setText(QApplication::translate("PrintEdit", "\346\211\223\345\215\260", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        StopPrintButton->setToolTip(QApplication::translate("PrintEdit", "stop print,can recover again", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        StopPrintButton->setText(QApplication::translate("PrintEdit", "\346\232\202\345\201\234", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        RecoverButton->setToolTip(QApplication::translate("PrintEdit", "Go on print", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        RecoverButton->setText(QApplication::translate("PrintEdit", "\346\201\242\345\244\215", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ResetButton->setToolTip(QApplication::translate("PrintEdit", "Reset the printer.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ResetButton->setText(QApplication::translate("PrintEdit", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        IPGroup->setTitle(QApplication::translate("PrintEdit", "\347\253\257\345\217\243\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ConnectButton->setToolTip(QApplication::translate("PrintEdit", "Connecte to the printer", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ConnectButton->setText(QApplication::translate("PrintEdit", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        IP_label->setText(QApplication::translate("PrintEdit", "\346\211\223\345\215\260\345\211\215\357\274\214\350\257\267\350\277\236\346\216\245\346\211\223\345\215\260\346\234\272\357\274\214\346\210\226\350\200\205\351\200\211\346\213\251\350\204\261\346\234\272\346\211\223\345\215\260", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("PrintEdit", "\347\251\272", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        ImageButton->setToolTip(QApplication::translate("PrintEdit", "Show the layer image", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ImageButton->setText(QApplication::translate("PrintEdit", "\351\242\204\350\247\210", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        SliceButton->setToolTip(QApplication::translate("PrintEdit", "Slice the object", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        SliceButton->setText(QApplication::translate("PrintEdit", "\345\210\207\347\211\207", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PrintEdit: public Ui_PrintEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRINTEDIT_H
