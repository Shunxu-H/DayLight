#include <QApplication>
#include <vector>
#include "Vector.h"
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



Config progConfig;
Patronus::Shaper * shaper = nullptr;
Lumos::Program * gProgram = nullptr;
WindowManager * winMan = nullptr;
Patronus::PhysicalWorld * world = nullptr;
Lumos::Instance * selectedInstance = nullptr;

void experimental(){

}

int main(int argc, char *argv[])
{
    experimental();

    //QApplication::setStyle("plastique");
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    QApplication a(argc, argv);

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
    shaper->getnCamera(0)->render(1280, 720);


//    GLsizei count;
//    GLuint shaderName[3];
//    glGetAttachedShaders(	gProgram->getObjId(),
//        3,
//        &count,
//        shaderName);


    return a.exec();
}




