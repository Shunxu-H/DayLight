#ifndef GL_INCLUDE_H
#define GL_INCLUDE_H

#include <opencv2/opencv.hpp>


#define GLM_FORCE_RADIANS
//#include <QOpenGLFunctions_4_5_Core>
#define GL_GLEXT_PROTOTYPES

// #include <glbinding/gl/gl.h>
// #include <glbinding/Binding.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glext.h>



typedef glm::vec4 point4;
typedef glm::vec3 point3;
typedef glm::vec2 point2;
typedef glm::vec3 color3;
typedef glm::vec4 color4;


#endif // GL_INCLUDE_H
