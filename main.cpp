#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include "Vector.h"
#include "WindowManager.h"
#include "Shader.h"
#include <QDebug>
#include "Program.h"
#include "Shaper.h"
#include "Config.h"
#include "Curve.h"

Config progConfig;
Patronus::Shaper shaper("./data/cube.obj");
Lumos::Program * gProgram;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    qDebug() << "App path : " << a.applicationDirPath();
    // set up shaper



    Lumos::WindowManager winMan{};
    winMan.show();
    gProgram = new Lumos::Program( Lumos::Shader::readFromFiles("/home/shunxu/QtProj/DayLight/GLSL") );


    GLsizei count;
    GLuint shaderName[3];
    glGetAttachedShaders(	gProgram->getObjId(),
        3,
        &count,
        shaderName);
    gProgram->preDrawSetUp();


    return a.exec();
}




