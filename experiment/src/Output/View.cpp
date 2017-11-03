
#include <cmath>
#include <experimental/filesystem>
#include <fstream>
#include "GL_include.h"
#include "View.h"
#include "Utility.h"
#include "Camera.h"

#include "Extern.h"


View::View(
        const size_t & w,
        const size_t & h,
        const std::shared_ptr< Patronus::Camera > & cam, 
        const std::string & shaderId )
    : _VAO( 0 )
    , _shaderId( shaderId )
    , _width(w)
    , _height(h)
{
    if ( cam == nullptr )
        _camInUse = Patronus::Camera::pers;



    //_renderer = new Renderer(this, nullptr, QSize(width(), height()));

    //initializeGL();
    //QOpenGLWidget::setRenderHint(QPainter::Antialiasing);
}

void View::loadAttribsAndUniform() const{

}

void View::initializeGL(){
    //qDebug() << context() << " " << global_glContext;
    //context()->setShareContext(global_glContext);

    //initializeOpenGLFunctions();
    //renderer->initializeGL();
    //makeCurrent();

    //assert(QOpenGLContext::areSharing(context(), _renderer->context()) );


    glEnable(GL_DEPTH_TEST);


    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);


    glGenVertexArrays(1, &_VAO);




}

void View::resizeGL(const size_t & w, const size_t & h){
    _width = w;
    _height = h;
}


void View::getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const{
/*
    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
        ((float)mouseX/(float)width()  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
        ((float)(height() - mouseY)/(float)height() - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
        -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
        1.0f
    );
    glm::vec4 lRayEnd_NDC(
        ((float)mouseX/(float)width()  - 0.5f) * 2.0f,
        ((float)(height() - mouseY)/(float)height() - 0.5f) * 2.0f,
        0.0,
        1.0f
    );

    // Faster way (just one inverse)
    glm::mat4 M = glm::inverse(_camInUse->getProjectionMatrix( static_cast<float>(width())/static_cast<float>(height()) ) *
                               _camInUse->getPerspectiveMatrix());
    glm::vec4 lRayStart_world = M * lRayStart_NDC;
    lRayStart_world/=lRayStart_world.w;
    glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ;
    lRayEnd_world  /=lRayEnd_world.w;

    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);
    *start = point3(lRayStart_world);
    *direction = lRayDir_world;
*/
}



void View::paintGL(){

    if( gProgram == nullptr )
        return;
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //shaper->getnCamera(0)->genFrameBuffer(1080, 720);
    gProgram->use();
    glViewport(0, 0, _width, _height);

    // if(selectedInstance != nullptr){
    //     gProgram->enableShadingPipe(Lumos::Shader::selected_instances_shader_id);

    //     loadAttribsAndUniform();

    //     glBindVertexArray(_VAO);

    //     _camInUse->loadUniforms(_width, _height);
    //     shaper->loadAttribsAndUniform();
    //     selectedInstance->renderMesh(nullptr);

    //     gProgram->disableShadingPipe(Lumos::Shader::selected_instances_shader_id);
    // }

    gProgram->enableShadingPipe(_shaderId);

    loadAttribsAndUniform();

    glBindVertexArray(_VAO);

    _camInUse->loadUniforms(_width, _height);
    shaper->loadAttribsAndUniform();
    Lumos::Material * materialInUse = nullptr;
    for(Lumos::Instance const * i : world->getInstances()){
        if (i->isOn())
            i->renderMesh(materialInUse);
    }

    gProgram->disableShadingPipe(_shaderId);




}


void View::fitSphere(const point3 & position, const float & radius){
    float z_y = radius / sin(_camInUse->getFovy()/2.0f),
          z_x = radius / sin( static_cast<float>(_width) /
                               static_cast<float>(_height) /
                               _camInUse->getFovy()/2.0f);
    _camInUse->setTranslate(position + point3(0.0f, 0.0f, std::fmax(z_y, z_x)));

}


// void View::mousePressEvent(QMouseEvent *event){
//     switch(event->button()){
//     case Qt::LeftButton:
//     {
//         glm::vec3 out_origin, out_direction;
//         getMouseBeam(event->pos().x(), event->pos().y(), &out_origin, &out_direction);
//         glm::vec3 out_end = out_origin + out_direction*_camInUse->getFarClipDist();
//         btVector3 start(out_origin.x, out_origin.y, out_origin.z ), end(out_end.x, out_end.y, out_end.z);

//         Lumos::Instance * selected = world->selectWithBean( start, end );
//         if (selected){
//             _camInUse->setAtGlobal( (selected->getMeshPtr()->getMaxPos() +
//                                    selected->getMeshPtr()->getMinPos()) / 2.0f ) ;
//             selectedInstance = selected;
//             //qDebug() << selected->getMeshPtr()->getMaxPos().x << selected->getMeshPtr()->getMaxPos().y << selected->getMeshPtr()->getMaxPos().z << "\n"
//             //         << selected->getMeshPtr()->getMinPos().x << selected->getMeshPtr()->getMinPos().y << selected->getMeshPtr()->getMinPos().z << "\n"
//             //         ;
//         }
//         else
//             selectedInstance = nullptr;

//     }
//         break;
//     case Qt::MiddleButton:
//     {
        
//         float rgba[4]
//                , depth_z = 0.0f;
//         glReadPixels(event->pos().x(), height() - event->pos().y(), 1, 1, GL_RGBA, GL_FLOAT, rgba);
//         std::cout << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3] <<std::endl;;

//         toImageFile_color( "color.png");
//         toImageFile_depth( "depth.png");


//         break;
//     }
//     case Qt::RightButton:

//         break;
//     default:
//         break;
//     }

//     _prevMousePos = event->pos();
//     winMan->updateAllViews();
// }



// void View::mouseMoveEvent(QMouseEvent *event){
//     //qDebug() << event->pos();
//     QPoint diff = _prevMousePos - event->pos();

//     switch(progConfig.opMode){


//     case NAVIGATING:
//         switch(event->buttons()){
//         case Qt::LeftButton:
//             _camInUse->rotateAroundFocus(static_cast<float>(diff.x())/100.0f,
//                                       static_cast<float>(diff.y())/100.0f
//                                       );
//             //_camInUse->setAtGlobal(point3(0, 0, 0));
//             break;
//         case Qt::MiddleButton:
//             _camInUse->panAndPadestal(static_cast<float>(diff.x())/100.0f,
//                                       -static_cast<float>(diff.y())/100.0f
//                                       );


//             break;
//         case Qt::RightButton:

//             break;
//         }
//         break;

//     }
//     _prevMousePos = event->pos();

//     winMan->updateAllViews();
// }

// void View::mouseReleaseEvent(QMouseEvent *event){

// }

// void View::wheelEvent ( QWheelEvent * event ){
//     //qDebug() << _camInUse->getPos().x << " " << _camInUse->getPos().y << " " << _camInUse->getPos().z << " " ;
//     bool isUp = event->angleDelta().y() > 0? true : false;
//     if ( isUp )
//         _camInUse->moveForward(0.1f);
//     else
//         _camInUse->moveForward(-0.1f);

//     winMan->updateAllViews();
// }
