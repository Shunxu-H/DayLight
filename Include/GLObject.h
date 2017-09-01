#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <GL/gl.h>

namespace Lumos {

    class GLObject{
    public:
        GLObject():_glObjId(0){ }
        GLObject( const GLObject & other ): _glObjId( other._glObjId ){}
        GLuint getGlObjId()const { return _glObjId; }

    protected:
        GLuint _glObjId;

    private:

    };
}

#endif // GLOBJECT_H
