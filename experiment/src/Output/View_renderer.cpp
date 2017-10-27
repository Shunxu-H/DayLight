#include "View_renderer.h"
#include "Extern.h"


View_renderer::View_renderer( const std::shared_ptr<Patronus::Camera> & cam, const std::string & shaderId )
    : View(cam, shaderId)
{

    //QTimer::singleShot(1000, this, SLOT(_checkRendererReady()));
}


void View_renderer::initializeGL() {

}


void View_renderer::paintGL(){

}

