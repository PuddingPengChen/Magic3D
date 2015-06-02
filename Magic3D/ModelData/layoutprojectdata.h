#ifndef  LAYOUTPROJECTDATA_H
#define LAYOUTPROJECTDATA_H

#include <QStringList>
#include <QVector3D>
#include <QVector2D>
#include <vector>
#include "../Interface/greentech.h"

#define LAYOUT_FILE_VERSION 15

class GreenTech;
class LayoutProjectData : public QObject
{
	Q_OBJECT
public:
    LayoutProjectData();
    ~LayoutProjectData();

	//File Access:
	void New();//Clears out internal project data, creates a new one with defualts
    bool Open(QString filepath, bool withoutVisuals = false); //returns success
	bool Save(QString filepath); //returns success

	//Structure Access:
	//Gets
	bool IsDirtied();
	QString GetFileName();//untitled if not saved yet
	QStringList GetModelFileList();
	QVector3D GetBuildSpace();
	double GetPixelSize();
    double GetPixelThickness();
	QVector2D GetResolution();
    double GetAttachmentSurfaceThickness(){return attachmentSurfaceThickness;}
    QString GetJobName();
    QString GetJobDescription();

	//Sets
	void SetDirtied(bool dirt);

	void SetBuildSpaceSize(QVector3D size);
	void SetPixelSize(double size);
    void SetPixelThickness(double thick);
	void SetResolution(QVector2D dim);
    void SetAttachmentSurfaceThickness(double thick){attachmentSurfaceThickness = thick;}
    void SetJobName(QString);
    void SetJobDescription(QString);

	void CalculateBuildArea();
	void UpdateZSpace();//calculates the size of the z box based on instance bounds
	
    GreenTech* pMain;
signals:
	void DirtChanged(bool dirt);
	void ProjectLoaded();

private:
	

	bool dirtied;
    QString mfilename;
	QStringList modelfilelist;
	QVector3D dimentions;
	QVector2D resolution;
	double xypixel;
	double zthick;
    double attachmentSurfaceThickness;
    QString jobExportName;//used when slicing to a job file.
    QString jobExportDesc;

    void LoadDefaults();

    void PromptFindLostModel(ModelInstance* &pinst, QString modelPath);//prompts the user to find the lost model returns true if found.

    void StreamOutSupportInfo(SupportStructure* sup, QTextStream &out);
    void StreamInSupportInfo(ModelInstance* pinst, QTextStream &in, bool asFoundation = false);

};
#endif
