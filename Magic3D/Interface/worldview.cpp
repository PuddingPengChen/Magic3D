#include <QtGui>
#include <QtOpenGL>
#include <QTime>
#include <QMessageBox>
#include <QColorDialog>

#include "OS_GL.h"
#include "math.h"
#include "worldview.h"
#include "../ModelData/layoutprojectdata.h"
#include "../ModelData/modelinstance.h"
#include "../SupportEngine/supportstructure.h"
#include "../geometric.h"
#include <qgl.h>
#include <QDebug>
#include <QGLWidget>
#include "../SliceEngine/utils/intpoint.h"

#ifndef  GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

#define MELD_DIST_SUPP MM2INT(15)

WorldView::WorldView(QObject *parent,GreenTech* main) :
    QGraphicsScene(parent)
{
    pMain = main;

    LayerValue = -1;
    xRot = 315.0;
    yRot = 0.0;
    zRot = 45.0;

    xRotTarget = 270.0;
    yRotTarget = 0.0;
    zRotTarget = 330;

    currViewAngle = "FREE";
    weight = "LIGHT";
    AutoSupportFlag = false;

    camdist = 350;
    camdistTarget = 350;

    deltaTime = 0.0;//milliseconds per frame.
    lastFrameTime = QTime::currentTime().msec();    //Returns the millisecond part (0 to 999) of the time.

    pan = QVector3D(0,0,0);//set pan to center of build area.
    panTarget = QVector3D(0,50,0);

    revolvePoint = QVector3D(0,0,0);

    cursorPos3D = QVector3D(0,0,0);
    cursorNormal3D = QVector3D(0,0,0);
    cursorPreDragPos3D = QVector3D(0,0,0);
    cursorPostDragPos3D = QVector3D(0,0,0);

    perspective = true;             //透视视角
    hideNonActiveSupports = false;

    //tools/keys
    currtool = "move";
    shiftdown = false;
    controldown = false;
    dragdown = false;
    IsModelSelected = false;
    pandown = 0;

    buildsizex = pMain->ProjectData()->GetBuildSpace().x();
    buildsizey = pMain->ProjectData()->GetBuildSpace().y();
    buildsizez = pMain->ProjectData()->GetBuildSpace().z();
    buildsizez = 100;

    //visual fence
    fencesOn[0] = false;
    fencesOn[1] = false;
    fencesOn[2] = false;
    fencesOn[3] = false;

    pDrawTimer = new QTimer();
    connect(pDrawTimer, SIGNAL(timeout()), this, SLOT(UpdateTick()));
    pDrawTimer->start(16.66);//aim for 60fps.

}

WorldView::~WorldView()
{
    delete pDrawTimer;
}

static void qNormalizeAngle(float &angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
}

///////////////////////////////////////
//Public Slots
///////////////////////////////////////
void WorldView::setXRotation(float angle)
{
    qNormalizeAngle(angle);

    if(angle < 180)
    {
        return;
    }

    if (angle != xRotTarget)
    {
        xRotTarget = angle;
        emit xRotationChanged(angle);
    }
}
QColor WorldView::GetColor()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
    {
       qDebug()<<"Get color success!";
       return color;
    }
    else
        qDebug()<<"Color invaliad";
}
void WorldView::setYRotation(float angle)
{
    //qNormalizeAngle(angle);
    if (angle != yRotTarget)
    {
        yRotTarget = angle;
        emit yRotationChanged(angle);
    }
}
void WorldView::setZRotation(float angle)
{
    //qNormalizeAngle(angle);
    if (angle != zRotTarget) {
        zRotTarget = angle;
        emit zRotationChanged(angle);
    }
}
void WorldView::CenterView()
{
    panTarget = QVector3D(0,pMain->ProjectData()->GetBuildSpace().z()/2.0,0);//set pan to center of build area.
    camdistTarget = 250;
}

