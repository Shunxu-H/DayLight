#include <QDebug>
#include <fstream>
#include <experimental/filesystem>
#include <iostream>
#include <climits>

#include "GL_include.h"
#include "Utility.h"
#include "Shaper.h"
#include "Instance.h"
#include "Face.h"
#include "ModelAsset.h"

#include "obj_loader.h"

#include "Extern.h"


namespace Patronus {
Lumos::Material* Shaper::_default_material   = new Lumos::Material();


Shaper::Shaper()
{

}

Shaper::Shaper( const std::string & fileName )
{
    loadFile( fileName );
    _lights.push_back(Light::makeDirectionalLight());

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
    objl::Loader loader;
    loader.LoadFile(f_name);

    for ( const objl::Mesh & m : loader.LoadedMeshes){
        Mesh newMesh( m.MeshName );
        newMesh.setIndices( m.Indices );
        for ( const objl::Vertex & v : m.Vertices ){
            newMesh.addVertex( *reinterpret_cast<const Vertex*>(&v) );
        }
        _shapes.push_back(newMesh);
    }
    //int s = sizeof(objl::Vertex);
    //int sizeofvec = sizeof(glm::vec3)*2 + sizeof(glm::vec2);
    //int s8f = sizeof(float)*8;

    //int a = 0;

    /*
    std::ifstream file (f_name.c_str());
    if( !file.is_open() ){
        printf("Faild To Open File\n");
        return false;
    }


    Mesh newGeo;
    std::deque<std::string> tokens;
    std::string line;
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

    while (std::getline( file, line) ){
        tokens = Utils::mystrtok( line, " /" );

        // do the parsing here
        // parsing vertex
        if( tokens[0].compare( "o" ) == 0 ){
            if ( newGeo.getNumOfVertices() == 0 )
                newGeo.setId( tokens[1] );
            else{
                _shapes.push_back(newGeo);
                newGeo = Mesh(tokens[1]);
            }
            tokens.erase( tokens.begin(), tokens.begin()+2 );
        }
        if( tokens[0].compare( "v" ) == 0 ){
            point3 newP (std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]) );
            updateMax(newP);
            updateMin(newP);
            newGeo.addVertex(newP);
            tokens.erase( tokens.begin(), tokens.begin()+4 );

        }
        else if ( tokens[0].compare( "vt" ) == 0 ){
            newGeo.addVu(glm::vec2( std::stof(tokens[1]), std::stof(tokens[2])) );
            tokens.erase( tokens.begin(), tokens.begin()+3 );
        }
        else if ( tokens[0].compare( "vn" ) == 0 ){
            newGeo.addNormal(glm::vec3 (std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]) ));
            tokens.erase( tokens.begin(), tokens.begin()+4 );
        }
        else if ( tokens[0].compare( "f" ) == 0 ){
            tokens.pop_front();
            Face newF;
            std::string vertex1, vertex2, vertex3;
            if (tokens.size() == 9){

                int vertexIndex[] = {std::stoi( tokens[0] )-1, std::stoi( tokens[3] )-1, std::stoi( tokens[6] )-1},
                    uvIndex[]     = {std::stoi( tokens[1] )-1, std::stoi( tokens[4] )-1, std::stoi( tokens[7] )-1},
                    normalIndex[] = {std::stoi( tokens[2] )-1, std::stoi( tokens[5] )-1, std::stoi( tokens[8] )-1};

                tokens.erase( tokens.begin(), tokens.begin()+9 );
                newF.setVertexIndeces(vertexIndex[0],vertexIndex[1],vertexIndex[2]);
                newF.setUvIndeces(uvIndex[0],uvIndex[1],uvIndex[2]);
                newF.setNormalIndeces(normalIndex[0],normalIndex[1],normalIndex[2]);
                newGeo.addFace( newF );
            }
            else if (tokens.size() == 6){

                int vertexIndex[] = {std::stoi( tokens[0] )-1, std::stoi( tokens[2] )-1, std::stoi( tokens[4] )-1},
                    uvIndex[]     = {0, 0, 0},
                    normalIndex[] = {std::stoi( tokens[1] )-1, std::stoi( tokens[3] )-1, std::stoi( tokens[5] )-1};

                tokens.erase( tokens.begin(), tokens.begin()+6 );
                newF.setVertexIndeces(vertexIndex[0],vertexIndex[1],vertexIndex[2]);
                newF.setNormalIndeces(normalIndex[0],normalIndex[1],normalIndex[2]);
                newGeo.addFace( newF );
            }
        }

    }
    newGeo.setMaxPos(max);
    newGeo.setMinPos(min);
    _shapes.push_back( newGeo );
    */

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


std::vector<Lumos::Instance> Shaper::getAllInstance(){
    std::vector<Lumos::Instance> ret;
    for (Mesh & mesh: _shapes)
        ret.push_back(mesh.instantiate());

    return ret;
}

}
