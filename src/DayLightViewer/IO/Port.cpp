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

#include <DayLightViewer/IO/Port.h>
#include <DayLightViewer/Canvas.h>

using namespace DayLight::IO; 

Port::Port(
        const size_t & w,
        const size_t & h,
        const std::shared_ptr< Patronus::Camera > & cam,
        const std::string & shaderId )
    : _VAO( 0 )
    , _shaderId( shaderId )
    , _width(w)
    , _height(h)
    , _isExposed(false)
{
    if ( cam == nullptr )
        _camInUse = Patronus::Camera::pers;
    
}



void Port::loadAttribsAndUniform() const{

}

void Port::initialize(){
    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);


    glGenVertexArrays(1, &_VAO);

}


void Port::cursorPosHandle(GLFWwindow *, double, double){

}

void Port::cursorScrollHandle (GLFWwindow * window, double xoffset, double yoffset){
    std::cout << ( std::to_string(_camInUse->getTranslate().x) + " " + std::to_string(_camInUse->getTranslate().y) + " " + std::to_string(_camInUse->getTranslate().z) ) << std::endl; 
    _camInUse->moveForward(yoffset*0.1f);
}

// bool PerspectiveView::_button_handle(const XEvent & xev)
// {
//     if (xev.xbutton.type == ButtonPress)
//     {
//         Debug( "PerpectiveView Buton presses at " << xev.xbutton.x << ", "
//                   << xev.xbutton.y  );
//         switch (xev.xbutton.button) {
//           case Button1: // left
//           {
//               Debug("Button1");
//               glm::vec3 out_origin, out_direction;
//               getMouseBeam(xev.xbutton.x, xev.xbutton.y, &out_origin, &out_direction);
//               glm::vec3 out_end = out_origin + out_direction*_camInUse->getFarClipDist();
//               btVector3 start(out_origin.x, out_origin.y, out_origin.z ), end(out_end.x, out_end.y, out_end.z);

//               Lumos::Instance * selected = world->selectWithBean( start, end );
//               if (selected){
//                   _camInUse->setAtGlobal( (selected->getMeshPtr()->getMaxPos() +
//                                          selected->getMeshPtr()->getMinPos()) / 2.0f ) ;
//                   selectedInstance = selected;
//               }
//               else
//                 selectedInstance = nullptr;
//           }
//           break;
//           case Button2: // middle
//           Debug("Button2");
//           break;
//           case Button3: // right
//           Debug("Button3");
//           break;
//           case Button4:// wheel up
//               Debug("Button4");
//               _camInUse->moveForward(0.1f);
//           break;
//           case Button5: // wheel down
//               Debug("Button5");
//               _camInUse->moveForward(-0.1f);
//           break;
//           default:
//           Debug("Unknow button " << xev.xbutton.button);
//         }
//     }
//     else if (xev.xbutton.type == ButtonRelease) // press 's' for SCREEN SHOT
//     {
//         Debug("Release at " << xev.xbutton.x << ", "
//                   << xev.xbutton.y);
//     }

//     _expose();
//     return true;
// }


void Port::resize(const size_t & w, const size_t & h){
    _width = w;
    _height = h;
}


void Port::getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const{

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



void Port::paint(){
    if(!_isExposed){
        initialize(); 
        _isExposed = true;
    }
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
        if (i->isOn())
            i->renderMesh(materialInUse);
    }

    gProgram->disableShadingPipe(_shaderId);

}


void Port::fitSphere(const point3 & position, const float & radius){
    float z_y = radius / sin(_camInUse->getFovy()/2.0f),
          z_x = radius / sin( static_cast<float>(_width) /
                               static_cast<float>(_height) /
                               _camInUse->getFovy()/2.0f);
    _camInUse->setTranslate(position + point3(0.0f, 0.0f, std::fmax(z_y, z_x)));
    _camInUse->setAtGlobal(position);
}
