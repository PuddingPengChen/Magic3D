#include "modelinstance.h"
#include "../geometric.h"
#include "layoutprojectdata.h"
#include "../SupportEngine/supportstructure.h"
#include "triangle3d.h"
#include "OS_Function.h"
#include <QtOpenGL>

unsigned char ModelInstance::gColorID[3] = {0,0,0};

///////////////////////////////////
//Public
///////////////////////////////////
ModelInstance::ModelInstance(ModelData* parent)
{
	pData = parent;
	listItem = new QListWidgetItem();
    parent->pMain->AddTagToModelList(listItem);             //用于显示加载好的模型的Model

    selectedcolor = QColor(0,100,220);

    support_z = 0.0;
    pos = QVector3D(0,0,0);
	rot = QVector3D(0,0,0);
	scale = QVector3D(1,1,1);
    SupportedBounding = QVector3D(0,0,0);

    isFlipped = false;

	maxbound = parent->maxbound;
	minbound = parent->minbound;
    p = (maxbound - minbound);
	//selection
	isselected = false;
    //support
    isInSupportMode = false;
    supportCounter = 1;//start with support 1, basePlate gets 0
    basePlateSupport = NULL;
	//color
    normalcolor = QColor(125,125,150);
    currcolor = normalcolor;        //默认的颜色
	
	//picking
	pickcolor[0] = gColorID[0];
    pickcolor[1] = gColorID[1];
    pickcolor[2] = gColorID[2];
 
    gColorID[0]++;                  //不同的物体之间的颜色ID不同
    if(gColorID[0] >= 255)
    {
        gColorID[0] = 0;
        gColorID[1]++;
        if(gColorID[1] >= 255)
        {
                gColorID[1] = 0;
                gColorID[2]++;
        }
	}
	RestOnBuildSpace();
}
ModelInstance::~ModelInstance()
{
	//the instance removes itself from the parent's list
    unsigned int i;
    std::vector<ModelInstance*> temp;
	for(i=0;i<pData->instList.size();i++)
	{
		if(pData->instList[i] != this)
		{
			temp.push_back(pData->instList[i]);
		}
	}
	pData->instList.clear();
	pData->instList = temp;
	
	pData = NULL;
	delete listItem;
    UnBakeGeometry();

    //free up any support structures
    for(i = 0; i < supportStructureList.size(); i++)
    {
        delete supportStructureList[i];
    }
    delete basePlateSupport;
    //free up any display lists
    FreeTriPickDispLists();
}
void ModelInstance::SetColor(QColor color)
{
    selectedcolor = color;
    SetSelected(true);


}
void ModelInstance::SetTag(QString tag)
{
    listItem->setText(tag);         //设置标签
}
//translation
void ModelInstance::RestOnBuildSpace()
{
    SetZ(pos.z() - minbound.z() );          //重新计算边界值
}
void ModelInstance::SetPos(QVector3D pos)
{
    QVector3D oldPos = this->pos;
    if(OnPosChangeRequest(pos - oldPos) == false)
        return;

    //update bounds cordinates.
    maxbound += pos - oldPos;
    minbound += pos - oldPos;
    this->pos = pos;
    //if(pos != oldPos)
        OnPosChanged(pos - oldPos);
}
void ModelInstance::SetX(double x)
{
	SetPos(QVector3D(x,pos.y(),pos.z()));
}
void ModelInstance::SetY(double y)
{
	SetPos(QVector3D(pos.x(),y,pos.z()));
}
void ModelInstance::SetZ(double z)
{
    SetPos(QVector3D(pos.x(),pos.y(),z));
}

void ModelInstance::SetScale(QVector3D scale)
{
    CorrectScale(scale);
    if(OnScaleChangeRequest(scale - this->scale) == false)
        return;

    if(scale != this->scale)
        OnScaleChanged( scale - this->scale);               //获得scale的差
	this->scale = scale;
    CorrectScale(this->scale);                             //设置当前的scale
}

void ModelInstance::SetScaleX(double x)
{
	SetScale(QVector3D(x,scale.y(),scale.z()));
}
void ModelInstance::SetScaleY(double y)
{
	SetScale(QVector3D(scale.x(),y,scale.z()));
}
void ModelInstance::SetScaleZ(double z)
{
	SetScale(QVector3D(scale.x(),scale.y(),z));
}

void ModelInstance::SetRot(QVector3D r)
{
    CorrectRot(r);                  // limit the angle  in 0~360

    if(OnRotationChangeRequest(r - this->rot) == false)
        return;

    if(r != this->rot)
        OnRotChanged(r - this->rot);

    if((r.x() != this->rot.x()) || (r.y() != this->rot.y()))
        OnRotXOrYChanged(r - this->rot);
    if((r.x() == this->rot.x()) && (r.y() == this->rot.y()) && (r.z() != this->rot.z()))
        OnRotZChangedOnly(r - this->rot);
    this->rot = r;
}

void ModelInstance::SetFlipped(int flipped)
{
    //ealy out
    if(flipped != int(isFlipped))
    {
        if(supportStructureList.size())
        {
            if(this->rot.x() || this->rot.y())
            {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setText("Mirroring will break all supports");
                msgBox.setInformativeText("Are you sure you want to Mirror?");
                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                msgBox.setDefaultButton(QMessageBox::No);
                int ret = msgBox.exec();

                if(ret == QMessageBox::No)
                {
                    pData->pMain->ExitToolAction();//fixes mouse problem
                    pData->pMain->UpdateInterface();
                    return;
                }
                else
                {
                    //Break Off supports
                    RemoveAllSupports();
                    pData->pMain->ExitToolAction();//fixes mouse problem
                }
            }
            else//we dont have any x or y rotation so we should be able to mirror supports.
            {
                FlipSupports();
            }
        }
    }
    isFlipped = flipped;

    if(flipped)
    {
        if(!pData->flippedDispLists.size())
        {
            pData->FormFlippedDisplayLists();
        }
    }
}

