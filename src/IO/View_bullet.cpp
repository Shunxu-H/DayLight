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

#include <btBulletDynamicsCommon.h>
#include <Common/Extern.h>

#include <Lumos/Instance.h>
#include <Patronus/PhysicalWorld.h>
#include <Patronus/Camera.h>

#include <Lumos/Program.h>

#include <IO/View_bullet.h>


using namespace Daylight::IO; 

View_bullet::View_bullet(
    const size_t & x,
    const size_t & y,
    const size_t & w,
    const size_t & h,
    const std::shared_ptr< Daylight::Patronus::Camera > & cam )
:PerspectiveView(x, y, w, h, cam), m_debugMode(1)
{
    world->setDebugView(this);
}

void View_bullet::resizeGL(const size_t & w, const size_t & h){
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

void  View_bullet::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{



    float vertices[6] = {
                    from[0], from[1], from[2],
                    to[0], to[1], to[2]
                    };

    gProgram->setUniform("ModelViewProjectionMatrix",
                         getCamInUse()->getProjectionMatrix(static_cast<float>(_width)/static_cast<float>(_height) )*
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
    // glPushMatrix();
    // glColor3f(1.0f, 0.0f, 0.0f);
    // std::cout << textString << std::endl;
    // glPopMatrix();
}

void View_bullet::reportErrorWarning(const char* warningString)
{
   std::cerr << warningString << std::endl;
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
