#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}


/** Copyright (C) 2013 Ultimaker - Released under terms of the AGPLv3 License */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#if defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/resource.h>
#endif
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


void slice(int argc, char **argv)
{
    FffProcessor::getInstance()->time_keeper.restart();

    FMatrix3x3 transformation; // the transformation applied to a model when loaded

    MeshGroup* meshgroup = new MeshGroup(FffProcessor::getInstance());

    int extruder_train_nr = 0;

    SettingsBase* last_extruder_train = nullptr;
    // extruder defaults cannot be loaded yet cause no json has been parsed
    SettingsBase* last_settings_object = FffProcessor::getInstance();
    for(int argn = 2; argn < argc; argn++)
    {
        char* str = argv[argn];
        if (str[0] == '-')
        {
            if (str[1] == '-')
            {
                if (stringcasecompare(str, "--next") == 0)
                {
                    try {
                        //Catch all exceptions, this prevents the "something went wrong" dialog on windows to pop up on a thrown exception.
                        // Only ClipperLib currently throws exceptions. And only in case that it makes an internal error.
                        log("Loaded from disk in %5.3fs\n", FffProcessor::getInstance()->time_keeper.restart());

                        for (int extruder_nr = 0; extruder_nr < FffProcessor::getInstance()->getSettingAsCount("machine_extruder_count"); extruder_nr++)
                        { // initialize remaining extruder trains and load the defaults
                            meshgroup->createExtruderTrain(extruder_nr); // create new extruder train objects or use already existing ones
                        }

                        meshgroup->finalize();

                        //start slicing
                        FffProcessor::getInstance()->processMeshGroup(meshgroup);

                        // initialize loading of new meshes
                        FffProcessor::getInstance()->time_keeper.restart();
                        delete meshgroup;
                        meshgroup = new MeshGroup(FffProcessor::getInstance());
                        last_extruder_train = meshgroup->createExtruderTrain(0);
                        last_settings_object = meshgroup;

                    }catch(...){
                        cura::logError("Unknown exception\n");
                        exit(1);
                    }
                }else{
                    cura::logError("Unknown option: %s\n", str);
                }
            }else{
                for(str++; *str; str++)
                {
                    switch(*str)
                    {
                    case 'v':
                        cura::increaseVerboseLevel();
                        break;
                    case 'p':
                        cura::enableProgressLogging();
                        break;
                    case 'j':
                        argn++;
                        if (SettingRegistry::getInstance()->loadJSONsettings(argv[argn], last_settings_object))
                        {
                            cura::logError("Failed to load json file: %s\n", argv[argn]);
                            std::exit(1);
                        }
                        break;
                    case 'e':
                        str++;
                        extruder_train_nr = std::strtol(str, &str, 10);
                        str--;
                        last_settings_object = meshgroup->createExtruderTrain(extruder_train_nr);
                        last_extruder_train = last_settings_object;
                        break;
                    case 'l':
                        argn++;

                        log("Loading %s from disk...\n", argv[argn]);

                        transformation = last_settings_object->getSettingAsPointMatrix("mesh_rotation_matrix"); // the transformation applied to a model when loaded

                        if (!last_extruder_train)
                        {
                            last_extruder_train = meshgroup->createExtruderTrain(0); // assume a json has already been provided on the command line
                        }
                        if (!loadMeshIntoMeshGroup(meshgroup, argv[argn], transformation, last_extruder_train))
                        {
                            logError("Failed to load model: %s\n", argv[argn]);
                            std::exit(1);
                        }
                        else
                        {
                            last_settings_object = &(meshgroup->meshes.back()); // pointer is valid until a new object is added, so this is OK
                        }
                        break;
                    case 'o':
                        argn++;
                        if (!FffProcessor::getInstance()->setTargetFile(argv[argn]))
                        {
                            cura::logError("Failed to open %s for output.\n", argv[argn]);
                            exit(1);
                        }
                        break;

                    case 's':
                    {
                        //Parse the given setting and store it.
                        argn++;
                        char* valuePtr = strchr(argv[argn], '=');
                        if (valuePtr)
                        {
                            *valuePtr++ = '\0';

                            last_settings_object->setSetting(argv[argn], valuePtr);
                        }
                    }
                        break;
                    default:
                        cura::logError("Unknown option: %c\n", *str);

                        exit(1);
                        break;
                    }
                }
            }
        }
        else
        {

            cura::logError("Unknown option: %s\n", argv[argn]);

            exit(1);
        }
    }

    int extruder_count = FffProcessor::getInstance()->getSettingAsCount("machine_extruder_count");
    for (extruder_train_nr = 0; extruder_train_nr < extruder_count; extruder_train_nr++)
    { // initialize remaining extruder trains and load the defaults
        meshgroup->createExtruderTrain(extruder_train_nr); // create new extruder train objects or use already existing ones
    }



    //Catch all exceptions, this prevents the "something went wrong" dialog on windows to pop up on a thrown exception.
    // Only ClipperLib currently throws exceptions. And only in case that it makes an internal error.
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

int main(int argc, char **argv)
{
    Progress::init();

    if (argc < 2)
    {
        printf(" argc input errors \n");
        exit(1);
    }

    if (stringcasecompare(argv[1], "slice") == 0)
    {
        slice(argc, argv);
    }

    return 0;
}

