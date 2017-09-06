#ifndef Mesh_H
    #define Mesh_H

#include <vector>
#include <string>
#include <memory>
#include "GL_include.h"
#include "Face.h"
#include "Transformable.h"
#include "Instance.h"

class Lumos::ArrayBuffer;

namespace Patronus {


    class Mesh: public Transformable
    {
    public:

        //Mesh(std::vector<Vector*> v=std::vector<Vector*>(),std::vector<Edge*> e=std::vector<Edge*>(), GeoType gt=AUTO,UnitType ut=COORDS);
        Mesh():_VAO(0), _VBO_VERT(0), _VBO_COLOR(0), _VBO_NORMAL(0){}
        ~Mesh();

        void addVertex(const point3 & v);
        void addFace(const Face & f);
        void addVu(const glm::vec2& uv);
        void addNormal(const glm::vec3& n);

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


        Lumos::Instance instantiate ();


    private:
        void _loadVertexToBuffer( );
        void _loadNormalToBuffer( );
        void _loadColorToBuffer( );

        std::vector< point3 > _vertices;
        std::vector< glm::vec2 > _uvs;
        std::vector< glm::vec3 > _normals;
        std::vector< Face > _faces;

        GLuint _VAO;
        GLuint _VBO_VERT;
        GLuint _VBO_COLOR;
        GLuint _VBO_NORMAL;

        Lumos::Material* _material;

    };


}


#endif 
