#include "greentech.h"
#include "ui_greentech.h"
#include "../ModelData/layoutprojectdata.h"
#include "loadingbar.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QVector3D>
#include <QGLWidget>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include "../ModelData/modeldata.h"
#include "../ModelData/modelinstance.h"
#include "OS_Function.h"
#include "../ModelData/modelwriter.h"


GreenTech::GreenTech(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GreenTech)
{
    ui->setupUi(this);
    //Initialize project data
    project = new LayoutProjectData();

    project->pMain = this;
    m_ModelEdit = new ModelEdit();
    m_ModelList = m_ModelEdit->GetModelList();
    m_ModelScale = m_ModelEdit->GetLineEdit();

    SliderValue = -1;
    LayThickness = 100;
    AddBase = false;
    setWindowTitle(tr("游侠三维"));
    setWindowIcon(QIcon(":/image/logo1.ico"));
    //Create the worldview and attach it to the window
    pWorldView = new WorldView(0,this);
    QGraphicsView *view = ui->graphicsView;         //操控ui上的graphicsView
//    view->setCacheMode(QGraphicsView::CacheBackground);


    main_button = new MainButton();
    print_dialog = new PrintEdit();
    proxy_mainbutton = new QGraphicsProxyWidget();
    proxy_mainbutton->setWidget(main_button);
    proxy_mainbutton->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    proxy_mainbutton->setPos(3,5);
    pWorldView->addItem(proxy_mainbutton);

//    printSetup = new PrintSetup();
//    proxy_printsetup = new QGraphicsProxyWidget();
//    proxy_printsetup->setWidget(printSetup);
//    proxy_printsetup->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
//    proxy_printsetup->setPos(200,100);
//    pWorldView->addItem(proxy_printsetup);

    proxy_printedit = new QGraphicsProxyWidget();
    proxy_printedit->setWidget(print_dialog);
    proxy_printedit->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    proxy_printedit->setPos(3,140);
    proxy_printedit->setWindowTitle("PrintEdit");
    pWorldView->addItem(proxy_printedit);
    proxy_printedit->hide();

    proxy_image = new QGraphicsProxyWidget();
    ImageWidget = new ImageViewWidget();
    proxy_image->setWidget(ImageWidget);
    proxy_image->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    proxy_image->setPos(3,140);
    pWorldView->addItem(proxy_image);
    proxy_image->hide();


    proxy_modeledit = new QGraphicsProxyWidget();
    proxy_modeledit->setWidget(m_ModelEdit);
    proxy_modeledit->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    proxy_modeledit->setPos(3,140);
    proxy_modeledit->setWindowTitle("ModelEdit");
    pWorldView->addItem(proxy_modeledit);
    proxy_modeledit->hide();



    view->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setScene(pWorldView);
    view->show();

    SetToolModelSelect();//start off with pointer tool
    //support editing

    currInstanceInSupportMode = NULL;
    useContourAid = true;
    useXRayVision = false;
    xRayPercentage = 0.5;
    hideSupports = true;

    //slicing
    processor = new fffProcessor(config);

    //build the interface initially - different than update interface..
    BuildInterface();
    UpdateInterface();
}

GreenTech::~GreenTech()
{
    unsigned int m;
    for(m=0;m<ModelDataList.size();m++)
    {
        delete ModelDataList[m];
    }
    delete project;
    delete pWorldView;
    delete ui;
}


//returns a list of the currently selected instances
std::vector<ModelInstance*> GreenTech::GetSelectedInstances()
{
    std::vector<ModelInstance*> insts;
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        insts.push_back(FindInstance(m_ModelList->selectedItems()[i]));
    }
    return insts;
}

std::vector<ModelInstance*> GreenTech::GetAllInstances()
{
    unsigned int d, i;
    std::vector<ModelInstance*> allInsts;

    for(d = 0; d < ModelDataList.size(); d++)
    {
        for(i = 0; i < ModelDataList[d]->instList.size(); i++)
        {
            allInsts.push_back(ModelDataList[d]->instList[i]);
        }
    }

    return allInsts;
}

