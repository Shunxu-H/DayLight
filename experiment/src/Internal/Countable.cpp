#include "GL_include.h"
#include "Countable.h"

namespace Lumos {

Countable::Countable():_refCount( nullptr ){

    _refCount = new unsigned;
    *_refCount = 1;
}


Countable::Countable( const Countable & other )
                : _refCount( other._refCount )
{
    _retain();
}

Countable& Countable::operator = (const Countable & other ){
    _release();
    _refCount = other._refCount;
    _retain();
    return *this;
}

Countable::~Countable(){
    if( _refCount ) _release();
}

void Countable::_retain(){
    assert( _refCount );
    *_refCount += 1;

}

void Countable::_release(){
    assert( _refCount && *_refCount > 0);
    *_refCount -= 1;
    if(*_refCount == 0){ // delete pointer if nothing pointing to THIS
        delete _refCount; _refCount = nullptr;
    }
}


}
