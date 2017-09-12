#include <QDebug>
#include <fstream>
#include <experimental/filesystem>
#include <iostream>
#include <climits>
#include <QGLWidget>

#include "GL_include.h"
#include "Utility.h"
#include "Shaper.h"
#include "Instance.h"
#include "Face.h"
#include "ModelAsset.h"

#include "obj_loader.h"

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

#include "Extern.h"


namespace Patronus {
Lumos::Material* Shaper::default_material   = new Lumos::Material();
std::vector< point3 > Shaper::global_vertices = std::vector< point3 >();
std::vector< point3 > Shaper::global_normal_vertices{};
std::vector< point2 > Shaper::global_uv_coords{};
GLuint Shaper::global_VAO          = 0;
GLuint Shaper::global_Vertex_VBO   = 0;
GLuint Shaper::global_Normal_VBO   = 0;
GLuint Shaper::global_TexCoord_VBO = 0;


Shaper::Shaper()
{

}

Shaper::Shaper( const std::string & fileName )
{
    loadFile( fileName );
    _lights.push_back(Light::makeDirectionalLight());

}


point3 Shaper::getGlobalMax(){
    glm::vec3 max(std::numeric_limits<float>::min(),
                  std::numeric_limits<float>::min(),
                  std::numeric_limits<float>::min());
    auto updateMax = [&max](const point3 & p){
        max.x = max.x > p.x? max.x : p.x;
        max.y = max.y > p.y? max.y : p.y;
        max.z = max.z > p.z? max.z : p.z;
    };
    for (const point3 & p: Shaper::global_vertices)
        updateMax(p);
    return max;
}

point3 Shaper::getGlobalMin(){
    glm::vec3 min(std::numeric_limits<float>::max(),
                  std::numeric_limits<float>::max(),
                  std::numeric_limits<float>::max());
    auto updateMin = [&min](const point3 & p){
        min.x = min.x < p.x? min.x : p.x;
        min.y = min.y < p.y? min.y : p.y;
        min.z = min.z < p.z? min.z : p.z;
    };

    for (const point3 & p: Shaper::global_vertices)
        updateMin(p);
    return min;

}

static void loadGlobalGlBuffer(){

}


void Shaper::getBoundingSphere(const std::vector< point3 > & points, point3 * position, float * radius){
    if ( points.size() == 0 ){
        *position = point3 (0.0f, 0.0f, 0.0f);
        *radius = 0.0f;
    }
    else if (points.size() == 1){
        *position = points[0];
        *radius = 0.0f;
    }
    point3 farthest1 = points[0],
           farthest2 = points[0],
           curPoint  = points[0],
           outside   = points[0];
    *position = curPoint;
    *radius = 0.0f;

    auto getFarthest = [&points](const point3 & curP){
                            float farthestDist = 0;
                            float curDist = 0;
                            point3 farthestPoint;
                            for (const point3 & p : points){
                                curDist = glm::length(p - curP);
                                if ( curDist > farthestDist ){
                                    farthestDist = curDist;
                                    farthestPoint = p;
                                }
                            }
                            return farthestPoint;
                        };
    auto isAllInSphere = [& points, &position, &radius]( point3 & outside ){
                            for (const point3 & p : points){
                                if ( glm::length(p - *position) > *radius ){
                                    outside = p;
                                    return false;
                                }
                            }
                            return true;
                        };
    curPoint = outside;
    farthest1 = getFarthest(curPoint);
    farthest2 = getFarthest(farthest1);
    *position = (farthest1 + farthest2) / 2.0f;
    *radius = glm::length(farthest1 - farthest2) / 2.0f;
    while (!isAllInSphere(outside))
        *radius = glm::length(outside - *position);



}

bool Shaper::loadFile( const std::string & fileName ){
    namespace fs = std::experimental::filesystem ;
    fs::path p(fileName);
    if( p.empty() )
        std::cerr << "Input file invalid " << std::endl;

    if ( std::string( p.extension() ).compare( ".obj" ) == 0 )
        _loadFile_obj( fileName );


}

bool Shaper::_loadFile_obj(const std::string & f_name){

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    using namespace std::experimental::filesystem;
    path p(f_name);
    std::string curDir = std::string(p.parent_path()) + "/";

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, f_name.c_str(), curDir.c_str(), true);

    if (!err.empty()) { // `err` may contain warning message.
      std::cerr << err << std::endl;
    }

    if (!ret) {
      exit(1);
    }

    assert(attrib.vertices.size() % 3 == 0 && attrib.normals.size() % 3 == 0 && attrib.texcoords.size() % 2 == 0 );

