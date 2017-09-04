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
    :_type( type ), _fov( fov ), _near( near ), _far( far ), _pos( pos ), _up( up ), _at( at )
{

}


void Camera::operator*( const glm::mat4 & m ){
    _pos.x = m[3][0];
    _pos.y = m[3][1];
    _pos.z = m[3][2];

}

void Camera::moveForward( const float & dist ){
    _pos = _pos + (glm::normalize(_at)*dist);
}

glm::mat4 Camera::getPerspectiveMatrix()const{

    return glm::lookAt	(  _pos, // eye
                           _pos + _at,
                           _up);

}

glm::mat4 Camera::getProjectionMatrix(const float & aspect_ratio )const {
    return glm::perspective	( _fov, aspect_ratio, _near, _far);
}

}
