#include "GLObject.h"



#include "GL_include.h"
#include "Countable.h"

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



