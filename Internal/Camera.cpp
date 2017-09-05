#include "GL_include.h"

#include "Camera.h"

namespace Patronus {

Camera::Camera(const CameraType & type,
               const float      & fov,
               const float      & near,
               const float      & far,
               const point3     & pos,
               const glm::vec3  & up,
               const glm::vec3  & at)
    :Transformable( pos ),
     _type( type ), _fov( fov ), _near( near ), _far( far ), _up( up ), _at( at )
{

}



void Camera::moveForward( const float & dist ){
    _translate += glm::normalize(_at)*dist;
}




void Camera::panAndPadestal( const float & x_axis, const float & y_axis ){
    glm::vec3 right = glm::normalize(glm::cross(_at, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _at));
    _translate += (right*x_axis + up*y_axis);
}


void Camera::rotateAroundFocus( const float & x_axis, const float & y_axis){
    glm::vec3 right = glm::normalize(glm::cross(_at, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _at));

    glm::vec3 b = (glm::normalize( -_at + ( up    * y_axis ) ) * glm::length( _at ) + _at) +
                  (glm::normalize( -_at + ( right * x_axis ) ) * glm::length( _at ) + _at);
    _translate += b;
    _up = glm::normalize(glm::cross(right, _at));

}

glm::mat4 Camera::getPerspectiveMatrix()const{

    return glm::lookAt	(  _translate, // eye
                           _translate + _at,
                           _up);

}

glm::mat4 Camera::getProjectionMatrix(const float & aspect_ratio )const {
    return glm::perspective	( _fov, aspect_ratio, _near, _far);
}

}
