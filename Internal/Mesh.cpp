
#include "GL_include.h"
#include "Mesh.h"



namespace Patronus {


Mesh::~Mesh(){
}



void Mesh::copyVertexData( size_t * initPos )const{
    for( const Face & f: _faces)
        for( const unsigned int & ind : f.verticesInds())
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                            sizeof(point3),  &(_vertices[ind]) );
}

void Mesh::copyVertexNormalData( size_t * initPos )const{
    for( const Face & f: _faces)
        for( const unsigned int & ind : f.normalInds())
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                            sizeof(point3),  &(_normals[ind]) );
}

void Mesh::addVertex(const point3 & v){
    _vertices.push_back(v);
}

void Mesh::addFace(const Face &f){
    _faces.push_back(f);
}


void Mesh::addVu(const glm::vec2& uv){
    _uvs.push_back(uv);
}

void Mesh::addNormal(const glm::vec3& n){
    _normals.push_back(n);
}




}
