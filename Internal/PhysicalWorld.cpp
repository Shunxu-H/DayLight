#include <QDebug>
#include "btBulletDynamicsCommon.h"
#include "PhysicalWorld.h"
#include "Mesh.h"
#include "View_bullet.h"

#include "Utility.h"


#define ARRAY_SIZE_Y 5
#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Z 5

namespace Patronus {

PhysicalWorld::PhysicalWorld(){
    _drawer = nullptr;
    // Initialize Bullet. This strictly follows http://bulletphysics.org/mediawiki-1.5.8/index.php/Hello_World,
    // even though we won't use most of this stuff.

    // Build the broadphase
    _broadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    _collisionConfiguration = new btDefaultCollisionConfiguration();
    _dispatcher = new btCollisionDispatcher(_collisionConfiguration);

    // The actual physics solver
    _solver = new btSequentialImpulseConstraintSolver();

    // The world.
    _dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher,_broadphase,_solver,_collisionConfiguration);
    _dynamicsWorld->setGravity(btVector3(0,-9.81f,0));



    /*
    //_drawer.DBG_DrawWireframe;
    {
        //create a few dynamic rigidbodies
        // Re-using the same collision is better for memory usage and performance

        btBoxShape* colShape = createBoxShape(btVector3(.1,.1,.1));


        //btCollisionShape* colShape = new btSphereShape(btScalar(1.));
        m_collisionShapes.push_back(colShape);

        /// Create Dynamic Objects
        btTransform startTransform;
        startTransform.setIdentity();

        btScalar	mass(1.f);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0,0,0);
        if (isDynamic)
            colShape->calculateLocalInertia(mass,localInertia);


        for (int k=0;k<ARRAY_SIZE_Y;k++)
        {
            for (int i=0;i<ARRAY_SIZE_X;i++)
            {
                for(int j = 0;j<ARRAY_SIZE_Z;j++)
                {
                    startTransform.setOrigin(btVector3(
                                        btScalar(0.2*i),
                                        btScalar(2+.2*k),
                                        btScalar(0.2*j)));


                    createRigidBody(mass,startTransform,colShape);


                }
            }
        }
    }

*/

}

void PhysicalWorld::test(){
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -10, 0));


    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

    btCollisionShape* fallShape = new btSphereShape(1);


    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);


    btDefaultMotionState* fallMotionState =
            new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    btScalar mass = 1;
    btVector3 fallInertia(0, 0, 0);
    fallShape->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
    dynamicsWorld->addRigidBody(fallRigidBody);


    for (int i = 0; i < 300; i++) {
            dynamicsWorld->stepSimulation(1 / 60.f, 10);

            btTransform trans;
            fallRigidBody->getMotionState()->getWorldTransform(trans);

            std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
    }

    dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;

    dynamicsWorld->removeRigidBody(groundRigidBody);
    delete groundRigidBody->getMotionState();
    delete groundRigidBody;


    delete fallShape;

    delete groundShape;


    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;

}

PhysicalWorld::~PhysicalWorld(){
    for (Lumos::Instance* i : _instances){
        _dynamicsWorld->removeRigidBody(i->getRidgidBody());
        delete i->getRidgidBody()->getMotionState();
        delete i->getRidgidBody();
        delete i;
    }
    delete _broadphase;

    // Set up the collision configuration and dispatcher
    delete _collisionConfiguration;
    delete _dispatcher;

    // The actual physics solver
    delete _solver;

    // The world.
    delete _dynamicsWorld;
}

void PhysicalWorld::setDebugView(View_bullet * debugView){
    debugView->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
    _dynamicsWorld->setDebugDrawer(debugView);
}

void PhysicalWorld::draw(){
    if( _drawer )
        _dynamicsWorld->debugDrawWorld();
}



bool PhysicalWorld::loadInstance( Patronus::Mesh & mesh ){
    Lumos::Instance * newI = mesh.instantiate_sequentialDraw();
    std::string name = Utils::genUniqueName(_names, mesh.getId() + "_instance");

    newI->setId(name);
    _names.insert(name);

/*
    btTransform t;	//position and rotation
    t.setIdentity();
    point3 center = (mesh.getMinPos() + mesh.getMaxPos() ) / 2.0f;
    t.setOrigin(btVector3(center.x, center.y, center.z));	//put it to x,y,z coordinates
    btSphereShape* sphere=new btSphereShape(10.0f);	//it's a sphere, so use sphereshape
    btVector3 inertia(0,0,0);	//inertia is 0,0,0 for static object, else

    btMotionState* motion=new btDefaultMotionState(t);	//set the position (and motion)
    btRigidBody::btRigidBodyConstructionInfo info(0.0f,motion,sphere,inertia);	//create the constructioninfo, you can create multiple bodies with the same info
    btRigidBody* body=new btRigidBody(info);	//let's create the body itself
    _dynamicsWorld->addRigidBody(body);	//and let the world know about it
    //bodies.push_back(body);	//to be easier to clean, I store them a vector
    newI->setRidgidBody( body );
    _dynamicsWorld->addCollisionObject(body);
*/

    // generate collidable body for the instance
    point3 center = (mesh.getMinPos() + mesh.getMaxPos() ) / 2.0f;
    point3 scale = glm::abs( mesh.getMaxPos() - mesh.getMinPos() ) / 2.0f;
    btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));

    //btVector3 test = boxCollisionShape->getHalfExtentsWithMargin();
    btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
        btQuaternion(newI->getOrientation().x, newI->getOrientation().y, newI->getOrientation().z, 1.0f),
        btVector3(center.x, center.y, center.z)
    ));

    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        0.0f,                  // mass, in kg. 0 -> Static object, will never move.
        motionstate,
        boxCollisionShape,  // collision shape of body
        btVector3(0,0,0)    // local inertia
    );
    btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

    _dynamicsWorld->addRigidBody(rigidBody);
    newI->setRidgidBody( rigidBody );



    _instances.push_back(newI);



}


Lumos::Instance * PhysicalWorld::selectWithBean( const btVector3 & start, const btVector3 & end ){


    btCollisionWorld::ClosestRayResultCallback RayCallback(
        start,
        end
    );
    _dynamicsWorld->rayTest(
        start,
        end,
        RayCallback
    );

    if(RayCallback.hasHit()) {
        std::cout << "Hit instance " + reinterpret_cast<Lumos::Instance*>(RayCallback.m_collisionObject->getUserPointer())->getId() << std::endl;
        return reinterpret_cast<Lumos::Instance*>(RayCallback.m_collisionObject->getUserPointer());
    }else{
        qDebug() << "Hit background";
        return nullptr;
    }

}


}
