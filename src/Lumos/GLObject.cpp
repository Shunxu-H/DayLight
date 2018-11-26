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
#include "GLObject.h"



#include "Common/GL_include.h"

using namespace Lumos;


GLObject::GLObject(
            void (*initFunc)(GLuint *),
            void (*df)(const GLuint *)
            )
			: _refCount( nullptr )
			, _deleteFunc( df )
{
	initFunc(&_glObjId);
	_refCount = new unsigned;
    *_refCount = 1;
}


GLObject::GLObject(
	    GLuint id,
	    void (*dl)(const GLuint *)
	    )
		: _glObjId(id)
		, _refCount( nullptr )
		, _deleteFunc( dl ){
	_refCount = new unsigned;
    *_refCount = 1;
}

GLObject::GLObject( const GLObject & other )
	            : _glObjId( other._glObjId )
	            , _refCount( other._refCount )
	            , _deleteFunc(other._deleteFunc)
{
    _retain();
}

GLObject& GLObject::operator = (const GLObject & other ){
    _release(); // becase this will be destroyed
    _refCount = other._refCount; // take over the other's counter
    _retain(); // add one to the counter
    _glObjId = other._glObjId;
    _deleteFunc = other._deleteFunc;
    return *this;
}

GLObject::~GLObject(){
    if( _refCount ) _release();
}

void GLObject::_retain(){
    assert( _refCount );
    *_refCount += 1;

}

void GLObject::_release(){
    assert( _refCount && *_refCount > 0); // make sure we are not making any mistake
    *_refCount -= 1;
    if(*_refCount == 0){ // delete pointer if nothing pointing to THIS

        _deleteFunc( &_glObjId );

        delete _refCount;
        _refCount = nullptr;
    }
}
