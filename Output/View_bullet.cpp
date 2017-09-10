#include <QDebug>

#include <QtWidgets>
#include "btBulletDynamicsCommon.h"
#include "Instance.h"
#include "View_bullet.h"

#include "Extern.h"



View_bullet::View_bullet( QWidget *parent, const std::shared_ptr< Patronus::Camera > & cam )
    :View(parent, cam), m_debugMode(1)
{
    world->setDebugView(this);
}

void View_bullet::resizeGL(int w, int h){
//    world->getWorld()->reshape(w,h);
}


void View_bullet::paintGL(){
    if( gProgram == nullptr )
        return;
    gProgram->use();
    //glClearColor(0.5, 0.5, 0.5, 1); // black
    gProgram->enableShadingPipe("bbox_shader");
    world->getWorld()->debugDrawWorld();
    gProgram->disableShadingPipe("bbox_shader");
    /*
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gProgram->use();
    gProgram->enableShadingPipe("bbox_shader");
    for(const Lumos::Instance & i : world->getInstances()){
        i.renderBoundngBox(*this);
    }

    gProgram->disableShadingPipe("bbox_shader");
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


void  View_bullet::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
   //      if (m_debugMode > 0)
    float vertices[6] = {
                    from[0], from[1], from[2],
                    to[0], to[1], to[2]
                    };

    gProgram->setUniform("ModelViewProjectionMatrix",
                         getCamInUse()->getProjectionMatrix(static_cast<float>(width())/static_cast<float>(height()) )*
                         getCamInUse()->getPerspectiveMatrix());

    gProgram->setUniform("color", color3(color.x(), color.y(), color.z()));
    GLuint vbo_vertices;
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //glm::mat4 m = _meshPtr->getModelMatrix() * transform;
    //glUniformMatrix4fv(uniform_m, 1, GL_FALSE, glm::value_ptr(m));

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glEnableVertexAttribArray(gProgram->getAttrib("vert"));
    glVertexAttribPointer(
    gProgram->getAttrib("vert"),  // attribute
        3,                  // number of elements per vertex, here (x,y,z,w)
        GL_FLOAT,           // the type of each element
        GL_FALSE,           // take our values as-is
        0,                  // no extra data between each position
        0                   // offset of first element
    );





    glDrawArrays(GL_LINE_STRIP, 0, 6);

    //glDisableVertexAttribArray(attribute_v_coord);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &vbo_vertices);



}

void View_bullet::setDebugMode(int debugMode)
{
   m_debugMode = debugMode;
}

void View_bullet::draw3dText(const btVector3& location,const char* textString)
{
   //glRasterPos3f(location.x(),  location.y(),  location.z());
   //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    qDebug() << textString;
    glPopMatrix();
}

void View_bullet::reportErrorWarning(const char* warningString)
{
   printf(warningString);
}

void View_bullet::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
{
   {
      //btVector3 to=pointOnB+normalOnB*distance;
      //const btVector3&from = pointOnB;
      //glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);

      //GLDebugDrawer::drawLine(from, to, color);

      //glRasterPos3f(from.x(),  from.y(),  from.z());
      //char buf[12];
      //sprintf(buf," %d",lifeTime);
      //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
   }
}

