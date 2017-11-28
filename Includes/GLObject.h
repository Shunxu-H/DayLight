#ifndef GLOBJECT_H
#define GLOBJECT_H

#include <GL/gl.h>

namespace Lumos {

    class GLObject{
    public:
        GLObject():_glObjId(0){ }
        GLObject( const GLObject & other ): _glObjId( other._glObjId ){ }
        GLObject& operator = ( const GLObject & other ){ _glObjId = other._glObjId; return *this; }
        virtual ~GLObject(){}

        inline GLuint
            getGlObjId()const { return _glObjId; }

        inline bool
            isSet() const { return _glObjId != 0; }

        inline GLuint
            getObjId() const { return _glObjId; }

        inline void
            setObjId( const GLuint id) { _glObjId = id; }

        virtual void bind() const = 0;

    protected:
        GLuint _glObjId;

    private:

    };
}

#endif // GLOBJECT_H
