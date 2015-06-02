#include "modelloader.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>




//USAGE: create a modelloader object and if readyread returns true, begin using loadnexttri()
ModelLoader::ModelLoader( QString filename, bool &readyRead, QObject *parent) :
    QObject(parent)
{   
    qDebug() << "3GreenTech: Initializing..";
    this->byteCount = 0;
    this->triCount = 0;
    this->lastError = "";
    this->lastpercent = 0.0;
    QFileInfo info(filename);

    fileType = DetermineFileType(filename, readyRead);

    if(readyRead == false)//it could be possible that the file couldnt even be opened.
        return;

    if(fileType == "BIN_STL")
    {
        PrepareSTLForReading(filename,readyRead);
    }
    else if(fileType == "ASCII_STL")
    {
        PrepareSTLForReading(filename,readyRead);
    }
    else if(fileType == "UNCOMPRESSED_AMF")
    {

    }
}

ModelLoader::~ModelLoader()
{
    binfile.close();
    asciifile.close();
}

QString ModelLoader::DetermineFileType(QString filename, bool &readyRead)
{
    QFileInfo info(filename);
    QString suffix = info.suffix();
    QFile parsefile(filename);
    QTextStream parseStream(&parsefile);
    QString asciiTest;
    unsigned int i = 0;


    if(suffix.toLower() == "stl")
    {
        //see if wee can open the file
        if(!parsefile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            lastError = "Unable to open file:" + filename;
            qDebug() << "3GreenTech: Unable to open file: " << filename;
            readyRead = false;
            return "";
        }

        //we can get the byte count right away
        byteCount = parsefile.size();

        //now determine if the Stl is binary or ascii
        while(i < 50)
        {
            parseStream >> asciiTest;
            if(asciiTest.toLower().trimmed() == "facet")
            {
                parsefile.close();
                qDebug() << "3GreenTech: the file is an ascii stl";
                readyRead = true;
                return "ASCII_STL";
            }
            i++;
        }
        //if we didnt find the string "facet within 50 words, assum its a bin.
        qDebug() << "3GreenTech: the file is a binary stl";
        readyRead = true;
        parsefile.close();
        return "BIN_STL";
    }
    else if(suffix.toLower() == "amf")
    {

        readyRead = false;//TODO AMF NOT IMPLEMENTED...
        return "UNCOMPRESSED_AMF";
    }

    return "";
}

void ModelLoader::PrepareSTLForReading(QString filename, bool &readyRead)
{
    QString buff;
    unsigned int i = 0;
    unsigned int pos;


    if(fileType == "ASCII_STL")//ascii
    {
        //prepare the ascii file for reading.
        asciifile.setFileName(filename);
        asciifile.open(QIODevice::ReadOnly | QIODevice::Text);
        asciiStream.setDevice(&asciifile);
        //we need to get the asciistream in the position
        //where it is about to read the first "facet" word
        while(i < 50)
        {
            pos = asciiStream.pos();
            asciiStream >> buff;
            if(buff.toLower().trimmed() == "facet")
            {
                asciiStream.seek(pos);//reverse to before we read facet.
                readyRead = true;
                return;
            }
            i++;
        }
        lastError = "No facet string found in stl file.";
        qDebug() << "3GreenTech: No facet string found in stl file.";
        readyRead = false;
    }
    else if(fileType == "BIN_STL")//binary
    {
        //Prepare the binay file for reading
        binfile.setFileName(filename);
        binfile.open(QIODevice::ReadOnly);
        //get information from the header.
        if(ReadBinHeader())
        {
            //make sure triangle count matches size of file etc.
            if(CheckBinFileValidity())
            {
                readyRead = true;
            }
            else
            {
                lastError = "Incomplete or non-standard file";
                qDebug() << "3GreenTech: Incomplete or non-standard file.";
                readyRead = false;
            }
        }
        else
        {
            lastError = "Error reading binary file header.";
            qDebug() << "3GreenTech: Error reading binary file header.";
            readyRead = false;
        }
    }
    else
    {
        qDebug() << "3GreenTechLoader: File Type Confusion";
        readyRead = false;
    }
}



bool ModelLoader::ReadBinHeader()
{
    int triCountSuccess;
    binfile.seek(80);//skip header
    triCountSuccess = binfile.read((char *)&triCount,4);

    if(triCountSuccess == 4){
        qDebug() << "3GreenTech: binary header triangle count: " << triCount;
        return true;
    }
    else
    {
        qDebug() << "3GreenTech: error reading binary header triangle count";
        return false;
    }
}


