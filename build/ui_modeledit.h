/********************************************************************************
** Form generated from reading UI file 'modeledit.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELEDIT_H
#define UI_MODELEDIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelEdit
{
public:
    QFrame *frame;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *AddModelButton;
    QPushButton *DuplicateModeButton;
    QPushButton *RemoveModelButton;
    QPushButton *ModelMoveButton;
    QPushButton *ModelRotButton;
    QPushButton *RestRotButton;
    QPushButton *ColorButton;
    QPushButton *ModelSelectedButton;
    QToolButton *ModelScaleButton;
    QLineEdit *lineEdit_scale;
    QPushButton *SupZ;
    QLineEdit *SupZ_linedit;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QPushButton *ModelExportButton;
    QListWidget *ModelList;
    QPushButton *ModelSnapButton;
    QFrame *frame_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_rot;
    QLineEdit *lineEdit_rotx;
    QLineEdit *lineEdit_roty;
    QLineEdit *lineEdit_rotz;
    QFrame *frame_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_sizex;
    QLabel *label_sizey;
    QLabel *label_sizez;

    void setupUi(QWidget *ModelEdit)
    {
        if (ModelEdit->objectName().isEmpty())
            ModelEdit->setObjectName(QStringLiteral("ModelEdit"));
        ModelEdit->resize(279, 336);
        ModelEdit->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"	background-color: rgb(244, 244, 244);\n"
"}\n"
"\n"
"\n"
"\n"
""));
        frame = new QFrame(ModelEdit);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(3, 10, 271, 321));
        frame->setStyleSheet(QLatin1String("QFrame\n"
"{\n"
"	background-color: rgb(116, 126, 146);\n"
"	border-radius: 12px;\n"
"}\n"
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
"    border-color: rgb(155,155,155);\n"
"    color: #fff;\n"
"}\n"
"\n"
"QToolButton:pressed, QPushButton:pressed, QPushButton[btn-secondary=true]:pressed, QPushButton[btn-icon=true]:pressed\n"
"{\n"
"    background-color: qli"
                        "neargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E1E3, stop:.25 #F6F7F9);\n"
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
""));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 10, 244, 111));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        AddModelButton = new QPushButton(frame_2);
        AddModelButton->setObjectName(QStringLiteral("AddModelButton"));
        AddModelButton->setMinimumSize(QSize(52, 27));
        AddModelButton->setMaximumSize(QSize(52, 102));
        QFont font;
        font.setFamily(QStringLiteral("Source Sans Pro"));
        AddModelButton->setFont(font);
        AddModelButton->setFocusPolicy(Qt::ClickFocus);

        gridLayout->addWidget(AddModelButton, 0, 0, 1, 1);

        DuplicateModeButton = new QPushButton(frame_2);
        DuplicateModeButton->setObjectName(QStringLiteral("DuplicateModeButton"));
        DuplicateModeButton->setEnabled(false);
        DuplicateModeButton->setMinimumSize(QSize(52, 27));
        DuplicateModeButton->setMaximumSize(QSize(52, 102));
        DuplicateModeButton->setFont(font);
        DuplicateModeButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(DuplicateModeButton, 0, 1, 1, 1);

        RemoveModelButton = new QPushButton(frame_2);
        RemoveModelButton->setObjectName(QStringLiteral("RemoveModelButton"));
        RemoveModelButton->setEnabled(false);
        RemoveModelButton->setMinimumSize(QSize(52, 27));
        RemoveModelButton->setMaximumSize(QSize(52, 102));
        RemoveModelButton->setFont(font);
        RemoveModelButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(RemoveModelButton, 0, 2, 1, 1);

        ModelMoveButton = new QPushButton(frame_2);
        ModelMoveButton->setObjectName(QStringLiteral("ModelMoveButton"));
        ModelMoveButton->setEnabled(false);
        ModelMoveButton->setMinimumSize(QSize(52, 27));
        ModelMoveButton->setMaximumSize(QSize(52, 102));
        ModelMoveButton->setFont(font);
        ModelMoveButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(ModelMoveButton, 0, 3, 1, 1);

        ModelRotButton = new QPushButton(frame_2);
        ModelRotButton->setObjectName(QStringLiteral("ModelRotButton"));
        ModelRotButton->setEnabled(false);
        ModelRotButton->setMinimumSize(QSize(52, 27));
        ModelRotButton->setMaximumSize(QSize(52, 102));
        ModelRotButton->setFont(font);
        ModelRotButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(ModelRotButton, 1, 0, 1, 1);

        RestRotButton = new QPushButton(frame_2);
        RestRotButton->setObjectName(QStringLiteral("RestRotButton"));
        RestRotButton->setEnabled(false);
        RestRotButton->setMinimumSize(QSize(52, 27));
        RestRotButton->setMaximumSize(QSize(52, 102));
        RestRotButton->setFont(font);
        RestRotButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(RestRotButton, 1, 1, 1, 1);

        ColorButton = new QPushButton(frame_2);
        ColorButton->setObjectName(QStringLiteral("ColorButton"));
        ColorButton->setEnabled(false);
        ColorButton->setMinimumSize(QSize(52, 27));
        ColorButton->setMaximumSize(QSize(52, 102));
        ColorButton->setFont(font);

        gridLayout->addWidget(ColorButton, 1, 2, 1, 1);

        ModelSelectedButton = new QPushButton(frame_2);
        ModelSelectedButton->setObjectName(QStringLiteral("ModelSelectedButton"));
        ModelSelectedButton->setEnabled(false);
        ModelSelectedButton->setMinimumSize(QSize(52, 27));
        ModelSelectedButton->setMaximumSize(QSize(52, 102));
        ModelSelectedButton->setFont(font);
        ModelSelectedButton->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(ModelSelectedButton, 1, 3, 1, 1);

        ModelScaleButton = new QToolButton(frame_2);
        ModelScaleButton->setObjectName(QStringLiteral("ModelScaleButton"));
        ModelScaleButton->setEnabled(false);
        ModelScaleButton->setMinimumSize(QSize(52, 27));
        ModelScaleButton->setMaximumSize(QSize(52, 102));
        ModelScaleButton->setFont(font);

        gridLayout->addWidget(ModelScaleButton, 2, 0, 1, 1);

        lineEdit_scale = new QLineEdit(frame_2);
        lineEdit_scale->setObjectName(QStringLiteral("lineEdit_scale"));
        lineEdit_scale->setEnabled(false);
        lineEdit_scale->setMinimumSize(QSize(52, 0));
        lineEdit_scale->setMaximumSize(QSize(52, 27));
        lineEdit_scale->setFocusPolicy(Qt::StrongFocus);
        lineEdit_scale->setLayoutDirection(Qt::LeftToRight);
        lineEdit_scale->setStyleSheet(QLatin1String("QLineEdit\n"
"{	\n"
"	\n"
"}"));
        lineEdit_scale->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_scale, 2, 1, 1, 1);

        SupZ = new QPushButton(frame_2);
        SupZ->setObjectName(QStringLiteral("SupZ"));
        SupZ->setEnabled(false);
        SupZ->setMinimumSize(QSize(52, 27));
        SupZ->setMaximumSize(QSize(52, 102));

        gridLayout->addWidget(SupZ, 2, 2, 1, 1);

        SupZ_linedit = new QLineEdit(frame_2);
        SupZ_linedit->setObjectName(QStringLiteral("SupZ_linedit"));
        SupZ_linedit->setMinimumSize(QSize(52, 0));
        SupZ_linedit->setMaximumSize(QSize(52, 27));
        SupZ_linedit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(SupZ_linedit, 2, 3, 1, 1);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(10, 126, 246, 87));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(2);
        gridLayout_2->setVerticalSpacing(4);
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        ModelExportButton = new QPushButton(frame_3);
        ModelExportButton->setObjectName(QStringLiteral("ModelExportButton"));
        ModelExportButton->setEnabled(false);
        ModelExportButton->setMinimumSize(QSize(81, 27));
        ModelExportButton->setMaximumSize(QSize(81, 102));
        ModelExportButton->setFont(font);
        ModelExportButton->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(ModelExportButton, 0, 0, 1, 1);

        ModelList = new QListWidget(frame_3);
        ModelList->setObjectName(QStringLiteral("ModelList"));
        ModelList->setMinimumSize(QSize(137, 0));
        ModelList->setMaximumSize(QSize(147, 16777215));
        ModelList->setFocusPolicy(Qt::NoFocus);
        ModelList->setStyleSheet(QLatin1String("QListWidget\n"
"{\n"
"	color: rgb(255, 255, 255);	\n"
"	background-color: rgb(115, 115, 115);\n"
"    font-family: \"Source Sans Pro\";\n"
"    font-size: 14px;\n"
"    font-weight: regular;\n"
"}"));
        ModelList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ModelList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(ModelList, 0, 1, 2, 1);

        ModelSnapButton = new QPushButton(frame_3);
        ModelSnapButton->setObjectName(QStringLiteral("ModelSnapButton"));
        ModelSnapButton->setEnabled(false);
        ModelSnapButton->setMinimumSize(QSize(81, 27));
        ModelSnapButton->setMaximumSize(QSize(81, 102));
        ModelSnapButton->setFont(font);
        ModelSnapButton->setFocusPolicy(Qt::NoFocus);

        gridLayout_2->addWidget(ModelSnapButton, 1, 0, 1, 1);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(8, 219, 251, 36));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_rot = new QLabel(frame_4);
        label_rot->setObjectName(QStringLiteral("label_rot"));
        label_rot->setMaximumSize(QSize(58, 16777215));
        label_rot->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_rot);

        lineEdit_rotx = new QLineEdit(frame_4);
        lineEdit_rotx->setObjectName(QStringLiteral("lineEdit_rotx"));
        lineEdit_rotx->setEnabled(false);
        lineEdit_rotx->setMaximumSize(QSize(52, 21));
        lineEdit_rotx->setStyleSheet(QStringLiteral(""));
        lineEdit_rotx->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_rotx);

        lineEdit_roty = new QLineEdit(frame_4);
        lineEdit_roty->setObjectName(QStringLiteral("lineEdit_roty"));
        lineEdit_roty->setEnabled(false);
        lineEdit_roty->setMaximumSize(QSize(52, 21));
        lineEdit_roty->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_roty);

        lineEdit_rotz = new QLineEdit(frame_4);
        lineEdit_rotz->setObjectName(QStringLiteral("lineEdit_rotz"));
        lineEdit_rotz->setEnabled(false);
        lineEdit_rotz->setMaximumSize(QSize(52, 21));
        lineEdit_rotz->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lineEdit_rotz);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(8, 260, 251, 39));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_5);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(frame_5);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(41, 0));
        label->setMaximumSize(QSize(16777215, 21));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        label_sizex = new QLabel(frame_5);
        label_sizex->setObjectName(QStringLiteral("label_sizex"));
        label_sizex->setMinimumSize(QSize(61, 21));
        label_sizex->setMaximumSize(QSize(61, 21));
        label_sizex->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_sizex);

        label_sizey = new QLabel(frame_5);
        label_sizey->setObjectName(QStringLiteral("label_sizey"));
        label_sizey->setMinimumSize(QSize(61, 21));
        label_sizey->setMaximumSize(QSize(61, 21));
        label_sizey->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_sizey);

        label_sizez = new QLabel(frame_5);
        label_sizez->setObjectName(QStringLiteral("label_sizez"));
        label_sizez->setMinimumSize(QSize(61, 21));
        label_sizez->setMaximumSize(QSize(61, 21));
        label_sizez->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_sizez);


        retranslateUi(ModelEdit);

        QMetaObject::connectSlotsByName(ModelEdit);
    } // setupUi

    void retranslateUi(QWidget *ModelEdit)
    {
        ModelEdit->setWindowTitle(QApplication::translate("ModelEdit", "Form", 0));
#ifndef QT_NO_TOOLTIP
        AddModelButton->setToolTip(QApplication::translate("ModelEdit", "Add  new model(s) ", 0));
#endif // QT_NO_TOOLTIP
        AddModelButton->setText(QApplication::translate("ModelEdit", "\346\267\273\345\212\240", 0));
#ifndef QT_NO_TOOLTIP
        DuplicateModeButton->setToolTip(QApplication::translate("ModelEdit", "Duplicate the selected model", 0));
#endif // QT_NO_TOOLTIP
        DuplicateModeButton->setText(QApplication::translate("ModelEdit", "\345\244\215\345\210\266", 0));
#ifndef QT_NO_TOOLTIP
        RemoveModelButton->setToolTip(QApplication::translate("ModelEdit", "Delete the seleted object", 0));
#endif // QT_NO_TOOLTIP
        RemoveModelButton->setText(QApplication::translate("ModelEdit", "\345\210\240\351\231\244", 0));
#ifndef QT_NO_TOOLTIP
        ModelMoveButton->setToolTip(QApplication::translate("ModelEdit", "Change to top view,move the object", 0));
#endif // QT_NO_TOOLTIP
        ModelMoveButton->setText(QApplication::translate("ModelEdit", "\347\247\273\345\212\250", 0));
        ModelRotButton->setText(QApplication::translate("ModelEdit", "\346\227\213\350\275\254", 0));
#ifndef QT_NO_TOOLTIP
        RestRotButton->setToolTip(QApplication::translate("ModelEdit", "Reset the rotation .", 0));
#endif // QT_NO_TOOLTIP
        RestRotButton->setText(QApplication::translate("ModelEdit", "\345\244\215\344\275\215", 0));
        ColorButton->setText(QApplication::translate("ModelEdit", "\351\242\234\350\211\262", 0));
#ifndef QT_NO_TOOLTIP
        ModelSelectedButton->setToolTip(QApplication::translate("ModelEdit", "Change to select mode", 0));
#endif // QT_NO_TOOLTIP
        ModelSelectedButton->setText(QApplication::translate("ModelEdit", "\351\200\211\346\213\251", 0));
#ifndef QT_NO_TOOLTIP
        ModelScaleButton->setToolTip(QApplication::translate("ModelEdit", "Scaled the selected object", 0));
#endif // QT_NO_TOOLTIP
        ModelScaleButton->setText(QApplication::translate("ModelEdit", "\347\274\251\346\224\276", 0));
        lineEdit_scale->setText(QApplication::translate("ModelEdit", "1.00", 0));
        SupZ->setText(QApplication::translate("ModelEdit", "\345\215\207\351\231\215", 0));
        SupZ_linedit->setText(QApplication::translate("ModelEdit", "0.0", 0));
#ifndef QT_NO_TOOLTIP
        ModelExportButton->setToolTip(QApplication::translate("ModelEdit", "Export the model to STL file", 0));
#endif // QT_NO_TOOLTIP
        ModelExportButton->setText(QApplication::translate("ModelEdit", "\344\277\235\345\255\230\346\250\241\345\236\213", 0));
#ifndef QT_NO_TOOLTIP
        ModelSnapButton->setToolTip(QApplication::translate("ModelEdit", "Drop the object to the floor", 0));
#endif // QT_NO_TOOLTIP
        ModelSnapButton->setText(QApplication::translate("ModelEdit", "\346\224\276\347\275\256\345\271\263\345\217\260", 0));
        label_rot->setText(QApplication::translate("ModelEdit", "\346\227\213\350\275\254\350\247\222\345\272\246", 0));
        lineEdit_rotx->setText(QApplication::translate("ModelEdit", "0.0", 0));
        lineEdit_roty->setText(QApplication::translate("ModelEdit", "0.0", 0));
        lineEdit_rotz->setText(QApplication::translate("ModelEdit", "0.0", 0));
        label->setText(QApplication::translate("ModelEdit", "Size:", 0));
        label_sizex->setText(QApplication::translate("ModelEdit", "0", 0));
        label_sizey->setText(QApplication::translate("ModelEdit", "0", 0));
        label_sizez->setText(QApplication::translate("ModelEdit", "0", 0));
    } // retranslateUi

};

namespace Ui {
    class ModelEdit: public Ui_ModelEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELEDIT_H
