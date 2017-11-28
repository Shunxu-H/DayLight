#include "GL_include.h"
#include "Transformable.h"


using namespace Patronus;


void Transformable::translate ( const float & x, const float & y, const float & z ){
    _translate += point3( x, y, z );
}

void Transformable::scale ( const float & x, const float & y, const float & z ){
    _scale *= point3( x, y, z );
}

void Transformable::rotate ( const float & x, const float & y, const float & z ){
    _orientation += point3( x, y, z );
}


glm::mat4 Transformable::getModelMatrix() const{
    glm::mat4 ret = glm::mat4(1);
    ret = glm::rotate(ret, _orientation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    ret = glm::rotate(ret, _orientation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    ret = glm::rotate(ret, _orientation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    ret = glm::translate(ret, _translate );
    return ret;
}

glm::mat4 Transformable::getInverseModelMatrix() const{
    return glm::inverse(getModelMatrix());
}


