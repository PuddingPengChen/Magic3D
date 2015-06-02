#include "layoutprojectdata.h"
#include "modeldata.h"
#include "modelinstance.h"
#include "../SupportEngine/supportstructure.h"
#include "OS_Function.h"
#include <QDebug>
#include <QFile>


//////////////////////////////////
//Public
//////////////////////////////////

	//constructors/destructors
    LayoutProjectData::LayoutProjectData() : QObject()
	{
		New();
	}
    LayoutProjectData::~LayoutProjectData()
	{

	}

	//File Access:
    void LayoutProjectData::New()//Clears out internal project data, creates a new one with defualts
	{
        LoadDefaults();
        SetDirtied(false);
	}
    bool LayoutProjectData::Open(QString filepath, bool withoutVisuals) //returns success
    {
        int i;
        int FileVersion;
		bool jumpout = false;

		double resx;
		double resy;
        double xp, yp, zp;//instance positions/rotations/scales
        double xr, yr, zr;
        double xs, ys, zs;
        bool flipped = false;
        int numSupports;
        int hasFoundation;

        QFile file(filepath);
        QTextStream in;
        QString buff;//for io operations
        QString modelpath;//current model this function is trying to load.


        //input file operations here
		if(!file.open(QIODevice::ReadOnly))
		{
			return false;
        }
        //check file extension
        if(QFileInfo(filepath).completeSuffix().toLower() != "l")
            return false;


        SetDirtied(false);//presumably good from here so undirty the project

        in.setDevice(&file);//begin text streaming.
        in >> buff;
        if(buff == "ver")//we are looking at a post 1.4 blayout file
        {
            in >> buff;
            FileVersion = buff.toInt();//should be 14 or greater.
            in.skipWhiteSpace();
            mfilename = in.readLine();//get project name
        }
        else//old file - we need to read first line for project name
        {
            FileVersion = 13;

            in.seek(0);//go back and re-read.
            mfilename = in.readLine();//get project name
        }

        qDebug() << "Layout Version: " << FileVersion;

		buff = in.readLine();//eat startmodellist
		while(!jumpout)
		{
            in.skipWhiteSpace();
			buff = in.readLine();
			
			if(buff != "endinstancelist")
			{
                modelpath = buff;

                if(!QFileInfo(modelpath).exists())
                {
                    modelpath = QFileInfo(filepath).absolutePath() + "/" + QFileInfo(modelpath).fileName();
                }

                ModelInstance* pinst = pMain->AddModel(modelpath,withoutVisuals);//inst will be null if it cant find the file.
				
                //model relocation chanches
                if(pinst == NULL)
                {
                    PromptFindLostModel(pinst,modelpath);
                }


                in >> xp >> yp >> zp;
                in >> xr >> yr >> zr;
                in >> xs >> ys >> zs;

                //version 14 added instance flipping
                if(FileVersion >= 14)
                {
                    in >> buff;
                    flipped = (bool)buff.toInt();
                }
                else
                    flipped = false;

                if(pinst != NULL)
                {
                    pinst->SetPos(QVector3D(xp,yp,zp));
                    pinst->SetRot(QVector3D(xr,yr,zr));
                    pinst->SetScale(QVector3D(xs,ys,zs));
                    pinst->SetFlipped(flipped);
                    pinst->UpdateBounds();//in order that zhieght is good and all.
                }
                //version 15 added instance supports
                // add the supports to the loaded model
                if(FileVersion >= 15)
                {
                    in.skipWhiteSpace();
                    in >> buff;//eat "beginsupports"
                    in >> numSupports;
                    in >> hasFoundation;

                    if(hasFoundation)
                    StreamInSupportInfo(pinst,in,true);

                    for(i = 0; i < numSupports; i++)
                    {
                        StreamInSupportInfo(pinst,in,false);
                    }
                    in >> buff; in.skipWhiteSpace();//eat "endsupports"
                }
			}
			else
			{
				jumpout = true;
			}
		}

		in >> buff >> resx >> resy;
		in >> buff >> xypixel;


		SetResolution(QVector2D(resx,resy));
		CalculateBuildArea();
        mfilename = filepath;


        //some post load warnings for legacy layouts
        if(FileVersion < 15)
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("This Layout was created with an older version of creator");
            msgBox.setInformativeText("Some models may be rotated differently");
            msgBox.exec();
        }

        Disable_User_Waiting_Cursor();

		emit ProjectLoaded();
		return true;
	}


    bool LayoutProjectData::Save(QString filepath) //returns success
	{
        unsigned int i,j;
        ModelInstance* inst;
        SupportStructure* pSup;
        bool instHasFoundation;

		QFile file(filepath);

		if(!file.open(QIODevice::Truncate | QIODevice::WriteOnly))
		{
			return false;
		}

		QTextStream out(&file);//begin text streaming.
        out << "ver " << LAYOUT_FILE_VERSION << '\n';
		out << filepath << '\n';//write project name
		
		out << "startinstancelist" << '\n';//begin model list

        for(i = 0; i < pMain->GetAllInstances().size(); i++)
        {
            inst = pMain->GetAllInstances()[i];
            instHasFoundation = (bool)inst->GetBasePlate();
            out << pMain->GetAllInstances()[i]->pData->GetFilePath() << '\n' << inst->GetPos().x() <<" "<< inst->GetPos().y() <<" "<< inst->GetPos().z();
            out <<" "<< inst->GetRot().x() << " "<< inst->GetRot().y() <<" "<< inst->GetRot().z();
            out <<" "<< inst->GetScale().x() << " "<< inst->GetScale().y() <<" "<< inst->GetScale().z();
            out <<" " << inst->GetFlipped() << "\n";
            out << "beginsupports " << inst->GetSupports().size() << " " << instHasFoundation << "\n";

            //DEFINiTION: if there is a foundation support, its the first one.
            if(instHasFoundation)
                StreamOutSupportInfo(inst->GetBasePlate(),out);

            for(j = 0; j < inst->GetSupports().size(); j++)
            {
                pSup = inst->GetSupports()[j];
                StreamOutSupportInfo(pSup,out);
            }
            out << "endsupports" << "\n";
        }

		out << "endinstancelist" << '\n';//end model list

		out << "resolution " << GetResolution().x() << " " << GetResolution().y() << '\n';
		out << "XYpixelsize " << GetPixelSize() << '\n';


		SetDirtied(false);
        mfilename = filepath;
		return true;
	}

	//Structure Access:
	//Gets
    bool LayoutProjectData::IsDirtied()
	{
		return dirtied;
	}
    QString LayoutProjectData::GetFileName()//untitled if not saved yet
	{
        return mfilename;
	}
    QStringList LayoutProjectData::GetModelFileList()
	{
		return modelfilelist;
	}
    QVector3D LayoutProjectData::GetBuildSpace()
	{
		return dimentions;
	}
    double LayoutProjectData::GetPixelSize()
	{
		return  xypixel;
	}
    double LayoutProjectData::GetPixelThickness()
    {
        return  zthick;
    }
    QVector2D LayoutProjectData::GetResolution()
	{
		return resolution;
	}
    QString LayoutProjectData::GetJobName()
    {
        return jobExportName;
    }
    QString LayoutProjectData::GetJobDescription()
    {
        return jobExportDesc;
    }



	//Sets
    void LayoutProjectData::SetDirtied(bool dirt)
	{
        dirtied = dirt;
	}

	
    void LayoutProjectData::SetBuildSpaceSize(QVector3D size)
	{
		dimentions = size;
        QSettings appSettings;
        appSettings.beginGroup("USERLAYOUT");
            appSettings.setValue("DIMENTION_X",size.x());
            appSettings.setValue("DIMENTION_Y",size.y());
        appSettings.endGroup();

		SetDirtied(true);
	}
    void LayoutProjectData::SetPixelSize(double size)
	{
		xypixel = size;

        QSettings appSettings;
        appSettings.beginGroup("USERLAYOUT");
            appSettings.setValue("PIXEL_SIZE",size);
        appSettings.endGroup();


		SetDirtied(true);
	}
    void LayoutProjectData::SetPixelThickness(double thick)
    {
        zthick = thick;

        SetDirtied(true);
    }
    void LayoutProjectData::SetResolution(QVector2D dim)
	{
		resolution = dim;

        QSettings appSettings;
        appSettings.beginGroup("USERLAYOUT");
        appSettings.setValue("RESOLUTION_X",dim.x());
        appSettings.setValue("RESOLUTION_Y",dim.y());
        appSettings.endGroup();

		SetDirtied(true);
	}

    void LayoutProjectData::SetJobName(QString name)
    {
        jobExportName = name;
    }

    void LayoutProjectData::SetJobDescription(QString desc)
    {
        jobExportDesc = desc;
    }




    void LayoutProjectData::CalculateBuildArea()
	{
		SetBuildSpaceSize(QVector3D((xypixel/1000.0)*resolution.x(),(xypixel/1000.0)*resolution.y(),dimentions.z()));
	}
    void LayoutProjectData::UpdateZSpace()
	{
        unsigned int i;
		double max = 0.0;

        for(i=0;i<pMain->GetAllInstances().size();i++)
        {
            ModelInstance* inst = pMain->GetAllInstances()[i];
            if(inst->GetMaxBound().z() > max)
                max = inst->GetMaxBound().z();
        }


		SetBuildSpaceSize(QVector3D(dimentions.x(),dimentions.y(),max));
	}


