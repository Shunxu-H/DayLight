#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include "Vector.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Config.h"
#include "Curve.h"

Config progConfig;
Shader *shader;
WindowManager* winMan;
std::vector<std::shared_ptr<Vector>> vertexBuffer;
std::shared_ptr<Curve> curveBuffer;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    WindowManager winMan(argc, argv, std::string("Ray Tracer"), 500, 500);
    winMan.show();

    return a.exec();
}




