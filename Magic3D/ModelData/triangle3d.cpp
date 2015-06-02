#include "triangle3d.h"
#include "../geometric.h"
#include <QDebug>

Triangle3D::Triangle3D()        //构造函数，这个函数只是对一个三角面进行处理的
{
	int i;
    normal*=0.0;//make the normal 0,0,0     //设置法向量为0

	for(i=0; i < 3; i++)
	{
        vertex[i]*= 0.0;//make the vertex all reside on 0,0,0       //设置向量为0
	}

	maxBound.setX(-99999999.0);
	maxBound.setY(-99999999.0);
	maxBound.setZ(-99999999.0);

	minBound.setX(99999999.0);
	minBound.setY(99999999.0);
	minBound.setZ(99999999.0);

}

Triangle3D::~Triangle3D()
{

}
void Triangle3D::UpdateBounds()         //遍历这个三角面的三个点的坐标，获得物体的大小边界
{
	int i;
	//reset the bounds:
	maxBound.setX(-99999999.0);
	maxBound.setY(-99999999.0);
	maxBound.setZ(-99999999.0);

	minBound.setX(99999999.0);
	minBound.setY(99999999.0);
	minBound.setZ(99999999.0);

	for(i=0; i < 3; i++)
	{
		//max
		if(vertex[i].x() > maxBound.x())
		{
			maxBound.setX(vertex[i].x());
		}
		if(vertex[i].y() > maxBound.y())
		{
			maxBound.setY(vertex[i].y());
		}
		if(vertex[i].z() > maxBound.z())
		{
			maxBound.setZ(vertex[i].z());
		}

		//min
		if(vertex[i].x() < minBound.x())
		{
			minBound.setX(vertex[i].x());
		}
		if(vertex[i].y() < minBound.y())
		{
			minBound.setY(vertex[i].y());
		}
		if(vertex[i].z() < minBound.z())
		{
			minBound.setZ(vertex[i].z());
		}	
	}
}
void Triangle3D::UpdateNormalFromGeom()     //获取发向量？
{
    normal = QVector3D::crossProduct(vertex[1] - vertex[0], vertex[2] - vertex[0]);
    normal.normalize();                     //将这个面的发向量变换成为单位向量
}

bool Triangle3D::IsBad()
{
	double d = Distance3D(maxBound,minBound);
	if(IsZero(d,0.00001))//for possible double error.
	{	
		return true;
	}
	return false;
}

bool Triangle3D::IntersectsXYPlane(double realAltitude)
{
	if(IsBad() || ParallelXYPlane())
	{	
		return false;
	}
	if(maxBound.z() > realAltitude && minBound.z() <= realAltitude)
	{
		return true;
	}

	//the triangle is not in bounds at all:
	return false;
}

bool Triangle3D::ParallelXYPlane()          //判断是否为平行的平面
{
	if((vertex[0].z() == vertex[1].z())&&(vertex[0].z() == vertex[2].z()))
	{
		return true;
	}
	return false;
}