//////////////////////////////////////////////////////
//Public Slots
//////////////////////////////////////////////////////
//interface
void GreenTech::BuildInterface()
{
    connect(main_button,SIGNAL(Sig_ModelMode()),this,SLOT(ChangeToModelMode()));
    connect(main_button,SIGNAL(Sig_SupportMode()),this,SLOT(ChangeToSupportMode()));
    connect(main_button,SIGNAL(Sig_PrintMode()),this,SLOT(ChangeToPrintMode()));

    connect(m_ModelEdit,SIGNAL(Sig_SupZ(QVector3D)),this,SLOT(ChangZ(QVector3D)));
    connect(m_ModelEdit,SIGNAL(Sig_AddModel()),this,SLOT(AddModel()));
    connect(m_ModelEdit,SIGNAL(Sig_DuplicateModel()),this,SLOT(DuplicateSelection()));
    connect(m_ModelEdit,SIGNAL(Sig_RemoveModel()),this,SLOT(DeleteSelectedInstances()));
    connect(m_ModelEdit,SIGNAL(Sig_ScaleModel(double)),this,SLOT(ChangeModelScale(double)));
    connect(m_ModelEdit,SIGNAL(Sig_SelectedModel()),this,SLOT(ChangeModelSelected()));
    connect(m_ModelEdit,SIGNAL(Sig_RotModel()),this,SLOT(ChangeModelRot()));
    connect(m_ModelEdit,SIGNAL(Sig_RotX(float)),this,SLOT(ChangeRotX(float)));
    connect(m_ModelEdit,SIGNAL(Sig_RotY(float)),this,SLOT(ChangeRotY(float)));
    connect(m_ModelEdit,SIGNAL(Sig_RotZ(float)),this,SLOT(ChangeRotZ(float)));
    connect(m_ModelEdit,SIGNAL(Sig_ResetRotModel()),this,SLOT(ResetSelectionRotation()));
    connect(m_ModelEdit,SIGNAL(Sig_SnapModel()),this,SLOT(DropSelectionToFloor()));
    connect(m_ModelEdit,SIGNAL(Sig_MoveModel()),this,SLOT(ChangeModeMove()));
    connect(m_ModelEdit,SIGNAL(Sig_ExportModel()),this,SLOT(PromptExportToSTL()));
    connect(m_ModelEdit,SIGNAL(Sig_ModelColor()),this,SLOT(ChangeColor()));
    connect(pWorldView,SIGNAL(Sig_modelSelected(bool)),m_ModelEdit,SLOT(IsModelSelected(bool)));

    connect(print_dialog,SIGNAL(Sig_ImageShow(bool)),this,SLOT(ShowTheImage(bool)));
    connect(print_dialog,SIGNAL(Sig_Slice()),this,SLOT(GreenTechSlice()));
    connect(print_dialog,SIGNAL(Sig_Thickness(int)),this,SLOT(ChangeLayerThickness(int)));
    connect(print_dialog,SIGNAL(Sig_ComError(QString)),this,SLOT(getComError(QString)));
    connect(this,SIGNAL(Sig_StorageToImage(SliceDataStorage*)),ImageWidget,SLOT(ReceiveStroage(SliceDataStorage*)));
    connect(ImageWidget,SIGNAL(Sig_SliderValue(int)),this,SLOT(ReceiveSliderValue(int)));
    connect(ImageWidget,SIGNAL(Sig_printEditShow()),this,SLOT(ShowPrintEdit()));
    /*************************************/
    /*      menubar's action set         */
    /*************************************/
    //open STL file
    ui->actionOpen->setCheckable(true);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(AddModel()));

    //save file
    ui->actionSave_2->setCheckable(true);
    ui->actionSave_2->setShortcut(QKeySequence::Save);
    connect(ui->actionSave_2,SIGNAL(triggered()),this,SLOT(PromptExportToSTL()));

    //quit
    ui->actionQuit_Pudding->setCheckable(true);
    ui->actionQuit_Pudding->setShortcut(QKeySequence::Quit);
    connect(ui->actionQuit_Pudding,SIGNAL(triggered()),this,SLOT(close()));

    //copy
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    connect(ui->actionCopy,SIGNAL(triggered()),this,SLOT(DuplicateSelection()));

    //delete
    ui->actionDelete->setShortcut(QKeySequence::Delete);
    connect(ui->actionDelete,SIGNAL(triggered()),this,SLOT(DeleteSelectedInstances()));

    //snap floor
    ui->actionSnap->setShortcut(tr("F"));
    connect(ui->actionSnap,SIGNAL(triggered()),this,SLOT(DropSelectionToFloor()));

    //selectve
    ui->actionSelect->setShortcut(tr("S"));
    connect(ui->actionSelect,SIGNAL(triggered()),this,SLOT(ChangeModelSelected()));

    //model move
    ui->actionMove->setShortcut(tr("M"));
    connect(ui->actionMove,SIGNAL(triggered()),this,SLOT(ChangeModeMove()));

    //reset rotate
    ui->actionReset_Rotate->setShortcut(tr("R"));
    connect(ui->actionReset_Rotate,SIGNAL(triggered()),this,SLOT(ResetSelectionRotation()));

    //view setting
    connect(ui->actionOrtho,SIGNAL(triggered()),this,SLOT(SetOrtho()));
    connect(ui->actionPerspective,SIGNAL(triggered()),this,SLOT(SetPerspective()));
    connect(ui->actionTopView,SIGNAL(triggered()),pWorldView,SLOT(TopView()));
    connect(ui->actionBottomView,SIGNAL(triggered()),pWorldView,SLOT(BottomView()));
    connect(ui->actionRightView,SIGNAL(triggered()),pWorldView,SLOT(RightView()));
    connect(ui->actionLeftView,SIGNAL(triggered()),pWorldView,SLOT(LeftView()));
    connect(ui->actionFrontView,SIGNAL(triggered()),pWorldView,SLOT(FrontView()));
    connect(ui->actionBackView,SIGNAL(triggered()),pWorldView,SLOT(BackView()));
/*********************************************************************************************/
    /*************************************/
    /*      for support mode's action    */
    /*************************************/
    connect(ui->actionBack_View,SIGNAL(activated()),this,SLOT(ChangeToModelMode()));
    connect(ui->actionAuto_Support,SIGNAL(activated()),pWorldView,SLOT(AutoSupport()));
    connect(ui->actionDeleteSupport,SIGNAL(activated()),this,SLOT(ChangeDelectedSupprt()));
    connect(ui->actionManuAddSupport,SIGNAL(activated()),this,SLOT(ChangeManuAddSupport()));
    connect(ui->actionLight_support,SIGNAL(activated()),this,SLOT(ResetSupportLight()));
    connect(ui->actionMedium_support,SIGNAL(activated()),this,SLOT(ResetSupportMedium()));
    connect(ui->actionHeavy_support,SIGNAL(activated()),this,SLOT(ResetSupportHeavy()));
    connect(ui->actionAddBasePlate,SIGNAL(activated()),this,SLOT(AddBasePlate()));
    connect(ui->actionRemoveAll,SIGNAL(activated()),this,SLOT(RemoveAllSupport()));

     ui->viewToolBar->addAction(ui->actionBack_View);
     ui->actionBack_View->setText("Out Support");
     ui->viewToolBar->hide();

     ui->viewToolBar->addAction(ui->actionAuto_Support);
     ui->actionAuto_Support->setText("AutoSupport");

     ui->viewToolBar->addAction(ui->actionDeleteSupport);
     ui->actionDeleteSupport->setText("DeletedSupport");

     ui->viewToolBar->addAction(ui->actionRemoveAll);
     ui->actionRemoveAll->setText("RemoveAll");

     ui->viewToolBar->addAction(ui->actionManuAddSupport);
     ui->actionManuAddSupport->setText("ManuAddSupport");

     ui->viewToolBar->addAction(ui->actionAddBasePlate);
     ui->actionAddBasePlate->setText("BasePlate");

     ui->supportEdit->addAction(ui->actionLight_support);
     ui->supportEdit->addAction(ui->actionMedium_support);
     ui->supportEdit->addAction(ui->actionHeavy_support);
     ui->supportEdit->hide();


}

