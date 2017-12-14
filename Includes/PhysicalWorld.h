/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

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
#ifndef PHYSICALWORLD_H
#define PHYSICALWORLD_H

#include <vector>
#include <set>
#include <Instance.h>
#include "btBulletDynamicsCommon.h"
#include "btDebugDrawer.h"


namespace Lumos {
    class Instance;
}

class View_bullet;
namespace Patronus {
    class PhysicalWorld{
    public:
        PhysicalWorld();
        virtual ~PhysicalWorld();

        /**
         * @brief loadInstance, load one instance in the physical world, make it interactable in the world
         */
        void loadInstance( Patronus::Mesh & mesh );


        void setDebugView(View_bullet * debugView);
        void draw();
        void test();

        /**
         * @brief selectWithBean, input the start and end position of ray in the world and see if it intersect with any ridgit body in the scene
         * @param start, start of the ray
         * @param end, end of the ray
         * @return the closest instance hit by ray or nullptr if none hit
         */
        Lumos::Instance * selectWithBean( const btVector3 & start, const btVector3 & end );

        inline std::vector< Lumos::Instance * >
            getInstances() { return _instances; }

        inline btDiscreteDynamicsWorld*
            getWorld() const { return _dynamicsWorld; }

        void clearAll();

    protected:

    private:
        std::vector< Lumos::Instance * > _instances;
        std::set< std::string > _names;
        btBroadphaseInterface* _broadphase;
        btDefaultCollisionConfiguration* _collisionConfiguration;
        btCollisionDispatcher* _dispatcher;
        btSequentialImpulseConstraintSolver* _solver;
        btDiscreteDynamicsWorld* _dynamicsWorld;
        GLDebugDrawer * _drawer;

    };
}


#endif // PHYSICALWORLD_H
