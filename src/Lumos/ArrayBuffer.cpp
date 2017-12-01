#include "GL_include.h"
#include "ArrayBuffer.h"
#include "Mesh.h"

using namespace Lumos;


ArrayBuffer::ArrayBuffer( )
    : GLObject( [](GLuint * id){glGenBuffers(1, id);}, 
                [](const GLuint * id){glDeleteBuffers(1, id);} )
{

}


ArrayBuffer::ArrayBuffer( const ArrayBuffer & rhs)
    : GLObject( rhs )
    , _numOfEntry( rhs._numOfEntry )
    , _bytesPerEntry( rhs._bytesPerEntry )
{

}

ArrayBuffer& ArrayBuffer::operator = ( const ArrayBuffer & other ){
    GLObject::operator =(other);
    _numOfEntry = other._numOfEntry;
    _bytesPerEntry = other._bytesPerEntry;
    return *this;
}

void ArrayBuffer::setVertexBuffer( const std::vector<Patronus::Mesh> & geos ){
    _numOfEntry = 0;
    _bytesPerEntry = sizeof(point3);
    for ( const Patronus::Mesh & geo: geos )
        _numOfEntry += geo.getNumOfFaces()*3;


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
}

void ArrayBuffer::use() const{
    glBindVertexArray(getObjId());
}

bool ArrayBuffer::isInUse() const{
    GLint currentVertexArrat = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &currentVertexArrat);
    return (currentVertexArrat == static_cast<GLint>( getObjId() ));

}

void ArrayBuffer::stopUsing() const{
    glBindVertexArray(0);
}

