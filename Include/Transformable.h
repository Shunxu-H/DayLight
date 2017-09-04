#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "GL_include.h"

namespace Patronus {

    class Transformable{
    public:
        virtual ~Transformable(){}

        virtual void operator*( const glm::mat4 & m ) = 0;

    protected:

    private:

};
}

#endif // TRANSFORMABLE_H
