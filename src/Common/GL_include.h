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
#ifndef GL_INCLUDE_H
#define GL_INCLUDE_H

#include <opencv2/opencv.hpp>


#define GLM_FORCE_RADIANS
#define GL_GLEXT_PROTOTYPES

// #include <glbinding/gl/gl.h>
// #include <glbinding/Binding.h>
// #define GLEW_EGL
#include <gl3w/gl3w.h>
#ifdef __APPLE__
    #include <OpenGL/gl.h>
   #include <OpenGL/glext.h>
#else 
    #include <GL/gl.h>
    #include <GL/glx.h>
#endif
#include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>



typedef glm::vec4 point4;
typedef glm::vec3 point3;
typedef glm::vec2 point2;
typedef glm::vec3 color3;
typedef glm::vec4 color4;


#endif // GL_INCLUDE_H
