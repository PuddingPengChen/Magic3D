QT       += core gui
QT       += svg
QT       += opengl
QT       += network


RESOURCES += \
    img.qrc

DISTFILES += \
    logo2.ico \
    pynxl.rc \
    SliceEngine/default.cfg \
    SliceEngine/clipper/License.txt \
    SliceEngine/clipper/README

HEADERS += \
    geometric.h \
    OS_Function.h \
    OS_GL.h \
    Interface/cilent.h \
    Interface/configset.h \
    Interface/graph.h \
    Interface/greentech.h \
    Interface/imageviewwidget.h \
    Interface/loadingbar.h \
    Interface/mainbutton.h \
    Interface/modeledit.h \
    Interface/painter.h \
    Interface/printedit.h \
    Interface/worldview.h \
    ModelData/layoutprojectdata.h \
    ModelData/modeldata.h \
    ModelData/modelinstance.h \
    ModelData/modelloader.h \
    ModelData/modelwriter.h \
    ModelData/triangle3d.h \
    ModelData/verticaltricontainer.h \
    SliceEngine/comb.h \
    SliceEngine/fffProcessor.h \
    SliceEngine/INCLUDES.h \
    SliceEngine/layerPart.h \
    SliceEngine/multiVolumes.h \
    SliceEngine/optimizedModel.h \
    SliceEngine/pathOrderOptimizer.h \
    SliceEngine/polygonOptimizer.h \
    SliceEngine/settings.h \
    SliceEngine/sliceDataStorage.h \
    SliceEngine/slicer.h \
    SliceEngine/timeEstimate.h \
    SliceEngine/clipper/clipper.hpp \
    SliceEngine/modelFile/modelFile.h \
    SliceEngine/utils/floatpoint.h \
    SliceEngine/utils/gettime.h \
    SliceEngine/utils/intpoint.h \
    SliceEngine/utils/logoutput.h \
    SliceEngine/utils/polygon.h \
    SliceEngine/utils/polygondebug.h \
    SupportEngine/supportstructure.h \
    SliceEngine/utils/socket.h \
    SliceEngine/bridge.h \
    SliceEngine/gcodeExport.h \
    SliceEngine/includes.h \
    SliceEngine/infill.h \
    SliceEngine/inset.h \
    SliceEngine/raft.h \
    SliceEngine/skin.h \
    SliceEngine/skirt.h \
    SliceEngine/support.h \
    Uart/qextserialbase.h \
    Uart/qextserialenumerator.h \
    Uart/qextserialport.h \
    Uart/win_qextserialport.h

SOURCES += \
    geometric.cpp \
    main.cpp \
    OS_Function.cpp \
    Interface/configset.cpp \
    Interface/graph.cpp \
    Interface/greentech.cpp \
    Interface/imageviewwidget.cpp \
    Interface/loadingbar.cpp \
    Interface/mainbutton.cpp \
    Interface/modeledit.cpp \
    Interface/painter.cpp \
    Interface/printedit.cpp \
    Interface/worldview.cpp \
    ModelData/layoutprojectdata.cpp \
    ModelData/modeldata.cpp \
    ModelData/modelinstance.cpp \
    ModelData/modelloader.cpp \
    ModelData/modelwriter.cpp \
    ModelData/triangle3d.cpp \
    ModelData/verticaltricontainer.cpp \
    SliceEngine/comb.cpp \
    SliceEngine/layerPart.cpp \
    SliceEngine/optimizedModel.cpp \
    SliceEngine/pathOrderOptimizer.cpp \
    SliceEngine/polygonOptimizer.cpp \
    SliceEngine/settings.cpp \
    SliceEngine/slicer.cpp \
    SliceEngine/timeEstimate.cpp \
    SliceEngine/clipper/clipper.cpp \
    SliceEngine/modelFile/modelFile.cpp \
    SliceEngine/utils/gettime.cpp \
    SliceEngine/utils/logoutput.cpp \
    SupportEngine/supportstructure.cpp \
    SliceEngine/utils/socket.cpp \
    SliceEngine/bridge.cpp \
    SliceEngine/gcodeExport.cpp \
    SliceEngine/infill.cpp \
    SliceEngine/inset.cpp \
    SliceEngine/raft.cpp \
    SliceEngine/skin.cpp \
    SliceEngine/skirt.cpp \
    SliceEngine/support.cpp \
    Uart/qextserialbase.cpp \
    Uart/qextserialenumerator.cpp \
    Uart/qextserialport.cpp \
    Uart/win_qextserialport.cpp

FORMS += \
    Interface/configset.ui \
    Interface/greentech.ui \
    Interface/imageviewwidget.ui \
    Interface/mainbutton.ui \
    Interface/modeledit.ui \
    Interface/painter.ui \
    Interface/printedit.ui
RC_FILE = pynxl.rc

