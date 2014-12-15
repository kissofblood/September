#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T02:10:40
#
#-------------------------------------------------

QT       += core gui uitools printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = september
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        septembereditor.cpp \
    widgetstyle.cpp \
    widgetuistyle.cpp \
    searchandreplace.cpp \
    src/viewwidgetui.cpp \
    src/coreEditor/coreeditor.cpp \
    src/coreEditor/highlighter.cpp \
    src/graphicswidget.cpp \
    src/coreEditor/observercodeqss.cpp \
    src/splitter.cpp \
    setting/settingkey.cpp \
    setting/settingseptember.cpp \
    src/fileView/listfileview.cpp \
    src/fileView/listfilemodel.cpp

HEADERS  += septembereditor.h \
    widgetstyle.h \
    widgetuistyle.h \
    searchandreplace.h \
    src/viewwidgetui.h \
    src/coreEditor/coreeditor.h \
    src/coreEditor/highlighter.h \
    src/graphicswidget.h \
    src/coreEditor/observercodeqss.h \
    src/splitter.h \
    setting/settingkey.h \
    setting/settingseptember.h \
    src/fileView/listfileview.h \
    src/common.h \
    src/fileView/listfilemodel.h

FORMS    += septembereditor.ui \
    widgetstyle.ui \
    widgetuistyle.ui \
    searchandreplace.ui \
    setting/settingkey.ui \
    setting/settingseptember.ui

RESOURCES += \
    qssKeyWords/resource.qrc
