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

namespace Patronus {
    class Shaper{
    public:
        Shaper():_pers( std::make_shared<Camera, CameraType> (CameraType::PERSPECTIVE ) ) { }

        Shaper( const std::string & fileName );

        inline Light getDefaultLight() const { return lights[0]; }

        /**
         * @brief load file and call corresponding functions based on file extension
         * @param fileName the file targeted to be loaded
         * @return boolean if the file is successfully loaded
         */
        bool loadFile( const std::string & fileName );

        inline bool
            isLoaded() const { return _shapes.size() > 0; }

        inline std::shared_ptr<Camera>
            getPerspectiveCam() const { return _pers; }



        int getNumOfVertices() const;

        Lumos::ArrayBuffer getVertexBuffer()const;
        Lumos::ArrayBuffer getNormalBuffer()const;



    protected:

    private:

        std::vector<Mesh> _shapes;
        std::vector<Camera> _cameras;
        std::shared_ptr<Camera> _pers;
        std::vector<Light> lights;


        /**
         * @brief _loadDefaultObjects
         *         construct a point light and perspective camera
         */
        void _loadDefaultObjects();
        bool _loadFile_obj(const std::string & f_name);

    };

}

#endif // SHAPER_H
