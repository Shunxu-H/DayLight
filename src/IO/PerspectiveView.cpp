/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <cmath>
#include <experimental/filesystem>
#include <fstream>

#include <Common/GL_include.h>
#include <Common/Utility.h>
#include <Common/Extern.h>

#include <Patronus/PhysicalWorld.h>
#include <Patronus/Shaper.h>
#include <Patronus/Camera.h>

#include <Lumos/Program.h>

#include <IO/PerspectiveView.h>

using namespace Daylight::IO; 

PerspectiveView::PerspectiveView(
        const size_t & x,
        const size_t & y,
        const size_t & w,
        const size_t & h,
        const std::shared_ptr< Patronus::Camera > & cam,
        const std::string & shaderId )
    : View("perspective view", x, y, w, h)
    , _VAO( 0 )
    , _shaderId( shaderId )
{
    if ( cam == nullptr )
        _camInUse = Patronus::Camera::pers;



    //_renderer = new Renderer(this, nullptr, QSize(width(), height()));

    //initializeGL();
}



void PerspectiveView::loadAttribsAndUniform() const{

}

void PerspectiveView::initializeGL(){
    glEnable(GL_DEPTH_TEST);


    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);


    glGenVertexArrays(1, &_VAO);

}


bool PerspectiveView::_keyboard_handle(const KeyboardEvent & xev)
{
    return true;
}

bool PerspectiveView::_cursor_handle(const CursorEvent & cursorEvent)
{
    
    switch (cursorEvent.type) {
        case EVENT_CURSORMOVE:
        {

            float sensitivity = 0.001; 
            _camInUse->panAndPadestal(cursorEvent.data.forMoveEvent.velocity.x*sensitivity, -cursorEvent.data.forMoveEvent.velocity.y*sensitivity ); 
        }
        break; 
        case EVENT_LBUTTONDOWN: // left
        {
            Debug("Button1");
            glm::vec3 out_origin, out_direction;
            getMouseBeam(cursorEvent.loc.x, cursorEvent.loc.y, &out_origin, &out_direction);
            glm::vec3 out_end = out_origin + out_direction*_camInUse->getFarClipDist();
            btVector3 start(out_origin.x, out_origin.y, out_origin.z ), end(out_end.x, out_end.y, out_end.z);

            Lumos::Instance * selected = world->selectWithBean( start, end );
            if (selected){
                _camInUse->setAtGlobal( (selected->getMeshPtr()->getMaxPos() +
                                        selected->getMeshPtr()->getMinPos()) / 2.0f ) ;
                selectedInstance = selected;
            }
            else
            selectedInstance = nullptr;
        }
        break;
        case EVENT_RBUTTONDOWN: // right
        Debug("EVENT_RBUTTONDOWN");
        break;
        case EVENT_MBUTTONDOWN: // middle
        Debug("EVENT_MBUTTONDOWN");
        break;
        case EVENT_CURSORWHEEL:// wheel up
            Debug("EVENT_CURSORWHEEL");
            _camInUse->moveForward(0.1f);
        break;
        case EVENT_CURSORHWHEEL: // wheel down
            Debug("Button5");
            _camInUse->moveForward(-0.1f);
        break;
        default:
        Debug("Unknow button " << cursorEvent.type);
    }


    _expose();
    return true;
}


void PerspectiveView::resizeGL(const size_t & w, const size_t & h){
    _width = w;
    _height = h;
}


void PerspectiveView::getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const{

    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
        ((float)mouseX/(float)_width  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
        ((float)(_height - mouseY)/(float)_height - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
        -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
        1.0f
    );
    glm::vec4 lRayEnd_NDC(
        ((float)mouseX/(float)_width  - 0.5f) * 2.0f,
        ((float)(_height - mouseY)/(float)_height - 0.5f) * 2.0f,
        0.0,
        1.0f
    );

    // Faster way (just one inverse)
    glm::mat4 M = glm::inverse(_camInUse->getProjectionMatrix(
                                    static_cast<float>(_width)/
                                    static_cast<float>(_height)) *
                               _camInUse->getPerspectiveMatrix());

    glm::vec4 lRayStart_world = M * lRayStart_NDC;
    lRayStart_world/=lRayStart_world.w;
    glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ;
    lRayEnd_world  /=lRayEnd_world.w;

    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);
    *start = point3(lRayStart_world);
    *direction = lRayDir_world;

}



void PerspectiveView::paintGL(){

    if( gProgram == nullptr )
        return;
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //shaper->getnCamera(0)->genFrameBuffer(1080, 720);
    gProgram->use();
    glViewport(0, 0, _width, _height);

    // paint selecte instance
    if(selectedInstance != nullptr){
        gProgram->enableShadingPipe(Lumos::Shader::selected_instances_shader_id);

        loadAttribsAndUniform();

        glBindVertexArray(_VAO);

        _camInUse->loadUniforms(_width, _height);
        shaper->loadAttribsAndUniform();
        selectedInstance->renderMesh(nullptr);

        gProgram->disableShadingPipe(Lumos::Shader::selected_instances_shader_id);
    }

    gProgram->enableShadingPipe(_shaderId);

    loadAttribsAndUniform();
    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );

    glBindVertexArray(_VAO);
    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );

    _camInUse->loadUniforms(_width, _height);
    shaper->loadAttribsAndUniform();
    Lumos::Material * materialInUse = nullptr;
    Utils::logOpenGLError( std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) );
    for(Lumos::Instance const * i : world->getInstances()){
        if (i->isVisible())
            i->renderMesh(materialInUse);
    }

    gProgram->disableShadingPipe(_shaderId);

}


void PerspectiveView::fitSphere(const point3 & position, const float & radius){
    float z_y = radius / sin(_camInUse->getFovy()/2.0f),
          z_x = radius / sin( static_cast<float>(_width) /
                               static_cast<float>(_height) /
                               _camInUse->getFovy()/2.0f);
    _camInUse->setTranslate(position + point3(0.0f, 0.0f, std::fmax(z_y, z_x)));
    _camInUse->setAtGlobal(position);
}


// void PerspectiveView::mousePressEvent(QMouseEvent *event){
//     switch(event->button()){
//     case Qt::LeftButton:
//     {
//         glm::vec3 out_origin, out_direction;
//         getMouseBeam(event->pos().x(), event->pos().y(), &out_origin, &out_direction);
//         glm::vec3 out_end = out_origin + out_direction*_camInUse->getFarClipDist();
//         btVector3 start(out_origin.x, out_origin.y, out_origin.z ), end(out_end.x, out_end.y, out_end.z);
//
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
//
//     }
//         break;
//     case Qt::MiddleButton:
//     {
//
//
//         break;
//     }
//     case Qt::RightButton:
//
//         break;
//     default:
//         break;
//     }
//
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
