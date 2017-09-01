#include <experimental/filesystem>
#include <GL/gl.h>
#include <iostream>
#include <memory>
#include "Utility.h"
#include "Shaper.h"

#include "Face.h"

namespace Patronus {


Shaper::Shaper( const std::string & fileName ){
    loadFile( fileName );


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
    FILE * file = fopen(f_name.c_str(), "r");
    if( file == NULL ){
        printf("Faild To Open File\n");
        return false;
    }


    char lineHeader[128];
    int res;
    Geometry newGeo;


    while (true){
        res = fscanf(file, "%s", lineHeader);

        if (res = EOF)
            break;

        // do the parsing here
        // parsing vertex
        if( strcmp( lineHeader, "v") == 0){
            point4 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
            newGeo.addVertex(vertex);
        }
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            newGeo.addVu(uv);
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            newGeo.addNormal(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            Face newF;
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                                    &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                                    &vertexIndex[1], &uvIndex[1], &normalIndex[1],
                                    &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            newF.setVertexIndeces(vertexIndex[0],vertexIndex[1],vertexIndex[2]);
            newF.setUvIndeces(uvIndex[0],uvIndex[1],uvIndex[2]);
            newF.setNormalIndeces(normalIndex[0],normalIndex[1],normalIndex[2]);
        }

    }

    _shapes.push_back( newGeo );

}

GLuint Shaper::getBuffer( )const
{
    size_t size = 0;
    for ( const auto & shape: _shapes )
        size += shape.getNumOfVertices();

    // check error
//    GLenum err;
//    if((err = glGetError()) != GL_NO_ERROR)
//    {
//        std::cerr << "Error: " << err << std::endl;
//        while ((err = glGetError()) != GL_NO_ERROR){
//            std::cerr << "Error: " << err << std::endl;
//        }
//        throw std::runtime_error("Program terminated, check log please");
//    }

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER,
                  sizeof(point4)*size,
                  nullptr, GL_STATIC_DRAW);

    size_t startPos = 0;
    for ( const auto & shape: _shapes ){
        startPos += shape.copyVertexData( startPos );
    }


}



}
