#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T18:29:42
#
#-------------------------------------------------

QT       += opengl core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

unix{
    LIBS += -lstdc++fs
    LIBS += -lglut -lGL -lGLU
}

TARGET = DayLight
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += GL_GLEXT_PROTOTYPES

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += Include/

SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    Input/Keyboard.cpp \
    Input/Mouse.cpp \
    Internal/Curve.cpp \
    Internal/Edge.cpp \
    Internal/Ellipsoid.cpp \
    Internal/Face.cpp \
    Internal/Geometry.cpp \
    Internal/Line.cpp \
    Internal/Object.cpp \
    Internal/Shader.cpp \
    Internal/Vector.cpp \
    Output/Cabinet.cpp \
    Output/CVM.cpp \
    Output/OrthoView.cpp \
    Output/TextView.cpp \
    Output/View.cpp \
    Utility/AEL.cpp \
    Utility/Color.cpp \
    Utility/Config.cpp \
    Utility/Matrix.cpp \
    Utility/Utility.cpp \
    Output/WindowManager.cpp \
    Internal/Program.cpp \
    Internal/Shaper.cpp \
    Internal/Countable.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    Include/AEL.h \
    Include/Cabinet.h \
    Include/Color.h \
    Include/Config.h \
    Include/Curve.h \
    Include/CVM.h \
    Include/Edge.h \
    Include/Ellipsoid.h \
    Include/Face.h \
    Include/Geometry.h \
    Include/Index.h \
    Include/Keyboard.h \
    Include/Line.h \
    Include/Matrix.h \
    Include/Mouse.h \
    Include/Object.h \
    Include/OrthoView.h \
    Include/Shader.h \
    Include/TextView.h \
    Include/Utility.h \
    Include/Vector.h \
    Include/View.h \
    Include/WindowManager.h \
    Include/Program.h \
    Include/GLObject.h \
    Include/Shaper.h \
    Include/GL_include.h \
    Include/Countable.h

FORMS    += mainwindow.ui \
    windowmanager.ui

DISTFILES += \
    Shader/shader.frag \
    Shader/shader.vert \
    Shader/rotate.NONE \
    GLSL/rotate.NONE \
    GLSL/shader.frag \
    GLSL/shader.vert \
    data/3d.gmt \
    data/cube.obj
