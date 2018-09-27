#include <QDebug>
#include <QApplication>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <stddef.h>
#include <vector>

#include "src/utils/gettime.h"
#include "src/utils/logoutput.h"
#include "src/utils/string.h"

#include "src/FffProcessor.h"
#include "src/settings/SettingRegistry.h"

#include "src/settings/SettingsToGV.h"

namespace cura
{

void cp_slice(std::string stl_path, std::string gcode_path)
{
    FffProcessor::getInstance()->time_keeper.restart();

    FMatrix3x3 transformation; // the transformation applied to a model when loaded

    MeshGroup* meshgroup = new MeshGroup(FffProcessor::getInstance());

    int extruder_train_nr = 0;

    SettingsBase* last_extruder_train = nullptr;
    // extruder defaults cannot be loaded yet cause no json has been parsed
    SettingsBase* last_settings_object = FffProcessor::getInstance();

    //日志相关
    cura::increaseVerboseLevel();
    cura::enableProgressLogging();

    //装载参数
    std::string file_name = std::string("fdmprinter.def.json");
    if (SettingRegistry::getInstance()->loadJSONsettings(file_name.c_str(), last_settings_object))
    {
        cura::logError("Failed to load json file: %s\n", file_name.c_str());
        std::exit(1);
    }

    //装载模型
    std::string stl_name = stl_path;
    transformation = last_settings_object->getSettingAsPointMatrix("mesh_rotation_matrix");
    if (!last_extruder_train)
    {
        last_extruder_train = meshgroup->createExtruderTrain(0);
    }
    if (!loadMeshIntoMeshGroup(meshgroup, stl_name.c_str(), transformation, last_extruder_train))
    {
        logError("Failed to load model: %s\n", stl_name.c_str());
        std::exit(1);
    }
    else
    {
        last_settings_object = &(meshgroup->meshes.back()); // pointer is valid until a new object is added, so this is OK
    }

    //设置输出函数
    std::string gcode_name = gcode_path;
    if (!FffProcessor::getInstance()->setTargetFile(gcode_name.c_str()))
    {
        cura::logError("Failed to open %s for output.\n", gcode_name.c_str());
        exit(1);
    }

    //设置喷头数量
    int extruder_count = FffProcessor::getInstance()->getSettingAsCount("machine_extruder_count");
    for (extruder_train_nr = 0; extruder_train_nr < extruder_count; extruder_train_nr++)
    {
        meshgroup->createExtruderTrain(extruder_train_nr);
    }

    meshgroup->finalize();
    log("Loaded from disk in %5.3fs\n", FffProcessor::getInstance()->time_keeper.restart());

    //start slicing
    FffProcessor::getInstance()->processMeshGroup(meshgroup);

    //Finalize the processor, this adds the end.gcode. And reports statistics.
    FffProcessor::getInstance()->finalize();

    delete meshgroup;
}


}//namespace cura

using namespace cura;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString inpuut_str;
    QString out_str;

    for(int i=0;i < argc; ++i)
    {
        QString file_str(argv[i]);

        if(file_str.startsWith("-input"))
        {
            inpuut_str = file_str.mid(file_str.indexOf("=")+1);
            qDebug()<<"input file"<<inpuut_str;
        }
        else if(file_str.startsWith("-output"))
        {
            out_str = file_str.mid(file_str.indexOf("=")+1);
            qDebug()<<"out file"<<out_str;

        }

    }
    cp_slice(inpuut_str.toStdString(), out_str.toStdString());
    return 0;

}
