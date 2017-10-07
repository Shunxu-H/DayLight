#-------------------------------------------------
#
# Project created by QtCreator 2017-03-31T18:29:42
#
#-------------------------------------------------

QT      += opengl core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lstdc++fs
CONFIG += std=c++1z
CONFIG += c++14
# CONFIG += -lstdc++fs
unix{
    INCLUDEPATH += /usr/local/include/bullet/
    LIBS += -lBulletDynamics
    LIBS += -lBulletCollision
    LIBS += -lLinearMath
    #INCLUDEPATH += /usr/local/include/bullet/
    #LIBS += -lBulletDynamics -lBulletCollision -lBulletSoftBody -lLinearMath
    LIBS += -lglut -lGL -lGLU
    #PKGCONFIG += bullet
}

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3

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

SOURCES += main.cpp \
    Internal/ArrayBuffer.cpp \
    Internal/Camera.cpp \
    Internal/Countable.cpp \
    Internal/Face.cpp \
    Internal/Instance.cpp \
    Internal/Light.cpp \
    Internal/Mesh.cpp \
    Internal/PhysicalWorld.cpp \
    Internal/Program.cpp \
    Internal/Shader.cpp \
    Internal/Shaper.cpp \
    Internal/Transformable.cpp \
    Output/View.cpp \
    Output/View_bullet.cpp \
    Output/WindowManager.cpp \
    Utility/Color.cpp \
    Utility/Config.cpp \
    Utility/Utility.cpp \
    Internal/btDebugDrawer.cpp \
    Internal/ModelAsset.cpp \
    Internal/OpenGlOffscreenSurface.cpp \
    Output/Renderer.cpp \
    Output/View_renderer.cpp


FORMS    += mainwindow.ui \
    windowmanager.ui

