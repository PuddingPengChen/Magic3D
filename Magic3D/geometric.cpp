#include "geometric.h"
#include "math.h"
#include <algorithm>
#include "qmath.h"
#include <QVector2D>
#include <QVector3D>

//Utility Function implementation
bool IsZero(double number, double tolerance)
{
	if(fabs(number) <= tolerance)
	{
		return true;
	}
	return false;
}

bool PointsShare(QVector2D point1, QVector2D point2, double tolerance)
{
	if(IsZero(point2.x() - point1.x(), tolerance) && IsZero(point2.y() - point1.y(),tolerance))
	{
		return true;
	}
	return false;
}
int PointLineCompare(QVector2D pointm, QVector2D dir, QVector2D quarrypoint)//returns 1 if point is on right, -1 if point is on left
{
	//double MAx = (quarrypoint.x() - pointm.x());
	//double MAy = (quarrypoint.y() - pointm.y());

	double position = (dir.x()*(quarrypoint.y() - pointm.y())) - (dir.y()*(quarrypoint.x() - pointm.x()));
	return -int(ceil(position));
}

double Distance2D(QVector2D point1, QVector2D point2)
{
	return sqrt( pow((point2.x()-point1.x()),2) + pow((point2.y()-point1.y()),2));
}
double Distance3D(QVector3D point1, QVector3D point2)
{
	return sqrt( pow((point2.x()-point1.x()),2) + pow((point2.y()-point1.y()),2) + pow((point2.z()-point1.z()),2));
}

bool VectorComponentsEqual(QVector3D &vec)
{
    if((vec.x() == vec.y()) && vec.x() == vec.z())
        return true;
    return false;
}

//returns the length of the largest compent in the vector.
double VectorMaxComponentLength(QVector3D vec)
{
    double max = -1.0;

    if(abs(vec.x()) > max)
        max = abs(vec.x());
    if(abs(vec.y()) > max)
        max = abs(vec.y());
    if(abs(vec.z()) > max)
        max = abs(vec.z());


    return max;
}

//returns the angle between 2 3dimentional vectors.
double MinAngleBetweenVectors(QVector3D a, QVector3D b)
{
    double dot = QVector3D::dotProduct(a,b);
    if(dot > 1)
        dot = 1;
    if(dot < -1)
        dot = -1;
    return acos(dot);
}