void GreenTech::UpdateInterface()
{

   if(m_ModelList->selectedItems().size() <= 0 || m_ModelList->selectedItems().size() > 1)  //no or multiple items selected.
    {
    }
    else //exactly ONE object selected
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[0]);
        QString scale = QString("%1").arg(inst->GetScale().x());
//        m_ModelScale->setValue(inst->GetScale().x());
        m_ModelScale->setText(scale);
        m_ModelEdit->SetPosText(inst->GetMaxBound()-inst->GetMinBound());
        m_ModelEdit->SetZ_value(inst->GetSupport_z());
        m_ModelEdit->SetRotText(inst->GetRot());

   }
}

//tools interface
void GreenTech::SetTool(QString toolname)
{
    if(toolname == "MODELSELECT")
        SetToolModelSelect();
    else if(toolname == "MODELMOVE")
        SetToolModelMove();
    else if(toolname == "MODELSPIN")
        SetToolModelSpin();
    else if(toolname == "MODELORIENTATE")
        SetToolModelOrientate();
    else if(toolname == "MODELSCALE")
        SetToolModelScale();
    else if(toolname == "SUPPORTMODIFY")
        SetToolSupportModify();
    else if(toolname == "SUPPORTADD")
        SetToolSupportAdd();
    else if(toolname == "SUPPORTDELETE")
        SetToolSupportDelete();
    else if(toolname == "PRINT")
        SetToolPrint();
}
void GreenTech::SetPerspective()
{
    pWorldView->setPerspective(true);
}
void GreenTech::SetOrtho()
{
    pWorldView->setPerspective(false);
}

void GreenTech::SetToolModelSelect()
{
    pWorldView->SetTool("MODELSELECT");
}
void GreenTech::SetToolModelMove()
{
    pWorldView->SetTool("MODELMOVE");
}
void GreenTech::SetToolModelSpin()
{
    pWorldView->SetTool("MODELSPIN");
}
void GreenTech::SetToolModelOrientate()
{
    pWorldView->SetTool("MODELORIENTATE");
}

void GreenTech::SetToolModelScale()
{
    pWorldView->SetTool("MODELSCALE");
}

void GreenTech::SetToolPrint()
{
    pWorldView->SetTool("PRINT");
}
//SupportTools interface
void GreenTech::SetToolSupportModify()
{
    pWorldView->SetTool("SUPPORTMODIFY");
}

void GreenTech::SetToolSupportAdd()
{
    pWorldView->SetTool("SUPPORTADD");
    DeSelectAllSupports();
}

void GreenTech::SetToolSupportDelete()
{
    pWorldView->SetTool("SUPPORTDELETE");
    DeSelectAllSupports();
}
void GreenTech::ExitToolAction()
{
    pWorldView->ExitToolAction();
}

//contour aid
void GreenTech::OnToggleContourAid(bool tog)
{
    useContourAid = tog;
}

bool GreenTech::ContourAidEnabled()
{
    return useContourAid;
}
//model
ModelInstance* GreenTech::AddModel(QString filepath, bool bypassVisuals)
{
    QSettings settings;
    if(filepath.isEmpty())
    {
        filepath = QFileDialog::getOpenFileName(this,
            tr("打开模型"), settings.value(tr("目录")).toString(), tr("Models (*.stl)"));
        modelPath = filepath;
        qDebug()<<tr("in add model: filepath =%1").arg(filepath);
        //cancel button
        if(filepath.isEmpty())
            return NULL;
    }
    //by this point we should have a valid file path, if we dont - abort.
    if(!QFileInfo(filepath).exists())
    {
        return NULL;
    }

    //if the file has already been opened and is in the project, we dont want to load in another! instead we want to make a new instance
    for(unsigned int i = 0; i < ModelDataList.size(); i++)
    {
        if(ModelDataList[i]->GetFilePath() == filepath)
        {
            return ModelDataList[i]->AddInstance();//make a new instance
        }
    }
    ModelData* pNewModel;
    pNewModel = new ModelData(this,bypassVisuals);
    bool success = pNewModel->LoadIn(filepath);
    if(!success)
    {
        delete pNewModel;
        return NULL;
    }

    //update registry
    settings.setValue("WorkingDir",QFileInfo(filepath).absolutePath());

    //add to the list
    ModelDataList.push_back(pNewModel);
    pWorldView->SetModelSelected(true);
    //make an Instance of the model!
    ModelInstance* pNewInst = pNewModel->AddInstance();
    project->UpdateZSpace();

    //select it too
//    UpdateGreentech_bounding(pNewInst->GetMaxBound(),pNewInst->GetMinBound());
    SelectOnly(pNewInst);

    qDebug()<<tr("ModelDataList.size = %1").arg(ModelDataList.size());
    return pNewInst;
}
void GreenTech::RemoveAllInstances()
{
    unsigned int m;
    unsigned int i;

    std::vector<ModelInstance*> allinstlist;
    for(m=0;m<this->ModelDataList.size();m++)
    {
        ModelDataList[m]->loadedcount = 0;//also reset the index counter for instances!
        for(i=0;i<ModelDataList[m]->instList.size();i++)
        {
            allinstlist.push_back(ModelDataList[m]->instList[i]);
        }
    }
    for(i=0;i<allinstlist.size();i++)
    {
        delete allinstlist[i];
    }

    CleanModelData();
}
void GreenTech::CleanModelData()
{
    unsigned int m;
    std::vector<ModelData*> templist;
    for(m=0;m<ModelDataList.size();m++)
    {
        if(ModelDataList[m]->instList.size() > 0)
        {
            templist.push_back(ModelDataList[m]);
        }
        else
        {
            delete ModelDataList[m];
        }
    }
    ModelDataList.clear();
//    if(storage->volumes.size()!=0)
//   storage->volumes.clear();
//    pWorldView->FinalAutoSupportPointIndex.clear();
//    pWorldView->AutoSupportIndex.clear();
    pWorldView->AutoSupportFlag = false;
    ModelDataList = templist;
}

