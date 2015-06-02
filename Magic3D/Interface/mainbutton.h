/*******************************************************************************
*                                                                              *
* Author    :  Peng Chen                                                       *
* Version   :  0.0.1                                                           *
* Date      :  12 July 2014                                                    *
* Website   :  http://www.3green-tech.com                                      *
* Copyright :  3green-tech 2010-2014                                           *
*                                                                              *
* Attributions:                                                                *
* This class include three mainbutton,model edit button,support edit button,   *
* and the print edit button.  Press the button,enter the corresponding mode.   *                                             *
*******************************************************************************/
#ifndef MAINBUTTON_H
#define MAINBUTTON_H

#include <QWidget>

namespace Ui {
class MainButton;
}

class MainButton : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainButton(QWidget *parent = 0);
    ~MainButton();
    
private:
    Ui::MainButton *ui;
signals:
    void Sig_ModelMode();
    void Sig_SupportMode();
    void Sig_PrintMode();
private slots:
    void on_ModelButton_clicked();
    void on_SupportMode_clicked();
    void on_PrintMode_clicked();
};

#endif // MAINBUTTON_H
