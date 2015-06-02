#include "modelwriter.h"
#include "triangle3d.h"
#include <QDebug>

ModelWriter::ModelWriter(QString filename, bool &readyWrite, QObject *parent) :
    QObject(parent)
{
    triCount = 0;


    binOUT.setFileName(filename);
    readyWrite = binOUT.open(QIODevice::WriteOnly | QIODevice::Truncate);

    if(readyWrite)
    {
        binStream.setDevice(&binOUT);
        binStream.setByteOrder(QDataStream::LittleEndian);
        WriteHeader(0);//initially but zero triangles in the header.
    }
}


ModelWriter::~ModelWriter()
{
    if(binOUT.isOpen())
        binOUT.close();
}



void ModelWriter::WriteHeader(quint32 triCount)
{
    unsigned int i;
    quint8 emptyByte1 = 'B';
    quint8 emptyByte2 = '9';

    //write 80byte header
    for(i = 0; i < 80; i++)
    {
        if(i%2)
            binStream << emptyByte1;
        else
            binStream << emptyByte2;
    }

    binStream << quint32(triCount);
}

void ModelWriter::WriteNextTri(Triangle3D* pTri)
{
    float nx = pTri->normal.x();
    float ny = pTri->normal.y();
    float nz = pTri->normal.z();

    float x0 = pTri->vertex[0].x();
    float y0 = pTri->vertex[0].y();
    float z0 = pTri->vertex[0].z();

    float x1 = pTri->vertex[1].x();
    float y1 = pTri->vertex[1].y();
    float z1 = pTri->vertex[1].z();

    float x2 = pTri->vertex[2].x();
    float y2 = pTri->vertex[2].y();
    float z2 = pTri->vertex[2].z();


    binOUT.write((char*)&nx,4);
    binOUT.write((char*)&ny,4);
    binOUT.write((char*)&nz,4);
    binOUT.write((char*)&x0,4);
    binOUT.write((char*)&y0,4);
    binOUT.write((char*)&z0,4);
    binOUT.write((char*)&x1,4);
    binOUT.write((char*)&y1,4);
    binOUT.write((char*)&z1,4);
    binOUT.write((char*)&x2,4);
    binOUT.write((char*)&y2,4);
    binOUT.write((char*)&z2,4);

    //atribute byte count (not used by most software)
    binStream << quint16(0);

    triCount++;
}


void ModelWriter::Finalize()
{
    binOUT.seek(80);
    binStream << quint32(triCount);

}




















