#ifndef GL_INCLUDE_H
#define GL_INCLUDE_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

typedef glm::vec4 point4;
typedef glm::vec3 point3;
typedef glm::vec4 color4;

#define GLM_FORCE_RADIANS

#endif // GL_INCLUDE_H
