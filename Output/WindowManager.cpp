#include <QtWidgets>
#include <experimental/filesystem>
#include <iostream>
#include <ctime>
#include "GL_include.h"
#include "WindowManager.h"
#include "View.h"
#include "View_bullet.h"
#include "Shader.h"
#include "Renderer.h"
#include "View_renderer.h"
#include "Utility.h"
#include "Extern.h"






WindowManager::WindowManager(QWidget *parent)
    :QMainWindow(parent)
     //ui(new Ui::WindowManager)
{

    QDockWidget *canvas_dock_left = new QDockWidget(tr("Canvas"), this);
    View * leftView = new View(canvas_dock_left);
    canvas_dock_left->setWidget(leftView);
    addDockWidget(Qt::LeftDockWidgetArea, canvas_dock_left);
    _views.push_back(leftView);


/*
    QDockWidget *canvas_dock_right_up = new QDockWidget(tr("Canvas"), this);
    View * rightView_up = new View_bullet( canvas_dock_right_up);
    //_render_hidden_view = new View_renderer(this);
    canvas_dock_right_up->setWidget(rightView_up);
    addDockWidget( Qt::TopDockWidgetArea, canvas_dock_right_up);
    //_views.push_back(rightView);
*/
    QDockWidget *canvas_dock_right_down = new QDockWidget(tr("Canvas"), this);
    //View * rightView_down = new View_bullet( canvas_dock_right_down );
    _render_hidden_view = new View_renderer(this);
    canvas_dock_right_down->setWidget(_render_hidden_view);
    //dock->setWidget(new OGLWidget());
    addDockWidget( Qt::RightDockWidgetArea, canvas_dock_right_down);
    //_views.push_back(rightView);


    _createActions();
    _createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("DayLight"));
    setMinimumSize(160, 160);
    resize(1080, 720);
    //_render_hidden_view = new View(this);





}

void WindowManager::keyPressEvent(QKeyEvent *event)
{
    std::cout << "You Pressed Key " <<(char) event->key() << std::endl;
    switch(event->key()){
        case 'R':
        double duration;
        int w = 1080, h = 720;
        clock_t start = std::clock();


        world->clearAll();
        shaper->clearAll();

        /** iterate from here **/
        shaper->loadFile("./data/indoor/0004dd3cb11e50530676f77b55262d38.obj");
        Patronus::Camera::loadCamerasFromDir("./data/indoor/camera/");
        gProgram->preDrawSetUp();

        Utils::cleanAndMkdir("./" + shaper->getCurFileName());

        for( size_t camPtr = 0; camPtr < shaper->getNumOfCameras(); camPtr++){
            _render_hidden_view->setCamInUse(shaper->getnCamera(camPtr));
            _render_hidden_view->resize(w, h);
            _render_hidden_view->generateData();
        }

        world->clearAll();
        shaper->clearAll();

        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

        qDebug() << "Time passed: " << duration;

        /** iterate to here **/

        /*
            if( !_renderer ){

                _renderer = new Renderer( nullptr, QSize(1, 1), nullptr);

                _renderer->setFormat(_views[0]->format());
                //_renderer->setScreen(_views[0]->acceptDrops());
                _renderer->create();
            }
            _renderer->resize(1080, 720);
            _renderer->render();

            QImage image = _renderer->grabFramebuffer();
            image.save(QString("image.png"));
            // draw hidden view
            _render_hidden_view->resize(1080, 720);
            _render_hidden_view->update();
            QImage image2 = _render_hidden_view->grabFramebuffer();
            image2.save(QString("image2.png"));
*/
        break;
    }
}



void WindowManager::keyReleaseEvent(QKeyEvent *event)
{
    //std::cout << "You Release Key " << event->key() << std::endl;
}


void WindowManager::updateAllViews(){
    for(View* & v : _views )
        v->update();
}


