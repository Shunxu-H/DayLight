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
#include "btDebugDrawer.h"
#include <iostream>

#include <Common/GL_include.h>

using namespace Daylight::IO; 

GLDebugDrawer::GLDebugDrawer()
:m_debugMode(0)
{

}

void  GLDebugDrawer::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
{
   //      if (m_debugMode > 0)
   {
      //float tmp[ 6 ] = { from.getX(), from.getY(), from.getZ(),
      //              to.getX(), to.getY(), to.getZ() };

      // glPushMatrix();
      // {
      //    glColor4f(color.getX(), color.getY(), color.getZ(), 1.0f);
      //    glVertexPointer( 3,
      //                GL_FLOAT,
      //                0,
      //                &tmp );

      //    glPointSize( 5.0f );
      //    glDrawArrays( GL_POINTS, 0, 2 );
      //    glDrawArrays( GL_LINES, 0, 2 );
      // }
      // glPopMatrix();
   }
}

void GLDebugDrawer::setDebugMode(int debugMode)
{
   m_debugMode = debugMode;
}

void GLDebugDrawer::draw3dText(const btVector3& location,const char* textString)
{
//    //glRasterPos3f(location.x(),  location.y(),  location.z());
//    //BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
//     glPushMatrix();
//     glColor3f(1.0f, 0.0f, 0.0f);
//     //renderText(location[0], location[1], location[2], textString);
//     glPopMatrix();
}

void GLDebugDrawer::reportErrorWarning(const char *warningString)
{
   std::cout << warningString << std::endl;
}

void GLDebugDrawer::drawContactPoint(const btVector3& pointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color)
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
