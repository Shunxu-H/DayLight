
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
#ifndef SHAPER_H
#define SHAPER_H

#include <vector>
#include <string>
#include <memory>
#include <Common/GL_include.h>
#include "Camera.h"
#include "Light.h"
#include <Patronus/Mesh.h>
#include <Lumos/ArrayBuffer.h>

namespace Lumos {
    class Instance;
    class Program; 
}

namespace Patronus {
    class Shaper{
    public:
        Shaper();

        Shaper( const std::string & fileName );
        virtual ~Shaper();

        //static const std::shared_ptr<Camera> _pers;
        Lumos::Material * default_material;
        static std::vector< point3 > global_vertices;
        static std::vector< point3 > global_normal_vertices;
        static std::vector< point2 > global_uv_coords;

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

        void loadAttribsAndUniform(Lumos::Program * gProgram) const;

        inline Light getDefaultLight() const { return _lights[0]; }
        /**
         * @brief load file and call corresponding functions based on file extension
         * @param fileName the file targeted to be loaded
         * @return boolean if the file is successfully loaded
         */
        bool loadFile( const std::string & fileName );

        /**
         * [clearAll clear all loaded data]
         */
        void clearAll();

        int getNumOfVertices() const;

        Lumos::ArrayBuffer getVertexBuffer()const;
        Lumos::ArrayBuffer getNormalBuffer()const;

        void addMaterial( Lumos::Material * m);



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
