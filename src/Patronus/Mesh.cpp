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
#include <Common/GL_include.h>
#include <Common/Extern.h>

#include <Patronus/Mesh.h>
#include <Patronus/Shaper.h>

#include <Lumos/ModelAsset.h>




using namespace Patronus;


Mesh::~Mesh(){

    glDeleteBuffers(1, &_VBO_VERT);
    glDeleteBuffers(1, &_VBO_NORMAL);
    glDeleteBuffers(1, &_VBO_TEXCOORD);
    glDeleteBuffers(1, &_VBO_COLOR);
}


void Mesh::copyVertexData( size_t * initPos )const{
    for( const Face & f: _faces)
        for( const int & ind : f.getVerticesInds())
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                            sizeof(point3),  &(Shaper::global_vertices[ind]) );
}

void Mesh::copyVertexNormalData( size_t * initPos )const{
    for( const Face & f: _faces)
        for( const int & ind : f.getNormalInds())
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                            sizeof(point3),  &(Shaper::global_normal_vertices[ind]) );
}

void Mesh::copyVertexTexCoordData( size_t * initPos )const{
    for( const Face & f: _faces)
        for( const int & ind : f.getUvInds()){
            if (ind == -1) return;
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point2),
                            sizeof(point2),  &(Shaper::global_uv_coords[ind]) );
        }

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

void Mesh::addVertex( const Vertex & v){
    _boundingBox.update(v.position);
    _vertices_combinded.push_back( v );
}


Lumos::Instance* Mesh::instantiate_sequentialDraw ( ){



    _loadVertexToBuffer();
    _loadNormalToBuffer();
    _loadTexCoordToBuffer();

    // get model Asset
    Lumos::ModelAsset asset{};
    asset.shaderId = Lumos::Shader::default_mesh_shader_id;
    asset.VBO_VERT = _VBO_VERT;
    asset.VBO_COLOR = _VBO_COLOR;
    asset.VBO_NORMAL = _VBO_NORMAL;
    asset.VBO_TEXCOORD = _VBO_TEXCOORD;
    asset.drawType = GL_TRIANGLES;
    asset.drawStart = 0;
    asset.drawCount = getNumOfFaces()*3;
    Lumos::Material * curM = nullptr;
    size_t entryCnt = 0, startPos = 0;
    for ( const Face & f: _faces ){
        if ( curM == nullptr ){ // first into the loop, skip making new materialPack
            curM = f.getMaterial();
        }
        else if ( curM != f.getMaterial() ) { // seeing a new material
            asset.materials.push_back( Lumos::MaterialPack(curM, startPos, entryCnt) );
            curM = f.getMaterial();
            startPos += entryCnt;
            entryCnt = 0;
        }
        //startPos += f.getVerticesInds().size();
        entryCnt += f.getVerticesInds().size();
    }

    if ( curM != nullptr )
        asset.materials.push_back( Lumos::MaterialPack(curM, startPos, entryCnt) );

    // return data
    return new Lumos::Instance(this, asset);
}


void Mesh::_loadVertexToBuffer( ){

    size_t _bytesPerEntry = sizeof(point3);
    size_t _numOfEntry = getNumOfFaces()*3;

    glGenBuffers(1, &_VBO_VERT);
    glBindBuffer( GL_ARRAY_BUFFER, _VBO_VERT );
    glBufferData( GL_ARRAY_BUFFER,
                  _numOfEntry*_bytesPerEntry,
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    copyVertexData( &startPos );

}

void Mesh::_loadNormalToBuffer( ){

    size_t _bytesPerEntry = sizeof(point3);
    size_t _numOfEntry = getNumOfFaces()*3;

    glGenBuffers(1, &_VBO_NORMAL);
    glBindBuffer( GL_ARRAY_BUFFER, _VBO_NORMAL );
    glBufferData( GL_ARRAY_BUFFER,
                  _numOfEntry*_bytesPerEntry,
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    copyVertexNormalData( &startPos );
}

void Mesh::_loadTexCoordToBuffer( ){

    size_t _bytesPerEntry = sizeof(point2);
    size_t _numOfEntry = getNumOfFaces()*3;

    glGenBuffers(1, &_VBO_TEXCOORD);
    glBindBuffer( GL_ARRAY_BUFFER, _VBO_TEXCOORD );
    glBufferData( GL_ARRAY_BUFFER,
                  _numOfEntry*_bytesPerEntry,
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    copyVertexTexCoordData( &startPos );
}

void Mesh::_loadColorToBuffer( ){

}




Lumos::Instance* Mesh::instantiate_indexedDraw ( const GLuint & VAO ){
    throw std::runtime_error("aborting such design for now");
}


void Mesh::_loadVertexIndicesToBuffer( ){

    size_t _numOfEntry = getNumOfFaces()*3;

    glGenBuffers(1, &_VBO_VERT);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _VBO_VERT );

    int * data = new int[_numOfEntry];
    // get data ready
    size_t curPos = 0;
    for (const Face & f : _faces){
        memcpy(data+curPos,
                &(f.getVerticesInds()[0]),
                f.getVerticesInds().size()*sizeof(int));
        curPos += f.getVerticesInds().size();
    }

    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  sizeof(data),
                  data, GL_STATIC_DRAW);
    delete [] data;
}

void Mesh::_loadNormalIndicesToBuffer( ){

    size_t _numOfEntry = getNumOfFaces()*3;

    glGenBuffers(1, &_VBO_VERT);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, _VBO_VERT );

    int * data = new int[_numOfEntry];
    // get data ready
    size_t curPos = 0;
    for (const Face & f : _faces){
        memcpy(data+curPos,
                &(f.getVerticesInds()[0]),
                f.getNormalInds().size()*sizeof(int));
        curPos += f.getNormalInds().size();
    }


    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  sizeof(data),
                  data, GL_STATIC_DRAW);
    delete [] data;
}




void Mesh::_loadColorIndicesToBuffer( ){

}
