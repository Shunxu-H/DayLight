
#include "GL_include.h"
#include "Mesh.h"
#include "ModelAsset.h"

#include "Extern.h"


namespace Patronus {


Mesh::~Mesh(){

}


void Mesh::copyVertexData( size_t * initPos )const{
    //for (const size_t & index : _indices )
    //    glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
    //                     sizeof(point3),  &(_vertices_combinded[index].position) );
    for( const Face & f: _faces)
        for( const int & ind : f.getVerticesInds())
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                            sizeof(point3),  &(Shaper::global_vertices[ind]) );
}

void Mesh::copyVertexNormalData( size_t * initPos )const{
//    for (const size_t & index : _indices )
//        glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
//                         sizeof(point3),  &(Shaper::global[index].normal) );

    for( const Face & f: _faces)
        for( const int & ind : f.getNormalInds())
            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                            sizeof(point3),  &(Shaper::global_normal_vertices[ind]) );
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


Lumos::Instance* Mesh::instantiate_sequentialDraw ( const GLuint & VAO ){


    if ( VAO == 0 ){
        glGenVertexArrays(1, &_VAO);

    }
    else
        _VAO = VAO;

    glBindVertexArray(_VAO);
    _loadVertexToBuffer();
    _loadNormalToBuffer();
    _loadColorToBuffer();


    // get Material
    Lumos::Material* m = _material == nullptr? shaper->_default_material : _material;


    // get model Asset
    Lumos::ModelAsset asset{};
    asset.shaderId = Lumos::Shader::default_mesh_shader_id;
    asset.VAO = _VAO;
    asset.material = m;
    asset.VBO_VERT = _VBO_VERT;
    asset.VBO_COLOR = _VBO_COLOR;
    asset.VBO_NORMAL = _VBO_NORMAL;
    asset.drawType = GL_TRIANGLES;
    asset.drawStart = 0;
    asset.drawCount = getNumOfFaces()*3;


    // return data
    return new Lumos::Instance(this, asset);
}


void Mesh::_loadVertexToBuffer( ){
    GLint cur_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &cur_vao);
    assert( _VAO == cur_vao );

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
    GLint cur_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &cur_vao);
    assert( _VAO == cur_vao );

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

void Mesh::_loadColorToBuffer( ){

}




Lumos::Instance* Mesh::instantiate_indexedDraw ( const GLuint & VAO ){
    if ( VAO == 0 ){
        glGenVertexArrays(1, &_VAO);
    }
    else
        _VAO = VAO;


    glBindVertexArray(_VAO);
    _loadVertexIndicesToBuffer();
    _loadNormalIndicesToBuffer();
    _loadColorIndicesToBuffer();


    // get Material
    Lumos::Material* m = _material == nullptr? shaper->_default_material : _material;


    // get model Asset
    Lumos::ModelAsset asset{};
    asset.shaderId = Lumos::Shader::default_mesh_shader_id;
    asset.VAO = _VAO;
    asset.material = m;
    asset.VBO_VERT = _VBO_VERT;
    asset.VBO_COLOR = _VBO_COLOR;
    asset.VBO_NORMAL = _VBO_NORMAL;
    asset.drawType = GL_TRIANGLES;
    asset.drawStart = 0;
    asset.drawCount = getNumOfFaces()*3;


    // return data
    return new Lumos::Instance(this, asset);
}


void Mesh::_loadVertexIndicesToBuffer( ){
    GLint cur_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &cur_vao);
    assert( _VAO == cur_vao );

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
    GLint cur_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &cur_vao);
    assert( _VAO == cur_vao );

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

//void Mesh::_loadBoundingBoxToBuffer( ){

//}

/*
struct Material{
    color4 color;
    float reflexitivity;
    Material():color(color4(1.0f, 1.0f, 1.0f, 1.0f)), reflexitivity(0.3){}
};

struct ModelAsset {
    Shader shaders;
    Material material;
    GLuint _VAO;
    std::vector<ArrayBuffer> _VBOs;
    GLenum drawType;
    GLint drawStart;
    GLint drawCount;
};

class Instance{
public:

protected:

private:
    glm::mat4 _modelMatrix;
    ModelAsset _asset;

};
*/
}