    for ( size_t i = 0; i < attrib.vertices.size(); i+=3 )
        global_vertices.push_back( point3( attrib.vertices[i], attrib.vertices[i+1], attrib.vertices[i+2] ));
    for ( size_t i = 0; i < attrib.normals.size(); i+=3 )
        global_normal_vertices.push_back( point3( attrib.normals[i], attrib.normals[i+1], attrib.normals[i+2] ));
    for ( size_t i = 0; i < attrib.texcoords.size(); i+=2 )
        global_uv_coords.push_back( point2( attrib.texcoords[i], attrib.texcoords[i+1]));

    for ( const tinyobj::material_t & m : materials ){
        Lumos::Material * newMaterial = new Lumos::Material;
        newMaterial->texture =  QGLWidget::convertToGLFormat( QImage((curDir + "/" + m.diffuse_texname).c_str() ) );
        newMaterial->id = m.name;
        newMaterial->diffuseColor = color4( m.diffuse[0], m.diffuse[1], m.diffuse[2], 1.0f ) ;
        newMaterial->reflexitivity = m.shininess;
        newMaterial->transmittance = color3(m.transmittance[0], m.transmittance[1], m.transmittance[2] );

        addMaterial(newMaterial);
    }

    glm::vec3 max(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min()),
              min(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    auto updateMin = [&min](const point3 & p){
        min.x = min.x < p.x? min.x : p.x;
        min.y = min.y < p.y? min.y : p.y;
        min.z = min.z < p.z? min.z : p.z;
    };
    auto updateMax = [&max](const point3 & p){
        max.x = max.x > p.x? max.x : p.x;
        max.y = max.y > p.y? max.y : p.y;
        max.z = max.z > p.z? max.z : p.z;
    };


    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        Mesh newMesh{};
        newMesh.setId(shapes[s].name);
        max = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min()),
        min = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            Face newFace{};


            int fv = shapes[s].mesh.num_face_vertices[f];
            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                float vx = attrib.vertices[3*idx.vertex_index+0];
                float vy = attrib.vertices[3*idx.vertex_index+1];
                float vz = attrib.vertices[3*idx.vertex_index+2];
                updateMax(point3(vx, vy, vz));
                updateMin(point3(vx, vy, vz));
                if(idx.normal_index < 0 || idx.normal_index > global_normal_vertices.size() )
                    int a = 1;
                newFace.addVertexIndex(idx.vertex_index);
                newFace.addNormalIndex(idx.normal_index);
                newFace.addUvIndex(idx.texcoord_index);
            }
            if ( shapes[s].mesh.material_ids[f] == -1)
                newFace.setMaterial( Shaper::default_material );
            else
                newFace.setMaterial( _materials[shapes[s].mesh.material_ids[f]] );
            newMesh.addFace(newFace);

            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
        newMesh.setMaxPos(max);
        newMesh.setMinPos(min);
        _shapes.push_back(newMesh);
    }
}


void Shaper::addMaterial( Lumos::Material * m, const GLint & minMagFiler, const GLint & wrapMode ){

    if (m->texture.isNull())
    {
        _materials.push_back(m);
        return;
    }

    // get texture if image is avaible
    glGenTextures(1, &(m->glTexId));
    glBindTexture(GL_TEXTURE_2D,  m->glTexId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 m->getBitmapFormat(),
                 (GLsizei)m->texture.width(),
                 (GLsizei)m->texture.height(),
                 0,
                 m->getBitmapFormat(),
                 GL_UNSIGNED_BYTE,
                 m->texture.bits());
    glBindTexture(GL_TEXTURE_2D, 0);

    _materials.push_back(m);
}

void Shaper::_loadDefaultObjects(){
    //_pers = std::make_shared<Camera, CameraType> ( CameraType::PERSPECTIVE );
    _lights.push_back(Light());
}

Lumos::ArrayBuffer Shaper::getVertexBuffer( )const
{
    Lumos::ArrayBuffer ret{};
    ret.setVertexBuffer(_shapes);
    return ret;
}

Lumos::ArrayBuffer Shaper::getNormalBuffer( )const
{
    Lumos::ArrayBuffer ret{};
    ret.setVertexNormalBuffer(_shapes);
    return ret;
}



int Shaper::getNumOfVertices() const{
    size_t size = 0;
    for ( const auto & shape: _shapes )
        size += shape.getNumOfVertices();
    return size;
}

/*
std::vector<Lumos::Instance> Shaper::getAllInstance(){
    std::vector<Lumos::Instance> ret;
    for (Mesh & mesh: _shapes)
        ret.push_back(mesh.instantiate());

    return ret;
}
*/

}
