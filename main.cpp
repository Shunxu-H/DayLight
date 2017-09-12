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
Patronus::Shaper * shaper;
Lumos::Program * gProgram;
WindowManager * winMan;
Patronus::PhysicalWorld * world;
Lumos::Instance * selectedInstance;

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
    shaper = new Patronus::Shaper("./data/teapot.obj");
    gProgram->loadShaders( "/home/shunxu/QtProj/DayLight/GLSL" );


//    GLsizei count;
//    GLuint shaderName[3];
//    glGetAttachedShaders(	gProgram->getObjId(),
//        3,
//        &count,
//        shaderName);
    gProgram->preDrawSetUp();


    return a.exec();
}




