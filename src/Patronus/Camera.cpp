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
#include <experimental/filesystem>
#include <fstream>
#include <sstream>
#include <cstdio>
#ifndef GLM_ENABLE_EXPERIMENTAL
    #define GLM_ENABLE_EXPERIMENTAL
#endif
#include <glm/gtx/transform.hpp>
#include "Common/GL_include.h"
#include "Common/Utility.h"
#include "Common/Extern.h"

#include "Patronus/Shaper.h"

#include "Lumos/Program.h"

#include "Camera.h"
using namespace Daylight::Patronus ;
using namespace std::experimental;
Camera * Camera::pers = new Camera{"pers"};



void Camera::loadCamerasFromDir( const std::string & dir, Shaper * shaper ){
    if ( shaper == nullptr ){
        std::cerr << "Shaper object is uninitialized!" << std::endl;
        //return false;
    }
    filesystem::path p ( dir );
    if ( p.empty() )
       throw std::runtime_error( "Invalid directory in Camera::loadCamerasFromDir()");

    std::string camNameFile = std::string( p ) + "/room_camera_name.txt";
    std::string camStatFile = std::string( p ) + "/room_camera.txt";

    std::ifstream f (camNameFile.c_str());
    if ( !f.is_open() )
        throw std::runtime_error( "Camera name file does not exist! ");
    std::stringstream ss;

    // load camera names
    std::string fileNameStr;
    ss << f.rdbuf();
    f.close();
    std::deque< std::string > camNames = Utils::mystrtok(ss.str(), "\n ");


    // iterate through camera stat file
    std::string line;
    f.open(camStatFile.c_str());
    if ( !f.is_open() )
        throw std::runtime_error( "Camera stat file does not exist! ");
    while(std::getline(f, line)){
        std::deque< std::string > tokens = Utils::mystrtok(line, " ");
        Camera * newCamera = new Camera(camNames[0]);
        newCamera->setTranslate (point3(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2])) * Shaper::multiplier );
        newCamera->setAt        (point3(std::stof(tokens[3]), std::stof(tokens[4]), std::stof(tokens[5])));
        newCamera->setUp        (point3(std::stof(tokens[6]), std::stof(tokens[7]), std::stof(tokens[8])));
        camNames.pop_front();
        shaper->addCamera( newCamera );
    }


}



Camera::Camera( const std::string& camId ,
                const CameraType & type  ,
                const glm::vec3  & up    ,
                const glm::vec3  & at    ,
                const float      & fov   ,
                const float      & near  ,
                const float      & far   ,
                const point3     & pos   )
    :Transformable( pos )
    ,_camId( camId )
    ,_type( type )
    ,_up( up )
    ,_at( at )
    ,_fov( fov )
    ,_near( near )
    ,_far( far )
{
   if (camId.size() == 0)
       throw std::runtime_error("Camera must be assigned an Id");
}

Camera::~Camera(){


}

// void Camera::loadUniforms( const unsigned int & width, const unsigned int & height ) const{
//     gProgram->setUniform("camera", getPerspectiveMatrix());
//     gProgram->setUniform("cameraPosition", getTranslate() );
//     gProgram->setUniform("projection", getProjectionMatrix(static_cast<float>(width)/static_cast<float>(height)));
//     gProgram->setUniform("ModelViewProjectionMatrix",
//                              getProjectionMatrix( static_cast<float>(width)/static_cast<float>(height) )*
//                              getPerspectiveMatrix()*
//                              getModelMatrix());


// }


void Camera::moveForward( const float & sensitivity ){
    point3 temp = _translate + _at;
    _translate += _at*sensitivity;
    setAtGlobal(temp);
}




void Camera::panAndPadestal( const float & x_axis, const float & y_axis ){
    glm::vec3 right = glm::normalize(glm::cross(_at, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _at));
    _translate += (right*x_axis + up*y_axis);
}


void Camera::rotateAroundFocus( const float & x_axis, const float & y_axis){
    glm::vec3 right = glm::normalize(glm::cross(_at, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _at));
    glm::mat4 m(1);
    m = glm::rotate(m, y_axis, right);
    m = glm::rotate(m, x_axis, up);
    glm::vec4 newMinusA = m * glm::vec4(-_at, 1.0);
    setTranslatev4(getTranslatev4()+point4(_at, 1.0)+newMinusA);
    _at = -point3(newMinusA);
    //_up = glm::normalize(glm::cross(right, _at));

}

glm::mat4 Camera::getPerspectiveMatrix()const{

    return glm::lookAt	(  _translate, // eye
                           _translate + _at,
                           _up);

}

glm::mat4 Camera::getProjectionMatrix(const float & aspect_ratio )const {
    return glm::perspective	( _fov, aspect_ratio, _near, _far);
}