void WorldView::TopView()
{
    qNormalizeAngle(xRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(zRot);
    xRotTarget = 360;
    zRotTarget = 0.1f;
    currViewAngle = "TOP";
}
void WorldView::RightView()
{
    qNormalizeAngle(xRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(zRot);
    xRotTarget = 180.0 + 90;
    zRotTarget = 180 + 90.0;
    currViewAngle = "RIGHT";
}
void WorldView::FrontView()
{
    qNormalizeAngle(xRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(zRot);
    xRotTarget = 180+90;
    zRotTarget = 0.1f;
    currViewAngle = "FRONT";
}
void WorldView::BackView()
{
    qNormalizeAngle(xRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(zRot);
    xRotTarget = 180+90;
    zRotTarget = 180.0f;
    currViewAngle = "BACK";
}
void WorldView::LeftView()
{
    qNormalizeAngle(xRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(zRot);
    xRotTarget = 180+90;
    zRotTarget = 180.0 - 90;
    currViewAngle = "LEFT";
}
void WorldView::BottomView()
{
    qNormalizeAngle(xRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(zRot);
    xRotTarget = 180;
    zRotTarget = 0.1f;
    currViewAngle = "BOTTOM";
}

void WorldView::SetRevolvePoint(QVector3D point)
{
    revolvePointTarget = point;
}
void WorldView::SetPan(QVector3D pan)
{
    panTarget = pan;
}
void WorldView::SetZoom(double zoom)
{
    camdistTarget = zoom;
}

//called by timer - draws the world and updates cool visual transitions
//no serious updating should happen here
void WorldView::UpdateTick()
{
    float dt = QTime::currentTime().msec() - lastFrameTime;
    bool anyFenceOn;

    if(dt > 0) deltaTime = dt;

    lastFrameTime = QTime::currentTime().msec();
    //float timeScaleFactor = deltaTime/33.333;


    buildsizex += ((pMain->ProjectData()->GetBuildSpace().x() - buildsizex)/2);
    buildsizey += ((pMain->ProjectData()->GetBuildSpace().y() - buildsizey)/2);
    buildsizez += ((pMain->ProjectData()->GetBuildSpace().z() - buildsizez)/2);

    anyFenceOn = (fencesOn[0] || fencesOn[1] || fencesOn[2] || fencesOn[3]);
    if(anyFenceOn)
        fenceAlpha += 0.01f;
    else
        fenceAlpha = 0;

    if(fenceAlpha >= 0.3)
        fenceAlpha = 0.3f;

    if(xRot < 200 && xRot >= 180)
    {
        supportAlpha = ((xRot-180)/20.0);
        if(supportAlpha < 0.1)
            supportAlpha = 0.1f;
    }
    else
        supportAlpha = 1.0;

    UpdatePlasmaFence();


    //always normalize all angles to 0-360
    //qNormalizeAngle(xRotTarget);
    qNormalizeAngle(yRotTarget);
    qNormalizeAngle(zRotTarget);
    qNormalizeAngle(xRot);
    qNormalizeAngle(yRot);
    qNormalizeAngle(zRot);


    if((zRotTarget - zRot) < -180)
        zRotTarget = zRotTarget + 360;

    if((zRot - zRotTarget) < -180)
        zRot = zRot + 360;

    xRot = xRot + ((xRotTarget - xRot)/5.0);
    yRot = yRot + ((yRotTarget - yRot)/5.0);
    zRot = zRot + ((zRotTarget - zRot)/5.0);


    camdist = camdist + (camdistTarget - camdist)/5.0;

    pan = pan + (panTarget - pan)/2.0;

    revolvePoint = revolvePoint + (revolvePointTarget - revolvePoint)/2.0;


    //update visiual slice
//    QTimer::singleShot(0,this,SLOT(UpdateVisSlice()));
    update();

//    glDraw();//actual draw (and flip buffers internally)
}
void WorldView::SetTool(QString tool)
{
    currtool = tool;
}
QString WorldView::GetTool()
{
     return currtool;
}

void WorldView::ExitToolAction()
{
    dragdown = false;
    shiftdown = false;
    controldown = false;
}


////////////////////////////////////////////////////////
//Public Gets
//////////////////////////////////////////////////////////////


QVector3D WorldView::GetPan()
{
    return panTarget;
}

float WorldView::GetZoom()
{
    return camdistTarget;
}
QVector3D WorldView::GetRotation()
{
    return QVector3D(xRotTarget,yRotTarget,zRotTarget);
}

//Private
void WorldView::initializeGL()
{

//    qglClearColor(QColor(0,100,100));
 //   glClearColor(0, 0.39063, 0.39063, 1);
     glClearColor(0.9531, 0.9531, 0.9531, 1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);
    glLineWidth(0.5);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);

    glEnable (GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


//    glDisable(GL_MULTISAMPLE);
    glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}
void WorldView::DrawLayerLine(int layers_n)
{
    SliceDataStorage*storage = pMain->storage;

//
    float x,y,z;
    ModelInstance* inst = pMain->GetAllInstances()[0];
    float x_pos = inst->GetPos().x();
    float y_pos = inst->GetPos().y();
    glPushMatrix();
    glTranslatef(x_pos, y_pos,0);
        for(unsigned int volumeIdx=0; volumeIdx<storage->volumes.size(); volumeIdx++)
        {
//            qDebug()<<tr("x= %1,y= %2").arg(x_pos).arg(y_pos);
                SliceLayer* layer = &storage->volumes[volumeIdx].layers[layers_n];
                for(unsigned int i=0;i<layer->parts.size();i++)
                {
//                  glTranslatef(0,0,0);
                    SliceLayerPart* part = &layer->parts[i];
                    for(unsigned int j=0;j<part->outline.size();j++)
                    {
                        glLineWidth (1);
                        if(j==0)
                        glColor3f(0.99,0.175,0.175);
                        else
                          glColor3f(0,1,0);
                        glBegin(GL_LINE_LOOP);

//                        glBegin(GL_POLYGON);
                        for(unsigned int k=0;k<part->outline[j].size();k++)
                        {

                            x=(((part->outline[j][k].X)-(storage->modelMin.x+(storage->modelMax.x-storage->modelMin.x)/2)))/1000.0;
                            z=(layer->sliceZ)/1000.0;
                            y=(((part->outline[j][k].Y)-(storage->modelMin.y+(storage->modelMax.y-storage->modelMin.y)/2)))/1000.0;
//                            x=(((part->outline[j][k].X)-(storage->modelMin.x)))/1000.0-x_pos;
//                            z=(layer->sliceZ)/1000.0;
//                            y=(((part->outline[j][k].Y)-(storage->modelMin.y)))/1000.0-y_pos;
                            glVertex3f((x),y,(z));
                        }

                        glEnd();

                    }

                }
        }
         glPopMatrix();
}

void WorldView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ResetCamera(false);
    DrawMisc();
    DrawInstances();
    LayerValue = pMain->GetSliderValue();
    if(LayerValue!=-1)
    {
        DrawLayerLine(LayerValue);
    }
    //draw slices
    //  DrawVisualSlice();
    if(currtool != "SUPPORTADD")
    {
        if(currtool != "SUPPORTDELETE")
         DrawBuildArea();
    }

}

void WorldView::resizeGL(int width, int height)
{
     glViewport(0,0,width,height);
}
void WorldView::ResetCamera(bool xrayon) 
{
    double nearClip;
    //perpective/ortho/xray stuff!
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();//restores default matrix.
    if(perspective)
    {
            nearClip = 1;
        gluPerspective(30,double(width())/height(),nearClip,5500);
    }
    else
    {
        float aspRatio = float(this->width())/this->height();
            nearClip = 0.1;

        glOrtho(-(camdist/120.0)*aspRatio*102.4/2,
                (camdist/120.0)*aspRatio*102.4/2,
                -(camdist/120.0)*102.4/2,
                (camdist/120.0)*102.4/2,
                nearClip,
                5500);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    static GLfloat lightPosition0[4] = { 0.0, 0.0, 100.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);


    if(perspective)
        glTranslatef(0.0, 0.0, -camdist);//step back amount
    else
        glTranslatef(0.0, 0.0, -200.0);//step back amount

    glTranslatef(pan.x(),-pan.y(),0);

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    glTranslatef(-revolvePoint.x(),-revolvePoint.y(),-revolvePoint.z());


}

void WorldView::DrawMisc()
{
    //show the  position
    if(currtool == "SUPPORTADD")
    {
        glDisable(GL_LIGHTING);
        glPushMatrix();
        if(cursorNormal3D.z() <= 0)
        glColor3f(1.0f,1.0f,0.0f);
        else
        glColor3f(1.0f,0.0f,0.0f);
            glBegin(GL_LINES);
                glVertex3f( cursorPos3D.x(), cursorPos3D.y(), cursorPos3D.z());
                glVertex3f( cursorPos3D.x() + cursorNormal3D.x(), cursorPos3D.y() + cursorNormal3D.y(), cursorPos3D.z() + cursorNormal3D.z());
            glEnd();
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
}


void WorldView::DrawInstances()
{
    unsigned int i;
    ModelInstance* pInst;

    glEnable(GL_DEPTH_TEST);

    //if were in support mode we want to only render
    //the support mode instance
    if(pMain->SupportModeInst() != NULL)
    {
        glColor3f(0.3f,0.3f,0.3f);
        glDisable(GL_CULL_FACE);
        glDisable(GL_MULTISAMPLE);
        pMain->SupportModeInst()->RenderGL(true);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_CULL_FACE);

        glEnable(GL_BLEND);
        glPushAttrib(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);

        pMain->SupportModeInst()->RenderSupportsGL(false,1.0,supportAlpha);

        glEnable(GL_CULL_FACE);
        glPopAttrib();
        glDisable(GL_BLEND);
    }
    else
    {
        if(LayerValue != -1)
        {
            double ll = (pMain->GetLayerThick())/1000.0;
            GLdouble eqn[4]={0.0,0.0,-1.0,(LayerValue)*ll};
            glClipPlane(GL_CLIP_PLANE0,eqn);
            glEnable(GL_CLIP_PLANE0);
        }
        for(i = 0; i < pMain->GetAllInstances().size();i++)
        {
            pInst = pMain->GetAllInstances()[i];
            pInst->RenderGL();
            glColor3f(pInst->visualcolor.redF()*0.5,
                    pInst->visualcolor.greenF()*0.5,
                    pInst->visualcolor.blueF()*0.5);

            pInst->RenderSupportsGL(false,1.0,1.0);

        }
        glDisable(GL_CLIP_PLANE0);
    }

}

void  WorldView::DrawVisualSlice()
{

}

void WorldView::DrawBuildArea()
{
    glEnable(GL_MULTISAMPLE);
    glPushMatrix();
    glColor3f(0.43f,0.43f,0.43f);
    glTranslatef(-buildsizex/2, -buildsizey/2, 0);

//    qDebug()<<tr("buildsize_z= %1").arg(buildsizez);
    glDisable(GL_LIGHTING);
    float buildsize_z = 110;

    //4 vertical lines_1
     glBegin(GL_LINES);
         glVertex3d( 0, 0, 0);
         glVertex3d( 0, 0, buildsize_z);
     glEnd();
     glBegin(GL_LINES);
         glVertex3d( buildsizex, 0,0);
         glVertex3d( buildsizex, 0,buildsize_z);
     glEnd();
     glBegin(GL_LINES);
         glVertex3d( 0, buildsizey,0);
         glVertex3d( 0, buildsizey,buildsize_z);
     glEnd();
     glBegin(GL_LINES);
         glVertex3d( buildsizex, buildsizey,0);
         glVertex3d( buildsizex, buildsizey,buildsize_z);
     glEnd();

     //4 Top lines_1
     glBegin(GL_LINES);
         glVertex3d( 0, 0, buildsize_z);
         glVertex3d( buildsizex, 0, buildsize_z);
     glEnd();
     glBegin(GL_LINES);
         glVertex3d( 0, 0, buildsize_z);
         glVertex3d( 0, buildsizey, buildsize_z);
     glEnd();
     glBegin(GL_LINES);
         glVertex3d( buildsizex, buildsizey, buildsize_z);
         glVertex3d( 0, buildsizey, buildsize_z);
     glEnd();
     glBegin(GL_LINES);
         glVertex3d( buildsizex, buildsizey, buildsize_z);
         glVertex3d( buildsizex, 0, buildsize_z);
     glEnd();


       //4 vertical lines
        glBegin(GL_LINES);
            glVertex3d( 0, 0, 0);
            glVertex3d( 0, 0, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( buildsizex, 0,0);
            glVertex3d( buildsizex, 0,0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( 0, buildsizey,0);
            glVertex3d( 0, buildsizey,0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( buildsizex, buildsizey,0);
            glVertex3d( buildsizex, buildsizey,0);
        glEnd();

        //4 Top lines
        glBegin(GL_LINES);
            glVertex3d( 0, 0, 0);
            glVertex3d( buildsizex, 0, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( 0, 0, 0);
            glVertex3d( 0, buildsizey, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( buildsizex, buildsizey, 0);
            glVertex3d( 0, buildsizey,0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( buildsizex, buildsizey, 0);
            glVertex3d( buildsizex, 0, 0);
        glEnd();
        //4 Bottom lines
        glBegin(GL_LINES);
            glVertex3d( 0, 0, 0);
            glVertex3d( buildsizex, 0,0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( 0, 0, 0);
            glVertex3d( 0, buildsizey, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( buildsizex, buildsizey, 0);
            glVertex3d( 0, buildsizey, 0);
        glEnd();
        glBegin(GL_LINES);
            glVertex3d( buildsizex, buildsizey, 0);
            glVertex3d( buildsizex, 0, 0);
        glEnd();


        glColor3f(1.0f,1.0f,1.0f);
        glEnable(GL_LIGHTING);
        glEnable(GL_BLEND);

       // top rectangle
        if(fencesOn[4] && !pMain->SupportModeInst())        //below the plan and not in support mode
              glColor4f(0.714f,0.75f,0.60f,0.98f);
        else
            glColor4f(0.714f,0.75f,0.60f,1.0f);
//               glColor4f(0.320f,0.3690f,0.34f,1.0f);
        glNormal3f(0,0,1);
            glBegin(GL_TRIANGLES);
                glVertex3f( buildsizex, 0, 0);
                glVertex3f( buildsizex, buildsizey, 0);
                glVertex3f( 0, buildsizey, 0);
            glEnd();

            glBegin(GL_TRIANGLES);
                glVertex3f( buildsizex, 0, 0);
                glVertex3f( 0, buildsizey, 0);
                glVertex3f( 0, 0, 0);
            glEnd();

        //bottom rectangle
        if(!pMain->SupportModeInst())
        {
       //     qDebug()<<tr("buildsizeX:%1,buildsizeX:%2").arg(buildsizex).arg(buildsizey);
            glNormal3f(0,0,-1);
            if(fencesOn[4])
                glColor4f(1.0f,0.0f,0.0f,0.5f);
            else
                glColor4f(0.714f,0.75f,0.60f,0.3);
//                glColor4f(0.0f,0.0f,1.0f,0.3f);

                glBegin(GL_TRIANGLES);//-0.1 is to hide z-fighting
                    glVertex3f( 0, buildsizey, -0.1f);
                    glVertex3f( buildsizex, buildsizey, -0.1f);
                    glVertex3f( buildsizex, 0, -0.1f);
                glEnd();
                glBegin(GL_TRIANGLES);
                    glVertex3f( 0, 0, -0.1f);
                    glVertex3f( 0, buildsizey, -0.1f);
                    glVertex3f( buildsizex, 0, -0.1f);
                glEnd();
            glColor4f(1.0f,1.0f,1.0f,1.0f);
        }
        //draw plasma fences!
        if(!pMain->SupportModeInst())
        {
            glColor4f(fenceAlpha*2,0.0f,0.0f,fenceAlpha);
            glDisable(GL_CULL_FACE);
            glDisable(GL_LIGHTING);
            //X+ fence
            if(fencesOn[0])
            {
                glNormal3f(1,0,0);
                glBegin(GL_QUADS);
                    glVertex3f( buildsizex, 0, 0);
                    glVertex3f( buildsizex, buildsizey, 0);
                    glVertex3f( buildsizex, buildsizey, buildsizez);
                    glVertex3f( buildsizex, 0, buildsizez);
                glEnd();
            }
            //X- fence
            if(fencesOn[1])
            {
                glNormal3f(1,0,0);
                glBegin(GL_QUADS);
                    glVertex3f( 0, 0, 0);
                    glVertex3f( 0, buildsizey, 0);
                    glVertex3f( 0, buildsizey, buildsizez);
                    glVertex3f( 0, 0, buildsizez);
                glEnd();
            }
            //Y+
            if(fencesOn[2])
            {
                glNormal3f(1,0,0);
                glBegin(GL_QUADS);
                    glVertex3f( 0, buildsizey, 0);
                    glVertex3f( buildsizex, buildsizey, 0);
                    glVertex3f( buildsizex, buildsizey, buildsizez);
                    glVertex3f( 0, buildsizey, buildsizez);
                glEnd();
            }
            //Y-
            if(fencesOn[3])
            {
                glNormal3f(1,0,0);
                glBegin(GL_QUADS);
                    glVertex3f( 0, 0, 0);
                    glVertex3f( buildsizex, 0, 0);
                    glVertex3f( buildsizex, 0, buildsizez);
                    glVertex3f( 0, 0, buildsizez);
                glEnd();
            }

            glEnable(GL_LIGHTING);
            glEnable(GL_DEPTH_TEST);
        }

        glDisable(GL_BLEND);
    glPopMatrix();
 }
 void WorldView::UpdateSelectedBounds()
 {
     unsigned int i;
     pMain->setCursor(Qt::WaitCursor);

     for(i=0;i<pMain->GetSelectedInstances().size();i++)
     {
         pMain->GetSelectedInstances()[i]->UpdateBounds();
     }
     pMain->setCursor(Qt::ArrowCursor);
 }

 //checks all instances against fences.
 void WorldView::UpdatePlasmaFence()
 {
     unsigned int i;
     ModelInstance* inst;

     fencesOn[0] = false;
     fencesOn[1] = false;
     fencesOn[2] = false;
     fencesOn[3] = false;
     fencesOn[4] = false;

     for(i = 0; i < pMain->GetAllInstances().size(); i++)
     {
         inst = pMain->GetAllInstances()[i];
         if(inst->GetMaxBound().x() > pMain->ProjectData()->GetBuildSpace().x()*0.5)
             fencesOn[0] = true;
         if(inst->GetMinBound().x() < -pMain->ProjectData()->GetBuildSpace().x()*0.5)
             fencesOn[1] = true;
         if(inst->GetMaxBound().y() > pMain->ProjectData()->GetBuildSpace().y()*0.5)
             fencesOn[2] = true;
         if(inst->GetMinBound().y() < -pMain->ProjectData()->GetBuildSpace().y()*0.5)
             fencesOn[3] = true;
         //Below Build Table
         if(inst->GetMinBound().z() < -0.01)
             fencesOn[4] = true;
     }
}

 //Mouse Interaction
void WorldView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     mouseLastPos = event->scenePos();
     mouseDownInitialPos = event->scenePos();


//     if(this->itemAt(QPointF(mouseLastPos.x(),mouseLastPos.y())))
//     {
//        event->accept();
//     }
//     else
     {
         if(event->button() == Qt::MiddleButton)
         {
            pandown = true;
            event->accept();
         }
         if(event->buttons()&Qt::LeftButton)
         {
             dragdown = true;
             OnToolInitialAction(currtool, event);
             event->accept();
         }
     }
     QGraphicsScene::mousePressEvent(event);
}
void WorldView::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    mouseLastPos = event->scenePos();
     const QPointF delta = event->scenePos() - event->lastScenePos();
     mouseDeltaPos.setX(delta.x());
     mouseDeltaPos.setY(delta.y());
    if((event->buttons() & Qt::RightButton) && !shiftdown)
    {
        setXRotation(xRotTarget + 0.5 * mouseDeltaPos.y());
        setZRotation(zRotTarget + 0.5 * mouseDeltaPos.x());
        //were rotating the view so switch view mode!
        currViewAngle = "FREE";
    }

    if(pandown ||(event->buttons() & Qt::RightButton && shiftdown))
    {
        panTarget += QVector3D(mouseDeltaPos.x()/5.0,mouseDeltaPos.y()/5.0,0);
        event->accept();
    }

    if(dragdown && (event->buttons() & Qt::LeftButton))
    {
        OnToolDragAction(currtool,event);
        event->accept();
    }

//    if((!dragdown) && (!pandown) && (!shiftdown)
//            &&( !(event->buttons() & Qt::LeftButton)) &&( !(event->buttons() & Qt::RightButton)))
//    {

           OnToolHoverMove(currtool,event);
//           event->accept();
//    }
    QGraphicsScene::mouseMoveEvent(event);

}
void WorldView::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        pandown = false;
        event->accept();
    }
    if(event->buttons()&Qt::LeftButton)
    {
        dragdown = false;
        OnToolReleaseAction(currtool, event);
        event->accept();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}


void WorldView::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    camdistTarget -= event->delta()/8.0;
    //zooming limits
    if(perspective)
    {
        if(camdistTarget <= 10.0)
        {
            camdistTarget = 10.0;
        }
        if(camdistTarget >= 350.00)
            camdistTarget = 350.00;
    }
    else
    {
        if(camdistTarget <= 5.0)
        {
            camdistTarget = 5.0;
        }
        if(camdistTarget >= 350.00)
            camdistTarget = 350.00;
    }
    QGraphicsScene::wheelEvent(event);
}

 //Keyboard interaction
void WorldView::keyPressEvent( QKeyEvent * event )
{ 
    if(event->key() == Qt::Key_Shift)
    {
        shiftdown = true;
    }
    if(event->key() == Qt::Key_Control)
    {
        controldown = true;
    }
     QGraphicsScene::keyPressEvent(event);
}
void WorldView::keyReleaseEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Shift)
    {
        shiftdown = false;
    }
    if(event->key() == Qt::Key_Control)
    {
        controldown = false;
    }
     QGraphicsScene::keyReleaseEvent(event);
}

void WorldView::AutoSupport()
{
    Triangle3D* pTempTri = NULL;
    Triangle3D* pBottomTri = NULL;
    SupportStructure* AutoAddedSupport;
    std::map<uint32_t, std::vector<uint32_t> > indexMap_s;
    bool hitGround;
    AutoSupportFlag = true;
    if((currtool == "SUPPORTADD")||currtool == "SUPPORTDELETE")
    {
        //first pick out all the faces that could be supported
        for(unsigned int m=0;m< pMain->SupportModeInst()->triList.size();m++)
        {
            pTempTri = pMain->SupportModeInst()->triList[m];
            if(pTempTri->normal.z()<=(-0.5))
            {
               AutoSupportIndex.push_back(m);
               double xs = ((pTempTri->vertex[0].x()+ pTempTri->vertex[1].x()+pTempTri->vertex[2].x()))/3;
               double ys = ((pTempTri->vertex[0].y()+ pTempTri->vertex[1].y()+pTempTri->vertex[2].y()))/3;
               double zs = ((pTempTri->vertex[0].z()+ pTempTri->vertex[1].z()+pTempTri->vertex[2].z()))/3;
               SimpleSupportPoint.push_back(QVector3D(xs,ys,zs));
            }
        }
        qDebug()<<tr("AutoSupportIndex.size = %1").arg(AutoSupportIndex.size());
        FinalSupportPoint.reserve(AutoSupportIndex.size());
        for(unsigned int k = 0; k < AutoSupportIndex.size();k++)
        {
            pTempTri = pMain->SupportModeInst()->triList[AutoSupportIndex[k]];
            int x = (1000*(pTempTri->vertex[0].x()+ pTempTri->vertex[1].x()+pTempTri->vertex[2].x()))/3;
            int y = (1000*(pTempTri->vertex[0].y()+ pTempTri->vertex[1].y()+pTempTri->vertex[2].y()))/3;
            int z = (1000*(pTempTri->vertex[0].z()+ pTempTri->vertex[1].z()+pTempTri->vertex[2].z()))/3;
            Point3 p = Point3(x,y,z);
            bool add = true;
            int hash = ((p.x + MELD_DIST_SUPP/2) / MELD_DIST_SUPP) ^ (((p.y + MELD_DIST_SUPP/2) / MELD_DIST_SUPP) << 10) ^ (((p.z + MELD_DIST_SUPP/2) / MELD_DIST_SUPP) << 20);
            for(unsigned int n = 0; n < indexMap_s[hash].size(); n++)
            {
                if ((FinalSupportPoint[indexMap_s[hash][n]] - p).testLength(MELD_DIST_SUPP))
                {
                    add = false;
                    break;
                }
            }
            if (add)
            {
                indexMap_s[hash].push_back(FinalSupportPoint.size());
                FinalSupportPoint.push_back(p);
                FinalAutoSupportPointIndex.push_back(AutoSupportIndex[k]);
            }
        }
        for(unsigned int j=0;j<FinalAutoSupportPointIndex.size();j++)
        {
            qDebug()<<tr("now is adding the %1 support").arg(j);
            pTempTri = pMain->SupportModeInst()->triList[FinalAutoSupportPointIndex[j]];
            double x = (pTempTri->vertex[0].x()+ pTempTri->vertex[1].x()+pTempTri->vertex[2].x())/3;
            double y = (pTempTri->vertex[0].y()+ pTempTri->vertex[1].y()+pTempTri->vertex[2].y())/3;
            double z = (pTempTri->vertex[0].z()+ pTempTri->vertex[1].z()+pTempTri->vertex[2].z())/3;
            QVector3D AutoTopPos = QVector3D(x,y,z);
            AutoTopPos = AutoTopPos - pMain->SupportModeInst()->GetPos();
            AutoAddedSupport = pMain->SupportModeInst()->AddSupport(QVector3D(),QVector3D());
            AutoAddedSupport->SetTopPoint(AutoTopPos);
            AutoAddedSupport->SetTopNormal(pTempTri->normal*-1.0);
            QVector3D basePos = GetDrillingHit(AutoAddedSupport->GetTopPivot(),pMain->SupportModeInst(), hitGround, pBottomTri);
            if(hitGround)
            {
                AutoAddedSupport->SetIsGrounded(true);
                AutoAddedSupport->SetVisible(false);
            }
            else
            {
//                AutoAddedSupport->SetBottomPoint(basePos);
//                AutoAddedSupport->SetBottomNormal(pBottomTri->normal*-1.0);
//                AutoAddedSupport->SetIsGrounded(false);
                pMain->DeleteSupport(AutoAddedSupport);
            }

            QSettings appSettings;
            appSettings.beginGroup("USERSUPPORTPARAMS");
            appSettings.beginGroup("SUPPORT_TOP");
                AutoAddedSupport->SetTopAttachShape(appSettings.value("ATTACHSHAPE",AutoAddedSupport->GetTopAttachShape()).toString());
                AutoAddedSupport->SetTopLength(appSettings.value("LENGTH",AutoAddedSupport->GetTopLength()).toDouble());
                AutoAddedSupport->SetTopPenetration(appSettings.value("PENETRATION",AutoAddedSupport->GetTopPenetration()).toDouble());
                AutoAddedSupport->SetTopRadius(appSettings.value("RADIUS",AutoAddedSupport->GetTopRadius()).toDouble());
                AutoAddedSupport->SetTopAngleFactor(appSettings.value("ANGLEFACTOR",AutoAddedSupport->GetTopAngleFactor()).toDouble());
            appSettings.endGroup();
            appSettings.beginGroup("SUPPORT_MID");
                AutoAddedSupport->SetMidAttachShape(appSettings.value("ATTACHSHAPE",AutoAddedSupport->GetMidAttachShape()).toString());
                AutoAddedSupport->SetMidRadius(appSettings.value("RADIUS",AutoAddedSupport->GetMidRadius()).toDouble());
                qDebug()<<tr("MidRadius = %1").arg(AutoAddedSupport->GetMidRadius());
                //addedSupport->GetMidRadius();
            appSettings.endGroup();
            if(AutoAddedSupport->GetIsGrounded())
            {
                appSettings.beginGroup("SUPPORT_BOTTOM_GROUNDED");
                AutoAddedSupport->SetBottomAttachShape(appSettings.value("ATTACHSHAPE",AutoAddedSupport->GetBottomAttachShape()).toString());
                AutoAddedSupport->SetBottomLength(appSettings.value("LENGTH",AutoAddedSupport->GetBottomLength()).toDouble());
                AutoAddedSupport->SetBottomPenetration(appSettings.value("PENETRATION",AutoAddedSupport->GetBottomPenetration()).toDouble());
                AutoAddedSupport->SetBottomRadius(appSettings.value("RADIUS",AutoAddedSupport->GetBottomRadius()).toDouble());
                AutoAddedSupport->SetBottomAngleFactor(appSettings.value("ANGLEFACTOR",AutoAddedSupport->GetBottomAngleFactor()).toDouble());
                appSettings.endGroup();
                AutoAddedSupport->SetBottomPoint(AutoAddedSupport->GetTopPivot());
            }
            else
            {
                appSettings.beginGroup("SUPPORT_BOTTOM_NONGROUNDED");
                    AutoAddedSupport->SetBottomAttachShape(appSettings.value("ATTACHSHAPE",AutoAddedSupport->GetTopAttachShape()).toString());
                    AutoAddedSupport->SetBottomLength(appSettings.value("LENGTH",AutoAddedSupport->GetTopLength()).toDouble());
                    AutoAddedSupport->SetBottomPenetration(appSettings.value("PENETRATION",AutoAddedSupport->GetTopPenetration()).toDouble());
                    AutoAddedSupport->SetBottomRadius(appSettings.value("RADIUS",AutoAddedSupport->GetTopRadius()).toDouble());
                    AutoAddedSupport->SetBottomAngleFactor(appSettings.value("ANGLEFACTOR",AutoAddedSupport->GetTopAngleFactor()).toDouble());
                appSettings.endGroup();
                //new support grounded on instance take que from for radius......
                appSettings.beginGroup("SUPPORT_TOP");
                AutoAddedSupport->SetBottomRadius(appSettings.value("RADIUS",AutoAddedSupport->GetBottomRadius()).toDouble());
                appSettings.endGroup();
            }
            appSettings.endGroup();

        }
    }

}

void WorldView::OnToolInitialAction(QString tool, QGraphicsSceneMouseEvent* event)
{
    ModelInstance* clickedInst = NULL;
    Triangle3D* pTopTri = NULL;
    Triangle3D* pBottomTri = NULL;
    SupportStructure* addedSupport;
    SupportStructure* pSup;
    bool hitGround;
    glDisable(GL_MULTISAMPLE);
    if(currtool == "MODELSELECT" ||
            currtool == "MODELMOVE" ||
            currtool == "MODELSCALE" ||
            currtool == "MODELORIENTATE")
    {
        Update3DCursor(event->scenePos());

        pMain->DeSelectAll();
        clickedInst = SelectInstanceByScreen(event->scenePos());
        IsModelSelected = false;
        if(clickedInst)
        {
            IsModelSelected = true;
            PreDragInstanceOffset = cursorPos3D - clickedInst->GetPos();
            float theta = qAtan2((cursorPos3D.y() - clickedInst->GetPos().y())
                               ,
                               (cursorPos3D.x() - clickedInst->GetPos().x()));

            theta = theta*(180/M_PI);

            PreDragRotationOffsetData.setX(theta);
            PreDragRotationOffsetData.setY(clickedInst->GetRot().z());
        }
        emit Sig_modelSelected(IsModelSelected);
    }

    if(currtool == "SUPPORTADD")//after the user clicked the add support button.
    {
        bool s;
        unsigned int tri;

        if(!pMain->SupportModeInst())
            return;

        tri = GetPickTriangleIndx(pMain->SupportModeInst(),event->scenePos(),s);

        if(s)
        {
            QVector3D topPos = GetPickOnTriangle(event->scenePos(),pMain->SupportModeInst(),tri);
            pTopTri = pMain->SupportModeInst()->triList[tri];
            if(pTopTri->normal.z() <= 0)
            {
                addedSupport = pMain->SupportModeInst()->AddSupport(QVector3D(),QVector3D());
              //  pMain->FillSupportList();

                addedSupport->SetTopPoint(topPos);
//                qDebug()<<tr("topPos ,x=%1,y=%2,z=%3").arg( topPos.x()).arg( topPos.y()).arg(topPos.z());
                addedSupport->SetTopNormal(pTopTri->normal*-1.0);

                //"drill" down from the toppivot position and see where the vertical ray hits.
                QVector3D basePos = GetDrillingHit(addedSupport->GetTopPivot(),pMain->SupportModeInst(), hitGround, pBottomTri);
                if(hitGround)
                {
                    addedSupport->SetIsGrounded(true);
                }
                else
                {
                    addedSupport->SetBottomPoint(basePos);
                    addedSupport->SetBottomNormal(pBottomTri->normal*-1.0);
                    addedSupport->SetIsGrounded(false);
                }
                //now the support is created - but we want to load in the default user settings for
                //things like shape and radius
//                addedSupport->FillRegistryDefaults(true,"MEDIUM");

                float topLen;
                float topPen;
                float topRadiu;
                float topAngle;

                float midRadiu;

                float botLen;
                float botPen;
                float botAngle;
                float botRadiu;
                if(weight=="LIGHT")
                {
                    topAngle = 0.5;
                    topLen = 1.0;
                    topPen = 0.8;
                    topRadiu = 0.5;
                    midRadiu = 0.5;
                    botAngle = 1.0;
                    botLen = 1.0;
                    botPen = 0.0;
                    botRadiu = 1.5;
                }
                else if(weight == "MEDIUM")
                {
                    topAngle = 0.5;
                    topLen = 1.5;
                    topPen = 0.8;
                    topRadiu = 1.0;
                    midRadiu = 1.0;
                    botAngle = 1.0;
                    botLen = 1.0;
                    botPen = 0.0;
                    botRadiu = 1.5;
                }
                else if(weight == "HEAVY")
                {
                    topAngle = 0.2;
                    topLen = 2.3;
                    topPen = 0.8;
                    topRadiu = 2.5;
                    midRadiu = 2.5;
                    botAngle = 1.0;
                    botLen = 1.0;
                    botPen = 0.0;
                    botRadiu = 2.5;
                }
                QSettings appSettings;
                appSettings.beginGroup("USERSUPPORTPARAMS");
                    appSettings.beginGroup("SUPPORT_TOP");
                        addedSupport->SetTopAttachShape(appSettings.value("ATTACHSHAPE",addedSupport->GetTopAttachShape()).toString());
                        addedSupport->SetTopLength(appSettings.value("LENGTH",topLen).toDouble());
                        addedSupport->SetTopPenetration(appSettings.value("PENETRATION",topPen).toDouble());
                        addedSupport->SetTopRadius(appSettings.value("RADIUS",topRadiu).toDouble());
                        addedSupport->SetTopAngleFactor(appSettings.value("ANGLEFACTOR",topAngle).toDouble());
                    appSettings.endGroup();

                    appSettings.beginGroup("SUPPORT_MID");
                        addedSupport->SetMidAttachShape(appSettings.value("ATTACHSHAPE",addedSupport->GetMidAttachShape()).toString());
                        addedSupport->SetMidRadius(appSettings.value("RADIUS",midRadiu).toDouble());
                    appSettings.endGroup();
                if(addedSupport->GetIsGrounded())
                {
                    appSettings.beginGroup("SUPPORT_BOTTOM_GROUNDED");
                    addedSupport->SetBottomAttachShape(appSettings.value("ATTACHSHAPE",addedSupport->GetBottomAttachShape()).toString());
                    addedSupport->SetBottomLength(appSettings.value("LENGTH",botLen).toDouble());
                    addedSupport->SetBottomPenetration(appSettings.value("PENETRATION",botPen).toDouble());
                    addedSupport->SetBottomRadius(appSettings.value("RADIUS",botRadiu).toDouble());
                    addedSupport->SetBottomAngleFactor(appSettings.value("ANGLEFACTOR",botAngle).toDouble());
                    appSettings.endGroup();
                    addedSupport->SetBottomPoint(addedSupport->GetTopPivot());
                }
                else
                {
                    appSettings.beginGroup("SUPPORT_BOTTOM_NONGROUNDED");
                        addedSupport->SetBottomAttachShape(appSettings.value("ATTACHSHAPE",addedSupport->GetTopAttachShape()).toString());
                        addedSupport->SetBottomLength(appSettings.value("LENGTH",topLen).toDouble());
                        addedSupport->SetBottomPenetration(appSettings.value("PENETRATION",topPen).toDouble());
                        addedSupport->SetBottomRadius(appSettings.value("RADIUS",topRadiu).toDouble());
                        addedSupport->SetBottomAngleFactor(appSettings.value("ANGLEFACTOR",topAngle/2).toDouble());
                    appSettings.endGroup();
                    //new support grounded on instance take que from for radius......
                    appSettings.beginGroup("SUPPORT_TOP");
                    addedSupport->SetBottomRadius(appSettings.value("RADIUS",topRadiu).toDouble());
                    appSettings.endGroup();
                }
                appSettings.endGroup();

            }
        }
    }
    //delete selected support
    if(currtool == "SUPPORTDELETE")
    {
        pMain->DeSelectAllSupports();

        pSup = GetSupportByScreen(event->scenePos());
        if(pSup != NULL)
        {
            pMain->DeleteSupport(pSup);
        }
    }
    glEnable(GL_MULTISAMPLE);
}

void WorldView::OnToolDragAction(QString tool, QGraphicsSceneMouseEvent* event)
{
    unsigned int i;
    ModelInstance* pInst;
    SupportStructure* pSup;
    QSettings appSettings;

    if(currtool == "MODELMOVE")
    {
        layerLinePos += mouseDeltaPos;
        Update3DCursor(event->scenePos());

        for(i = 0; i < pMain->GetSelectedInstances().size(); i++)
        {
            if(shiftdown)
            {
                pMain->GetSelectedInstances()[i]->Move(QVector3D(0,0,-mouseDeltaPos.y()*0.1));
            }
            else
            {
                if(currViewAngle == "FREE" || currViewAngle == "TOP" || currViewAngle == "BOTTOM")
                {
                    pMain->GetSelectedInstances()[i]->SetX(cursorPos3D.x() - PreDragInstanceOffset.x());
                    pMain->GetSelectedInstances()[i]->SetY(cursorPos3D.y() - PreDragInstanceOffset.y());
                }
                else if(currViewAngle == "FRONT" || currViewAngle == "BACK")
                {
                    pMain->GetSelectedInstances()[i]->SetX(cursorPos3D.x() - PreDragInstanceOffset.x());
                    pMain->GetSelectedInstances()[i]->SetZ(cursorPos3D.z() - PreDragInstanceOffset.z());
                }
                else if(currViewAngle == "RIGHT" || currViewAngle == "LEFT")
                {
                    pMain->GetSelectedInstances()[i]->SetY(cursorPos3D.y() - PreDragInstanceOffset.y());
                    pMain->GetSelectedInstances()[i]->SetZ(cursorPos3D.z() - PreDragInstanceOffset.z());
                }
            }
            pMain->UpdateInterface();
        }

    }
    if(currtool == "MODELORIENTATE")
    {

            for(unsigned int i = 0; i < pMain->GetSelectedInstances().size(); i++)
            {
                pInst = pMain->GetSelectedInstances()[i];
                pInst->Rotate(QVector3D(mouseDeltaPos.y()*0.2,mouseDeltaPos.x()*0.2,0));
            }
            pMain->UpdateInterface();


    }
    if(currtool == "MODELSCALE")
    {
        for(unsigned int i = 0; i<pMain->GetSelectedInstances().size(); i++)
        {
            //pMain->GetSelectedInstances()[i]->Scale(QVector3D(dx*0.01,dx*0.01,dx*0.01));
            QVector3D cScale = pMain->GetSelectedInstances()[i]->GetScale();
            pMain->GetSelectedInstances()[i]->SetScale(cScale*(1+mouseDeltaPos.x()/50.0));
        }
        pMain->UpdateInterface();

    }
    if(currtool == "SUPPORTMODIFY")
    {
        pInst = pMain->SupportModeInst();
        if(!pInst)
            return;

        if(!pMain->GetSelectedSupports()->size())
            return;

        if(pMain->GetSelectedSupports()->size() > 1)
            pMain->SelectOnly(pMain->GetSelectedSupports()->at(pMain->GetSelectedSupports()->size()-1));


        bool isAgainstInst;
        hideNonActiveSupports = true;

        pSup = pMain->GetSelectedSupports()->at(0);

        //check if we need to render warning
        if(!pSup->IsPrintable())
            pSup->EnableErrorGlow();
        else
            pSup->DisableErrorGlow();

        if(toolStringMemory == "BOTTOM" )
        {
            if(controldown)
            {
                pSup->SetBottomLength(pSup->GetBottomLength() - mouseDeltaPos.y()/30.0);
                if(pSup->GetBottomLength() <= 0.2)
                    pSup->SetBottomLength(0.2);
            }
            else if(shiftdown)
            {
                //Mouse based bottom normal rotation.
                if(!toolSupportMemory.GetIsGrounded())
                {
                    ModelInstance* pInst = pMain->SupportModeInst();
                    QVector3D instPos = pInst->GetPos();
                    QVector3D normCur;
                    QVector3D delta = pSup->GetBottomPoint() - (Get3DCursorOnScreen(event->scenePos(),pSup->GetBottomPoint()+instPos,2.0)
                                                                - instPos);
                    delta.normalize();
                    normCur = delta;
                    pSup->SetBottomNormal(normCur);
                }
            }
            else
            {
                Update3DCursor(event->scenePos(),pInst,isAgainstInst);
                if(isAgainstInst)
                    pSup->SetBottomPoint(cursorPos3D - pInst->GetPos());//back to local pos
                else
                {
                     pSup->SetBottomPoint(cursorPos3D - pInst->GetPos() - toolVectorOffsetMemory);//move on floor
                     //with offset
                }
                pSup->SetBottomNormal(-cursorNormal3D);
                pSup->SetBottomAngleFactor(1.0);

                if(isAgainstInst)
                {
                    pSup->SetIsGrounded(false);
                    if(toolSupportMemory.GetIsGrounded())//tracking on the inst and not originally inst based
                    {
                        appSettings.beginGroup("USERSUPPORTPARAMS");
                        appSettings.beginGroup("SUPPORT_BOTTOM_NONGROUNDED");
                        pSup->SetBottomAttachShape(appSettings.value("ATTACHSHAPE").toString());
                        pSup->SetBottomRadius(appSettings.value("RADIUS").toDouble());
                        pSup->SetBottomLength(appSettings.value("LENGTH").toDouble());
                        pSup->SetBottomPenetration(appSettings.value("PENETRATION").toDouble());
                        appSettings.endGroup();
                        appSettings.endGroup();
                    }
                    else
                    {
                        pSup->SetBottomAttachShape(toolSupportMemory.GetBottomAttachShape());
                        pSup->SetBottomRadius(toolSupportMemory.GetBottomRadius());
                        pSup->SetBottomLength(toolSupportMemory.GetBottomLength());
                        pSup->SetBottomPenetration(toolSupportMemory.GetBottomPenetration());
                    }

                }
                else
                {
                    pSup->SetIsGrounded(true);
                    if(!toolSupportMemory.GetIsGrounded())//tracking on the ground and not originally grounded
                    {
                        appSettings.beginGroup("USERSUPPORTPARAMS");
                        appSettings.beginGroup("SUPPORT_BOTTOM_GROUNDED");
                        pSup->SetBottomAttachShape(appSettings.value("ATTACHSHAPE").toString());
                        pSup->SetBottomRadius(appSettings.value("RADIUS").toDouble());
                        pSup->SetBottomLength(appSettings.value("LENGTH").toDouble());
                        pSup->SetBottomPenetration(appSettings.value("PENETRATION").toDouble());
                        appSettings.endGroup();
                        appSettings.endGroup();

                    }
                    else
                    {
                        pSup->SetBottomAttachShape(toolSupportMemory.GetBottomAttachShape());
                        pSup->SetBottomRadius(toolSupportMemory.GetBottomRadius());
                        pSup->SetBottomLength(toolSupportMemory.GetBottomLength());
                        pSup->SetBottomPenetration(toolSupportMemory.GetBottomPenetration());
                    }
                }
            }
        }
        else if(toolStringMemory == "TOP" || toolStringMemory == "MID")
        {
            if(controldown && toolStringMemory == "TOP")//top length scaling
            {
                pSup->SetTopLength(pSup->GetTopLength() + mouseDeltaPos.y()/30.0);
                if(pSup->GetTopLength() <= 0.2)
                    pSup->SetTopLength(0.2);
            }
            else if(controldown && toolStringMemory == "MID")//radius scaling
            {
                double rt = pSup->GetTopRadius() + mouseDeltaPos.x()/80.0;
                if(rt <= 0.05)
                    rt = 0.05;
                pSup->SetTopRadius(rt);

                double rm = pSup->GetMidRadius() + mouseDeltaPos.x()/80.0;
                if(rm <= 0.05)
                    rm = 0.05;
                pSup->SetMidRadius(rm);

                if(!pSup->GetIsGrounded())
                {
                    double rb = pSup->GetBottomRadius() + mouseDeltaPos.x()/80.0;
                    if(rb <= 0.05)
                        rb = 0.05;
                    pSup->SetBottomRadius(rb);
                }

            }
            else if(shiftdown)
            {
                //Mouse based top normal rotation.
                ModelInstance* pInst = pMain->SupportModeInst();
                QVector3D instPos = pInst->GetPos();
                QVector3D normCur;
                QVector3D delta = pSup->GetTopPoint() - (Get3DCursorOnScreen(event->scenePos(),pSup->GetTopPoint()+instPos,2.0)
                                                            - instPos);
                delta.normalize();
                normCur = delta;
                pSup->SetTopNormal(normCur);

            }
            else
            {
                Update3DCursor(event->scenePos(),pInst,isAgainstInst);
                pSup->SetTopPoint(cursorPos3D - pInst->GetPos());//back to local pos
                pSup->SetTopNormal(-cursorNormal3D);
                pSup->SetTopAngleFactor(1.0);

                //if we started out vertical, move base along with top
                if(toolSupportMemory.IsVertical() && toolSupportMemory.GetIsGrounded())
                {
                    pSup->SetBottomPoint(QVector3D(pSup->GetTopPivot().x(),
                                                   pSup->GetTopPivot().y(),
                                                   pSup->GetBottomPoint().z()));

                }
            }
        }
    }
}

void WorldView::OnToolReleaseAction(QString tool, QGraphicsSceneMouseEvent* event)
{
    SupportStructure* pSup;

    hideNonActiveSupports = false;
    pMain->UpdateInterface();
    if( currtool == "MODELORIENTATE" || currtool == "MODELSCALE")
    {
        UpdateSelectedBounds();
    }

}

void WorldView::OnToolHoverMove(QString tool, QGraphicsSceneMouseEvent* event)
{
    ModelInstance* pInst;
    if(tool == "SUPPORTADD" || tool == "SUPPORTDELETE")
    {
       if(!pMain->SupportModeInst())
            return;
       pInst = pMain->SupportModeInst();
       Update3DCursor(event->scenePos(),pInst);
//       qDebug()<<tr("curr3DCursor ,x=%1,y=%2,z=%3").arg( cursorPos3D.x()).arg( cursorPos3D.y()).arg( cursorPos3D.z());

    }
}



////////////////////////////////////////////////////////////////////
//Private Functions
////////////////////////////////////////////////////////////////////
ModelInstance* WorldView::SelectInstanceByScreen(QPointF pos)      //急需解决的问题，通过颜色识别来判断物体是否被选中了
{
   unsigned int i;
   unsigned char pixel[3];
   //clear the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glDisable(GL_LIGHTING);

   for(i = 0; i < pMain->GetAllInstances().size();i++)
   {
       pMain->GetAllInstances()[i]->RenderPickGL();
   }

   glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glEnable(GL_LIGHTING);

   //now that we have the color, compare it against every instance
   for(i = 0; i < pMain->GetAllInstances().size();i++)
   {
       ModelInstance* inst = pMain->GetAllInstances()[i];

       if((pixel[0] == inst->pickcolor[0]) && (pixel[1] == inst->pickcolor[1]) && (pixel[2] == inst->pickcolor[2]))
       {

           pMain->Select(inst);
           return inst;
       }
   }

   return NULL;
}

SupportStructure* WorldView::GetSupportByScreen(QPointF pos)
{
    unsigned int i;
    unsigned char pixel[3];
    ModelInstance* pInst;
    SupportStructure* pSup;

    pInst = pMain->SupportModeInst();
    if(pInst == NULL)
        return NULL;


    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);

    //we need to render the model too so it can occlude hidden supports
    pInst->RenderGL(true);

    for(i = 0; i < pInst->GetSupports().size(); i++)
    {
        pSup = pInst->GetSupports()[i];
        pSup->RenderPickGL(supportAlpha > 0.99 || !pSup->GetIsGrounded(),true);
    }

    glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);

    //now that we have the color, compare it against every instance
    for(i = 0; i < pInst->GetSupports().size();i++)
    {
        pSup = pInst->GetSupports()[i];

        if((pixel[0] == pSup->pickcolor[0]) && (pixel[1] == pSup->pickcolor[1]) && (pixel[2] == pSup->pickcolor[2]))
        {
            return pSup;
        }
    }
    return NULL;
}

QString WorldView::GetSupportSectionByScreen(QPointF pos, SupportStructure* sup)
{
    unsigned char pixel[3];

    //clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);

    sup->RenderPartPickGL(supportAlpha > 0.99 || !sup->GetIsGrounded(),true);//renders all 3 sections in different colors.

    glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_LIGHTING);

    if(pixel[0] > 200)
        return "TOP";

    if(pixel[1] > 200)
        return "MID";

    if(pixel[2] > 200)
        return "BOTTOM";

    //else
    return "";
}


//returns global cordinates of mouse position, the plane is centered around hintPos.
//standoff if how much to nudge the plane towards the viewer.
QVector3D WorldView::Get3DCursorOnScreen(QPointF screenPos, QVector3D hintPos, double standoff)
{

    unsigned char pixel[3];//color picked pixel
    QVector3D firstPassPos;
    QVector3D finalPos;

    //clear the screen and set the background to pure green.
   // qglClearColor(QColor(0,255,0));
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);//dont cull so we can track from back side too :)
    glPushMatrix();


    //computer standoff vector
    QVector3D standoffv(0,0,1);
    RotateVector(standoffv,-xRot,QVector3D(1,0,0));
    RotateVector(standoffv,-yRot,QVector3D(0,1,0));
    RotateVector(standoffv,-zRot,QVector3D(0,0,1));

    standoffv = standoffv*standoff;

    hintPos += standoffv;

    glTranslatef(hintPos.x(),hintPos.y(),hintPos.z());

    //rotate to face camera and move to hint position
    glRotatef(-zRot,0.0,0.0,1.0);
    glRotatef(-yRot,0.0,1.0,0.0);
    glRotatef(-xRot,1.0,0.0,0.0);


    //In the first pass we will render a very large quad
    //that is 10 times the size of the build area

    //render colored cordinate table
    //255,0,0-------------255,0,255
    //|                       |
    //|                       |
    //|                       |
    //0,0,0----------------0,0,255
    //
    //y cordinate maps to red channel
    //x cordinate maps to blue channel

    glNormal3f(0,0,1.0f);
    glBegin(GL_QUADS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f( -buildsizex*5, -buildsizey*5, 0);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f( buildsizex*5, -buildsizey*5, 0);
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( buildsizex*5, buildsizey*5, 0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( -buildsizex*5, buildsizey*5, 0);
    glEnd();

    glReadPixels(screenPos.x(), this->height() - screenPos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    //lets map the colors to the first pass course position
    firstPassPos.setX((float(pixel[2])/255.0)*buildsizex*10 - buildsizex*5);
    firstPassPos.setY((float(pixel[0])/255.0)*buildsizey*10 - buildsizey*5);


    //now we are ready to begin second pass based on first pass position
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f( firstPassPos.x() - buildsizex*2*0.039063*0.5, firstPassPos.y() - buildsizey*2*0.039063*0.5, 0);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f( firstPassPos.x() + buildsizex*2*0.039063*0.5, firstPassPos.y() - buildsizey*2*0.039063*0.5, 0);
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( firstPassPos.x() + buildsizex*2*0.039063*0.5, firstPassPos.y() + buildsizey*2*0.039063*0.5, 0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( firstPassPos.x() - buildsizex*2*0.039063*0.5, firstPassPos.y() + buildsizey*2*0.039063*0.5, 0);
    glEnd();

    //re-read pixels for second pass
    glReadPixels(screenPos.x(), this->height() - screenPos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    glPopMatrix();

    //set openGl stuff back the way we found it...
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);

   // qglClearColor(QColor(0,100,100));
    glClearColor(0, 0.39063, 0.39063, 1);


    //if we hit pure green - we've hit the clear color (and vector is unknowns)
    if(pixel[1] > 200)
        return QVector3D(0,0,0);

    //lets map the colors to the real world
    finalPos.setX((float(pixel[2])/255.0)*buildsizex*2*0.039063 - buildsizex*2*0.039063*0.5 + firstPassPos.x());
    finalPos.setY((float(pixel[0])/255.0)*buildsizey*2*0.039063 - buildsizey*2*0.039063*0.5 + firstPassPos.y());
//    finalPos.setZ(0.0);
    finalPos.setZ(1.0);  //chenge by ChenPeng 2014-10-15

    //bring to real space.
    RotateVector(finalPos,-xRot,QVector3D(1,0,0));
    RotateVector(finalPos,-yRot,QVector3D(0,1,0));
    RotateVector(finalPos,-zRot,QVector3D(0,0,1));

    finalPos += hintPos;

    return finalPos;
}


//Unseen by the user - does a two pass render on the base of the
// track the mouse against the plane given by current view angle
// if an instance is given - it will track against the whole model AS WELL
void WorldView::Update3DCursor(QPointF pos)
{
    bool b;
    Update3DCursor(pos, NULL, b);
}
void WorldView::Update3DCursor(QPointF pos, ModelInstance* trackInst)
{
    bool b;
    Update3DCursor(pos, trackInst, b);
}
void WorldView::Update3DCursor(QPointF pos, ModelInstance* trackInst, bool &isAgainstInst)
{
    unsigned char pixel[3];//color picked pixel
    QVector3D firstPassPos;
    bool hitInstSuccess;
    unsigned int hitTri;

    isAgainstInst = false;

    //before starting plane tracking - see if we hit the instance
    if(trackInst != NULL)
    {
        hitTri = GetPickTriangleIndx(trackInst,pos,hitInstSuccess);
        if( hitInstSuccess )
        {
            isAgainstInst = true;
            cursorPos3D = GetPickOnTriangle(pos,trackInst,hitTri) + trackInst->GetPos();
            cursorNormal3D = trackInst->triList[hitTri]->normal;

            return;
        }
    }
    //clear the screen and set the background to pure green.
   // qglClearColor(QColor(0,255,0));
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);//dont cull so we can track from back side too :)
    glPushMatrix();
    //Depending on the current view angle - we may want the cursor canvas
    //vertical and/or rotated
    if(currViewAngle == "FREE" || currViewAngle == "TOP" || currViewAngle == "BOTTOM")
        glRotatef(0.0f,0.0f,0.0f,1.0f);//no rotating - put on ground
    else if(currViewAngle == "FRONT" || currViewAngle == "BACK"){
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
    }
    else if(currViewAngle == "RIGHT" || currViewAngle == "LEFT")
    {
        glRotatef(-90.0f,0.0f,0.0f,1.0f);
        glRotatef(-90.0f,1.0f,0.0f,0.0f);
    }

    //In the first pass we will render a very large quad
    //that is 10 times the size of the build area

    //render colored cordinate table
    //255,0,0-------------255,0,255
    //|                       |
    //|                       |
    //|                       |
    //0,0,0----------------0,0,255
    //
    //y cordinate maps to red channel
    //x cordinate maps to blue channel

    glNormal3f(0,0,1.0f);
    glBegin(GL_QUADS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f( -buildsizex*5, -buildsizey*5, 0);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f( buildsizex*5, -buildsizey*5, 0);
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( buildsizex*5, buildsizey*5, 0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( -buildsizex*5, buildsizey*5, 0);
    glEnd();

    glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    //lets map the colors to the first pass course position
    firstPassPos.setX((float(pixel[2])/255.0)*buildsizex*10 - buildsizex*5);
    firstPassPos.setY((float(pixel[0])/255.0)*buildsizey*10 - buildsizey*5);


    //now we are ready to begin second pass based on first pass position
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f( firstPassPos.x() - buildsizex*2*0.039063*0.5, firstPassPos.y() - buildsizey*2*0.039063*0.5, 0);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f( firstPassPos.x() + buildsizex*2*0.039063*0.5, firstPassPos.y() - buildsizey*2*0.039063*0.5, 0);
        glColor3f(1.0f,0.0f,1.0f);
        glVertex3f( firstPassPos.x() + buildsizex*2*0.039063*0.5, firstPassPos.y() + buildsizey*2*0.039063*0.5, 0);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f( firstPassPos.x() - buildsizex*2*0.039063*0.5, firstPassPos.y() + buildsizey*2*0.039063*0.5, 0);
    glEnd();
    //re-read pixels for second pass
    glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    glPopMatrix();

    //set openGl stuff back the way we found it...
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);

  //  qglClearColor(QColor(0,100,100));
    glClearColor(0, 0.39063, 0.39063, 1);


    //if we hit pure green - we've hit the clear color and dont want to make any changes
    if(pixel[1] > 200)
        return;


    //lets map the colors to the real world
    if(currViewAngle == "FREE" || currViewAngle == "TOP" || currViewAngle == "BOTTOM"){
        cursorPos3D.setX((float(pixel[2])/255.0)*buildsizex*2*0.039063 - buildsizex*2*0.039063*0.5 + firstPassPos.x());
        cursorPos3D.setY((float(pixel[0])/255.0)*buildsizey*2*0.039063 - buildsizey*2*0.039063*0.5 + firstPassPos.y());
//        cursorPos3D.setZ(0.0);
        cursorPos3D.setZ(1.0);  //change by ChenPeng 2014-10-15
        cursorNormal3D = QVector3D(0,0,1);
        cursorPosOnTrackCanvas.setX(cursorPos3D.x());
        cursorPosOnTrackCanvas.setY(cursorPos3D.y());
    }
    else if(currViewAngle == "FRONT" || currViewAngle == "BACK"){
        cursorPos3D.setX((float(pixel[2])/256.0)*buildsizex*2*0.039063 - buildsizex*2*0.039063*0.5 + firstPassPos.x());
        cursorPos3D.setY(0.0);
        cursorPos3D.setZ(-((float(pixel[0])/256.0)*buildsizey*2*0.039063 - buildsizey*2*0.039063*0.5 + firstPassPos.y()));
        cursorNormal3D = QVector3D(0,1,0);
        cursorPosOnTrackCanvas.setX(cursorPos3D.x());
        cursorPosOnTrackCanvas.setY(cursorPos3D.z());
    }
    else if(currViewAngle == "RIGHT" || currViewAngle == "LEFT")
    {
        cursorPos3D.setX(0.0);
        cursorPos3D.setY(-((float(pixel[2])/255.0)*buildsizex*2*0.039063 - buildsizex*2*0.039063*0.5 + firstPassPos.x()));
        cursorPos3D.setZ(-((float(pixel[0])/255.0)*buildsizey*2*0.039063 - buildsizey*2*0.039063*0.5 + firstPassPos.y()));
        cursorNormal3D = QVector3D(1,0,0);
        cursorPosOnTrackCanvas.setX(cursorPos3D.y());
        cursorPosOnTrackCanvas.setY(cursorPos3D.z());
    }
}

unsigned int WorldView::GetPickTriangleIndx(ModelInstance* inst, QPointF pos, bool &success)
{
    unsigned char pixel[3];

    if(inst == NULL)
    {
        success = false;
        return 0;
    }

    //clear the screen
    glPushMatrix();
   // qglClearColor(QColor(0,0,0));
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);

    inst->RenderTrianglePickGL();
    glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

  //  qglClearColor(QColor(0,100,100));
    glClearColor(0, 0.39063, 0.39063, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    //now that we have the color, we should know what triangle index it is.
    //if the color is 0,0,0, then we missed the model
    unsigned int result = pixel[0]*1 + pixel[1]*256 + pixel[2]*65536;
    if(!result)
    {
        success = false;
        return 0;
    }
    else
    {
        if((result - 1) < inst->triList.size())//make sure the indx is in a valid range!
        {                                //just in case..
            success = true;
            return result - 1;//to get actual index
        }
        else
        {
            success = false;
            return 0;
        }

    }
}
//return position relative to instance center!
QVector3D WorldView::GetPickOnTriangle(QPointF pos, ModelInstance* inst, unsigned int triIndx)
{
    unsigned char pixel[3];

    //clear the screen
    glPushMatrix();
   // qglClearColor(QColor(128,128,128));// so if by chance we miss it will be center bounds
    glClearColor(0.5,0.5,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    inst->RenderSingleTrianglePickGL(triIndx);
    glPopMatrix();

    glReadPixels(pos.x(), this->height() - pos.y(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    double xPercent = float(pixel[0])/256.0;
    double yPercent = float(pixel[1])/256.0;
    double zPercent = float(pixel[2])/256.0;
    QVector3D Slew(xPercent,yPercent,zPercent);

    QVector3D minBound = inst->triList[triIndx]->minBound;
    QVector3D maxBound = inst->triList[triIndx]->maxBound;

    QVector3D globalPos = minBound + (maxBound - minBound)*Slew;


    QVector3D localPos = globalPos - inst->GetPos();


   // qglClearColor(QColor(0,100,100));
     glClearColor(0, 0.39063, 0.39063, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);

    return localPos;

}

//returns local position on the instance
QVector3D WorldView::GetDrillingHit(QVector3D localBeginPosition, ModelInstance *inst, bool &hitground, Triangle3D *&pTri)
{
    unsigned int hitTri;
    const float viewRad = 1.0;
    const float nearPlane = 0.5;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //lets set up a ortho view facing down from the begining position.
    glOrtho((inst->GetPos().x() + localBeginPosition.x()) - viewRad,
            (inst->GetPos().x() + localBeginPosition.x()) + viewRad,
            (inst->GetPos().y() + localBeginPosition.y()) - viewRad,
            (inst->GetPos().y() + localBeginPosition.y()) + viewRad,
            nearPlane,
            (inst->GetMaxBound().z() - inst->GetMinBound().z()));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //move the "camera" into the right position.
    glTranslatef(0.0f,
                 0.0f,
                 -(inst->GetPos().z() + localBeginPosition.z()));
    bool s;
    hitTri = GetPickTriangleIndx(inst, QPoint(this->width()/2,this->height()/2), s);
    if(!s)
    {
        hitground = true;
        pTri = NULL;
        return QVector3D(0,0,0);
    }
    hitground = false;
    pTri = inst->triList[hitTri];
    return GetPickOnTriangle(QPoint(this->width()/2,this->height()/2),inst,hitTri);
}
void WorldView::UpdateVisSlice()
{

}
void WorldView::drawBackground(QPainter *painter, const QRectF &)
{
    if (painter->paintEngine()->type()!= QPaintEngine::OpenGL2)
    {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }
    initializeGL();
    paintGL();

}
