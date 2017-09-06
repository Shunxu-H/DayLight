#include "GL_include.h"
#include "ArrayBuffer.h"
#include "Mesh.h"

namespace Lumos {


ArrayBuffer& ArrayBuffer::operator = ( const ArrayBuffer & other ){
    GLObject::operator =(other);
    Countable::operator =(other);
    _numOfEntry = other._numOfEntry;
    _bytesPerEntry = other._bytesPerEntry;
}

void ArrayBuffer::setVertexBuffer( const std::vector<Patronus::Mesh> & geos ){
    _numOfEntry = 0;
    _bytesPerEntry = sizeof(point3);
    for ( const Patronus::Mesh & geo: geos )
        _numOfEntry += geo.getNumOfFaces()*3;


    glGenBuffers(1, &_glObjId);
    glBindBuffer( GL_ARRAY_BUFFER, _glObjId );
    glBufferData( GL_ARRAY_BUFFER,
                  getSizeInByte(),
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    for ( const Patronus::Mesh & geo: geos ){
        geo.copyVertexData( &startPos );
    }

}


void ArrayBuffer::setVertexNormalBuffer( const std::vector<Patronus::Mesh> & meshes ){
    _numOfEntry = 0;
    _bytesPerEntry = sizeof(color3);
    for ( const Patronus::Mesh & mesh: meshes )
        _numOfEntry += mesh.getNumOfFaces()*3;

    glGenBuffers(1, &_glObjId);
    glBindBuffer( GL_ARRAY_BUFFER, _glObjId );
    glBufferData( GL_ARRAY_BUFFER,
                  getSizeInByte(),
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    for ( const Patronus::Mesh & mesh: meshes ){
        mesh.copyVertexNormalData( &startPos );
    }
}

void ArrayBuffer::setColorBuffer( const std::vector<Patronus::Mesh> & shapes  ){

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

