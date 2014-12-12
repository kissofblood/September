#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T02:10:40
#
#-------------------------------------------------

QT       += core gui uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = september
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        septembereditor.cpp \
    widgetstyle.cpp \
    widgetuistyle.cpp \
    searchandreplace.cpp \
    assistant/viewwidgetui.cpp \
    assistant/coreEditor/coreeditor.cpp \
    assistant/coreEditor/highlighter.cpp \
    assistant/graphicswidget.cpp \
    assistant/coreEditor/observercodeqss.cpp \
    assistant/splitter.cpp \
    setting/settingkey.cpp \
    setting/settingseptember.cpp \
    assistant/fileView/listfileview.cpp \
    assistant/fileView/listfilemodel.cpp

HEADERS  += septembereditor.h \
    widgetstyle.h \
    widgetuistyle.h \
    searchandreplace.h \
    assistant/viewwidgetui.h \
    assistant/coreEditor/coreeditor.h \
    assistant/coreEditor/highlighter.h \
    assistant/graphicswidget.h \
    assistant/coreEditor/observercodeqss.h \
    assistant/splitter.h \
    setting/settingkey.h \
    setting/settingseptember.h \
    assistant/fileView/listfileview.h \
    assistant/common.h \
    assistant/fileView/listfilemodel.h

FORMS    += septembereditor.ui \
    widgetstyle.ui \
    widgetuistyle.ui \
    searchandreplace.ui \
    setting/settingkey.ui \
    setting/settingseptember.ui

RESOURCES += \
    qssKeyWords/resource.qrc