void GreenTech::AddTagToModelList(QListWidgetItem* item)
{
   // ui.ModelList->addItem(item);        //very important
    m_ModelList->addItem(item);
}

ModelInstance* GreenTech::FindInstance(QListWidgetItem* item)
{
    unsigned int d;
    unsigned int i;
    for(d=0;d<ModelDataList.size();d++)
    {
        for(i=0;i<ModelDataList[d]->instList.size();i++)
        {
            if(ModelDataList[d]->instList[i]->listItem == item)
            {
                return ModelDataList[d]->instList[i];
            }
        }
    }
    return NULL;
}
//获取com口的错误
void GreenTech::getComError(QString t)
{
    if(t=="NO1")
    {
        QMessageBox msgBox;
        msgBox.setText(QObject::tr("串口连接成功！"));
        msgBox.exec();
        //QMessageBox::information(this, QObject::tr("打开成功"), QObject::tr("已成功打开串口 "), QMessageBox::Ok);
    }
    else if(t=="NO2")
    {
        QMessageBox msgBox1;
        msgBox1.setText(QObject::tr("串口打开失败！"));
        msgBox1.exec();
//        QMessageBox::critical(this, QObject::tr("打开失败"), QObject::tr("未能打开串口 ") +  QObject::tr("\n该串口设备不存在或已被占用"), QMessageBox::Ok);
    }
    else if(t=="NO3")
    {
        QMessageBox msgBox2;
        msgBox2.setText(QObject::tr("串口已经关闭"));
        msgBox2.exec();
//        QMessageBox::information(this, QObject::tr("关闭成功"), QObject::tr("已成功关闭串口 "), QMessageBox::Ok);
    }

}
//selection
void GreenTech::RefreshSelectionsFromList()
{
    int i;
    for(i=0;i<m_ModelList->count();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->item(i));
        if(inst == NULL)
            return;

        if(!m_ModelList->item(i)->isSelected())
        {
            DeSelect(FindInstance(m_ModelList->item(i)));
        }
        else if(m_ModelList->item(i)->isSelected())
        {
            Select(FindInstance(m_ModelList->item(i)));
        }
    }
}
void GreenTech::Select(ModelInstance* inst)
{
    //qDebug() << inst << "added to selection";
    inst->SetSelected(true);
    UpdateInterface();
}
void GreenTech::DeSelect(ModelInstance* inst)
{
    //qDebug() << inst << "removed from selection";
    inst->SetSelected(false);
    UpdateInterface();
}
void GreenTech::SelectOnly(ModelInstance* inst)
{
    DeSelectAll();
    Select(inst);
}
void GreenTech::SelectOnly(SupportStructure* sup)
{
    DeSelectAllSupports();
    SelectSupport(sup);
}


void GreenTech::DeSelectAll()
{
    unsigned int m;
    unsigned int i;
    for(m=0;m<ModelDataList.size();m++)
    {
        for(i=0;i<ModelDataList[m]->instList.size();i++)
        {
            DeSelect(ModelDataList[m]->instList[i]);
        }
    }
}

void GreenTech::SetSelectionPos(double x, double y, double z, int axis)
{
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[i]);
        if(axis==0)
            inst->SetPos(QVector3D(x,y,z));
        else if(axis==1)
            inst->SetPos(QVector3D(x,inst->GetPos().y(),inst->GetPos().z()));
        else if(axis==2)
            inst->SetPos(QVector3D(inst->GetPos().x(),y,inst->GetPos().z()));
        else if(axis==3)
            inst->SetPos(QVector3D(inst->GetPos().x(),inst->GetPos().y(),z + inst->GetPos().z() - inst->GetMinBound().z()));
    }
}
void GreenTech::SetSelectionRot(QVector3D newRot)
{
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[i]);
        inst->SetRot(newRot);
    }
}
void GreenTech::SetSelectionScale(double x, double y, double z, int axis)
{
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[i]);
        if(axis==0)
            inst->SetScale(QVector3D(x,y,z));
        else if(axis==1)
            inst->SetScale(QVector3D(x,inst->GetScale().y(),inst->GetScale().z()));
        else if(axis==2)
            inst->SetScale(QVector3D(inst->GetScale().x(),y,inst->GetScale().z()));
        else if(axis==3)
            inst->SetScale(QVector3D(inst->GetScale().x(),inst->GetScale().y(),z));
    }
}
void GreenTech::SetSelectionFlipped(bool flipped)
{
    unsigned int i;
    std::vector<ModelInstance*> instList = GetSelectedInstances();

    for(i=0; i < instList.size(); i++)
    {
        instList[i]->SetFlipped(flipped);
    }
}


void GreenTech::DropSelectionToFloor()
{
    unsigned int i;
    for(int  i = 0; i < GetSelectedInstances().size(); i++)
    {
       GetSelectedInstances()[i]->UpdateBounds();
       GetSelectedInstances()[i]->RestOnBuildSpace();
    }
//    for( i = 0; i < GetSelectedInstances().size(); i++)
//    {
//        GetSelectedInstances()[i]->RestOnBuildSpace();
//    }
    UpdateInterface();
}
void GreenTech::ResetSelectionRotation()
{
    unsigned int i;
    for(i = 0; i < GetSelectedInstances().size(); i++)
    {
        GetSelectedInstances()[i]->SetRot(QVector3D(0,0,0));
        GetSelectedInstances()[i]->UpdateBounds();
    }
    UpdateInterface();
}


