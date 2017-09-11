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
        static Lumos::Material * _default_material;
        static std::vector< point3 > global_vertices;
        static std::vector< point3 > global_normal_vertices;
        static std::vector< point2 > global_uv_coords;
        static GLuint global_VAO;
        static GLuint global_Vertex_VBO;
        static GLuint global_Normal_VBO;
        static GLuint global_TexCoord_VBO;
        static point3 getGlobalMax();
        static point3 getGlobalMin();
        static void getBoundingSphere(const std::vector< point3 > & points, point3 * position, float * radius);
        static void loadGlobalGlBuffer();

        inline Light getDefaultLight() const { return _lights[0]; }
        /**
         * @brief load file and call corresponding functions based on file extension
         * @param fileName the file targeted to be loaded
         * @return boolean if the file is successfully loaded
         */
        bool loadFile( const std::string & fileName );


        int getNumOfVertices() const;

        Lumos::ArrayBuffer getVertexBuffer()const;
        Lumos::ArrayBuffer getNormalBuffer()const;

        //std::vector<Lumos::Instance> getAllInstance();


        inline bool
            isLoaded() const { return _shapes.size() > 0; }

        inline std::vector< Light > getLights()
            const { return _lights; }

        inline std::vector<Mesh>&
            getMeshes() { return _shapes; }
    protected:

    private:

        std::vector<Mesh> _shapes;
        std::vector<Camera> _cameras;
        std::vector<Light> _lights;


        /**
         * @brief _loadDefaultObjects
         *         construct a point light and perspective camera
         */
        void _loadDefaultObjects();
        bool _loadFile_obj (const std::string & f_name);

    };

}

#endif // SHAPER_H
