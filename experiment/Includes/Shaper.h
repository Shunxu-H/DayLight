#ifndef SHAPER_H
#define SHAPER_H

#include <vector>
#include <string>
#include <memory>
#include "GL_include.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "ArrayBuffer.h"

namespace Lumos {
    class Instance;
}

namespace Patronus {
    class Shaper{
    public:
        Shaper();

        Shaper( const std::string & fileName );

        //static const std::shared_ptr<Camera> _pers;
        static Lumos::Material * default_material;
        static std::vector< point3 > global_vertices;
        static std::vector< point3 > global_normal_vertices;
        static std::vector< point2 > global_uv_coords;
        static GLuint global_VAO;
        static GLuint global_Vertex_VBO;
        static GLuint global_Normal_VBO;
        static GLuint global_TexCoord_VBO;

        static const float multiplier;

        /**
         * @return global maxinmum of all vertices in the scene
         */
        static point3 getGlobalMax();
        /**
         * @return global minimum of all vertices in the scene
         */
        static point3 getGlobalMin();


        /**
         * @brief getBoundingSphere, compute the bounding sphere given points loaded in @points
         * @param points, the points which will be bounded by the computed sphere
         * @param position, a pointer to a location where the center of the sphere will be stored
         * @param radius, a pointer to a location where the radius of the sphere will be stored
         */
        static void getBoundingSphere(const std::vector< point3 > & points, point3 * position, float * radius);
        static void loadGlobalGlBuffer();

        void loadAttribsAndUniform() const;

        inline Light getDefaultLight() const { return _lights[0]; }
        /**
         * @brief load file and call corresponding functions based on file extension
         * @param fileName the file targeted to be loaded
         * @return boolean if the file is successfully loaded
         */
        bool loadFile( const std::string & fileName );

        void clearAll();

        int getNumOfVertices() const;

        Lumos::ArrayBuffer getVertexBuffer()const;
        Lumos::ArrayBuffer getNormalBuffer()const;

        void addMaterial( Lumos::Material * m,
                          const GLint & minMagFiler = GL_LINEAR,
                          const GLint & wrapMode = GL_REPEAT );



        inline bool
            isLoaded() const { return _shapes.size() > 0; }

        inline std::vector< Light > getLights()
            const { return _lights; }

        inline std::vector<Mesh>&
            getMeshes() { return _shapes; }
        inline void addCamera( Camera * c ) { _cameras.push_back(c); }
        inline Camera*
            getnCamera( const size_t & index ){ if (index >= _cameras.size()) return nullptr; else return _cameras[index]; }
        inline size_t
            getNumOfCameras() const { return _cameras.size(); }

        inline void
            setCurFileName( const std::string & fn ) { _curFileName = fn; }
        inline std::string
            getCurFileName() const { return _curFileName; }


    protected:

    private:

        std::vector<Mesh> _shapes;
        std::vector< Camera * > _cameras;
        std::vector<Light> _lights;

        std::vector< Lumos::Material * > _materials;
        std::string _curFileName;


        /**
         * @brief _loadDefaultObjects
         *         construct a point light and perspective camera
         */
        void _loadDefaultObjects();
        bool _loadFile_obj (const std::string & f_name);


    };

}

#endif // SHAPER_H
