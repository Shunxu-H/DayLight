#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include "Vector.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Config.h"
#include "Curve.h"

Config progConfig;
Lumos::Shader *shader;
std::vector<std::shared_ptr<Vector>> vertexBuffer;
std::shared_ptr<Curve> curveBuffer;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Lumos::WindowManager winMan{};
    winMan.show();
    winMan.setUpProgram("/home/shunxu/QtProj/DayLight/GLSL");

    return a.exec();
}




