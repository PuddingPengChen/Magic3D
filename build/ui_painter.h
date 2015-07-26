/********************************************************************************
** Form generated from reading UI file 'painter.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAINTER_H
#define UI_PAINTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Painter
{
public:

    void setupUi(QWidget *Painter)
    {
        if (Painter->objectName().isEmpty())
            Painter->setObjectName(QStringLiteral("Painter"));
        Painter->resize(400, 300);

        retranslateUi(Painter);

        QMetaObject::connectSlotsByName(Painter);
    } // setupUi

    void retranslateUi(QWidget *Painter)
    {
        Painter->setWindowTitle(QApplication::translate("Painter", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Painter: public Ui_Painter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAINTER_H
