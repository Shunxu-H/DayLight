#include <QApplication>
#include <vector>
#include <QGLFormat>
#include <QOpenGLContext>
#include <QSurfaceFormat>
#include <QOpenGLFunctions_4_5_Core>
#include "WindowManager.h"
#include "Shader.h"
#include <QDebug>
#include "Program.h"
#include "Shaper.h"
#include "Config.h"
#include "Instance.h"
#include "WindowManager.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicalWorld.h"

#include "Renderer.h"

Config progConfig;
Patronus::Shaper * shaper = nullptr;
Lumos::Program * gProgram = nullptr;
WindowManager * winMan = nullptr;
Patronus::PhysicalWorld * world = nullptr;
Lumos::Instance * selectedInstance = nullptr;
QOpenGLContext * global_glContext = nullptr;
QSurfaceFormat * global_format = nullptr;

void experimental(){
    Renderer paintSurface;
    paintSurface.resize(300, 200);
    paintSurface.render();
    QImage image = paintSurface.grabFramebuffer();
    image.save(QString("image.png"));
}

int main(int argc, char *argv[])
{

    //QApplication::setStyle("plastique");
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    QApplication a(argc, argv);


    //QGLFormat glFormat;
    //glFormat.setVersion(3, 3);
    //glFormat.setProfile(QGLFormat::CoreProfile);

    // Set the default GL format to OpenGL 3.2 Core
    //QGLFormat::setDefaultFormat(glFormat);

    qDebug() << "App path : " << a.applicationDirPath();
    // set up shaper
    world = new Patronus::PhysicalWorld();

    winMan = new WindowManager{};
    winMan->show();

    gProgram = new Lumos::Program( );
    shaper = new Patronus::Shaper("./data/indoor/0004dd3cb11e50530676f77b55262d38.obj");
    Patronus::Camera::loadCamerasFromDir("./data/indoor/camera/");
    gProgram->loadShaders( "/home/shunxu/QtProj/DayLight/GLSL" );
    gProgram->preDrawSetUp();

    /*
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setMajorVersion(4);
    surfaceFormat.setMinorVersion(3);

    QOpenGLContext openGLContext;
    openGLContext.setFormat(surfaceFormat);
    openGLContext.create();
    if(!openGLContext.isValid()) return -1;

    QOffscreenSurface surface;
    surface.setFormat(surfaceFormat);
    surface.create();
    if(!surface.isValid()) return -2;

    openGLContext.makeCurrent(&surface);
*/

    //experimental();


//    GLsizei count;
//    GLuint shaderName[3];
//    glGetAttachedShaders(	gProgram->getObjId(),
//        3,
//        &count,
//        shaderName);


    return a.exec();
}




