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
#ifndef BTDEBUGDRAWER_H
#define BTDEBUGDRAWER_H

 #include "Common/GL_include.h"
#include "LinearMath/btIDebugDraw.h"

class GLDebugDrawer : public btIDebugDraw
{
        int m_debugMode;

   public:

        GLDebugDrawer();

        virtual void   drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

        virtual void   drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

        virtual void   reportErrorWarning(const char* warningString);

        virtual void   draw3dText(const btVector3& location,const char* textString);

        virtual void   setDebugMode(int debugMode);

        virtual int      getDebugMode() const { return m_debugMode;}

};

#endif // BTDEBUGDRAWER_H
