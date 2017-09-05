#include "GL_include.h"
#include "Transformable.h"


namespace Patronus {


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

}

glm::mat4 Transformable::getInverseModelMatrix() const{

}

}
