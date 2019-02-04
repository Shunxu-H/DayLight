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
#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

#include <bullet/btBulletCollisionCommon.h>

#include <Common/GL_include.h>
#include <Common/Color.h>


#include <Lumos/ModelAsset.h>
#include <Lumos/Program.h>

#include <Patronus/Transformable.h>

#include <IO/PerspectiveView.h>


namespace Daylight{
    namespace Patronus {
        class Mesh;
        class PhysicalWorld; 
    }
}

namespace Daylight{
    namespace Lumos {
        class ArrayBuffer;
        class Program; 

        class Instance: public Daylight::Patronus::Transformable {
        public:
            Instance(
                    Daylight::Patronus::Mesh * meshPtr = nullptr,
                    const ModelAsset & asset = ModelAsset()
                    );

            //virtual ~Instance(){}

            /**
             * @brief bind data to attributes and uniforms of the shaders currently binded to openGL
             */
            void loadAttribsAndUniform(Program program) const;

            /**
             * [renderMesh render the instance to viewport]
             * @param materialInUse [the last material used, no need to change
             *  material is they are the same]
             */
            void renderMesh(Program program, Material * materialInUse ) const;

            /**
             * [renderBoundngBox render the bounding box for the instance]
             * @param v [description]
             */
            void renderBoundngBox( const Daylight::IO::PerspectiveView & v) const;


            /**
             * @brief setter and getter for private members
             */
            inline void
                setMeshAsset( ModelAsset asset ) { _asset = asset; }

            inline ModelAsset
                getMeshAsset() const { return _asset; }

            inline void
                setId( const std::string & id ) { _id = id; }
            inline std::string
                getId() const { return _id; }

            void setRidgidBody(  Daylight::Patronus::PhysicalWorld * world, btRigidBody * const &  arg );
            inline btRigidBody*
                getRidgidBody() const { return _rigidBody; }

            inline Daylight::Patronus::Mesh *
                getMeshPtr() const { return _meshPtr; }

            inline color3
                getPickingColor() const { return _pickingColor; }
            inline void
                setPickingColor( const color3 & c ) { _pickingColor = c; }

        protected:

        private:
            Daylight::Patronus::Mesh * _meshPtr;
            ModelAsset _asset;
            std::string _id;
            btRigidBody * _rigidBody;
            color3 _pickingColor;

            //friend void View_renderer::getVisibleObjects(const std::string &);


        };
    }
}

#endif // INSTANCE_H
