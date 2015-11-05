#ifndef READGCODE_H
#define READGCODE_H
#include <QObject>
#include <QFile>
#include <QTimer>
#include <QTextStream>
class readGcode : public QObject
{
    Q_OBJECT
public:
    explicit readGcode(QObject *parent = 0);
    ~readGcode();
    QString readOneLine();
    void setTargetFile(QString file);
    void reset();
    unsigned int  getTotalLayer();
    unsigned int  getTotalGcmd();
    unsigned int  getTotalTime();
signals:

public slots:

private slots:


private:
    QFile* targetGcode;
    QString printFile;

    QTextStream* in;
    QString currentLine;

    unsigned int layers;
    unsigned int g_cmds;
    unsigned int totaltimes;
};

#endif // READGCODE_H
