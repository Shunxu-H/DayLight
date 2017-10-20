#include "View_renderer.h"
#include "Extern.h"
#include <QTimer>


View_renderer::View_renderer(QWidget *parent, const std::shared_ptr<Patronus::Camera> & cam, const std::string & shaderId )
    : View(parent, cam, shaderId)
{

    //QTimer::singleShot(1000, this, SLOT(_checkRendererReady()));
}


void View_renderer::initializeGL() {
    _timer = new QTimer(this);
    qDebug() << connect(_timer, &QTimer::timeout, this, &View_renderer::_checkRendererReady);
    _timer->start(3000);
    View::initializeGL();
}

void View_renderer::mousePressEvent(QMouseEvent *event){

}

void View_renderer::mouseMoveEvent(QMouseEvent *event){

}

void View_renderer::mouseReleaseEvent(QMouseEvent *event){

}

void View_renderer::wheelEvent ( QWheelEvent * event ) {

}

void View_renderer::_checkRendererReady(){
    if(_isReadyToRender){
        winMan->render();
        exit(EXIT_SUCCESS);
    }
}


void View_renderer::paintGL(){
    if( isValid() && gProgram && gProgram->isSet() && _isReadyToRender == false)
        _isReadyToRender = true;

    View::paintGL();
}

