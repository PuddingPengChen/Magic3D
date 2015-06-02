/*******************************************************************************
* Author    :  Peng Chen                                                       *
* Version   :  0.0.1                                                           *
* Date      :  12 July 2014                                                    *
* Website   :  http://www.3green-tech.com                                      *
* Copyright :  3green-tech 2010-2014                                           *
*                                                                              *
* Attributions:                                                                *
* A loadingbar,can be used gloable                                             *
*******************************************************************************/
#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include <QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>


class LoadingBar : public QDialog
{
	Q_OBJECT

public:
    LoadingBar();
    LoadingBar(int min, int max, bool autoshow = true);
	~LoadingBar();

public slots:
	void setMax(int max);
	void setMin(int min);
	void setValue(int val);
	void setDescription(QString str);
    void setProgress(qint64 fraction, qint64 total);
    void useCancelButton(bool use);
	int GetValue();

private:
    void SetupUI(bool autoshow);
	void SetupConnections();
	QHBoxLayout* horizontalLayout;
	QProgressBar* progressBar;
	QPushButton* cancelButton;
};
#endif
