#ifndef COUNTABLE_H
#define COUNTABLE_H

#include "GL_include.h"

namespace Lumos {

     /**
     * @brief The Countable class, used to keep check of the ref count for an object,
     *        designed such way to call appropriate openGL clean up function when the last reference is deleted
     */
    class Countable{
    public:
        Countable(){}
        Countable(void (*_releaseFunc)(GLsizei n, const GLuint * textures));
        Countable( const Countable & other );
        Countable & operator = (const Countable & other );
        virtual ~Countable();

    protected:

    private:
        unsigned int *_refCount; // use to keep the reference count for the shader
        void _retain();
        void _release();
        void (*_releaseFunc)(GLsizei n, const GLuint * textures);
    };

}


#endif // COUNTABLE_H
