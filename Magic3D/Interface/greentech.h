/*******************************************************************************
*                                                                              *
* Author    :  Peng Chen                                                       *
* Version   :  0.0.1                                                           *
* Date      :  12 July 2014                                                    *
* Website   :  http://www.3green-tech.com                                      *
* Copyright :  3green-tech 2010-2014                                           *
*                                                                              *
* Attributions:                                                                *
* This class was the Mainwindows,which include the QGraphicsCiew,and include   *
* the modeledit,supportedit,and printedit interface.All the big data struct    *
* are be used in this class                                                                             *
*******************************************************************************/
#ifndef GREENTECH_H
#define GREENTECH_H

#include <QMainWindow>
#include <QtGui>
#include "worldview.h"
#include "mainbutton.h"
#include "modeledit.h"
#include "printedit.h"
#include "../SupportEngine/supportstructure.h"
#include "./SliceEngine/modelFile/modelFile.h"
#include "./SliceEngine/fffProcessor.h"
#include "./SliceEngine/sliceDataStorage.h"
#include "./SliceEngine/settings.h"
#include "imageviewwidget.h"

class LayoutProjectData;
class WorldView;
class ModelData;
class ModelInstance;
class SliceDebugger;
class SupportStructure;
class PrintEdit;

namespace Ui {
class GreenTech;
}

class GreenTech : public QMainWindow
{
    Q_OBJECT
public:
    explicit GreenTech(QWidget *parent = 0);
    ~GreenTech();
    WorldView* pWorldView;

    std::vector<ModelInstance*> GetAllInstances();
    std::vector<ModelInstance*> GetSelectedInstances();
    std::vector<ModelData*> GetAllModelData(){return ModelDataList;}
    LayoutProjectData* ProjectData(){return project;}

    //save the instance to SimpleModel which can be sliced by the SliceEngine
    SimpleModel* SaveToSliceModel(FMatrix3x3& matrix);
    SimpleModel* m_simpleModel;
    FMatrix3x3 matri;
    fffProcessor  *processor;
    SliceDataStorage  *storage;
    ConfigSettings config;
    QString modelPath;

    MainButton* main_button;
    PrintEdit* print_dialog;
    ImageViewWidget *ImageWidget;
    QGraphicsProxyWidget* proxy_mainbutton;
    QGraphicsProxyWidget* proxy_modeledit;
    QGraphicsProxyWidget* proxy_printedit;
    QGraphicsProxyWidget* proxy_image;
    QGraphicsProxyWidget* proxy_printsetup;

    int GetSliderValue(){return SliderValue;}
    int GetLayerThick(){return LayThickness;}
    void UpdateGreentech_bounding(QVector3D ma,QVector3D mi);
    QVector3D minB;
    QVector3D maxB;

signals:
    void eventHiding();
    void Sig_StorageToImage(SliceDataStorage*);

public slots:

    //slot for MainButton widget
    void ChangeToModelMode();
    void ChangeToSupportMode();
    void ChangZ(QVector3D);
    void ChangeToPrintMode();
    void ChangeColor();

    void ChangeModelScale(double scale);
    void ChangeModelSelected();
    void ChangeModelRot();
    void ChangeRotX(float);
    void ChangeRotY(float);
    void ChangeRotZ(float);

    void ChangeModeMove();
    void ChangeLayerThickness(int);

    void ChangeDelectedSupprt();
    void ChangeManuAddSupport();
    void ResetSupportLight();
    void ResetSupportMedium();
    void ResetSupportHeavy();
    void AddBasePlate();

    void ShowTheImage(bool);
    void ShowPrintEdit();
    void ReceiveSliderValue(int);
    void GreenTechSlice();

    //interface
    void BuildInterface();
    void UpdateInterface();//sets the translation interface fields acourding to what instance/instances are selected.

    //TOOLS
    void SetTool(QString toolname);//calls the functions below

