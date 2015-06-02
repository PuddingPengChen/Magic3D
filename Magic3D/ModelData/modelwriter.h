#ifndef MODELWRITER_H
#define MODELWRITER_H

#include <QObject>
#include <QFile>
#include <QDataStream>

//Usage: create a ModelWriter object with filename and if readyWrite is true,
//begin feeding triangles in using WriteNextTri();
//when finished use Finalize();


class Triangle3D;
class ModelWriter : public QObject
{
    Q_OBJECT
public:

    explicit ModelWriter(QString filename, bool &readyWrite, QObject *parent = 0);
    ~ModelWriter();


signals:

    //void PercentCompletedUpdate(qint64 frac, qint64 total);

public:
    void WriteNextTri(Triangle3D* pTri);
    void Finalize();//goes back to the begining of the file and writes tri count. etc

private:
    QFile binOUT;
    QDataStream binStream;
    unsigned long int triCount;

    void WriteHeader(quint32 triCount);


};

#endif // MODELWRITER_H
