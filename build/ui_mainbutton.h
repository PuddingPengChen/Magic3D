/********************************************************************************
** Form generated from reading UI file 'mainbutton.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINBUTTON_H
#define UI_MAINBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainButton
{
public:
    QPushButton *ModelButton;
    QPushButton *SupportMode;
    QPushButton *PrintMode;

    void setupUi(QWidget *MainButton)
    {
        if (MainButton->objectName().isEmpty())
            MainButton->setObjectName(QStringLiteral("MainButton"));
        MainButton->resize(90, 131);
        MainButton->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"	background-color: rgb(244, 244, 244);\n"
"	border-radius: 12px;\n"
"}\n"
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
" 	background-color: rgb(108,113,201);\n"
"\n"
"    border-color: rgb(155,155,155);\n"
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
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, st"
                        "op:0 #0072a9, stop:.25 #2288C1);\n"
"}\n"
"QPushButton:hover,QToolButton:hover\n"
"{\n"
"    background-color: #6C22E2;\n"
"}\n"
"\n"
""));
        ModelButton = new QPushButton(MainButton);
        ModelButton->setObjectName(QStringLiteral("ModelButton"));
        ModelButton->setGeometry(QRect(3, 8, 79, 32));
        QFont font;
        font.setFamily(QStringLiteral("Source Sans Pro"));
        ModelButton->setFont(font);
        ModelButton->setFocusPolicy(Qt::NoFocus);
        SupportMode = new QPushButton(MainButton);
        SupportMode->setObjectName(QStringLiteral("SupportMode"));
        SupportMode->setGeometry(QRect(1, 47, 81, 31));
        SupportMode->setFont(font);
        SupportMode->setFocusPolicy(Qt::NoFocus);
        PrintMode = new QPushButton(MainButton);
        PrintMode->setObjectName(QStringLiteral("PrintMode"));
        PrintMode->setGeometry(QRect(1, 86, 81, 33));
        PrintMode->setFont(font);
        PrintMode->setFocusPolicy(Qt::NoFocus);
        PrintMode->setStyleSheet(QStringLiteral(""));

        retranslateUi(MainButton);

        QMetaObject::connectSlotsByName(MainButton);
    } // setupUi

    void retranslateUi(QWidget *MainButton)
    {
        MainButton->setWindowTitle(QApplication::translate("MainButton", "Form", 0));
#ifndef QT_NO_TOOLTIP
        ModelButton->setToolTip(QApplication::translate("MainButton", "Model edit interface", 0));
#endif // QT_NO_TOOLTIP
        ModelButton->setText(QApplication::translate("MainButton", "\347\274\226\350\276\221", 0));
#ifndef QT_NO_TOOLTIP
        SupportMode->setToolTip(QApplication::translate("MainButton", "Support edit ", 0));
#endif // QT_NO_TOOLTIP
        SupportMode->setText(QApplication::translate("MainButton", "\350\256\276\347\275\256", 0));
#ifndef QT_NO_TOOLTIP
        PrintMode->setToolTip(QApplication::translate("MainButton", "Print setting", 0));
#endif // QT_NO_TOOLTIP
        PrintMode->setText(QApplication::translate("MainButton", "\346\211\223\345\215\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainButton: public Ui_MainButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINBUTTON_H
