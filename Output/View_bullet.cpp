#include <QDebug>

#include <QtWidgets>
#include "btBulletDynamicsCommon.h"
#include "Instance.h"
#include "View_bullet.h"

#include "Extern.h"



View_bullet::View_bullet( QWidget *parent, const std::shared_ptr< Patronus::Camera > & cam )
    :View(parent, cam)
{

}


void View_bullet::paintGL(){
    if( gProgram == nullptr )
        return;

    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gProgram->use();
    gProgram->enableShadingPipe("bbox_shader");
    for(const Lumos::Instance & i : drawingInstances){
        i.renderBoundngBox(*this);
    }

    gProgram->disableShadingPipe("bbox_shader");
    /*
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();

    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    // The actual physics solver
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    // The world.
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0,-9.81f,0));
    btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

    btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
        0,                  // mass, in kg. 0 -> Static object, will never move.
        motionstate,
        boxCollisionShape,  // collision shape of body
        btVector3(0,0,0)    // local inertia
    );
    btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

    dynamicsWorld->addRigidBody(rigidBody);
*/

}

bool View_bullet::event(QEvent *event) {
    switch(event->type())
    {
    case QEvent::HoverEnter:
        hoverEnter(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverLeave:
        hoverLeave(static_cast<QHoverEvent*>(event));
        return true;
        break;
    case QEvent::HoverMove:
        hoverMove(static_cast<QHoverEvent*>(event));
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(event);
}

void View_bullet::hoverEnter(QHoverEvent *event){

}

void View_bullet::hoverLeave(QHoverEvent *event){

}

void View_bullet::hoverMove(QHoverEvent *event){
    //qDebug() << event->pos() ;
}