void GreenTech::DuplicateSelection()
{
    unsigned int i;
    ModelInstance* inst;
    ModelInstance* newinst;
    ModelInstance* compareinst;
    SupportStructure* newSup;
    bool good = true;
    double x;
    double y;
    double xkeep;
    double ykeep;
    std::vector<ModelInstance*> sellist = GetSelectedInstances();
    for(i=0;i<sellist.size();i++)
    {
        inst = sellist[i];

        double xsize = inst->GetMaxBound().x() - inst->GetMinBound().x();
        double ysize = inst->GetMaxBound().y() - inst->GetMinBound().y();

        xkeep = 0;
        ykeep = 0;
        for(x = -project->GetBuildSpace().x()*0.5 + xsize/2; x <= project->GetBuildSpace().x()*0.5 - xsize/2; x += xsize + 1)
        {
            for(y = -project->GetBuildSpace().y()*0.5 + ysize/2; y <= project->GetBuildSpace().y()*0.5 - ysize/2; y += ysize + 1)
            {
                good = true;
                for(unsigned int d=0;d<ModelDataList.size();d++)
                {
                    for(unsigned int n=0;n<ModelDataList[d]->instList.size();n++)
                    {
                        compareinst = ModelDataList[d]->instList[n];

                        if(((x - xsize/2) < compareinst->GetMaxBound().x()) && ((x + xsize/2) > compareinst->GetMinBound().x()) && ((y - ysize/2) < compareinst->GetMaxBound().y()) && ((y + ysize/2) > compareinst->GetMinBound().y()))
                        {
                            good = false;
                        }
                    }
                }
                if(good)
                {
                    xkeep = x;
                    ykeep = y;
                }
            }
        }

        newinst = inst->pData->AddInstance();
        newinst->SetPos(QVector3D(xkeep,ykeep,inst->GetPos().z()));
        newinst->SetRot(inst->GetRot());
        newinst->SetScale(inst->GetScale());
        newinst->SetFlipped(inst->GetFlipped());
        newinst->SetBounds(inst->GetMaxBound()+(newinst->GetPos() - inst->GetPos()),
        inst->GetMinBound() + (newinst->GetPos() - inst->GetPos()));
        //dup supports
        for(i = 0; i < inst->GetSupports().size(); i++)
        {
            newSup = newinst->AddSupport();
            newSup->CopyFrom(inst->GetSupports()[i]);
            newSup->SetInstanceParent(newinst);

        }//and base plate
        if(inst->GetBasePlate())
        {
            newinst->EnableBasePlate();
            newinst->GetBasePlate()->CopyFrom(inst->GetBasePlate());
            newinst->GetBasePlate()->SetInstanceParent(newinst);
        }
//        UpdateGreentech_bounding(newinst->GetMaxBound(),newinst->GetMinBound());
        SelectOnly(newinst);
    }
         qDebug()<<tr("normalDisPlay.size = %1").arg(inst->pData->normDispLists.size());
}

//Upper level del action branching
void GreenTech::DeleteSelection()//delete whatever is selected - support or instance..
{
    if(SupportModeInst())
    {
        DeleteSelectedSupports();
    }
    else
    {
        DeleteSelectedInstances();
    }
}
void GreenTech::DeleteSelectedInstances()
{
    unsigned int i;
    std::vector<ModelInstance*> list = GetSelectedInstances();

    if(SupportModeInst())
        return;

    for(i=0;i < list.size();i++)
    {
        delete list[i];
    }
    //cleanup any unnessecary modeldata
    CleanModelData();
    UpdateInterface();
    project->UpdateZSpace();
    print_dialog->DisableSome();
    m_ModelEdit->SetRotText(QVector3D(0,0,0));
    m_ModelEdit->SetPosText(QVector3D(0,0,0));
}
//Support Mode/////////////////////////////////
void GreenTech::SetSupportMode(bool tog)
{
    if(tog && (currInstanceInSupportMode == NULL))  //go into support mode
    {
        qDebug() << "Entering Support Mode";
        //make sure weve selected somthing
        if(!GetSelectedInstances().size())
        {
             return;
        }
        //we can assume weve selected something...
        currInstanceInSupportMode = GetSelectedInstances()[0];

        //if the instance is on the ground, raise it so we dont get crunched supports.
        if(currInstanceInSupportMode->GetMinBound().z() < 0.01 && !currInstanceInSupportMode->GetSupports().size())
        {
            oldModelConstricted = true;
            currInstanceInSupportMode->Move(QVector3D(0,0,0)); //模型转换到支撑添加模式时在Z轴上升的高度
        }else oldModelConstricted = false;

        currInstanceInSupportMode->SetInSupportMode(true);
        //bake the instance in a manner similar to slice preparation
        //but without support baking!

        qDebug()<<"Now in the pick prepare ";
        currInstanceInSupportMode->BakeGeometry();
        currInstanceInSupportMode->FormTriPickDispLists();
        qDebug()<<"pick prepare over";
        oldZoom = pWorldView->GetZoom();
        oldPan = pWorldView->GetPan();
        oldRot = pWorldView->GetRotation();
        oldTool = pWorldView->GetTool();

        qDebug()<<tr("SetRevolvePoint x=%1,y=%2,z=%3 ").arg(currInstanceInSupportMode->GetPos().x()).arg(currInstanceInSupportMode->GetPos().y()).arg(currInstanceInSupportMode->GetPos().z());
        pWorldView->SetRevolvePoint(currInstanceInSupportMode->GetPos());
        pWorldView->SetPan(QVector3D(0,0,0));
        pWorldView->SetZoom(80.0);
        currInstanceInSupportMode->SetSupportBounding(QVector3D(0,0,0));
        //set tool to support addition
        SetToolSupportAdd();
    }
    else if(!tog && (currInstanceInSupportMode != NULL))
    {
        qDebug() << "Exiting Support Mode";

        if(currInstanceInSupportMode != NULL)
        {
            currInstanceInSupportMode->SetInSupportMode(false);
            currInstanceInSupportMode->FreeTriPickDispLists();
            currInstanceInSupportMode->UnBakeGeometry();
            currInstanceInSupportMode->FreeTriContainers();
            if(oldModelConstricted && !currInstanceInSupportMode->GetSupports().size())
            {
                currInstanceInSupportMode->Move(QVector3D(0,0,0));//物体在support模式下悬空的高度
                currInstanceInSupportMode->SetSupportBounding(QVector3D(0,0,0));
            }
            else
            {
                currInstanceInSupportMode->SetPos(currInstanceInSupportMode->GetPos());//nudge to fix supports
                currInstanceInSupportMode->SetSupportBounding(QVector3D(0,0,0));
            }

            currInstanceInSupportMode = NULL;
        }
        pWorldView->SetRevolvePoint(QVector3D(0,0,0));
        pWorldView->SetPan(oldPan);
        pWorldView->SetZoom(oldZoom);
        SetTool(oldTool);
    }
    //if entering or leaving we always deselect all supports
    DeSelectAllSupports();
    UpdateInterface();
}