bool ModelLoader::CheckBinFileValidity()
{
    //each facet should be 50bytes, with a header and facet count of 84 bytes.
    if(byteCount >= (triCount*50 + 84))
        return true;
    else
        return false;
}


//returns a pointer to the next triangle loaded,
//the user must delete pointer when done!
bool ModelLoader::LoadNextTri(STLTri* &tri, bool &errorFlag)
{

    STLTri* pNewTri;
    QString buff;
    unsigned int bytesRead;


    //if ascii
    if(fileType == "ASCII_STL")
    {
        asciiStream >> buff;//eat facet
        if(buff == "endsolid" || asciiStream.atEnd())
        {
            tri = NULL;
            errorFlag = false;
            return false;
        }
        pNewTri = new(std::nothrow) STLTri;
        if(pNewTri == NULL)
        {
            qDebug() << "3GreenTech: Not Enough Memory to allocate new triange";
            errorFlag = true;
            lastError = "Not Enough Memory to allocate new triange";
            return false;
        }

        //skip "normal"
        asciiStream >> buff;
        asciiStream >> pNewTri->nx;
        asciiStream >> pNewTri->ny;
        asciiStream >> pNewTri->nz;
        asciiStream.skipWhiteSpace();

        asciiStream >> buff; //skip "outer"
        asciiStream >> buff;//skip "loop"
        asciiStream.skipWhiteSpace();
        asciiStream >> buff;//eat "vertex"
        asciiStream >> pNewTri->x0;
        asciiStream >> pNewTri->y0;
        asciiStream >> pNewTri->z0;
        asciiStream.skipWhiteSpace();
        asciiStream >> buff;//eat "vertex"
        asciiStream >> pNewTri->x1;
        asciiStream >> pNewTri->y1;
        asciiStream >> pNewTri->z1;
        asciiStream.skipWhiteSpace();
        asciiStream >> buff;//eat "vertex"
        asciiStream >> pNewTri->x2;
        asciiStream >> pNewTri->y2;
        asciiStream >> pNewTri->z2;
        asciiStream.skipWhiteSpace();
        asciiStream >> buff;//eat endloop
        asciiStream.skipWhiteSpace();
        asciiStream >> buff;//eat endfacet
        asciiStream.skipWhiteSpace();


        tri = pNewTri;



    }
    else if(fileType == "BIN_STL")//read triangle from binary file.
    {
        bytesRead = 0;

        if(binfile.atEnd())
        {
            tri = NULL;
            errorFlag = false;
            return false;
        }
        pNewTri = new(std::nothrow) STLTri;
        if(pNewTri == NULL)
        {
            qDebug() << "3GreenTech: Not Enough Memory to allocate new triange";
            lastError = "Not Enough Memory to allocate new triange";
            errorFlag = true;
            return false;
        }

        bytesRead += binfile.read((char *)&pNewTri->nx,4);
        bytesRead += binfile.read((char *)&pNewTri->ny,4);
        bytesRead += binfile.read((char *)&pNewTri->nz,4);

        bytesRead += binfile.read((char *)&pNewTri->x0,4);
        bytesRead += binfile.read((char *)&pNewTri->y0,4);
        bytesRead += binfile.read((char *)&pNewTri->z0,4);
        bytesRead += binfile.read((char *)&pNewTri->x1,4);
        bytesRead += binfile.read((char *)&pNewTri->y1,4);
        bytesRead += binfile.read((char *)&pNewTri->z1,4);
        bytesRead += binfile.read((char *)&pNewTri->x2,4);
        bytesRead += binfile.read((char *)&pNewTri->y2,4);
        bytesRead += binfile.read((char *)&pNewTri->z2,4);



        //skip attribute byte count;
        binfile.seek(binfile.pos()+ 2);

        if(bytesRead != 48)
        {
            qDebug() << "3GreenTech: end of file before triangle done reading";
            tri = NULL;
            errorFlag = true;
            return false;
        }
        tri = pNewTri;
    }
    else
    {
        //amf....
    }


    //only send signal for progress bar on the 1%, 2%, 3%, etc
    float t = GetPercentDone();
    if(t > (lastpercent + 0.01))
    {
        lastpercent = t;
        emit PercentCompletedUpdate(100.0*lastpercent,100);
        QCoreApplication::processEvents();

    }




    errorFlag = false;
    return true;
}

float ModelLoader::GetPercentDone()
{

    if(fileType == "ASCII_STL")
    {
        return float(asciifile.pos())/ byteCount;
    }
    else if(fileType == "BIN_STL")
    {
        return float(binfile.pos())/ byteCount;
    }
    else
    {
        //amf percentage
    }

    return 0.0;
}








