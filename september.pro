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
    graphicswidget.cpp \
    assistant/viewwidgetui.cpp \
    assistant/coreEditor/coreeditor.cpp \
    assistant/coreEditor/highlighter.cpp

HEADERS  += septembereditor.h \
    widgetstyle.h \
    widgetuistyle.h \
    searchandreplace.h \
    graphicswidget.h \
    assistant/viewwidgetui.h \
    keywords.h \
    assistant/coreEditor/coreeditor.h \
    assistant/coreEditor/highlighter.h

FORMS    += septembereditor.ui \
    widgetstyle.ui \
    widgetuistyle.ui \
    searchandreplace.ui

RESOURCES += \
    qssKeyWords/resource.qrc
