#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T14:01:50
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += axcontainer
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++11

TARGET = Finite_Element
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        App\mainwindow.cpp \
    App/App_Main_Widget.cpp \
    Dialog/Dialog_ModelInformation.cpp \
    Global/Global_Variable.cpp \
    OpenGL/My_OpenGl.cpp \
    Tools/Led.cpp \
    Dialog/Dialog_SerialPort.cpp \
    Global/Global_Function.cpp \
    Dialog/Dialog_AppSetting.cpp \
    Dialog/Dialog_AppSetting_Pages.cpp \
    OpenGL/Information_OpenGL.cpp \
    Tools/arcball.cpp \
    Other/openmethod.cpp \
    Other/projectname.cpp

HEADERS += \
        App\mainwindow.h \
    Global/Global_Variable.h \
    Global/Global_Function.h \
    App/App_Main_Widget.h \
    Dialog/Dialog_ModelInformation.h \
    OpenGL/My_OpenGl.h \
    Tools/Led.h \
    Dialog/Dialog_SerialPort.h \
    Dialog/Dialog_AppSetting.h \
    Dialog/Dialog_AppSetting_Pages.h \
    OpenGL/Information_OpenGL.h \
    Tools/arcball.h \
    Other/openmethod.h \
    Other/projectname.h

win32: LIBS += -L$$PWD/Lib/freeglut/ -lfreeglut

INCLUDEPATH += $$PWD/Lib/freeglut
DEPENDPATH += $$PWD/Lib/freeglut

RESOURCES += \
    source.qrc

DISTFILES += \
    OpenGL/m_fragmentshader.frag \
    OpenGL/m_vertexshader.vert

win32: LIBS += -L'D:/Visual Leak Detector/lib/Win64/' -lvld

INCLUDEPATH += 'D:/Visual Leak Detector/include'
DEPENDPATH += 'D:/Visual Leak Detector/include'

FORMS += \
    Other/openmethod.ui \
    Other/projectname.ui
