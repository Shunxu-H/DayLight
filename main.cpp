#include "mainwindow.h"
#include <QApplication>
#include "WindowManager.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    WindowManager winMan(argc, argv, nullptr, "title", 500, 500);
    winMan.show();

    return a.exec();
}




