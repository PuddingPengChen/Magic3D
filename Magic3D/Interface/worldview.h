#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include <QGraphicsScene>
#include <QGLWidget>
#include "../SupportEngine/supportstructure.h"
#include <QPoint>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "greentech.h"
#include "../SliceEngine/utils/intpoint.h"

//class Slice;
class ModelInstance;
class SupportStructure;
class MainWindow;
class GreenTech;
class Triangle3D;

class WorldView : public QGraphicsScene
{
    Q_OBJECT
public:
    WorldView(QObject *parent = 0, GreenTech *lay = 0);
    ~WorldView();
    QTimer* pDrawTimer; //refreshes the 3d scene

    void drawBackground(QPainter *painter, const QRectF &rect);
    void setWeight(QString a){weight = a;}
    void setPerspective(bool a){ perspective = a;}

    bool shiftdown; //public so that the mainwindow can alter these values easy.
    bool controldown;
public slots:
   void CenterView();
   void TopView();
   void RightView();
   void FrontView();
   void BackView();
   void LeftView();
   void BottomView();
   void SetPerpective(bool persp){perspective = persp;}
   void SetRevolvePoint(QVector3D point);
   void SetPan(QVector3D pan);
   void SetZoom(double zoom);
   void setXRotation(float angle);
   void setYRotation(float angle);
   void setZRotation(float angle);

   void setLayerValue(int la){LayerValue = la;}

   void UpdatePlasmaFence();//check if any instances are out of the build area and show fence.
   void UpdateVisSlice();
   void UpdateTick();//called every 1/60th of a second by update timer. also refreshes the openGL Screen
   void SetTool(QString tool);
   QString GetTool();
   void ExitToolAction();//stops the using of tool while the mouse is moving.

   //Autosupport
   void AutoSupport();

public://GETS

   QVector3D GetPan();
   float GetZoom();
   QColor GetColor();
   QVector3D GetRotation();

public:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   void wheelEvent(QGraphicsSceneWheelEvent *event);
   void keyPressEvent(QKeyEvent * event );
   void keyReleaseEvent(QKeyEvent * event );

   //tools code
   void OnToolInitialAction(QString tool, QGraphicsSceneMouseEvent* event);
   void OnToolDragAction(QString tool, QGraphicsSceneMouseEvent* event);
   void OnToolReleaseAction(QString tool, QGraphicsSceneMouseEvent* event);
   void OnToolHoverMove(QString tool, QGraphicsSceneMouseEvent* event);
   QString toolStringMemory;
   QString toolStringMemory2;
   QVector3D toolVectorMemory1;
   QVector3D toolVectorMemory2;
   QVector3D toolVectorOffsetMemory;
   double toolDoubleMemory1;
   double toolDoubleMemory2;
   double toolDoubleMemory3;
   SupportStructure toolSupportMemory;
   bool toolBoolMemory1;
   bool IsModelSelect(){return IsModelSelected;}
   void SetModelSelected(bool te){IsModelSelected = te;}


   bool AutoSupportFlag;



signals:
   void xRotationChanged(int angle);
   void yRotationChanged(int angle);
   void zRotationChanged(int angle);
   void Sig_modelSelected(bool);

private://functions
   void initializeGL();
   void paintGL();
   void resizeGL(int width, int height);

   void ResetCamera(bool xrayon = false);
   void DrawLayerLine(int layervalue);
   void DrawMisc();//draw stuff...
   void DrawInstances(); //draws all instances!
   void DrawVisualSlice();//draws the visual slice indicator.
   void DrawBuildArea();//draws the bounds of the build area.
   void DrawPlan();


   ModelInstance* SelectInstanceByScreen(QPointF pos);// quarrys the screen for an object at the pos,
   SupportStructure* GetSupportByScreen(QPointF pos);// returns pointer to object.
   QString GetSupportSectionByScreen(QPointF pos, SupportStructure* sup);

   void Update3DCursor(QPointF pos);
   void Update3DCursor(QPointF pos, ModelInstance *trackInst);
   void Update3DCursor(QPointF pos, ModelInstance *trackInst, bool &isAgainstInst);
   QVector3D Get3DCursorOnScreen(QPointF pos, QVector3D hintPos, double standoff);

   unsigned int GetPickTriangleIndx(ModelInstance *inst, QPointF pos, bool &success);//returns the triangle of any model that the user clicks on. success is returned.
   QVector3D GetPickOnTriangle(QPointF pos, ModelInstance *inst, unsigned int triIndx);
   QVector3D GetDrillingHit(QVector3D localBeginPosition, ModelInstance *inst, bool &hitground, Triangle3D *&pTri);
   void UpdateSelectedBounds();

private: //members
   //viewing vars
   float xRot;
   float yRot;
   float zRot;
   float xRotTarget;//target values for smooth transitions.
   float yRotTarget;
   float zRotTarget;

   //Auto support

   std::vector<unsigned int> AutoSupportIndex;
   std::vector<unsigned int> FinalAutoSupportPointIndex;
   std::vector<Point3> FinalSupportPoint;
   std::vector<QVector3D>SimpleSupportPoint;

    int LayerValue;

   float camdist;
   float camdistTarget;

   QString currViewAngle;//"FREE", "TOP", "FRONT", etc
   QString weight;

   bool perspective;
   bool hideNonActiveSupports;
   bool IsModelSelected;

   QVector3D pan;                      //托盘
   QVector3D panTarget;
   QVector3D revolvePoint;
   QVector3D revolvePointTarget;

   float deltaTime;//frame rate and delta time vars
   float lastFrameTime;


   QVector3D cursorPos3D;//true global position of cursor
   QVector3D cursorNormal3D;//法向量
   QVector2D cursorPosOnTrackCanvas;//similar to pixel cords, but in real units in world.
   QVector3D cursorPreDragPos3D;
   QVector3D cursorPostDragPos3D;//TODO not yet implemented
   QVector3D PreDragInstanceOffset;
   QVector3D PreDragRotationOffsetData;//not really a cordinate just info.

   //tools/keys
   QString currtool;
   bool pandown;
   bool dragdown;

   //visual build size only - use project settings as actual size 并不是真正的尺寸
   float buildsizex;
   float buildsizey;
   float buildsizez;

   //visual fence stuff
   bool fencesOn[5];
   float fenceAlpha;
   float supportAlpha;

   //mouse cords 鼠标的坐标
   QVector2D mouseDeltaPos;
   QVector2D layerLinePos;
   QPointF mouseDownInitialPos;
   QPointF mouseLastPos;

   GreenTech* pMain;
    
};

#endif // WORLDVIEW_H