SupportStructure* GreenTech::FindSupportByName(QString name)
{
    unsigned int s;
    unsigned int searchNum = name.remove("Support ").toInt();
    std::vector<SupportStructure*> supList;

    if(!currInstanceInSupportMode)
    {
        qDebug() << "WARNING: finding support out of support mode";
         return NULL;
    }

    supList = currInstanceInSupportMode->GetSupports();

    for(s = 0; s < supList.size(); s++)
    {
        if(searchNum == supList[s]->SupportNumber)
        {
            return supList[s];
        }
    }
    return NULL;
}

ModelInstance* GreenTech::SupportModeInst()
{
    return currInstanceInSupportMode;
}

void GreenTech::SelectSupport(SupportStructure* sup)
{
    //first see if the support is already selected, we dont want duplicates.
    int i;
    for(i = 0; i < currSelectedSupports.size(); i++)
    {
        if(sup == currSelectedSupports[i])
            return;
    }

    //qDebug() << "Support: "<< sup << " added to selection";
    sup->SetSelected(true);
    currSelectedSupports.push_back(sup);

    UpdateInterface();


}

std::vector<SupportStructure*>* GreenTech::GetSelectedSupports()
{
    return &currSelectedSupports;
}

bool GreenTech::IsSupportSelected(SupportStructure* sup)
{
    unsigned int i;
    for(i = 0; i < currSelectedSupports.size(); i++)
    {
        if(currSelectedSupports[i] == sup)
            return true;
    }

    return false;
}

void GreenTech::DeSelectSupport(SupportStructure* sup)
{
    unsigned int s;
    std::vector<SupportStructure*> keepers;

    for(s = 0; s < currSelectedSupports.size(); s++)
    {
        if(currSelectedSupports[s] == sup)
        {
            //qDebug() << "Support: " << sup << " removed from selection";
            sup->SetSelected(false);
        }
        else
            keepers.push_back(currSelectedSupports[s]);
    }
    currSelectedSupports.clear();
    currSelectedSupports = keepers;

    UpdateInterface();

}

void GreenTech::DeSelectAllSupports()
{
    //qDebug() << "De-Selecting All Supports, selection list size: " << currSelectedSupports.size();
    while(currSelectedSupports.size())
    {
        DeSelectSupport(currSelectedSupports[0]);
    }
}


void GreenTech::DeleteSelectedSupports()//called from remove button.
{
    unsigned int s;
    if(!SupportModeInst())
        return;

    for(s = 0; s < currSelectedSupports.size(); s++)
    {
        SupportModeInst()->RemoveSupport(currSelectedSupports[s]);
    }
    currSelectedSupports.clear();
    UpdateInterface();
}

void GreenTech::DeleteSupport(SupportStructure* pSup)
{
    if(SupportModeInst() != NULL)
    {
        if(IsSupportSelected(pSup))
            DeSelectSupport(pSup);

        SupportModeInst()->RemoveSupport(pSup);
    }
    UpdateInterface();
}

void GreenTech::MakeSelectedSupportsVertical()
{
    unsigned int i;
    SupportStructure* pSup;

    if(SupportModeInst()== NULL)
        return;

    for(i = 0; i < currSelectedSupports.size(); i++)
    {
        pSup = currSelectedSupports[i];
        pSup->SetBottomPoint(QVector3D(pSup->GetTopPivot().x(),
                                       pSup->GetTopPivot().y(),
                                       pSup->GetBottomPoint().z()));
    }
}

void GreenTech::MakeSelectedSupportsStraight()
{
    unsigned int i;
    SupportStructure* pSup;
    QVector3D lenVec;
    QVector3D topNorm, bottomNorm;

    if(SupportModeInst() == NULL)
        return;
    for(i = 0; i < currSelectedSupports.size(); i++)
    {
        pSup = currSelectedSupports[i];

        lenVec = pSup->GetTopPoint() - pSup->GetBottomPoint();
        lenVec.normalize();

        topNorm = pSup->GetTopNormal();
        bottomNorm = pSup->GetBottomNormal();

        topNorm = lenVec;
        topNorm.normalize();

        bottomNorm = -lenVec;
        bottomNorm.normalize();


        pSup->SetTopNormal(topNorm);
        if(!pSup->GetIsGrounded())
            pSup->SetBottomNormal(bottomNorm);

        pSup->SetTopAngleFactor(1.0);
        if(!pSup->GetIsGrounded())
            pSup->SetBottomAngleFactor(1.0);
    }
}

