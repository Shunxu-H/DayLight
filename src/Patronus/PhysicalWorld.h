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
#ifndef PHYSICALWORLD_H
#define PHYSICALWORLD_H

#include <vector>
#include <tuple>

#include <Patronus/Mesh.h>

#include "bullet/btBulletDynamicsCommon.h"
#include "IO/btDebugDrawer.h"


namespace Daylight {
    namespace Lumos{
        class Instance;
    }
    namespace IO
    {
        class View_bullet;
    } // IO
    
}

namespace Daylight::Patronus {
    class PhysicalWorld{
    public:
        PhysicalWorld();
        virtual ~PhysicalWorld();

        /**
         * @brief loadInstance, load one instance in the physical world, make it interactable in the world
         */
        void loadInstance( Daylight::Patronus::Mesh & mesh );


        void setDebugView(Daylight::IO::View_bullet * debugView);
        void draw();
        void test();

        /**
         * ASSESORS AND MUTATORS
         */
        inline std::vector< Daylight::Lumos::Instance * >
            getInstances() { return _instances; }

        inline btDiscreteDynamicsWorld*
            getWorld() const { return _dynamicsWorld; }

        void clearAll();
        /**
         * END OF ASSESORS AND MUTATORS
         */

        /**
         * @brief selectWithBean, input the start and end position of ray in the world and see if it intersect with any ridgit body in the scene
         * @param start, start of the ray
         * @param end, end of the ray
         * @return the closest instance hit by ray or nullptr if none hit
         */
        Daylight::Lumos::Instance * selectWithBean( const btVector3 & start, const btVector3 & end );

        /**
         * Check if a unique picking color is set for each instance in the
         * physical world
         * @return boolean indicating whether the statement above is true
         */
        bool hasSetPickingColorProperly()const;
        /**
         * Assign a unique color to all the instances in the physical world
         * Note: (0, 0, 0) is reserved to indicate empty space
         */
        void setPickingColor();

        /**
         * generate mapping from picking color to instance id
         * @return a vector of tuple mapping a color (0~255) to a string(instance
         * id)
         */
        std::vector<std::tuple<color3, std::string>> getColor2InstanceMapping();
        std::vector<std::tuple<color3, std::string>>
            saveColor2InstanceMapping(const std::string & filename);

    protected:

    private:
        std::vector< Daylight::Lumos::Instance * > _instances;
        std::set< std::string > _names;
        btBroadphaseInterface* _broadphase;
        btDefaultCollisionConfiguration* _collisionConfiguration;
        btCollisionDispatcher* _dispatcher;
        btSequentialImpulseConstraintSolver* _solver;
        btDiscreteDynamicsWorld* _dynamicsWorld;
        Daylight::IO::GLDebugDrawer * _drawer;

    };
}


#endif // PHYSICALWORLD_H
