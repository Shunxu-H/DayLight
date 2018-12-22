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
#pragma once

#include "Common/GL_include.h"

namespace Daylight::Lumos {
    class Program; 
    class GLObject{
    public:

        // static Program * gProgram; 
        /**
         * [GLObject constructor]
         * @param initFunc [function that generate the openGL resource
         * @param df [function that delete the openGL resource]
         */
        GLObject(
            void (*initFunc)(GLuint *)=[](GLuint * id){*id = 0;},
            void (*df)(const GLuint *)=[](const GLuint * id){}
            );
        /**
         * [GLObject constructor]
         * @param id [an OpenGL resource pointer]
         * @param dl [function that delete the resource]
         */
        GLObject(
            GLuint id,
            void (*dl)(const GLuint *)
            );

        GLObject( const GLObject & other );
        GLObject& operator = ( const GLObject & other );


        virtual ~GLObject();

        inline GLuint
            getGlObjId()const { return _glObjId; }

        /**
         * [isSet if the instance is pointing to an openGL resource by checking
         *  if _glObjId == 0]
         */
        inline bool
            isSet() const { return _glObjId != 0; }

        inline GLuint
            getObjId() const { return _glObjId; }

        inline void
            setObjId( const GLuint id) { _glObjId = id; }

        /**
         * [use to bind the resource to openGL]
         */
        virtual void use() const = 0;
        /**
         * [isInUse if the resource is currently binding to openGL]
         */
        virtual bool isInUse() const =0;
        /**
         * unbind openGL resource
         */
        virtual void stopUsing() const = 0;
    protected:
        GLuint _glObjId;

    private:

        void _retain();
        void _release();
        //void (*_releaseFunc)(GLsizei n, const GLuint);
        unsigned int *_refCount; // use to keep the reference count for the shader
        void (*_deleteFunc)(const GLuint *); // function will be called when refCount is 0

    };
}