//////////////////////////////////
//Private
//////////////////////////////////

    void LayoutProjectData::LoadDefaults()
    {
        QSettings appSettings;

        appSettings.beginGroup("USERLAYOUT");


        mfilename = "untitled";

        if(appSettings.value("PIXEL_SIZE").toInt())
            SetPixelSize(appSettings.value("PIXEL_SIZE").toInt());
        else
            SetPixelSize(100);


        SetPixelThickness(50.8);


        if(appSettings.value("RESOLUTION_X").toInt())
            SetResolution(QVector2D(appSettings.value("RESOLUTION_X").toInt(),appSettings.value("RESOLUTION_Y").toInt()));
        else
            SetResolution(QVector2D(1024,768));

        CalculateBuildArea();

        if(appSettings.value("DIMENTION_X").toInt())
            SetBuildSpaceSize(QVector3D(appSettings.value("DIMENTION_X").toInt(),appSettings.value("DIMENTION_Y").toInt(),0));
        else
            SetBuildSpaceSize(QVector3D(dimentions.x(),dimentions.y(),0));

        appSettings.endGroup();
    }

    void LayoutProjectData::PromptFindLostModel(ModelInstance* &pinst, QString modelpath)
    {
        if(pinst != NULL)
            return;//dont need to find a found thing..

        SetDirtied(true);

        //chance popup dialog asking if the user wants to manually find the file.
        QMessageBox msgBox;
        msgBox.setText("The model: " + QFileInfo(modelpath).baseName() + " can not be located.");
        msgBox.setInformativeText("Do you want to locate it manually?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Discard);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int response = msgBox.exec();
        if(response == QMessageBox::Yes)
        {
            QString correctedfilepath = QFileDialog::getOpenFileName(0, QString("Locate File: " + QFileInfo(modelpath).baseName()),
                                                                     "",QString(QFileInfo(modelpath).baseName()+"(*" + QFileInfo(modelpath).suffix() + ")"));
            if(!correctedfilepath.isEmpty())
            {
                pinst = pMain->AddModel(correctedfilepath);
            }
            if(pinst == NULL)//otherwise the user failed to find one
            {
                QMessageBox msgBox;
                msgBox.setText("substitute file unable to be imported.");
                msgBox.exec();
            }
        }
    }




    void LayoutProjectData::StreamOutSupportInfo(SupportStructure* sup, QTextStream &out)
    {
        out << "\"" << sup->GetTopAttachShape() << "\" ";
        out << "\"" << sup->GetMidAttachShape() << "\" ";
        out << "\"" << sup->GetBottomAttachShape() << "\" ";
        out << QString::number(sup->GetTopPoint().x()) << " ";
        out << QString::number(sup->GetTopPoint().y()) << " ";
        out << QString::number(sup->GetTopPoint().z()) << " ";

        out << QString::number(sup->GetBottomPoint().x()) << " ";
        out << QString::number(sup->GetBottomPoint().y()) << " ";
        out << QString::number(sup->GetBottomPoint().z()) << " ";

        out << QString::number(sup->GetTopLength()) << " ";
        out << QString::number(sup->GetBottomLength()) << " ";

        out << QString::number(sup->GetTopNormal().x()) << " ";
        out << QString::number(sup->GetTopNormal().y()) << " ";
        out << QString::number(sup->GetTopNormal().z()) << " ";

        out << QString::number(sup->GetBottomNormal().x()) << " ";
        out << QString::number(sup->GetBottomNormal().y()) << " ";
        out << QString::number(sup->GetBottomNormal().z()) << " ";

        out << QString::number(sup->GetTopAngleFactor()) << " ";
        out << QString::number(sup->GetBottomAngleFactor()) << " ";
        out << QString::number(sup->GetTopPenetration()) << " ";
        out << QString::number(sup->GetBottomPenetration()) << " ";
        out << QString::number(sup->GetTopRadius()) << " ";
        out << QString::number(sup->GetMidRadius()) << " ";
        out << QString::number(sup->GetBottomRadius()) << " ";
        out << sup->GetIsGrounded() << "\n";
    }

    void LayoutProjectData::StreamInSupportInfo(ModelInstance* pinst, QTextStream &in, bool asFoundation)
    {
        SupportStructure* pSup;
        QString sup_top_shape, sup_mid_shape, sup_bot_shape;
        double sup_top_point_x, sup_top_point_y, sup_top_point_z;
        double sup_bot_point_x, sup_bot_point_y, sup_bot_point_z;
        double sup_top_normal_x, sup_top_normal_y, sup_top_normal_z;
        double sup_bot_normal_x, sup_bot_normal_y, sup_bot_normal_z;
        double sup_top_angF, sup_bot_angF;
        double sup_top_len, sup_bot_len;
        double sup_top_pen, sup_bot_pen;
        double sup_top_rad, sup_mid_rad, sup_bot_rad;
        int sup_grounded;


        sup_top_shape = StreamInTextQuotes(in);
        sup_top_shape.remove("\"");

        sup_mid_shape = StreamInTextQuotes(in);
        sup_mid_shape.remove("\"");

        sup_bot_shape = StreamInTextQuotes(in);
        sup_bot_shape.remove("\"");


        in >> sup_top_point_x >> sup_top_point_y >> sup_top_point_z;
        in >> sup_bot_point_x >> sup_bot_point_y >> sup_bot_point_z;
        in >> sup_top_len >> sup_bot_len;
        in >> sup_top_normal_x >> sup_top_normal_y >> sup_top_normal_z;
        in >> sup_bot_normal_x >> sup_bot_normal_y >> sup_bot_normal_z;
        in >> sup_top_angF >> sup_bot_angF;
        in >> sup_top_pen >> sup_bot_pen;
        in >> sup_top_rad >> sup_mid_rad >> sup_bot_rad;
        in >> sup_grounded;
        in.skipWhiteSpace();//go to next line


        //APPLY...
        if(pinst == NULL)
            return;

        //add the support to the instance
        if(asFoundation)
        {
            pinst->EnableBasePlate();
            pSup = pinst->GetBasePlate();
        }
        else{
            pSup = pinst->AddSupport(QVector3D(sup_top_point_x, sup_top_point_y, sup_top_point_z),
                   QVector3D(sup_bot_point_x, sup_bot_point_y, sup_bot_point_z));
        }

        pSup->SetTopNormal(QVector3D(sup_top_normal_x, sup_top_normal_y, sup_top_normal_z));
        pSup->SetBottomNormal(QVector3D(sup_bot_normal_x, sup_bot_normal_y, sup_bot_normal_z));
        pSup->SetTopAngleFactor(sup_top_angF);
        pSup->SetBottomAngleFactor(sup_bot_angF);
        pSup->SetTopLength(sup_top_len);
        pSup->SetBottomLength(sup_bot_len);
        pSup->SetTopPenetration(sup_top_pen);
        pSup->SetBottomPenetration(sup_bot_pen);
        pSup->SetTopRadius(sup_top_rad);
        pSup->SetMidRadius(sup_mid_rad);
        pSup->SetBottomRadius(sup_bot_rad);
        pSup->SetTopAttachShape(sup_top_shape);
        pSup->SetMidAttachShape(sup_mid_shape);
        pSup->SetBottomAttachShape(sup_bot_shape);
        pSup->SetIsGrounded(sup_grounded);
    }
