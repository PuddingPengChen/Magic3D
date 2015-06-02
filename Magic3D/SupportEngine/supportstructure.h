#ifndef  SUPPOTATTACHMENTDATA_H
#define SUPPOTATTACHMENTDATA_H

#include <vector>
#include <QVector3D>
#include <QListWidgetItem>
#include "../ModelData/triangle3d.h"


#define SUPPORT_MID_PRINTABLE_ANGLE_RATIO  0.4 //(vertical_difference/mid_length)

class ModelInstance;
class SupportAttachmentData
{
private:
    std::vector<Triangle3D> triList;
    QString name;//the name of the attachment "Simple Cone" for example
    unsigned int dispListIndx;

public:
    SupportAttachmentData();

    ~SupportAttachmentData();
    void CenterGeometry();
    void FormDisplayList();
    bool HasDisplayList(){if(dispListIndx) return true; return false;}
    void Render();//renders the attachment geometry at 0,0 with no rotations of scales.

    //Sets
    void SetName(QString newName){name = newName;}

    //Gets
    std::vector<Triangle3D>* GetTriangles(){return &triList;}
    QString GetName(){return name;}

};
//SupportStructure//
///////////////////////////////////////////////////////////////////////////
//  |
//  |   TOP
//  |
//  +
//  |
//  |
//  |   MID
//  |
//  |
//  +
//  |
//  |   BOTTOM
//  |
//
class SupportStructure
{
public: //enums and static vars
    static std::vector<SupportAttachmentData> AttachmentDataList;
    static void ImportAttachmentDataFromStls();
    static void FillRegistryDefaults( bool reset = false, QString supportWeight = "LIGHT");
    static void FreeAttachmentData(){}
    static unsigned char sColorID[3];

public:
    SupportStructure(ModelInstance* parent = NULL);
    ~SupportStructure();

    void AssignPickId();

    void CopyFrom(SupportStructure* referenceSupport);

    //Get Primary Characteristics
    QVector3D GetTopPoint();
    QVector3D GetTopPivot();
    QVector3D GetBottomPoint();
    QVector3D GetBottomPivot();
    double GetTopRadius();
    double GetMidRadius();
    double GetBottomRadius();
    double GetTopLength();
    double GetMidLength();
    double GetBottomLength();
    QVector3D GetTopNormal();
    QVector3D GetBottomNormal();
    double GetTopAngleFactor();
    double GetBottomAngleFactor();
    double GetTopPenetration();
    double GetBottomPenetration();
    QString GetTopAttachShape();
    QString GetMidAttachShape();
    QString GetBottomAttachShape();
    bool GetIsGrounded();

    bool IsUpsideDown();
    bool IsVertical();
    bool IsUnderground(double &depth);
    bool IsConstricted(double &depthPastContricted);

    //validity checks
    bool IsPrintable();
        bool IsTopPrintable();
            bool IsTopAngleUp();
        bool IsMidPrintable();
        bool IsBottomPrintable();
            bool IsBottomAngleDown();

    bool IsVisible();

    //Set Characteristics
    void SetInstanceParent(ModelInstance* parentInst);
    void SetTopAttachShape(QString shapeName);
    void SetMidAttachShape(QString shapeName);
    void SetBottomAttachShape(QString shapeName);
    void SetTopPoint(QVector3D cord);
    void SetMidRadius(double rad);
    void SetTopRadius(double rad);
    void SetBottomRadius(double rad);
    void SetBottomPoint(QVector3D cord);
    void SetTopNormal(QVector3D normalVector);
    void SetBottomNormal(QVector3D normalVector);
    void SetTopAngleFactor(double factor);
    void SetBottomAngleFactor(double factor);
    void SetTopPenetration(double pen);
    void SetBottomPenetration(double pen);
    void SetTopLength(double len);
    void SetBottomLength(double len);
    void SetIsGrounded(bool grnd);

    void ForceUpdate();//updates all values from source values..

    //rotation
    void Rotate(QVector3D deltaRot);

    //selection
    void SetSelected(bool sel);//enables things like colored rendering

    //rendering
    void RenderUpper(bool disableColor = false, float alpha = 1.0);//must be called with instance transform
    void RenderLower(bool disableColor = false, float alpha = 1.0);//must be called with instance transform

        void RenderTopGL();
        void RenderMidGL();
        void RenderBottomGL();
    void RenderPickGL(bool renderBottom = true, bool renderTop = true);
    void RenderPartPickGL(bool renderBottom = true, bool renderTop = true);//independantly callable rendering function
    void EnableErrorGlow();
    void DisableErrorGlow();
    void DebugRender();
    void SetVisible(bool vis);

    //Baking
    unsigned int BakeToInstanceGeometry();
    std::vector<Triangle3D>* GetTriList();

    int SupportNumber;
    unsigned char pickcolor[3];//pick color is based off static incremented variable.
private:
    ModelInstance* instanceParent;

    //all vectors and values are defined to be in millimeters.
    //they are also defined as being local to the Model Data!.

    //Saved and Source Vars
    QVector3D topPoint;//ie the "top" of the support
    QVector3D bottomPoint;
    double topRadius, midRadius, bottomRadius;
    double length;//overall length of support
    double topLength;
    double bottomLength;
    double topPenetration;
    double bottomPenetration;
    QVector3D topNormal; //normal going outwards from top/bottom hinge
    QVector3D bottomNormal;
    double topAngleFactor; //"percentage" to use real normal.
    double bottomAngleFactor;
    SupportAttachmentData* midAttachShape;
    SupportAttachmentData* bottomAttachShape;
    SupportAttachmentData* topAttachShape;
    bool isGrounded;
    //Computation Helper Vars (can be derived from source vars in ForceUpdate)
    double midLength;
    double topMidExtension;
    QVector3D topMidExtensionPoint;
    double bottomMidExtension;
    QVector3D bottomMidExtensionPoint;
    QVector3D topPivot;
    QVector3D bottomPivot;
    QVector3D topPenetrationPoint;
    QVector3D bottomPenetrationPoint;
    double topThetaX, topThetaZ;
    double midThetaX, midThetaZ;
    double bottomThetaX, bottomThetaZ;
    //selection
    bool isSelected;
    //rendering
    bool isErrorGlowing;
private: //functions
    void ReBuildGeometry();
    bool isVisible;
};
#endif