DISTFILES += \
    Shader/shader.frag \
    Shader/shader.vert \
    Shader/rotate.NONE \
    data/3d.gmt \
    data/cube.obj \
    data/teapot.obj \
    GLSL/mask.frag \
    GLSL/mask.vert \
    GLSL/mesh_shader.frag \
    GLSL/mesh_shader.vert \
    GLSL/bbox_shader.frag \
    GLSL/bbox_shader.vert \
    GLSL/multilight_shader.frag \
    GLSL/multilight_shader.vert \
    GLSL/wired_frame_shader.frag \
    GLSL/wired_frame_shader.vert \
    GLSL/depth.frag \
    GLSL/depth.vert \
    data/bed with nightstands.obj \
    data/cube.obj \
    data/Enviroment_GroupTrees.obj \
    data/low-poly-mill.obj \
    data/RUST_3d_Low1.obj \
    data/teapot.obj \
    data/Wood.obj \
    data/3d.gmt \
    data/addFace.gmt \
    data/backup.gmt \
    data/bu.gmt \
    data/bu2.gmt \
    data/p3init.gmt \
    data/temp.gmt \
    data/indoor/main.serialized \
    data/indoor/main.xml \
    data/indoor/main_template_color.xml \
    data/indoor/texture/laminate_1_2.jpg \
    data/indoor/texture/laminate_1_3.jpg \
    data/indoor/texture/laminate_2_1.jpg \
    data/indoor/texture/leather_1_6.jpg \
    data/indoor/texture/leather_1_7.jpg \
    data/indoor/texture/leather_2_2.jpg \
    data/indoor/texture/leather_2_6.jpg \
    data/indoor/texture/leather_3_1.jpg \
    data/indoor/texture/linen_1_1.jpg \
    data/indoor/texture/linen_1_3.jpg \
    data/indoor/texture/linen_1_4.jpg \
    data/indoor/texture/stone_6.jpg \
    data/indoor/texture/stone_7.jpg \
    data/indoor/texture/stucco_1_4.jpg \
    data/indoor/texture/stucco_2_1.jpg \
    data/indoor/texture/textile_1_10.jpg \
    data/indoor/texture/textile_1_3.jpg \
    data/indoor/texture/textile_1_5.jpg \
    data/indoor/texture/textile_1_7.jpg \
    data/indoor/texture/textile_1_8.jpg \
    data/indoor/texture/textile_2_7.jpg \
    data/indoor/texture/textile_3_2.jpg \
    data/indoor/texture/textile_3_6.jpg \
    data/indoor/texture/tile_1_1.jpg \
    data/indoor/texture/tile_2_2.jpg \
    data/indoor/texture/wallp_1_1.jpg \
    data/indoor/texture/wallp_1_2.jpg \
    data/indoor/texture/wallp_22_3.jpg \
    data/indoor/texture/wallp_23_1.jpg \
    data/indoor/texture/wallp_3_1.jpg \
    data/indoor/texture/wood_12.jpg \
    data/indoor/texture/wood_14_5.jpg \
    data/indoor/texture/wood_3.jpg \
    data/indoor/texture/wood_4.jpg \
    data/indoor/texture/wood_6.jpg \
    data/indoor/texture/wood_7.jpg \
    data/indoor/texture/wood_8.jpg \
    data/indoor/texture/wood_9.jpg \
    data/indoor/texture/leaves_16.png \
    data/indoor/texture/laminate_1_2.tx \
    data/indoor/texture/laminate_1_3.tx \
    data/indoor/texture/laminate_2_1.tx \
    data/indoor/texture/leather_1_6.tx \
    data/indoor/texture/leather_1_7.tx \
    data/indoor/texture/leather_2_2.tx \
    data/indoor/texture/leather_2_6.tx \
    data/indoor/texture/leather_3_1.tx \
    data/indoor/texture/leaves_16.tx \
    data/indoor/texture/linen_1_1.tx \
    data/indoor/texture/linen_1_3.tx \
    data/indoor/texture/linen_1_4.tx \
    data/indoor/texture/stone_6.tx \
    data/indoor/texture/stone_7.tx \
    data/indoor/texture/stucco_1_4.tx \
    data/indoor/texture/stucco_2_1.tx \
    data/indoor/texture/textile_1_10.tx \
    data/indoor/texture/textile_1_3.tx \
    data/indoor/texture/textile_1_5.tx \
    data/indoor/texture/textile_1_7.tx \
    data/indoor/texture/textile_1_8.tx \
    data/indoor/texture/textile_2_7.tx \
    data/indoor/texture/textile_3_2.tx \
    data/indoor/texture/textile_3_6.tx \
    data/indoor/texture/tile_1_1.tx \
    data/indoor/texture/tile_2_2.tx \
    data/indoor/texture/wallp_1_1.tx \
    data/indoor/texture/wallp_1_2.tx \
    data/indoor/texture/wallp_22_3.tx \
    data/indoor/texture/wallp_23_1.tx \
    data/indoor/texture/wallp_3_1.tx \
    data/indoor/texture/wood_12.tx \
    data/indoor/texture/wood_14_5.tx \
    data/indoor/texture/wood_3.tx \
    data/indoor/texture/wood_4.tx \
    data/indoor/texture/wood_6.tx \
    data/indoor/texture/wood_7.tx \
    data/indoor/texture/wood_8.tx \
    data/indoor/texture/wood_9.tx \
    data/camera/room_camera.txt \
    data/camera/room_camera_good.txt \
    data/camera/room_camera_name.txt \
    data/camera/room_camera_node.txt \
    data/indoor/camera/room_camera.txt \
    data/indoor/camera/room_camera_good.txt \
    data/indoor/camera/room_camera_name.txt \
    data/indoor/camera/room_camera_node.txt \
    data/indoor/0004dd3cb11e50530676f77b55262d38.mtl \
    GLSL/gen_data.frag \
    GLSL/gen_data.vert

HEADERS += \
    Include/ArrayBuffer.h \
    Include/Cabinet.h \
    Include/Camera.h \
    Include/Color.h \
    Include/Config.h \
    Include/Countable.h \
    Include/Extern.h \
    Include/Face.h \
    Include/GL_include.h \
    Include/GLObject.h \
    Include/Instance.h \
    Include/Keyboard.h \
    Include/Light.h \
    Include/Mesh.h \
    Include/ModelAsset.h \
    Include/obj_loader.h \
    Include/PhysicalWorld.h \
    Include/Program.h \
    Include/Shader.h \
    Include/Shaper.h \
    Include/TextView.h \
    Include/Transformable.h \
    Include/Utility.h \
    Include/View.h \
    Include/View_bullet.h \
    Include/WindowManager.h \
    Include/btDebugDrawer.h \
    Include/tiny_obj_loader.h \
    Include/CImg.h \
    Include/OpenGlOffscreenSurface.h \
    Include/Renderer.h \
    Include/View_renderer.h
