
#include "GL_include.h"
#include "Mesh.h"
#include "ModelAsset.h"

#include "Extern.h"


namespace Patronus {


Mesh::~Mesh(){

}


void Mesh::copyVertexData( size_t * initPos )const{
    for (const size_t & index : _indices )
        glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                         sizeof(point3),  &(_vertices_combinded[index].position) );
//    for( const Face & f: _faces)
//        for( const unsigned int & ind : f.verticesInds())
//            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
//                            sizeof(point3),  &(_vertices[ind]) );
}

void Mesh::copyVertexNormalData( size_t * initPos )const{
    for (const size_t & index : _indices )
        glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
                         sizeof(point3),  &(_vertices_combinded[index].normal) );

//    for( const Face & f: _faces)
//        for( const unsigned int & ind : f.normalInds())
//            glBufferSubData( GL_ARRAY_BUFFER, ((*initPos)++)*sizeof(point3),
//                            sizeof(point3),  &(_normals[ind]) );
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


Lumos::Instance* Mesh::instantiate (){
    GLint current_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &current_vao);
    //assert( current_vao != 0 );

    if ( _VAO == 0 ){
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);
        _loadVertexToBuffer();
        _loadNormalToBuffer();
        _loadColorToBuffer();

    }
    else
    {
        //throw std::runtime_error( "Free VBO here, will build later");
    }



    // get Material
    Lumos::Material* m = _material == nullptr? shaper._default_material : _material;


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
    asset.drawCount = _vertices_combinded.size();


    // return data
    return new Lumos::Instance(this, asset);
}


void Mesh::_loadVertexToBuffer( ){
    GLint cur_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &cur_vao);
    assert( _VAO == cur_vao );

    size_t _bytesPerEntry = sizeof(point3);
    size_t _numOfEntry = _vertices_combinded.size();

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
    size_t _numOfEntry = _vertices_combinded.size()*3;

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