    //ModelTools interface
    void SetToolModelSelect();
    void SetToolModelMove();
    void SetToolModelSpin();
    void SetToolModelOrientate();
    void SetToolModelScale();
    void SetToolPrint();

    void SetPerspective();
    void SetOrtho();

    //SupportTools interface
    void SetToolSupportModify();
    void SetToolSupportAdd();
    void SetToolSupportDelete();

    void ExitToolAction();//use to panic out of a mouse down tool action.

    //contour aid
    void OnToggleContourAid(bool tog);
    bool ContourAidEnabled();

    //model
    ModelInstance* AddModel(QString filepath = "", bool bypassVisuals = false);
    void RemoveAllInstances();
    void CleanModelData();//cleans andy modeldata that does not have a instance!
    void AddTagToModelList(QListWidgetItem* item);

    ModelInstance* FindInstance(QListWidgetItem* item);//given a item you can find the connected instance

    //selection
    void RefreshSelectionsFromList();//searches through all active listitems and selects their corresponding instance;
    void Select(ModelInstance* inst);//selects the given instance
    void DeSelect(ModelInstance* inst);//de-selects the given instance
    void SelectOnly(ModelInstance* inst);//deselects eveything and selects only the instance
    void DeSelectAll();//de-selects all instances
    void SetSelectionPos(double x, double y, double z, int axis = 0);
    void SetSelectionRot(QVector3D newRot);
    void SetSelectionScale(double x, double y, double z, int axis = 0);
    void SetSelectionFlipped(bool flipped);
    void DropSelectionToFloor();
    void ResetSelectionRotation();
    void DuplicateSelection();
    void DeleteSelection();//delete whatever is selected - support or instance..
    void DeleteSelectedInstances();

    //Support Mode
    void SetSupportMode(bool tog);//Sets everything up for editing supports for the selected instance.
                            //when either the tab is clicked or the menu item - a selected instance
                            //can be assumed
    SupportStructure* FindSupportByName(QString name);

    void SelectSupport(SupportStructure* sup);
    void SelectOnly(SupportStructure* sup);//deselects eveything and selects only the instance
    std::vector<SupportStructure*>* GetSelectedSupports();
    bool IsSupportSelected(SupportStructure* sup);
    void DeSelectSupport(SupportStructure* sup);
    void DeSelectAllSupports();
    void DeleteSelectedSupports();//called from remove button.
    void DeleteSupport(SupportStructure* pSup);
    void RemoveAllSupport();
    void MakeSelectedSupportsVertical();
    void MakeSelectedSupportsStraight();

    //returns a valid instance if we are editing it in support mode.
    ModelInstance* SupportModeInst();

    //exporting
    void PromptExportToSTL();//export the whole GreenTech to a stl file.
    int PrintExportToSTL();
    bool ExportToSTL(QString filename);



    //events
    void keyPressEvent(QKeyEvent * event );
    void keyReleaseEvent(QKeyEvent * event );
    void mouseReleaseEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);

    void getComError(QString t); //获取com口的错误

private slots:
//    void on_actionBack_View_triggered();

private:
    Ui::GreenTech *ui;
    QSlider* pXRaySlider;
    LayoutProjectData* project;

    int SliderValue;
    int LayThickness;

    bool AddBase;

    ModelEdit *m_ModelEdit;
    QListWidget *m_ModelList;
    QLineEdit *m_ModelScale;

    std::vector<ModelData*> ModelDataList;

    //support mode
    ModelInstance* currInstanceInSupportMode;
    bool oldModelConstricted;//for raising models that are too close to the ground in support mode.
    QVector3D oldPan;
    QVector3D oldRot;
    float oldZoom;
    QString oldTool;
    bool useContourAid;
    bool useXRayVision;
    float xRayPercentage;
    bool hideSupports;
    std::vector<SupportStructure*> currSelectedSupports;//what supports are currently in selection.
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent * event );
    void contextMenuEvent(QContextMenuEvent *event);

};

#endif // GREENTECH_H
