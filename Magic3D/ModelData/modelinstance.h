/*************************************************************************************
//
//  LICENSE INFORMATION
//
//  BCreator(tm)
//  Software for the control of the 3D Printer, "Creator"(tm)
//
//  Copyright 2011-2012 Creations, LLC
//  Creations(tm) and Creator(tm) are trademarks of Creations, LLC
//
//  This file is part of Creator
//
//    Creator is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Creator is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Creator .  If not, see <http://www.gnu.org/licenses/>.
//
//  The above copyright notice and this permission notice shall be
//    included in all copies or substantial portions of the Software.
//
//    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
//    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
//    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
//    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
//    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
*************************************************************************************/

#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H
#include <QVector3D>
#include <QColor>
#include <QListWidget>
#include "triangle3d.h"
#include "modeldata.h"
#include "verticaltricontainer.h"


#define INSTANCE_MIN_SCALE 0.01

class ModelData;
class Triangle3D;
class SupportStructure;

class ModelInstance
{

//friend class ModelData;
public:
    ModelInstance(ModelData* parent);
    ~ModelInstance();
	
	//translation
	void RestOnBuildSpace(); //rests the model as low as possible on the print area.
	void SetPos(QVector3D pos);
	void SetX(double x);
	void SetY(double y);
	void SetZ(double z);
    void SetSupport_Z(double z){support_z = z;}


    void SetColor(QColor color);
    void SetScale(QVector3D scale);
	void SetScaleX(double x);
	void SetScaleY(double y);
	void SetScaleZ(double z);
	void SetRot(QVector3D r);
    void SetFlipped(int flipped);//x-flipping
    void SetSupportBounding(QVector3D r){SupportedBounding = r;}

    //manual bounds sets (no baking)
    void SetBounds(QVector3D newmax, QVector3D newmin);

    //pre-move checking
    bool OnPosChangeRequest(QVector3D deltaPos);
    bool OnScaleChangeRequest(QVector3D deltaScale);
    bool OnRotationChangeRequest(QVector3D deltaRot);

    //post move callbacks
    void OnPosChanged(QVector3D deltaPos);
    void OnScaleChanged(QVector3D deltaScale);
    void OnRotChanged(QVector3D deltaRot);
    void OnRotXOrYChanged(QVector3D deltaRot);
    void OnRotZChangedOnly(QVector3D deltaRot);
	//Incremental
	void Scale(QVector3D scalar);
	void Move(QVector3D translation);
	void Rotate(QVector3D rotation);

	//gets
    double GetSupport_z(){return support_z;}
	QVector3D GetPos();
	QVector3D GetRot();
	QVector3D GetScale();
	QVector3D GetMaxBound();
	QVector3D GetMinBound();
    bool GetFlipped();
    QVector3D GetTriangleLocalPosition(unsigned int tri); // returns the position of the given tri index.
    std::vector<SupportStructure*> GetSupportList(){return supportStructureList;}

	//selection
	void SetTag(QString tag);
	void SetSelected(bool sel);

    //support
    bool IsInSupportMode();
    void SetInSupportMode(bool s);
    std::vector<SupportStructure*> GetSupports();
    SupportStructure* GetBasePlate();
    void EnableBasePlate();
    void DisableBasePlate();
    SupportStructure* AddSupport(QVector3D localTopPosition = QVector3D(), QVector3D localBottomPosition = QVector3D());//adds a support to the local cordinate on the model.
    void RemoveSupport(SupportStructure* sup);
    void RemoveAllSupports();
    void UpdateSupports();
    void RotateSupports(QVector3D deltaRot);
    void ScaleSupportPositionsAroundCenter(QVector3D newScale, QVector3D oldScale);
    void FlipSupports();
    void ShowSupports();
    void HideSupports();

	//render
    void RenderGL(bool disableColor = false);//renders the instance using the modeldata's displaylist with this instances transforms applied
    void RenderSupportsGL(bool solidColor, float topAlpha, float bottomAlpha);//renderes the support shapes.
    void renderSupportGL(SupportStructure* pSup, bool solidColor, float topAlpha, float bottomAlpha);
    void RenderSupportsTipsGL();
    void RenderPickGL();//simple flat rendering with color id
    void RenderTrianglePickGL();//renders all triangles with slightly different colors, - flat shaded for tri picking.
    void RenderSingleTrianglePickGL(unsigned int triIndx);//renders a color coded triangle for precice position picking.
    bool FormTriPickDispLists();
    void FreeTriPickDispLists();

    void DrawBounding();
    //geometry
    void BakeGeometry(bool withsupports = false);//copies triangle data from the model data
    //with applied transforms, also calculates bounds. also copies in support geometry too.
    unsigned int AddSupportsToBake(bool recompBounds);//add support geometry to bake, also updates bounds..
    void UnBakeGeometry();//frees up the triangle data of this model.
	void UpdateBounds();//updates the bounds, this is somewhat time consuming!
    //this triangle list is only full
    //when the instance is in a "baked" state;
    std::vector<Triangle3D*> triList;

    //slicing - these members are called/used in slicing routine ONLY!
    void PrepareForSlicing(double containerThickness);//does all baking, sorting and filling routines
        void SortBakedTriangles();//sorts the triList in assending altitude
        void AllocateTriContainers(double containerThickness); //creates vertical tri containers
        void FillTriContainers();

    std::vector<Triangle3D*>* GetTrianglesAroundZ(double zAltitude);

    void FreeFromSlicing();//unbakes - frees lists
    void FreeTriContainers();
    std::vector<VerticalTriContainer*> triContainers;
    double containerExtents;
	QListWidgetItem* listItem;
	ModelData* pData;
    unsigned char pickcolor[3];//this instances pick color!

    QColor selectedcolor;
    QColor normalcolor;
    QColor currcolor;
    QColor visualcolor;//actual rendering color - is always smoothely running to match currcolor.
private:
    //translation/rotation/scaling
    double support_z;
	QVector3D pos;
	QVector3D rot;
	QVector3D scale;
	QVector3D maxbound;
	QVector3D minbound;
    QVector3D SupportedBounding;
    QVector3D p;
    bool isFlipped;

    void CorrectRot(QVector3D &rot);//puts rotation in 0-360 form
    void CorrectScale(QVector3D& scale);//does not allow 0 or negative values
	//selection
	static unsigned char gColorID[3];
	bool isselected;
    //support
    bool isInSupportMode;
    unsigned int supportCounter;

    //in support editing mode we need a display list for triangle picking.
    std::vector<unsigned int> triPickDispLists;     //在支撑结构模式下，我们需要一个列表来存储被选中的三角面

    //the list of support structures - supports belong to individual instances
    //so there is no sharing
    std::vector<SupportStructure*> supportStructureList;

    //the baseplate support structure;
    SupportStructure* basePlateSupport;
};
#endif
