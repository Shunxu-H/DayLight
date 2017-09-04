#include "GL_include.h"
#include "ArrayBuffer.h"

namespace Lumos {

void ArrayBuffer::setVertexBuffer( const std::vector<Geometry> & geos ){

    _numOfEntry = 0;
    _bytesPerEntry = sizeof(point4);
    for ( const Geometry & geo: geos )
        _numOfEntry += geo.getNumOfFaces()*3;


    glGenBuffers(1, &_glObjId);
    glBindBuffer( GL_ARRAY_BUFFER, _glObjId );
    glBufferData( GL_ARRAY_BUFFER,
                  getSizeInByte(),
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    for ( const Geometry & geo: geos ){
        geo.copyVertexData( &startPos );
    }


}

void ArrayBuffer::setColorBuffer( const std::vector<Geometry> & shapes  ){

}

ArrayBuffer::~ArrayBuffer(){
    if ( *_refCount == 1){
        GLuint n = getObjId();
        glDeleteBuffers( 1, &n );
    }
}

void ArrayBuffer::bind() const{
    glBindVertexArray(getObjId());
}


}

