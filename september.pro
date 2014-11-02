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
    viewwidgetui.cpp \
    graphicswidget.cpp

HEADERS  += septembereditor.h \
    widgetstyle.h \
    widgetuistyle.h \
    searchandreplace.h \
    qsskeywords.h \
    viewwidgetui.h \
    graphicswidget.h

FORMS    += septembereditor.ui \
    widgetstyle.ui \
    widgetuistyle.ui \
    searchandreplace.ui
