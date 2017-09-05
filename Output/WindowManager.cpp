
#include <string>
#include <QDesktopWidget>
#include <QDockWidget>
#include <experimental/filesystem>
#include "GL_include.h"
#include "WindowManager.h"
#include "View.h"
#include "Shader.h"

extern Config progConfig;


namespace Lumos {


int MARGIN = 20;

WindowManager::WindowManager(QWidget *parent)
    :QMainWindow(parent)
     //ui(new Ui::WindowManager)
{

    // Initialize Ui
    //ui->setupUi(this);
    resize( INITIAL_WIN_SIZE[0], INITIAL_WIN_SIZE[1] );


    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
    dock->setWidget(new View(dock));
    //dock->setWidget(new OGLWidget());
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    // load Object
    // shader.loadFile();

}


WindowManager::~WindowManager(){


}

}


