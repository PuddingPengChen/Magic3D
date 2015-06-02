#include <vector>
#include "triangle3d.h"

#define TRICONTAINER_PLAY 0.001

class VerticalTriContainer
{
public:
    VerticalTriContainer();

    double maxZ;
    double minZ;

    VerticalTriContainer* upContainer;
    VerticalTriContainer* downContainer;

    std::vector<Triangle3D*> tris;


    bool TriangleFits(Triangle3D* tri)
    {
        //test if the triangle has any part in the container.
        if((tri->maxBound.z() >= (minZ - TRICONTAINER_PLAY))
          &&
          (tri->minBound.z() <= (maxZ + TRICONTAINER_PLAY)))

           return true;

        return false;
    }

};