//manual bounds sets (no baking)
//warning - only use this if as a result of a movement.
void ModelInstance::SetBounds(QVector3D newmax, QVector3D newmin)
{
    maxbound = newmax;
    minbound = newmin;
}

//pre-move checking callbacks
bool ModelInstance::OnPosChangeRequest(QVector3D deltaPos)
{
    return true;
}

bool ModelInstance::OnScaleChangeRequest(QVector3D deltaScale)
{
    return true;
}

bool ModelInstance::OnRotationChangeRequest(QVector3D deltaRot)
{
    if((deltaRot.x() || deltaRot.y()) && supportStructureList.size())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setText("Orientating will break all supports");
        msgBox.setInformativeText("Are you sure you want to orientate?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

        if(ret == QMessageBox::No)
        {
            pData->pMain->ExitToolAction();//fixes mouse problem
            return false;
        }
        else
        {
            //Break Off supports
            RemoveAllSupports();
            pData->pMain->ExitToolAction();//fixes mouse problem
        }
    }
    return true;
}
//post move callbacks
void ModelInstance::OnPosChanged(QVector3D deltaPos)
{
    unsigned int s;
    double maxDepth = -99999.0;
    double depth;
    double buildAreaMaxX,buildAreaMaxY;

    UpdateSupports();

    //check prohibite inverted supports by keeping the model up
    for(s = 0; s < supportStructureList.size(); s++)
    {
        if(supportStructureList[s]->IsConstricted(depth) && supportStructureList[s]->GetIsGrounded())
        {
            if(depth > maxDepth)
                maxDepth = depth;
        }
    }
    if((maxDepth > 0))
    {
        Move(QVector3D(0,0,maxDepth+0.01));
    }

    if(GetBasePlate())
    {
        if(minbound.z() < GetBasePlate()->GetBottomLength())
        {
            Move(QVector3D(0,0,GetBasePlate()->GetBottomLength() - minbound.z()));
        }
    }
    //Restrict movement when completely off build table
    //allow the min bound to extend out of build table have a instance size
    buildAreaMaxX = pData->pMain->ProjectData()->GetBuildSpace().x()/2.0 + (maxbound.x() - minbound.x())*0.5;
    buildAreaMaxY = pData->pMain->ProjectData()->GetBuildSpace().y()/2.0 + (maxbound.y() - minbound.y())*0.5;


    if(minbound.x() > buildAreaMaxX)
    {
        Move(QVector3D(-(minbound.x() - buildAreaMaxX)-0.01,0,0));
    }
    if(maxbound.x() < -buildAreaMaxX)
    {
        Move(QVector3D((-buildAreaMaxX - maxbound.x())+0.01,0,0));
    }
    if(minbound.y() > buildAreaMaxY)
    {
        Move(QVector3D(0,-(minbound.y() - buildAreaMaxY)-0.01,0));
    }
    if(maxbound.y() < -buildAreaMaxY)
    {
        Move(QVector3D(0,(-buildAreaMaxY - maxbound.y())+0.01,0));
    }
    pData->pMain->ProjectData()->UpdateZSpace();
}

void ModelInstance::OnScaleChanged(QVector3D deltaScale)
{
    unsigned int s;
    double maxDepth = -99999.0;
    double depth;

    ScaleSupportPositionsAroundCenter(scale, scale + deltaScale);

    //after a scaling action we want to move the model up if
    //there are supports underground.
    for(s = 0; s < GetSupports().size(); s++)
    {
        if(GetSupports()[s]->IsConstricted(depth) && GetSupports()[s]->GetIsGrounded())
        {
            if(depth > maxDepth)
                maxDepth = depth;
        }
    }
    if((maxDepth > 0))
    {
        Move(QVector3D(0,0,maxDepth+0.01));
    }

    if(GetBasePlate())
    {
        if(minbound.z() < GetBasePlate()->GetBottomLength())
        {
            Move(QVector3D(0,0,GetBasePlate()->GetBottomLength() - minbound.z()));
        }
    }
}
void ModelInstance::OnRotChanged(QVector3D deltaRot)
{
}
void ModelInstance::OnRotXOrYChanged(QVector3D deltaRot)
{
}
void ModelInstance::OnRotZChangedOnly(QVector3D deltaRot)
{
    //rotate all the supports incrementally.
    RotateSupports(deltaRot);
}

//Incremental
void ModelInstance::Scale(QVector3D scalar)
{
    SetScale(QVector3D(scale.x() + scalar.x(),scale.y() + scalar.y(),scale.z() + scalar.z()));
}
void ModelInstance::Move(QVector3D translation)
{
	SetPos(QVector3D(pos.x() + translation.x(),pos.y() + translation.y(),pos.z() + translation.z()));
}
void ModelInstance::Rotate(QVector3D rotation)
{
	SetRot(QVector3D(rot.x() + rotation.x(),rot.y() + rotation.y(),rot.z() + rotation.z()));
}


//gets
QVector3D ModelInstance::GetPos()
{
	return pos;
}
QVector3D ModelInstance::GetRot()
{
	return rot;
}

QVector3D ModelInstance::GetScale()
{
	return scale;
}

QVector3D ModelInstance::GetMaxBound()
{
	return maxbound;
}

QVector3D ModelInstance::GetMinBound()
{
	return minbound;
}

bool ModelInstance::GetFlipped()
{
    return isFlipped;
}

//this should always be called after a bake.
QVector3D ModelInstance::GetTriangleLocalPosition(unsigned int tri)
{
    return(triList[tri]->maxBound + triList[tri]->minBound)*0.5 - GetPos();
}
//selection
void ModelInstance::SetSelected(bool sel)         //变换物体的颜色
{
	isselected = sel;
	if(sel)
	{
		currcolor = selectedcolor;
	}
	else
	{
		currcolor = normalcolor;
	}
	listItem->setSelected(sel);
}