int GreenTech::PrintExportToSTL()
{
    QString filename;
//    QSettings settings;
    filename = "./print.stl";
//    qDebug()<<filename;
    QMessageBox msgBox;
    msgBox.setText("Notice");
     msgBox.setInformativeText("Ready to print,and you can't edit the model again,are you sure to make it?");
     msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
     msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret)
    {
      case QMessageBox::Yes:
           ExportToSTL(filename);
           return 1;
          break;
      case QMessageBox::No:
           msgBox.close();
           return 0;
          break;
      default:
          return 0;
          break;
    }
    return 0;
}
 void GreenTech::PromptExportToSTL()
 {
     QString filename;
     QSettings settings;
     filename = CROSS_OS_GetSaveFileName(this, tr("Export To STL"),
                                         settings.value("WorkingDir").toString() + "/" + ProjectData()->GetFileName(),
                                         tr("stl (*.stl)"));

     if(filename.isEmpty())
         return;

     if(ExportToSTL(filename))
     {
         QMessageBox msgBox;
         msgBox.setText("Stl Export Complete");
         msgBox.exec();
     }
     else
     {
         QMessageBox msgBox;
         msgBox.setIcon(QMessageBox::Warning);
         msgBox.setText("Unable To Export stl File");
         msgBox.exec();
     }
 }
 bool GreenTech::ExportToSTL(QString filename)
 {
     unsigned int i;
     unsigned long int t;
     ModelInstance* pInst = NULL;
     Triangle3D* pTri = NULL;
     bool fileOpened;

     ModelWriter exporter(filename, fileOpened);
     if(!fileOpened)
         return false;

     SetSupportMode(false);
     for(i = 0; i < GetAllInstances().size(); i++)
     {
         pInst = GetAllInstances().at(i);
         pInst->BakeGeometry(true);

         for(t = 0; t < pInst->triList.size(); t++)
         {
             pTri = pInst->triList[t];
             exporter.WriteNextTri(pTri);
         }

         pInst->UnBakeGeometry();
     }
     exporter.Finalize();
     return true;
 }

 SimpleModel* GreenTech::SaveToSliceModel(FMatrix3x3& matrix)
 {
     unsigned int i;
     unsigned long int t;
     ModelInstance* pInst = NULL;
     Triangle3D* pTri = NULL;

     SimpleModel* m = new SimpleModel();
     m->volumes.push_back(SimpleVolume());
     SimpleVolume* vol = &m->volumes[0];

     FPoint3 vertex;
     Point3 V[3];

     SetSupportMode(false);

     for(i = 0; i < GetAllInstances().size(); i++)
     {
//         SimpleVolume * vol = new SimpleVolume();
         pInst = GetAllInstances().at(i);
         pInst->BakeGeometry(true);

         for(t = 0; t < pInst->triList.size(); t++)
         {
             pTri = pInst->triList[t];
             for(int nm=0;nm<3;nm++)
             {
                 vertex.x = pTri->vertex[nm].x();
                 vertex.y = pTri->vertex[nm].y();
                 vertex.z = pTri->vertex[nm].z();
                 V[nm] = matrix.apply(vertex);
             }
             vol->addFace(V[0],V[1],V[2]);
         }
//         m->volumes.push_back(*vol);
         qDebug()<<tr("volumes.size = %1").arg(m->volumes.size());
         pInst->UnBakeGeometry();
     }
     return m;
}

//////////////////////////////////////////////////////
//Private
//////////////////////////////////////////////////////


///////////////////////////////////////////////////
//Events 传递到pWorldaiew类里面去了
///////////////////////////////////////////////////
void GreenTech::keyPressEvent(QKeyEvent * event )
{
    if(event->key() == Qt::Key_Escape)
    {
        SetSupportMode(false);
    }
    pWorldView->keyPressEvent(event);
}
void GreenTech::keyReleaseEvent(QKeyEvent * event )
{
    pWorldView->keyReleaseEvent(event);
}
void GreenTech::mousePressEvent(QMouseEvent *event)
{
  //  pWorldView->mousePressEvent(event);
   event->accept();
}
void GreenTech::mouseReleaseEvent(QMouseEvent *event)
{
//    pWorldView->mouseReleaseEvent(event);
    event->accept();
}

void GreenTech::hideEvent(QHideEvent *event)
{
    emit eventHiding();

 //   pWorldView->pDrawTimer->stop();
    event->accept();
}
void GreenTech::showEvent(QShowEvent *event)
{

 //   pWorldView->pDrawTimer->start();
    showMaximized();
    event->accept();
}

void GreenTech::closeEvent ( QCloseEvent * event )
{
    //if th GreenTech is dirty - ask the user if they want to save.
    if(project->IsDirtied())
    {
        QMessageBox msgBox;
        msgBox.setText("The GreenTech has been modified.");
         msgBox.setInformativeText("Do you want to save your changes?");
         msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Ignore | QMessageBox::Cancel);
         msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
          case QMessageBox::Ignore:
                //nothing
              break;
          case QMessageBox::Cancel:
                event->ignore();
                return;
              break;
          default:
              break;
        }
    }
    //when we close the window - we want to make a new project.
    //because we might open the window again and we want a fresh start.
    event->accept();

}

void GreenTech::contextMenuEvent(QContextMenuEvent *event)
{

}
//slot for MainButton
void GreenTech::ChangeToModelMode()
{
    SetSupportMode(false);
    ui->menuEdit->setDisabled(false);
    ui->menuView->setDisabled(false);
    ui->menuFile->setDisabled(false);

    ui->viewToolBar->hide();
    ui->supportEdit->hide();
    //add a model interface to the scene
    proxy_modeledit->show();
    proxy_printedit->hide();
    proxy_image->hide();
    pWorldView->setLayerValue(-1);
}
void GreenTech::ChangeToSupportMode()
{
    bool temp_modelselecte = pWorldView->IsModelSelect();
    if(temp_modelselecte)
    {
        ui->menuEdit->setDisabled(true);
        ui->menuView->setDisabled(true);
        ui->menuFile->setDisabled(true);
        ui->viewToolBar->show();
        SetSupportMode(true);
        proxy_modeledit->hide();
        proxy_printedit->hide();
    }
    else
    {
        QMessageBox message(QMessageBox::NoIcon,"Warning","No model selected,please selected one");
        message.exec();
    }
}

void GreenTech::ChangeToPrintMode()
{
    ui->menuEdit->setDisabled(true);
    ui->menuView->setDisabled(false);
    ui->menuFile->setDisabled(false);
    ui->actionOpen->setEnabled(false);
    if(QFile::exists("./test.svg"))
    {
        QFile::remove("./test.svg");
    }
    if(GetAllInstances().size()>0)
    {
       if(PrintExportToSTL())
       {
           RemoveAllInstances();
           AddModel("./print.stl",false);
       }
    }
    proxy_printedit->show();
    proxy_modeledit->hide();
    proxy_image->hide();
    SetTool("MODELSELECT");
}

