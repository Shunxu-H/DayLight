#ifndef Mesh_H
    #define Mesh_H

#include <vector>
#include <string>
#include <memory>
#include <climits>
#include "GL_include.h"
#include "Face.h"
#include "Instance.h"
#include "Countable.h"

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
            _VAO(0),
            _VBO_VERT(0),
            _VBO_COLOR(0),
            _VBO_NORMAL(0),
            _material(nullptr){}
        virtual ~Mesh();

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
         * @brief copyVertices all the faces ( triangles ) and copy the appropriate vertices to buffer
         *        should have called glBindBuffer before calling this function
         * @param initPos the starting position where the data will be copied to, initPos will be incremented
         *        each time a vertex is copied to the bufer
         */
        void copyVertexData( size_t * initPos )const;

        /**
         * @brief copyVertices all the faces ( triangles ) and copy the appropriate normals to buffer
         *        should have called glBindBuffer before calling this function
         * @param initPos the starting position where the data will be copied to, initPos will be incremented
         *        each time a vertex is copied to the bufer
         */
        void copyVertexNormalData( size_t * initPos )const;


        Lumos::Instance * instantiate_sequentialDraw ( const GLuint & VAO = 0 );
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



    private:


        std::string _id;
        BoundingBox _boundingBox;
        GLuint _VAO;
        GLuint _VBO_VERT;
        GLuint _VBO_COLOR;
        GLuint _VBO_NORMAL;

        std::vector< Vertex > _vertices_combinded;
        std::vector< unsigned int > _indices;

        std::vector< point3 > _vertices;
        std::vector< glm::vec2 > _uvs;
        std::vector< glm::vec3 > _normals;
        std::vector< Face > _faces;

        Lumos::Material* _material;
        Lumos::ModelAsset * _meshAsset;
        Lumos::ModelAsset * _BoundingAsset;

        void _loadVertexToBuffer( );
        void _loadNormalToBuffer( );
        void _loadColorToBuffer( );

        void _loadVertexIndicesToBuffer( );
        void _loadNormalIndicesToBuffer( );
        void _loadColorIndicesToBuffer( );

    };


}


#endif 