//support
bool ModelInstance::IsInSupportMode()
{
    return isInSupportMode;
}

void ModelInstance::SetInSupportMode(bool s)
{
    isInSupportMode = s;
}

std::vector<SupportStructure*> ModelInstance::GetSupports()
{
    return supportStructureList;
}

SupportStructure* ModelInstance::GetBasePlate()
{
    return basePlateSupport;
}
void ModelInstance::EnableBasePlate()
{
    if(basePlateSupport != NULL)
    {
        delete basePlateSupport;
        basePlateSupport = NULL;
    }
    QVector2D Rdi_1 = QVector2D(minbound.x(),minbound.y());
    QVector2D Rdi_2 = QVector2D(maxbound.x(),maxbound.y());
    QVector2D R_a = Rdi_2 - Rdi_1;
    double len = R_a.length()/2;

    basePlateSupport = new SupportStructure(this);
    basePlateSupport->SetIsGrounded(true);
    basePlateSupport->SetTopAttachShape("");
    basePlateSupport->SetMidAttachShape("");
    basePlateSupport->SetBottomAttachShape("Cylinder");
    basePlateSupport->SetBottomRadius(len);
    basePlateSupport->SetBottomPenetration(0.0);
}

void ModelInstance::DisableBasePlate()
{
    if(basePlateSupport != NULL)
    {
        delete basePlateSupport;
        basePlateSupport = NULL;
    }
}

SupportStructure* ModelInstance::AddSupport(QVector3D localTopPosition, QVector3D localBottomPosition)
{
    SupportStructure* newSup = new SupportStructure(this);
    newSup->AssignPickId();
    newSup->SetBottomPoint(localBottomPosition);
    newSup->SetTopPoint(localTopPosition);
    newSup->SupportNumber = supportCounter;
    supportStructureList.push_back(newSup);
    supportCounter++;
    return newSup;
}
void ModelInstance::RemoveSupport(SupportStructure* sup)
{
    unsigned int s;
    std::vector<SupportStructure*> keepers;
    for(s = 0; s < supportStructureList.size(); s++)
    {
        if(supportStructureList[s] == sup)
        {
            delete sup;
        }
        else
            keepers.push_back(supportStructureList[s]);
    }
    supportStructureList = keepers;
}
void ModelInstance::RemoveAllSupports()
{
    unsigned int s;
    for(s = 0; s < supportStructureList.size(); s++)
    {
        delete supportStructureList[s];
    }
    supportStructureList.clear();
    supportCounter = 1;
}
void ModelInstance::UpdateSupports()
{
    unsigned int s;
    for(s = 0; s < supportStructureList.size(); s++)
    {
        supportStructureList[s]->ForceUpdate();
    }
    if(basePlateSupport != NULL)
    {
        basePlateSupport->ForceUpdate();
    }
}

void ModelInstance::RotateSupports(QVector3D deltaRot)
{
    //we need to rotate all support points numerically.
    unsigned int s;
    SupportStructure* cSprt;
    QVector3D oldTopLocalPosition;
    QVector3D oldBottomLocalPosition;

    for(s = 0; s < supportStructureList.size(); s++)
    {
        cSprt = supportStructureList[s];
        cSprt->Rotate(deltaRot);
    }
}

void ModelInstance::ScaleSupportPositionsAroundCenter(QVector3D newScale, QVector3D oldScale)
{
    //"Scaling" the supports is really just changing
    //their positions accourdingly.
    // were given a delta scale which is the different between
    //the old scale vector and the new scale vector.
    unsigned int s;
    SupportStructure* cSprt;
    QVector3D oldTopLocalPosition;
    QVector3D oldBottomLocalPosition;
    QVector3D newTopLocalPosition;
    QVector3D newBottomLocalPosition;

    QVector3D moveFactor;
    moveFactor = oldScale*QVector3D(1/newScale.x(),1/newScale.y(),1/newScale.z());

    for(s = 0; s < supportStructureList.size(); s++)
    {
        cSprt = supportStructureList[s];

        oldTopLocalPosition = cSprt->GetTopPoint();
        oldBottomLocalPosition = cSprt->GetBottomPoint();
        //move old positions into local model rotation domain.
        RotateVector(oldTopLocalPosition,-this->rot.z(),QVector3D(0,0,1));
        RotateVector(oldTopLocalPosition,-this->rot.x(),QVector3D(1,0,0));
        RotateVector(oldTopLocalPosition,-this->rot.y(),QVector3D(0,1,0));
        RotateVector(oldBottomLocalPosition,-this->rot.z(),QVector3D(0,0,1));
        RotateVector(oldBottomLocalPosition,-this->rot.x(),QVector3D(1,0,0));
        RotateVector(oldBottomLocalPosition,-this->rot.y(),QVector3D(0,1,0));
        //do the resulting translation

        newTopLocalPosition = oldTopLocalPosition*moveFactor;
        newBottomLocalPosition = oldBottomLocalPosition*moveFactor;

        //go back to global domain.
        RotateVector(newTopLocalPosition,this->rot.y(),QVector3D(0,1,0));
        RotateVector(newTopLocalPosition,this->rot.x(),QVector3D(1,0,0));
        RotateVector(newTopLocalPosition,this->rot.z(),QVector3D(0,0,1));
        RotateVector(newBottomLocalPosition,this->rot.y(),QVector3D(0,1,0));
        RotateVector(newBottomLocalPosition,this->rot.x(),QVector3D(1,0,0));
        RotateVector(newBottomLocalPosition,this->rot.z(),QVector3D(0,0,1));

        cSprt->SetTopPoint(newTopLocalPosition);
        cSprt->SetBottomPoint(newBottomLocalPosition);

    }

    //additionally we want to deal with the basePlate and scale the radius
    if(GetBasePlate())
    {
        GetBasePlate()->SetBottomRadius(GetBasePlate()->GetBottomRadius()*moveFactor.x());
    }
}

