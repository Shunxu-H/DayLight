/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

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

void ArrayBuffer::setVertexBuffer( const std::vector<Patronus::Mesh> & meshes ){
    _numOfEntry = 0;
    _bytesPerEntry = sizeof(point3);
    for ( const Patronus::Mesh & mesh: meshes )
        _numOfEntry += mesh.getNumOfFaces()*3;

    glBindBuffer( GL_ARRAY_BUFFER, _glObjId );
    glBufferData( GL_ARRAY_BUFFER,
                  getSizeInByte(),
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    for ( const Patronus::Mesh & mesh: meshes ){
        mesh.copyVertexData( &startPos );
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
