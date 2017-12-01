#ifndef GLOBJECT_H
#define GLOBJECT_H

#include "GL_include.h"

namespace Lumos {

    class GLObject{
    public:
        GLObject(
            void (*initFunc)(GLuint *)=[](GLuint * id){*id = 0;},
            void (*df)(const GLuint *)=[](const GLuint * id){}
            );
        GLObject(
            GLuint id,
            void (*dl)(const GLuint *)
            );

        GLObject( const GLObject & other );
        GLObject& operator = ( const GLObject & other );


        virtual ~GLObject();

        inline GLuint
            getGlObjId()const { return _glObjId; }

        inline bool
            isSet() const { return _glObjId != 0; }

        inline GLuint
            getObjId() const { return _glObjId; }

        inline void
            setObjId( const GLuint id) { _glObjId = id; }

        virtual void use() const = 0;
        virtual bool isInUse() const =0;
        virtual void stopUsing() const = 0;
    protected:
        GLuint _glObjId;

    private:

        void _retain();
        void _release();
        //void (*_releaseFunc)(GLsizei n, const GLuint);
        unsigned int *_refCount; // use to keep the reference count for the shader
        void (*_deleteFunc)(const GLuint *);

    };
}

#endif // GLOBJECT_H