//mirrors all supports based on z rotation.
//wont work with x or y rotation.
void ModelInstance::FlipSupports()
{
    unsigned int s;
    SupportStructure* cSprt;
    QVector3D oldTopLocalPosition;
    QVector3D oldBottomLocalPosition;
    QVector3D newTopLocalPosition;
    QVector3D newBottomLocalPosition;
    QVector3D TopNorm;
    QVector3D BottomNorm;

    QVector3D mirrorVec(0,1,0);
    RotateVector(mirrorVec,this->rot.z(),QVector3D(0,0,1));
    QVector3D flipVec(0,1,0);
    RotateVector(flipVec,this->rot.z()-90,QVector3D(0,0,1));

    double side;
    double distToPlane;

    for(s = 0; s < supportStructureList.size(); s++)
    {
        cSprt = supportStructureList[s];

        //top
        oldTopLocalPosition = cSprt->GetTopPoint();
        distToPlane = QVector3D().distanceToLine(QVector2D(oldTopLocalPosition),mirrorVec);
        side = QVector3D::crossProduct(mirrorVec,QVector2D(oldTopLocalPosition).normalized()).z();
        if(side < 0) side = -1.0;
        else side = 1.0;
        newTopLocalPosition = oldTopLocalPosition + side*2.0*distToPlane*flipVec;

        //bottom
        oldBottomLocalPosition = cSprt->GetBottomPoint();
        distToPlane = QVector3D().distanceToLine(QVector2D(oldBottomLocalPosition),mirrorVec);
        side = QVector3D::crossProduct(mirrorVec,QVector2D(oldBottomLocalPosition).normalized()).z();
        if(side < 0) side = -1.0;
        else side = 1.0;
        newBottomLocalPosition = oldBottomLocalPosition + side*2.0*distToPlane*flipVec;


        //topnorm
        TopNorm = cSprt->GetTopNormal();
        distToPlane = QVector3D().distanceToLine(QVector2D(TopNorm),mirrorVec);
        side = QVector3D::crossProduct(mirrorVec,QVector2D(TopNorm).normalized()).z();
        if(side < 0) side = -1.0;
        else side = 1.0;
        TopNorm = TopNorm + side*distToPlane*2.0*flipVec;
        TopNorm.normalize();


        //bottomnorm
        BottomNorm = cSprt->GetBottomNormal();
        distToPlane = QVector3D().distanceToLine(QVector2D(BottomNorm),mirrorVec);
        side = QVector3D::crossProduct(mirrorVec,QVector2D(BottomNorm).normalized()).z();
        if(side < 0) side = -1.0;
        else side = 1.0;
        BottomNorm = BottomNorm + side*distToPlane*2.0*flipVec;
        BottomNorm.normalize();

        //set new values.
        cSprt->SetTopPoint(newTopLocalPosition);
        cSprt->SetBottomPoint(newBottomLocalPosition);

        cSprt->SetTopNormal(TopNorm);
        cSprt->SetBottomNormal(BottomNorm);
    }
}



void ModelInstance::ShowSupports()
{
    unsigned int s;
    for(s = 0; s < supportStructureList.size(); s++)
    {
        supportStructureList[s]->SetVisible(true);
    }
}

void ModelInstance::HideSupports()
{
    unsigned int s;
    for(s = 0; s < supportStructureList.size(); s++)
    {
        supportStructureList[s]->SetVisible(false);
    }
}

//render
void ModelInstance::RenderGL(bool disableColor)
{
    unsigned int ls;

	//do a smooth visual transition.
	visualcolor.setRedF(visualcolor.redF() + (currcolor.redF() - visualcolor.redF())/2.0);
	visualcolor.setGreenF(visualcolor.greenF() + (currcolor.greenF() - visualcolor.greenF())/2.0);
	visualcolor.setBlueF(visualcolor.blueF() + (currcolor.blueF() - visualcolor.blueF())/2.0);

	glPushMatrix();
            if(!disableColor)
            glColor3f(visualcolor.redF(),visualcolor.greenF(),visualcolor.blueF());
                glTranslatef(pos.x(),pos.y(),pos.z());
                    //global z spinin
                    glRotatef(rot.z(), 0.0, 0.0, 1.0);
                    glRotatef(rot.x(), 1.0, 0.0, 0.0);
                    glRotatef(rot.y(), 0.0, 1.0, 0.0);

                        glScalef(scale.x(),scale.y(),scale.z());
                        if(!isInSupportMode)
                        {
                            DrawBounding();
                        }
                        if(isFlipped)//choose which display list to used
                            for(ls = 0; ls < pData->flippedDispLists.size(); ls++)
                                glCallList(pData->flippedDispLists[ls]);
                        else
                        {
                            for(ls = 0; ls < pData->normDispLists.size(); ls++)
                                glCallList(pData->normDispLists[ls]);
                        }
	glPopMatrix();
}