void GreenTech::ChangeModelScale(double scale)
{
//    SetTool("MODELSCALE");
    SetSelectionScale(scale,0,0,1);
    SetSelectionScale(0,scale,0,2);
    SetSelectionScale(0,0,scale,3);
//    for(int  i = 0; i < GetSelectedInstances().size(); i++)
//    {
//       GetSelectedInstances()[i]->UpdateBounds();
//       GetSelectedInstances()[i]->RestOnBuildSpace();
//    }
    for( int i = 0; i < GetSelectedInstances().size(); i++)
    {
        GetSelectedInstances()[i]->UpdateBounds();
        GetSelectedInstances()[i]->RestOnBuildSpace();
    }
    UpdateInterface();
    SetTool("MODELSELECT");
}

void GreenTech::ChangeModelSelected()
{
    SetTool("MODELSELECT");
}

void GreenTech::ChangeModelRot()
{
    SetTool("MODELORIENTATE");
}
void GreenTech::ChangeRotX(float va)
{
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[i]);
        inst->SetRot(QVector3D(va,inst->GetRot().y(),inst->GetRot().z()));
    }
    UpdateInterface();
    SetTool("MODELSELECT");
}
void GreenTech::ChangeRotY(float va)
{
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[i]);
        inst->SetRot(QVector3D(inst->GetRot().x(),va,inst->GetRot().z()));
    }
     UpdateInterface();
     SetTool("MODELSELECT");
}
void GreenTech::ChangeRotZ(float va)
{
    int i;
    for(i=0;i<m_ModelList->selectedItems().size();i++)
    {
        ModelInstance* inst = FindInstance(m_ModelList->selectedItems()[i]);
        inst->SetRot(QVector3D(inst->GetRot().x(),inst->GetRot().y(),va));
    }
     UpdateInterface();
     SetTool("MODELSELECT");
}

void GreenTech::ChangeModeMove()
{
    pWorldView->TopView();
    SetTool("MODELMOVE");
}
 void GreenTech::ChangeColor()
{
     QColor color = pWorldView->GetColor();

     for( int i = 0; i < GetSelectedInstances().size(); i++)
     {
         GetSelectedInstances()[i]->SetColor(color);
     }
}
void GreenTech::ChangeLayerThickness(int thickness)
{
    LayThickness = thickness;
//    processor->changeThickness(thickness);
}
void GreenTech::ChangeDelectedSupprt()
{
    SetTool("SUPPORTDELETE");
    ui->supportEdit->hide();
}
void GreenTech::ChangeManuAddSupport()
{
    SetTool("SUPPORTADD");
    ui->supportEdit->show();
}

void GreenTech::ResetSupportLight()//connected to push button will always use hardcoded values!
{
//    SupportStructure::FillRegistryDefaults(true,"LIGHT");
    pWorldView->setWeight("LIGHT");

}
void GreenTech::ResetSupportMedium()//connected to push button will always use hardcoded values!
{
//    SupportStructure::FillRegistryDefaults(true,"MEDIUM");
    pWorldView->setWeight("MEDIUM");
}
void GreenTech::ResetSupportHeavy()//connected to push button will always use hardcoded values!
{
//    SupportStructure::FillRegistryDefaults(true,"HEAVY");
    pWorldView->setWeight("HEAVY");
}

void GreenTech::AddBasePlate()
{
    if(AddBase)
    {
       SupportModeInst()->EnableBasePlate();
       AddBase = false;
    }
    else
    {
        SupportModeInst()->DisableBasePlate();
        AddBase = true;
    }
}

void GreenTech::ShowTheImage(bool show)
{
    if(show)
    {
      proxy_image->show();
      proxy_printedit->hide();
    }
    else
    {
        proxy_image->hide();
    }
}

void GreenTech::GreenTechSlice()
{
    if(modelPath=="")
    {
        qDebug()<<"You didn't load any file";
    }
    else
    {
        char*  ch;
        QByteArray ba = modelPath.toLatin1();
        ch=ba.data();
        qDebug()<<modelPath;
        char* target = "D:/BaiduYunDownload/Pudding-for-display/fuck.gcode";
        Enable_User_Waiting_Cursor();
        processor->setTargetFile(target);
        processor->processFile(ch);
        processor->finalize();
        Disable_User_Waiting_Cursor();
    }
//     modelPath
//             processor->processFile( modelPath);
//    m_simpleModel = SaveToSliceModel(matri);
//    //slice
//    Enable_User_Waiting_Cursor();
//    qDebug()<<"Slicing...";
//    processor->processFile(m_simpleModel);
//    Disable_User_Waiting_Cursor();
//    SliceDataStorage *storage_temp = &(processor->storage);
//    storage = storage_temp;
//    emit Sig_StorageToImage(storage_temp);
}

void GreenTech::ReceiveSliderValue(int la)
{
    SliderValue = la;
}
void GreenTech::ShowPrintEdit()
{
    proxy_printedit->show();
}

void GreenTech::UpdateGreentech_bounding(QVector3D ma,QVector3D mi)
{
//    if(maxB.x()<ma.x())
//        maxB.setX(ma.x());
//    if(maxB.y()<ma.y())
//        maxB.setY(ma.y());
//    if(maxB.z()<ma.z())
//        maxB.setZ(ma.z());

//    if(minB.x()>mi.x())
//        minB.setX(mi.x());
//    if(minB.y()>mi.y())
//        minB.setY(mi.y());
//    if(minB.z()>mi.z())
//        minB.setZ(mi.z());
}
void GreenTech::ChangZ(QVector3D te)
{
    ModelInstance* pp;
    pp = GetSelectedInstances()[0];
    pp->SetSupport_Z(te.z());
    pp->Move(te);
}
void GreenTech::RemoveAllSupport()
{
    ModelInstance * tp = SupportModeInst();
    tp->RemoveAllSupports();
//    SetTool("SUPPORTDELETE");
//    unsigned int s;
//    if((!SupportModeInst())||(tp->GetSupportList().size()==0))
//        return;

//    for(s = 0; s < tp->GetSupportList().size(); s++)
//    {
//        tp->RemoveSupport(tp->GetSupportList()[s]);
//    }
    UpdateInterface();

}
