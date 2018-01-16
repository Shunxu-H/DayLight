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
#ifndef Mesh_H
    #define Mesh_H

#include <vector>
#include <string>
#include <memory>
#include <climits>
#include "GL_include.h"
#include "Face.h"
#include "Instance.h"

namespace Lumos {
    class ArrayBuffer;
    struct Material;
}

namespace Patronus {

    struct BoundingBox{
        glm::vec3 minPos;
        glm::vec3 maxPos;
        BoundingBox():minPos(glm::vec3(std::numeric_limits<float>::max())),
                      maxPos(glm::vec3(std::numeric_limits<float>::min())){}
        void update( const point3 & p){
            minPos.x = minPos.x < p.x? minPos.x : p.x;
            minPos.y = minPos.y < p.y? minPos.y : p.y;
            minPos.z = minPos.z < p.z? minPos.z : p.z;

            maxPos.x = maxPos.x > p.x? maxPos.x : p.x;
            maxPos.y = maxPos.y > p.y? maxPos.y : p.y;
            maxPos.z = maxPos.z > p.z? maxPos.z : p.z;

        }
    };

    struct Vertex{
        point3 position;
        point3 normal;
        point2 uvCoords;
    };

    class Mesh
    {
    public:

        //Mesh(std::vector<Vector*> v=std::vector<Vector*>(),std::vector<Edge*> e=std::vector<Edge*>(), GeoType gt=AUTO,UnitType ut=COORDS);
        Mesh(const std::string & id = "" ):
            _id( id ),
            _VBO_VERT(0),
            _VBO_NORMAL(0),
            _VBO_COLOR(0){}
        virtual ~Mesh();

        /// Load data to the mesh
        void addVertex(const point3 & v);
        void addFace(const Face & f);
        void addVu(const glm::vec2& uv);
        void addNormal(const glm::vec3& n);
        void addVertex( const Vertex & v);

        inline size_t
            getNumOfVertices() const { return _vertices.size(); }
        inline size_t
            getNumOfFaces() const { return _faces.size(); }

        /**
         * @brief iterate all the faces ( triangles ) and copy the appropriate vertices to buffer
         *        should have called glBindBuffer before calling this function
         * @param initPos the starting position where the data will be copied to, initPos will be incremented
         *        each time a vertex is copied to the bufer
         */
        void copyVertexData( size_t * initPos )const;

        /**
         * @brief iterate all the faces ( triangles ) and copy the appropriate normals to buffer
         *        should have called glBindBuffer before calling this function
         * @param initPos the starting position where the data will be copied to, initPos will be incremented
         *        each time a vertex is copied to the bufer
         */
        void copyVertexNormalData( size_t * initPos )const;

        /**
         * @brief iterate all the faces ( triangles ) and copy the appropriate texture coordinate to buffer
         *        should have called glBindBuffer before calling this function
         * @param initPos the starting position where the data will be copied to, initPos will be incremented
         *        each time a vertex is copied to the bufer
         */
        void copyVertexTexCoordData( size_t * initPos )const;


        Lumos::Instance * instantiate_sequentialDraw ( );
        Lumos::Instance * instantiate_indexedDraw ( const GLuint & VAO = 0 );

        /**
         * @brief setter and getter
         */
        inline glm::vec3
            getMinPos() const { return _boundingBox.minPos; }
        inline glm::vec3
            getMaxPos() const { return _boundingBox.maxPos; }

        inline void
            setMinPos( const glm::vec3 & p ) { _boundingBox.minPos = p; }
        inline void
            setMaxPos( const glm::vec3 & p ) { _boundingBox.maxPos = p; }

        inline std::string
            getId() const { return _id; }
        inline void
            setId( const std::string & id ){ _id = id; }

        inline void
            setIndices( const std::vector< unsigned int > & indx ) { _indices = indx; }
        inline std::vector< unsigned int >
            getIndices() const { return _indices; }

        // inline void
        //     setMaterial( Lumos::Material * m_ptr ) { _material = m_ptr; }
        // inline Lumos::Material *
        //     getMaterial( ) const { return _material; }


    private:


        std::string _id;
        BoundingBox _boundingBox;
        GLuint _VBO_VERT;
        GLuint _VBO_NORMAL;
        GLuint _VBO_TEXCOORD;
        GLuint _VBO_COLOR;

        std::vector< Vertex > _vertices_combinded;
        std::vector< unsigned int > _indices;

        std::vector< point3 > _vertices;
        std::vector< glm::vec2 > _uvs;
        std::vector< glm::vec3 > _normals;
        std::vector< Face > _faces;


        void _loadVertexToBuffer( );
        void _loadNormalToBuffer( );
        void _loadColorToBuffer( );
        void _loadTexCoordToBuffer( );

        // experimenting code sections, unreleased
        void _loadVertexIndicesToBuffer( );
        void _loadNormalIndicesToBuffer( );
        void _loadColorIndicesToBuffer( );
        void _loadTextCoordIndicesToBuffer( );

    };


}


#endif