void ModelInstance::DrawBounding()
{
    if(isselected)
    {
        glPushMatrix();
        float x = (p.x()+SupportedBounding.x())/2;
        float y = (p.y()+SupportedBounding.y())/2;
        float z = (p.z()+SupportedBounding.z())/2;
        //4 vertical lines_1
         glBegin(GL_LINES);
             glVertex3d( -x, -y, -z);
             glVertex3d( -x, -y, z);
         glEnd();
         glBegin(GL_LINES);
             glVertex3d( x, -y,-z);
             glVertex3d( x, -y,z);
         glEnd();
         glBegin(GL_LINES);
             glVertex3d( -x, y,-z);
             glVertex3d( -x, y,z);
         glEnd();
         glBegin(GL_LINES);
             glVertex3d( x, y,-z);
             glVertex3d( x, y,z);
         glEnd();

         //4 Top lines_1
         glBegin(GL_LINES);
             glVertex3d( -x, -y, z);
             glVertex3d( x, -y, z);
         glEnd();
         glBegin(GL_LINES);
             glVertex3d( -x, -y, z);
             glVertex3d( -x, y, z);
         glEnd();
         glBegin(GL_LINES);
             glVertex3d( x, y, z);
             glVertex3d( -x, y, z);
         glEnd();
         glBegin(GL_LINES);
             glVertex3d( x, y, z);
             glVertex3d( x, -y, z);
         glEnd();


           //4 vertical lines
            glBegin(GL_LINES);
                glVertex3d( -x, -y, -z);
                glVertex3d( -x, -y, z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( x, -y,-z);
                glVertex3d( x, -y,z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( -x, y,-z);
                glVertex3d( -x, y,z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( x, y,-z);
                glVertex3d( x, y,z);
            glEnd();

            //4 Top lines
            glBegin(GL_LINES);
                glVertex3d( -x, -y, z);
                glVertex3d( x, -y, z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( -x, -y, z);
                glVertex3d( -x, y, z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( x, y, z);
                glVertex3d( -x, y, z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( x, y, z);
                glVertex3d( x, -y, z);
            glEnd();
            //4 Bottom lines
            glBegin(GL_LINES);
                glVertex3d( -x, -y,-z);
                glVertex3d( x, -y,-z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( -x, -y, -z);
                glVertex3d( -x, y, -z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( x, y, -z);
                glVertex3d( -x, y, -z);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d( x, y, -z);
                glVertex3d( x, -y, -z);
            glEnd();
            glPopMatrix();
    }

}
void ModelInstance::RenderSupportsGL(bool solidColor, float topAlpha, float bottomAlpha)
{
    //lets also render all the supports.
    //since supports are defined as offsets from the global center of an instance
    //-we have to gltranslate.
    unsigned int s;
   // qDebug()<<"RenderSupportsGL()";
    glPushMatrix();
        glTranslatef(pos.x(),pos.y(),pos.z());
        for(s = 0; s < supportStructureList.size(); s++)
        {
            supportStructureList[s]->RenderUpper(solidColor, topAlpha);
        }
        for(s = 0; s < supportStructureList.size(); s++)
        {
            supportStructureList[s]->RenderLower(solidColor, bottomAlpha);
        }
        if(basePlateSupport) basePlateSupport->RenderLower(solidColor, bottomAlpha);
    glPopMatrix();
}

void ModelInstance::renderSupportGL(SupportStructure* pSup, bool solidColor, float topAlpha, float bottomAlpha)
{
    glPushMatrix();
        glTranslatef(pos.x(),pos.y(),pos.z());
            pSup->RenderUpper(solidColor, topAlpha);
            pSup->RenderLower(solidColor, bottomAlpha);
    glPopMatrix();
}


//renders just lines for support tips.
void ModelInstance::RenderSupportsTipsGL()
{
  //  qDebug()<<"RenderSupportsTipsGL()";
    unsigned int s;
    SupportStructure* pSup;
    glPushMatrix();
        glTranslatef(pos.x(),pos.y(),pos.z());
        for(s = 0; s < supportStructureList.size(); s++)
        {
            pSup = supportStructureList[s];
            glBegin(GL_LINES);

                glVertex3f(pSup->GetTopPoint().x(),pSup->GetTopPoint().y(),pSup->GetTopPoint().z());
                glVertex3f(pSup->GetTopPivot().x(),pSup->GetTopPivot().y(),pSup->GetTopPivot().z());

                glVertex3f(pSup->GetTopPivot().x(),pSup->GetTopPivot().y(),pSup->GetTopPivot().z());
                glVertex3f(pSup->GetBottomPivot().x(),pSup->GetBottomPivot().y(),pSup->GetBottomPivot().z());


                glVertex3f(pSup->GetBottomPivot().x(),pSup->GetBottomPivot().y(),pSup->GetBottomPivot().z());
                glVertex3f(pSup->GetBottomPoint().x(),pSup->GetBottomPoint().y(),pSup->GetBottomPoint().z());

            glEnd();
        }

    glPopMatrix();
}
void ModelInstance::RenderPickGL()
{
    unsigned int ls,s;

	glPushMatrix();
		glColor3f(pickcolor[0]/255.0,pickcolor[1]/255.0,pickcolor[2]/255.0);
			glTranslatef(pos.x(),pos.y(),pos.z());
			
                //global z spining
                glRotatef(rot.z(), 0.0, 0.0, 1.0);
                glRotatef(rot.x(), 1.0, 0.0, 0.0);
                glRotatef(rot.y(), 0.0, 1.0, 0.0);
					glScalef(scale.x(),scale.y(),scale.z());
						
                    if(isFlipped)//choose which display list to use
                        for(ls = 0; ls < pData->flippedDispLists.size(); ls++)
                            glCallList(pData->flippedDispLists[ls]);
                    else
                    {
                        for(ls = 0; ls < pData->normDispLists.size(); ls++)
                            glCallList(pData->normDispLists[ls]);
                    }
	glPopMatrix();
    glPushMatrix();
        glColor3f(pickcolor[0]/255.0,pickcolor[1]/255.0,pickcolor[2]/255.0);
        glTranslatef(pos.x(),pos.y(),pos.z());
        //glRotatef(rot.z(), 0.0, 0.0, 1.0);
        for(s = 0; s < supportStructureList.size(); s++)
        {
            supportStructureList[s]->RenderUpper(true, 1.0);
            supportStructureList[s]->RenderLower(true, 1.0);
        }
        if(basePlateSupport) basePlateSupport->RenderLower(true, 1.0);
    glPopMatrix();
}

//This Function is slower because it does not use a display list.
//there is a 16 million + sum triangle limit before overflow...
//assumes the instance is baked and uses the baked triangles;
//subtract tris if for skipping the last triangles in the baked triangle list
//(usefull for support mode)
bool ModelInstance::FormTriPickDispLists()
{
    unsigned char r = 1;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned int l;
    unsigned int t;
    const unsigned int listSize = 10000;//each list to be 10000 triangles big.
    unsigned int tSeamCount = 0;

    //first lets free up existing display lists if there are any
    for( l = 0; l < triPickDispLists.size(); l++)
    {
        glDeleteLists(triPickDispLists[l],1);
    }

    triPickDispLists.push_back(glGenLists(1));

//    qDebug()<<"FormTriPickDispLists()";

    glNewList(triPickDispLists.at(triPickDispLists.size()-1),GL_COMPILE);
    glBegin(GL_TRIANGLES);// Drawing Using Triangles
    for(t = 0; t < triList.size(); t++)//for each triangle
    {        
        glColor3ub(r,g,b);
        glNormal3f( triList[t]->normal.x(),triList[t]->normal.y(),triList[t]->normal.z());//normals

        glVertex3f( triList[t]->vertex[0].x(), triList[t]->vertex[0].y(), triList[t]->vertex[0].z());
        glVertex3f( triList[t]->vertex[1].x(), triList[t]->vertex[1].y(), triList[t]->vertex[1].z());
        glVertex3f( triList[t]->vertex[2].x(), triList[t]->vertex[2].y(), triList[t]->vertex[2].z());

        //inc color counter
        r++;
        if(!r)
        {
            g++;
            if(!g)
            {
                b++;
                if(!b)
                    qDebug() << "WARNING! Triangle Pick Overflow!";
            }
        }

        //make a new seam.
        if(tSeamCount >= listSize)
        {
            glEnd();
            glEndList();
            triPickDispLists.push_back(glGenLists(1));

            glNewList(triPickDispLists.at(triPickDispLists.size()-1),GL_COMPILE);
            glBegin(GL_TRIANGLES);// Drawing Using Triangles
            tSeamCount = 0;
        }
        tSeamCount++;
    }
    glEnd();
    glEndList();

    //check for errors afterwards
    if(glGetError())
    {
       for( l = 0; l < triPickDispLists.size(); l++)
       {
            glDeleteLists(triPickDispLists[l],1);
       }
       triPickDispLists.clear();
       qDebug() << "TriPick Display List creation failed for Instance " << this;
       qDebug() << "Using Procedural rendering.";

       return false;
    }


    qDebug() << triPickDispLists.size() << "TriPick Display Lists created for Instance " << this;

    return true;
}
void ModelInstance::FreeTriPickDispLists()
{
    unsigned int l;
    for( l = 0; l < triPickDispLists.size(); l++)
    {
         glDeleteLists(triPickDispLists[l],1);
    }
    triPickDispLists.clear();
}

void ModelInstance::RenderTrianglePickGL()
{
    unsigned char r = 1;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned int t;
    unsigned int i;

    if(triPickDispLists.size())
    {
        for(i = 0; i < triPickDispLists.size(); i++)
            glCallList(triPickDispLists[i]);
      //  qDebug()<<"Now I use the triPickDispLists";
    }
    else//else do slow procedural rendering
    {
        glEnable(GL_DEPTH_TEST);
        glBegin(GL_TRIANGLES);// Drawing Using Triangles     
        for(t = 0; t < triList.size(); t++)//for each triangle
        {
            glColor3ub(r,g,b);
            glNormal3f( triList[t]->normal.x(),triList[t]->normal.y(),triList[t]->normal.z());//normals
            glVertex3f( triList[t]->vertex[0].x(), triList[t]->vertex[0].y(), triList[t]->vertex[0].z());
            glVertex3f( triList[t]->vertex[1].x(), triList[t]->vertex[1].y(), triList[t]->vertex[1].z());
            glVertex3f( triList[t]->vertex[2].x(), triList[t]->vertex[2].y(), triList[t]->vertex[2].z());
            r++;
            if(!r)
            {
                g++;
                if(!g)
                {
                    b++;
                    if(!b)
                        qDebug() << "WARNING! Triangle Pick Overflow!";
                }
            }
        }
        glEnd();
    }
}
//render a triangle with specific colors on the vertexes based on position inside bounding box.
void ModelInstance::RenderSingleTrianglePickGL(unsigned int triIndx)
{
    float vert0X = triList[triIndx]->vertex[0].x();
    float vert0Y = triList[triIndx]->vertex[0].y();
    float vert0Z = triList[triIndx]->vertex[0].z();

    float vert1X = triList[triIndx]->vertex[1].x();
    float vert1Y = triList[triIndx]->vertex[1].y();
    float vert1Z = triList[triIndx]->vertex[1].z();

    float vert2X = triList[triIndx]->vertex[2].x();
    float vert2Y = triList[triIndx]->vertex[2].y();
    float vert2Z = triList[triIndx]->vertex[2].z();

    QVector3D maxbound = triList[triIndx]->maxBound;
    QVector3D minbound = triList[triIndx]->minBound;




    float vert0XPercent = (vert0X - minbound.x())/(maxbound.x() - minbound.x());
    float vert0YPercent = (vert0Y - minbound.y())/(maxbound.y() - minbound.y());
    float vert0ZPercent = (vert0Z - minbound.z())/(maxbound.z() - minbound.z());

    float vert1XPercent = (vert1X - minbound.x())/(maxbound.x() - minbound.x());
    float vert1YPercent = (vert1Y - minbound.y())/(maxbound.y() - minbound.y());
    float vert1ZPercent = (vert1Z - minbound.z())/(maxbound.z() - minbound.z());

    float vert2XPercent = (vert2X - minbound.x())/(maxbound.x() - minbound.x());
    float vert2YPercent = (vert2Y - minbound.y())/(maxbound.y() - minbound.y());
    float vert2ZPercent = (vert2Z - minbound.z())/(maxbound.z() - minbound.z());


    glBegin(GL_TRIANGLES);// Drawing Using Triangles
    if(isFlipped)
    {
        glNormal3f( triList[triIndx]->normal.x(),triList[triIndx]->normal.y(),triList[triIndx]->normal.z());//normals
        glColor3f(vert2XPercent,vert2YPercent,vert2ZPercent);
        glVertex3f( triList[triIndx]->vertex[2].x(),
                    triList[triIndx]->vertex[2].y(),
                    triList[triIndx]->vertex[2].z());


        glColor3f(vert1XPercent,vert1YPercent,vert1ZPercent);
        glVertex3f( triList[triIndx]->vertex[1].x(),
                    triList[triIndx]->vertex[1].y(),
                    triList[triIndx]->vertex[1].z());

        glColor3f(vert0XPercent,vert0YPercent,vert0ZPercent);
        glVertex3f( triList[triIndx]->vertex[0].x(),
                    triList[triIndx]->vertex[0].y(),
                    triList[triIndx]->vertex[0].z());
    }
    else
    {
        glNormal3f( triList[triIndx]->normal.x(),triList[triIndx]->normal.y(),triList[triIndx]->normal.z());//normals

        glColor3f(vert0XPercent,vert0YPercent,vert0ZPercent);
        glVertex3f( triList[triIndx]->vertex[0].x(),
                    triList[triIndx]->vertex[0].y(),
                    triList[triIndx]->vertex[0].z());

        glColor3f(vert1XPercent,vert1YPercent,vert1ZPercent);
        glVertex3f( triList[triIndx]->vertex[1].x(),
                    triList[triIndx]->vertex[1].y(),
                    triList[triIndx]->vertex[1].z());

        glColor3f(vert2XPercent,vert2YPercent,vert2ZPercent);
        glVertex3f( triList[triIndx]->vertex[2].x(),
                    triList[triIndx]->vertex[2].y(),
                    triList[triIndx]->vertex[2].z());
    }
    glEnd();
}
//geometry
void ModelInstance::BakeGeometry(bool withsupports)
{
    unsigned long int t;
    unsigned short int v;
    Triangle3D* pNewTri;

	UnBakeGeometry();
	
    //update bounds
    maxbound = QVector3D(-999999.0,-999999.0,-999999.0);
    minbound = QVector3D(999999.0,999999.0,999999.0);

    //since this function is usually where the user is waiting, put up wait cursor.
    Enable_User_Waiting_Cursor();
	//copy the triangles from pData into the list with transforms applied
    for(t = 0; t < pData->triList.size(); t++)
	{
        //all data is copied
        pNewTri = new Triangle3D(pData->triList[t]);

        //APPLY TRANSFORMS TO NORMAL
        //scale with the inverse
        pNewTri->normal *= QVector3D(1/scale.x(),1/scale.y(),1/scale.z());
        //flip
        if(isFlipped)
            pNewTri->normal.setX(-pNewTri->normal.x());

        //rotate
        RotateVector(pNewTri->normal,rot.y(),QVector3D(0,1,0));         //物体被旋转后，需要重新计算物体的各个面的法向量
        RotateVector(pNewTri->normal,rot.x(),QVector3D(1,0,0));
        RotateVector(pNewTri->normal,rot.z(),QVector3D(0,0,1));

        pNewTri->normal.normalize();//force to unit length again
        for(v=0;v<3;v++)
		{
            //scale triangle vertices 1st
            pNewTri->vertex[v] *= scale;
            if(isFlipped)
                pNewTri->vertex[v].setX(-pNewTri->vertex[v].x());
            //Rotate 2nd
            RotateVector(pNewTri->vertex[v], rot.y(), QVector3D(0,1,0));//y
            RotateVector(pNewTri->vertex[v], rot.x(), QVector3D(1,0,0));//x
            RotateVector(pNewTri->vertex[v], rot.z(), QVector3D(0,0,1));//z
            //Translate 3rd
			pNewTri->vertex[v] += pos;
		}


		//update the triangles bounds
		pNewTri->UpdateBounds();

        if(withsupports == false)//if we are doing it with supports we do the bound
                                 //check after triangle copy.
        {
            //update the instance bounds.
            if(pNewTri->maxBound.x() > this->maxbound.x())
                this->maxbound.setX(pNewTri->maxBound.x());
            if(pNewTri->maxBound.y() > this->maxbound.y())
                this->maxbound.setY(pNewTri->maxBound.y());
            if(pNewTri->maxBound.z() > this->maxbound.z())
                this->maxbound.setZ(pNewTri->maxBound.z());

            if(pNewTri->minBound.x() < this->minbound.x())
                this->minbound.setX(pNewTri->minBound.x());
            if(pNewTri->minBound.y() < this->minbound.y())
                this->minbound.setY(pNewTri->minBound.y());
            if(pNewTri->minBound.z() < this->minbound.z())
                this->minbound.setZ(pNewTri->minBound.z());
        }
        triList.push_back(pNewTri);
	}

    //Bake Supports as well if that flag is set.
    if(withsupports)
    AddSupportsToBake(true);

    //qDebug() << "Baked instance";
    Disable_User_Waiting_Cursor();
}

//returns number of triangles added
unsigned int ModelInstance::AddSupportsToBake(bool recompBounds)
{
    unsigned int s, t;
    unsigned int trisAdded = 0;
    SupportStructure* pSup;
    Triangle3D* pCurTri;

    for(s = 0; s < supportStructureList.size(); s++)//for each support
    {
        pSup = supportStructureList[s];
        trisAdded += pSup->BakeToInstanceGeometry();
    }

    if(basePlateSupport)
        trisAdded += basePlateSupport->BakeToInstanceGeometry();

    if(recompBounds)
    {
        //since we are adding supports too we need to re-compute instance bounds
        for(t = 0; t < triList.size(); t++)
        {
            pCurTri = triList[t];
            //update the instance bounds.
            if(pCurTri->maxBound.x() > this->maxbound.x())
                this->maxbound.setX(pCurTri->maxBound.x());
            if(pCurTri->maxBound.y() > this->maxbound.y())
                this->maxbound.setY(pCurTri->maxBound.y());
            if(pCurTri->maxBound.z() > this->maxbound.z())
                this->maxbound.setZ(pCurTri->maxBound.z());

            if(pCurTri->minBound.x() < this->minbound.x())
                this->minbound.setX(pCurTri->minBound.x());
            if(pCurTri->minBound.y() < this->minbound.y())
                this->minbound.setY(pCurTri->minBound.y());
            if(pCurTri->minBound.z() < this->minbound.z())
                this->minbound.setZ(pCurTri->minBound.z());
        }
    }

    return trisAdded;
}

void ModelInstance::UnBakeGeometry()
{
    if(!triList.size())
        return;

    for(unsigned long int i=0;i<triList.size();i++)
    {
        delete triList[i];
    }
    triList.clear();
    //qDebug() << "Unbaked instance";
}
void ModelInstance::UpdateBounds()
{
	BakeGeometry();
	UnBakeGeometry();
	//tell the project to update the overal bounds!
    pData->pMain->ProjectData()->UpdateZSpace();
    pData->pMain->UpdateInterface();
}


//Called from slicing routine
void ModelInstance::PrepareForSlicing(double containerThickness)
{
    BakeGeometry(true);
    SortBakedTriangles();
    AllocateTriContainers(containerThickness);
    FillTriContainers();
}
void ModelInstance::FreeFromSlicing()
{
    UnBakeGeometry();
    FreeTriContainers();
}


//sorts the triList in assending altitude and generates and fills containers.
//sliceThickness is needed to determine container size and quantity
void ModelInstance::SortBakedTriangles()
{
    std::sort(triList.begin(),triList.end(), Triangle3D::GreaterBottomAltitude);
}

void ModelInstance::AllocateTriContainers(double containerThickness)
{
    unsigned int i;
    unsigned int numContainers;
    double modelZExtent;
    VerticalTriContainer* newContainer = NULL;
    VerticalTriContainer* prevContainer = NULL;

    modelZExtent = maxbound.z() - minbound.z();
    numContainers = modelZExtent/containerThickness;
    if(numContainers <= 0)
        numContainers = 1;//just in case we have a REALLY thin model.

    containerExtents = modelZExtent/numContainers;

    //now lets start generating containers and linking them
    for( i = 0; i < numContainers; i++ )//bottom -> up
    {
        newContainer = new VerticalTriContainer();

        newContainer->minZ = minbound.z() + containerExtents*i;
        newContainer->maxZ = newContainer->minZ + containerExtents;
        newContainer->downContainer = prevContainer;

        if(prevContainer != NULL)
            prevContainer->upContainer = newContainer;

        prevContainer = newContainer;

        triContainers.push_back(newContainer);
    }

    qDebug() << "num containers created" << triContainers.size();
}

//walk through the sorted triangle list
//and fill the tri containers effieciently
void ModelInstance::FillTriContainers()
{
    unsigned int tIndx;
    VerticalTriContainer* currContainer;
    VerticalTriContainer* iterContainer;
    Triangle3D* currTri;

    qDebug() << "ModelInstance: filling tri containers...";

    currContainer = triContainers[0];

    for(tIndx = 0; tIndx < triList.size(); tIndx++)//bottom -> top
    {
        currTri = triList[tIndx];
        //first move referernce base if needed
        while(!currContainer->TriangleFits(currTri)) //测试当前三角形是否与某一个container相交，如果不相交
        {
            if(currContainer->upContainer == NULL)
            {
                qDebug() << "ERROR: last container exists below model top";

            }
            currContainer = currContainer->upContainer;  //如果不相交，那么这个三角形与在这个container上面的container进行相交判断
        }                                                //一直到找到第一个container的相交
        iterContainer = currContainer;

        while((iterContainer != NULL) && (iterContainer->TriangleFits(currTri)))
        {
            iterContainer->tris.push_back(currTri);
            iterContainer = iterContainer->upContainer;
        }
    }
}

std::vector<Triangle3D*>* ModelInstance::GetTrianglesAroundZ(double zAltitude)
{
    VerticalTriContainer* targetContainer;

    unsigned int indx = int(minbound.z() + zAltitude*containerExtents);
    if(indx <= 0) indx = 0;
    if(indx > triContainers.size()-1)
        indx = triContainers.size()-1;

    targetContainer = triContainers[ indx ];

    //just in case - well double check that this container inclues this zAltitude
    while((targetContainer->upContainer != NULL) && (targetContainer->maxZ < zAltitude))//go up
    {
        targetContainer = targetContainer->upContainer;
    }
    while((targetContainer->downContainer != NULL) && (targetContainer->minZ > zAltitude))//go down
    {
        targetContainer = targetContainer->downContainer;
    }

    return &targetContainer->tris;
}



void ModelInstance::FreeTriContainers()
{
    unsigned int i;
    for(i = 0; i < triContainers.size(); i++)
    {
        delete triContainers[i];
    }
    triContainers.clear();
}


//////////////////////////////////////////////////////////
//Private
///////////////////////////////////////////////////////////

void ModelInstance::CorrectRot(QVector3D &rot)
{
	while (rot.x() < 0)
        rot += QVector3D(360,0,0);
    while (rot.x() >= 360 )
        rot -= QVector3D(360,0,0);

	while (rot.y() < 0)
        rot += QVector3D(0,360,0);
    while (rot.y() >= 360 )
        rot -= QVector3D(0,360,0);

	while (rot.z() < 0)
        rot += QVector3D(0,0,360);
    while (rot.z() >= 360 )
        rot -= QVector3D(0,0,360);
}
void ModelInstance::CorrectScale(QVector3D &scl)
{
    if(scl.x() <= INSTANCE_MIN_SCALE)
        scl.setX(INSTANCE_MIN_SCALE);

    if(scl.y() <= INSTANCE_MIN_SCALE)
        scl.setY(INSTANCE_MIN_SCALE);

    if(scl.z() <= INSTANCE_MIN_SCALE)
        scl.setZ(INSTANCE_MIN_SCALE);
}
