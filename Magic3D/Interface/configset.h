#ifndef CONFIGSET_H
#define CONFIGSET_H
#define GuangI 1024
#define GuangII 1920

#include <QDialog>

namespace Ui {
class ConfigSet;
}

class ConfigSet : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigSet(QWidget *parent = 0);
    ~ConfigSet();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
     int Revolution;
    Ui::ConfigSet *ui;
};

#endif // CONFIGSET_H
