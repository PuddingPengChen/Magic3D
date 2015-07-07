/********************************************************************************
** Form generated from reading UI file 'greentech.ui'
**
** Created: Tue Jun 2 12:22:59 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GREENTECH_H
#define UI_GREENTECH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <./Interface/graph.h>

QT_BEGIN_NAMESPACE

class Ui_GreenTech
{
public:
    QAction *actionBack_View;
    QAction *actionAuto_Support;
    QAction *actionDeleteSupport;
    QAction *actionManuAddSupport;
    QAction *actionAddBasePlate;
    QAction *actionLight_support;
    QAction *actionMedium_support;
    QAction *actionHeavy_support;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionQuit_Pudding;
    QAction *actionSave_2;
    QAction *actionMove;
    QAction *actionScale;
    QAction *actionRotate;
    QAction *actionReset_Rotate;
    QAction *actionSelect;
    QAction *actionCopy;
    QAction *actionDelete;
    QAction *actionSnap;
    QAction *actionOrtho;
    QAction *actionPerspective;
    QAction *actionTopView;
    QAction *actionBottomView;
    QAction *actionRightView;
    QAction *actionLeftView;
    QAction *actionFrontView;
    QAction *actionBackView;
    QAction *actionAuto;
    QAction *actionManuDelete;
    QAction *actionLight;
    QAction *actionMid;
    QAction *actionHeavy;
    QAction *actionDeleteAll;
    QAction *actionRemoveAll;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    Graph *graphicsView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuView;
    QStatusBar *statusbar;
    QToolBar *viewToolBar;
    QToolBar *supportEdit;

    void setupUi(QMainWindow *GreenTech)
    {
        if (GreenTech->objectName().isEmpty())
            GreenTech->setObjectName(QString::fromUtf8("GreenTech"));
        GreenTech->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GreenTech->sizePolicy().hasHeightForWidth());
        GreenTech->setSizePolicy(sizePolicy);
        GreenTech->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color: rgb(244, 244, 244);\n"
"}"));
        actionBack_View = new QAction(GreenTech);
        actionBack_View->setObjectName(QString::fromUtf8("actionBack_View"));
        QFont font;
        font.setFamily(QString::fromUtf8("Andalus"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        actionBack_View->setFont(font);
        actionAuto_Support = new QAction(GreenTech);
        actionAuto_Support->setObjectName(QString::fromUtf8("actionAuto_Support"));
        actionAuto_Support->setFont(font);
        actionDeleteSupport = new QAction(GreenTech);
        actionDeleteSupport->setObjectName(QString::fromUtf8("actionDeleteSupport"));
        actionDeleteSupport->setFont(font);
        actionManuAddSupport = new QAction(GreenTech);
        actionManuAddSupport->setObjectName(QString::fromUtf8("actionManuAddSupport"));
        actionManuAddSupport->setFont(font);
        actionAddBasePlate = new QAction(GreenTech);
        actionAddBasePlate->setObjectName(QString::fromUtf8("actionAddBasePlate"));
        actionAddBasePlate->setFont(font);
        actionLight_support = new QAction(GreenTech);
        actionLight_support->setObjectName(QString::fromUtf8("actionLight_support"));
        actionLight_support->setCheckable(true);
        actionLight_support->setFont(font);
        actionMedium_support = new QAction(GreenTech);
        actionMedium_support->setObjectName(QString::fromUtf8("actionMedium_support"));
        actionMedium_support->setCheckable(true);
        actionMedium_support->setFont(font);
        actionHeavy_support = new QAction(GreenTech);
        actionHeavy_support->setObjectName(QString::fromUtf8("actionHeavy_support"));
        actionHeavy_support->setCheckable(true);
        actionHeavy_support->setFont(font);
        actionOpen = new QAction(GreenTech);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(GreenTech);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionQuit_Pudding = new QAction(GreenTech);
        actionQuit_Pudding->setObjectName(QString::fromUtf8("actionQuit_Pudding"));
        actionSave_2 = new QAction(GreenTech);
        actionSave_2->setObjectName(QString::fromUtf8("actionSave_2"));
        actionMove = new QAction(GreenTech);
        actionMove->setObjectName(QString::fromUtf8("actionMove"));
        actionScale = new QAction(GreenTech);
        actionScale->setObjectName(QString::fromUtf8("actionScale"));
        actionRotate = new QAction(GreenTech);
        actionRotate->setObjectName(QString::fromUtf8("actionRotate"));
        actionReset_Rotate = new QAction(GreenTech);
        actionReset_Rotate->setObjectName(QString::fromUtf8("actionReset_Rotate"));
        actionSelect = new QAction(GreenTech);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actionCopy = new QAction(GreenTech);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionDelete = new QAction(GreenTech);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionSnap = new QAction(GreenTech);
        actionSnap->setObjectName(QString::fromUtf8("actionSnap"));
        actionOrtho = new QAction(GreenTech);
        actionOrtho->setObjectName(QString::fromUtf8("actionOrtho"));
        actionPerspective = new QAction(GreenTech);
        actionPerspective->setObjectName(QString::fromUtf8("actionPerspective"));
        actionTopView = new QAction(GreenTech);
        actionTopView->setObjectName(QString::fromUtf8("actionTopView"));
        actionBottomView = new QAction(GreenTech);
        actionBottomView->setObjectName(QString::fromUtf8("actionBottomView"));
        actionRightView = new QAction(GreenTech);
        actionRightView->setObjectName(QString::fromUtf8("actionRightView"));
        actionLeftView = new QAction(GreenTech);
        actionLeftView->setObjectName(QString::fromUtf8("actionLeftView"));
        actionFrontView = new QAction(GreenTech);
        actionFrontView->setObjectName(QString::fromUtf8("actionFrontView"));
        actionBackView = new QAction(GreenTech);
        actionBackView->setObjectName(QString::fromUtf8("actionBackView"));
        actionAuto = new QAction(GreenTech);
        actionAuto->setObjectName(QString::fromUtf8("actionAuto"));
        actionManuDelete = new QAction(GreenTech);
        actionManuDelete->setObjectName(QString::fromUtf8("actionManuDelete"));
        actionLight = new QAction(GreenTech);
        actionLight->setObjectName(QString::fromUtf8("actionLight"));
        actionMid = new QAction(GreenTech);
        actionMid->setObjectName(QString::fromUtf8("actionMid"));
        actionHeavy = new QAction(GreenTech);
        actionHeavy->setObjectName(QString::fromUtf8("actionHeavy"));
        actionDeleteAll = new QAction(GreenTech);
        actionDeleteAll->setObjectName(QString::fromUtf8("actionDeleteAll"));
        actionRemoveAll = new QAction(GreenTech);
        actionRemoveAll->setObjectName(QString::fromUtf8("actionRemoveAll"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Andalus"));
        font1.setPointSize(12);
        actionRemoveAll->setFont(font1);
        centralwidget = new QWidget(GreenTech);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new Graph(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setStyleSheet(QString::fromUtf8("Graph{\n"
"	background-color: rgb(244, 244, 244);\n"
"}"));
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemShape);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        GreenTech->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GreenTech);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        GreenTech->setMenuBar(menubar);
        statusbar = new QStatusBar(GreenTech);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GreenTech->setStatusBar(statusbar);
        viewToolBar = new QToolBar(GreenTech);
        viewToolBar->setObjectName(QString::fromUtf8("viewToolBar"));
        GreenTech->addToolBar(Qt::TopToolBarArea, viewToolBar);
        supportEdit = new QToolBar(GreenTech);
        supportEdit->setObjectName(QString::fromUtf8("supportEdit"));
        GreenTech->addToolBar(Qt::TopToolBarArea, supportEdit);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave_2);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit_Pudding);
        menuEdit->addAction(actionSelect);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionMove);
        menuEdit->addAction(actionScale);
        menuEdit->addAction(actionRotate);
        menuEdit->addAction(actionReset_Rotate);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSnap);
        menuView->addAction(actionOrtho);
        menuView->addAction(actionPerspective);
        menuView->addSeparator();
        menuView->addAction(actionTopView);
        menuView->addAction(actionBottomView);
        menuView->addAction(actionRightView);
        menuView->addAction(actionLeftView);
        menuView->addAction(actionFrontView);
        menuView->addAction(actionBackView);

        retranslateUi(GreenTech);

        QMetaObject::connectSlotsByName(GreenTech);
    } // setupUi

    void retranslateUi(QMainWindow *GreenTech)
    {
        GreenTech->setWindowTitle(QApplication::translate("GreenTech", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionBack_View->setText(QApplication::translate("GreenTech", "Back_View", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionBack_View->setToolTip(QApplication::translate("GreenTech", "OutSupportMode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAuto_Support->setText(QApplication::translate("GreenTech", "Auto_Support", 0, QApplication::UnicodeUTF8));
        actionDeleteSupport->setText(QApplication::translate("GreenTech", "DeleteSupport", 0, QApplication::UnicodeUTF8));
        actionManuAddSupport->setText(QApplication::translate("GreenTech", "ManuAddSupport", 0, QApplication::UnicodeUTF8));
        actionAddBasePlate->setText(QApplication::translate("GreenTech", "AddBasePlate", 0, QApplication::UnicodeUTF8));
        actionLight_support->setText(QApplication::translate("GreenTech", "Light_support", 0, QApplication::UnicodeUTF8));
        actionMedium_support->setText(QApplication::translate("GreenTech", "Medium_support", 0, QApplication::UnicodeUTF8));
        actionHeavy_support->setText(QApplication::translate("GreenTech", "Heavy_support", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("GreenTech", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("GreenTech", "Save", 0, QApplication::UnicodeUTF8));
        actionQuit_Pudding->setText(QApplication::translate("GreenTech", "Quit Pudding", 0, QApplication::UnicodeUTF8));
        actionSave_2->setText(QApplication::translate("GreenTech", "Save", 0, QApplication::UnicodeUTF8));
        actionMove->setText(QApplication::translate("GreenTech", "Move", 0, QApplication::UnicodeUTF8));
        actionScale->setText(QApplication::translate("GreenTech", "Scale", 0, QApplication::UnicodeUTF8));
        actionRotate->setText(QApplication::translate("GreenTech", "Rotate", 0, QApplication::UnicodeUTF8));
        actionReset_Rotate->setText(QApplication::translate("GreenTech", "Reset Rotate", 0, QApplication::UnicodeUTF8));
        actionSelect->setText(QApplication::translate("GreenTech", "Select", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("GreenTech", "Copy", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("GreenTech", "Delete", 0, QApplication::UnicodeUTF8));
        actionSnap->setText(QApplication::translate("GreenTech", "Snap floor", 0, QApplication::UnicodeUTF8));
        actionOrtho->setText(QApplication::translate("GreenTech", "Ortho", 0, QApplication::UnicodeUTF8));
        actionPerspective->setText(QApplication::translate("GreenTech", "Perspective", 0, QApplication::UnicodeUTF8));
        actionTopView->setText(QApplication::translate("GreenTech", "TopView", 0, QApplication::UnicodeUTF8));
        actionBottomView->setText(QApplication::translate("GreenTech", "BottomView", 0, QApplication::UnicodeUTF8));
        actionRightView->setText(QApplication::translate("GreenTech", "RightView", 0, QApplication::UnicodeUTF8));
        actionLeftView->setText(QApplication::translate("GreenTech", "LeftView", 0, QApplication::UnicodeUTF8));
        actionFrontView->setText(QApplication::translate("GreenTech", "FrontView", 0, QApplication::UnicodeUTF8));
        actionBackView->setText(QApplication::translate("GreenTech", "BackView", 0, QApplication::UnicodeUTF8));
        actionAuto->setText(QApplication::translate("GreenTech", "Auto", 0, QApplication::UnicodeUTF8));
        actionManuDelete->setText(QApplication::translate("GreenTech", "ManuDelete", 0, QApplication::UnicodeUTF8));
        actionLight->setText(QApplication::translate("GreenTech", "Light", 0, QApplication::UnicodeUTF8));
        actionMid->setText(QApplication::translate("GreenTech", "Medium", 0, QApplication::UnicodeUTF8));
        actionHeavy->setText(QApplication::translate("GreenTech", "Heavy", 0, QApplication::UnicodeUTF8));
        actionDeleteAll->setText(QApplication::translate("GreenTech", "DeleteAll", 0, QApplication::UnicodeUTF8));
        actionRemoveAll->setText(QApplication::translate("GreenTech", "RemoveAll", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRemoveAll->setToolTip(QApplication::translate("GreenTech", "Remove all support struct", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("GreenTech", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("GreenTech", "Edit", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("GreenTech", "Help", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("GreenTech", "View", 0, QApplication::UnicodeUTF8));
        viewToolBar->setWindowTitle(QApplication::translate("GreenTech", "toolBar", 0, QApplication::UnicodeUTF8));
        supportEdit->setWindowTitle(QApplication::translate("GreenTech", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GreenTech: public Ui_GreenTech {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GREENTECH_H
