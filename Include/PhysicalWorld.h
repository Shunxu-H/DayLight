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
         * @return if the object is successully loaded
         */
        bool loadInstance( Patronus::Mesh & mesh );


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

        inline const std::vector< Lumos::Instance * >
            getInstances() const { return _instances; }

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