void WindowManager::positionAllViewsToFitAllInstances(){
    // compute bounding circle
    point3 position;
    float radius;
    Patronus::Shaper::getBoundingSphere(Patronus::Shaper::global_vertices, &position, &radius);

    for( View * v: _views )
        v->fitSphere(position, radius);

}

void WindowManager::_createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, &QAction::triggered, this, &WindowManager::newFile);
    //alignmentGroup = new QActionGroup(this);
    //alignmentGroup->addAction(leftAlignAct);
    //alignmentGroup->addAction(rightAlignAct);
    //alignmentGroup->addAction(justifyAct);
    //alignmentGroup->addAction(centerAct);
    //leftAlignAct->setChecked(true);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, &QAction::triggered, this, &WindowManager::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Open);
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, &QAction::triggered, this, &WindowManager::save);


    printAct = new QAction(tr("&Print"), this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip(tr("Print a file"));
    connect(printAct, &QAction::triggered, this, &WindowManager::print);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Quit"));
    connect(exitAct, &QAction::triggered, this, &WindowManager::exit);


    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last action"));
    connect(undoAct, &QAction::triggered, this, &WindowManager::undo);


    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    connect(redoAct, &QAction::triggered, this, &WindowManager::redo);

    cutAct = new QAction(tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut"));
    connect(cutAct, &QAction::triggered, this, &WindowManager::cut);

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy selected object"));
    connect(copyAct, &QAction::triggered, this, &WindowManager::copy);


    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste copied object"));
    connect(pasteAct, &QAction::triggered, this, &WindowManager::paste);


    // for views
    showCameraOulinerAct = new QAction(tr("&Ouliner"), this);
    //pasteAct->setShortcuts(QKeySequence::Paste);
    showCameraOulinerAct->setStatusTip(tr("Open Camera Ouliner Window"));
    connect(showCameraOulinerAct, &QAction::triggered, this, &WindowManager::showCameraOuliner);



    aboutAct = new QAction(tr("&About"), this);
    //aboutAct->setShortcuts(QKeySequence::Copy);
    aboutAct->setStatusTip(tr("About this software"));
    connect(aboutAct, &QAction::triggered, this, &WindowManager::about);


}

void WindowManager::_createMenus()
{
    menuBar()->setNativeMenuBar(false);
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(showCameraOulinerAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);



    //qDebug() << menuBar()->isVisible();

    /*
    helpMenu->addAction(aboutQtAct);
    formatMenu = editMenu->addMenu(tr("&Format"));
    formatMenu->addAction(boldAct);
    formatMenu->addAction(italicAct);
    formatMenu->addSeparator()->setText(tr("Alignment"));
    formatMenu->addAction(leftAlignAct);
    formatMenu->addAction(rightAlignAct);
    formatMenu->addAction(justifyAct);
    formatMenu->addAction(centerAct);
    formatMenu->addSeparator();
    formatMenu->addAction(setLineSpacingAct);
    formatMenu->addAction(setParagraphSpacingAct);
    */
}

#ifndef QT_NO_CONTEXTMENU
void WindowManager::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

WindowManager::~WindowManager(){


}

void WindowManager::newFile(){

}

void WindowManager::open(){

}

void WindowManager::save(){

}

void WindowManager::print(){

}

void WindowManager::undo(){

}

void WindowManager::redo(){

}

void WindowManager::cut(){

}

void WindowManager::copy(){

}

void WindowManager::paste(){

}

void WindowManager::bold(){

}

void WindowManager::italic(){

}

void WindowManager::leftAlign(){

}

void WindowManager::rightAlign(){

}

void WindowManager::justify(){

}

void WindowManager::center(){

}

void WindowManager::setLineSpacing(){

}

void WindowManager::setParagraphSpacing(){

}

void WindowManager::about(){

}

void WindowManager::aboutQt(){

}

void WindowManager::exit(){
    std::exit(EXIT_SUCCESS);
}

void WindowManager::showCameraOuliner(){

}



