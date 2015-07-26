/********************************************************************************
** Form generated from reading UI file 'greentech.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GREENTECH_H
#define UI_GREENTECH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "./Interface/graph.h"

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
            GreenTech->setObjectName(QStringLiteral("GreenTech"));
        GreenTech->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GreenTech->sizePolicy().hasHeightForWidth());
        GreenTech->setSizePolicy(sizePolicy);
        GreenTech->setStyleSheet(QLatin1String("QMainWindow{\n"
"	background-color: rgb(244, 244, 244);\n"
"}"));
        actionBack_View = new QAction(GreenTech);
        actionBack_View->setObjectName(QStringLiteral("actionBack_View"));
        QFont font;
        font.setFamily(QStringLiteral("Andalus"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        actionBack_View->setFont(font);
        actionAuto_Support = new QAction(GreenTech);
        actionAuto_Support->setObjectName(QStringLiteral("actionAuto_Support"));
        actionAuto_Support->setFont(font);
        actionDeleteSupport = new QAction(GreenTech);
        actionDeleteSupport->setObjectName(QStringLiteral("actionDeleteSupport"));
        actionDeleteSupport->setFont(font);
        actionManuAddSupport = new QAction(GreenTech);
        actionManuAddSupport->setObjectName(QStringLiteral("actionManuAddSupport"));
        actionManuAddSupport->setFont(font);
        actionAddBasePlate = new QAction(GreenTech);
        actionAddBasePlate->setObjectName(QStringLiteral("actionAddBasePlate"));
        actionAddBasePlate->setFont(font);
        actionLight_support = new QAction(GreenTech);
        actionLight_support->setObjectName(QStringLiteral("actionLight_support"));
        actionLight_support->setCheckable(true);
        actionLight_support->setFont(font);
        actionMedium_support = new QAction(GreenTech);
        actionMedium_support->setObjectName(QStringLiteral("actionMedium_support"));
        actionMedium_support->setCheckable(true);
        actionMedium_support->setFont(font);
        actionHeavy_support = new QAction(GreenTech);
        actionHeavy_support->setObjectName(QStringLiteral("actionHeavy_support"));
        actionHeavy_support->setCheckable(true);
        actionHeavy_support->setFont(font);
        actionOpen = new QAction(GreenTech);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(GreenTech);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionQuit_Pudding = new QAction(GreenTech);
        actionQuit_Pudding->setObjectName(QStringLiteral("actionQuit_Pudding"));
        actionSave_2 = new QAction(GreenTech);
        actionSave_2->setObjectName(QStringLiteral("actionSave_2"));
        actionMove = new QAction(GreenTech);
        actionMove->setObjectName(QStringLiteral("actionMove"));
        actionScale = new QAction(GreenTech);
        actionScale->setObjectName(QStringLiteral("actionScale"));
        actionRotate = new QAction(GreenTech);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionReset_Rotate = new QAction(GreenTech);
        actionReset_Rotate->setObjectName(QStringLiteral("actionReset_Rotate"));
        actionSelect = new QAction(GreenTech);
        actionSelect->setObjectName(QStringLiteral("actionSelect"));
        actionCopy = new QAction(GreenTech);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionDelete = new QAction(GreenTech);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        actionSnap = new QAction(GreenTech);
        actionSnap->setObjectName(QStringLiteral("actionSnap"));
        actionOrtho = new QAction(GreenTech);
        actionOrtho->setObjectName(QStringLiteral("actionOrtho"));
        actionPerspective = new QAction(GreenTech);
        actionPerspective->setObjectName(QStringLiteral("actionPerspective"));
        actionTopView = new QAction(GreenTech);
        actionTopView->setObjectName(QStringLiteral("actionTopView"));
        actionBottomView = new QAction(GreenTech);
        actionBottomView->setObjectName(QStringLiteral("actionBottomView"));
        actionRightView = new QAction(GreenTech);
        actionRightView->setObjectName(QStringLiteral("actionRightView"));
        actionLeftView = new QAction(GreenTech);
        actionLeftView->setObjectName(QStringLiteral("actionLeftView"));
        actionFrontView = new QAction(GreenTech);
        actionFrontView->setObjectName(QStringLiteral("actionFrontView"));
        actionBackView = new QAction(GreenTech);
        actionBackView->setObjectName(QStringLiteral("actionBackView"));
        actionAuto = new QAction(GreenTech);
        actionAuto->setObjectName(QStringLiteral("actionAuto"));
        actionManuDelete = new QAction(GreenTech);
        actionManuDelete->setObjectName(QStringLiteral("actionManuDelete"));
        actionLight = new QAction(GreenTech);
        actionLight->setObjectName(QStringLiteral("actionLight"));
        actionMid = new QAction(GreenTech);
        actionMid->setObjectName(QStringLiteral("actionMid"));
        actionHeavy = new QAction(GreenTech);
        actionHeavy->setObjectName(QStringLiteral("actionHeavy"));
        actionDeleteAll = new QAction(GreenTech);
        actionDeleteAll->setObjectName(QStringLiteral("actionDeleteAll"));
        actionRemoveAll = new QAction(GreenTech);
        actionRemoveAll->setObjectName(QStringLiteral("actionRemoveAll"));
        QFont font1;
        font1.setFamily(QStringLiteral("Andalus"));
        font1.setPointSize(12);
        actionRemoveAll->setFont(font1);
        centralwidget = new QWidget(GreenTech);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new Graph(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setStyleSheet(QLatin1String("Graph{\n"
"	background-color: rgb(244, 244, 244);\n"
"}"));
        graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemShape);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);

        GreenTech->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GreenTech);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        GreenTech->setMenuBar(menubar);
        statusbar = new QStatusBar(GreenTech);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        GreenTech->setStatusBar(statusbar);
        viewToolBar = new QToolBar(GreenTech);
        viewToolBar->setObjectName(QStringLiteral("viewToolBar"));
        GreenTech->addToolBar(Qt::TopToolBarArea, viewToolBar);
        supportEdit = new QToolBar(GreenTech);
        supportEdit->setObjectName(QStringLiteral("supportEdit"));
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
        GreenTech->setWindowTitle(QApplication::translate("GreenTech", "MainWindow", 0));
        actionBack_View->setText(QApplication::translate("GreenTech", "Back_View", 0));
#ifndef QT_NO_TOOLTIP
        actionBack_View->setToolTip(QApplication::translate("GreenTech", "OutSupportMode", 0));
#endif // QT_NO_TOOLTIP
        actionAuto_Support->setText(QApplication::translate("GreenTech", "Auto_Support", 0));
        actionDeleteSupport->setText(QApplication::translate("GreenTech", "DeleteSupport", 0));
        actionManuAddSupport->setText(QApplication::translate("GreenTech", "ManuAddSupport", 0));
        actionAddBasePlate->setText(QApplication::translate("GreenTech", "AddBasePlate", 0));
        actionLight_support->setText(QApplication::translate("GreenTech", "Light_support", 0));
        actionMedium_support->setText(QApplication::translate("GreenTech", "Medium_support", 0));
        actionHeavy_support->setText(QApplication::translate("GreenTech", "Heavy_support", 0));
        actionOpen->setText(QApplication::translate("GreenTech", "Open", 0));
        actionSave->setText(QApplication::translate("GreenTech", "Save", 0));
        actionQuit_Pudding->setText(QApplication::translate("GreenTech", "Quit Pudding", 0));
        actionSave_2->setText(QApplication::translate("GreenTech", "Save", 0));
        actionMove->setText(QApplication::translate("GreenTech", "Move", 0));
        actionScale->setText(QApplication::translate("GreenTech", "Scale", 0));
        actionRotate->setText(QApplication::translate("GreenTech", "Rotate", 0));
        actionReset_Rotate->setText(QApplication::translate("GreenTech", "Reset Rotate", 0));
        actionSelect->setText(QApplication::translate("GreenTech", "Select", 0));
        actionCopy->setText(QApplication::translate("GreenTech", "Copy", 0));
        actionDelete->setText(QApplication::translate("GreenTech", "Delete", 0));
        actionSnap->setText(QApplication::translate("GreenTech", "Snap floor", 0));
        actionOrtho->setText(QApplication::translate("GreenTech", "Ortho", 0));
        actionPerspective->setText(QApplication::translate("GreenTech", "Perspective", 0));
        actionTopView->setText(QApplication::translate("GreenTech", "TopView", 0));
        actionBottomView->setText(QApplication::translate("GreenTech", "BottomView", 0));
        actionRightView->setText(QApplication::translate("GreenTech", "RightView", 0));
        actionLeftView->setText(QApplication::translate("GreenTech", "LeftView", 0));
        actionFrontView->setText(QApplication::translate("GreenTech", "FrontView", 0));
        actionBackView->setText(QApplication::translate("GreenTech", "BackView", 0));
        actionAuto->setText(QApplication::translate("GreenTech", "Auto", 0));
        actionManuDelete->setText(QApplication::translate("GreenTech", "ManuDelete", 0));
        actionLight->setText(QApplication::translate("GreenTech", "Light", 0));
        actionMid->setText(QApplication::translate("GreenTech", "Medium", 0));
        actionHeavy->setText(QApplication::translate("GreenTech", "Heavy", 0));
        actionDeleteAll->setText(QApplication::translate("GreenTech", "DeleteAll", 0));
        actionRemoveAll->setText(QApplication::translate("GreenTech", "RemoveAll", 0));
#ifndef QT_NO_TOOLTIP
        actionRemoveAll->setToolTip(QApplication::translate("GreenTech", "Remove all support struct", 0));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("GreenTech", "\346\226\207\344\273\266", 0));
        menuEdit->setTitle(QApplication::translate("GreenTech", "\347\274\226\350\276\221", 0));
        menuHelp->setTitle(QApplication::translate("GreenTech", "\345\270\256\345\212\251", 0));
        menuView->setTitle(QApplication::translate("GreenTech", "\350\247\206\345\233\276", 0));
        viewToolBar->setWindowTitle(QApplication::translate("GreenTech", "toolBar", 0));
        supportEdit->setWindowTitle(QApplication::translate("GreenTech", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class GreenTech: public Ui_GreenTech {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GREENTECH_H
