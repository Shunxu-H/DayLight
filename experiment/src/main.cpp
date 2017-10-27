#include <string>
#include <iostream>


#include <opencv2/opencv.hpp>

#include <EGL/egl.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "WindowManager.h"

static const EGLint configAttribs[] = {
      EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
      EGL_BLUE_SIZE, 8,
      EGL_GREEN_SIZE, 8,
      EGL_RED_SIZE, 8,
      EGL_DEPTH_SIZE, 8,
      EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
      EGL_NONE
};    

static const int pbufferWidth = 512;
static const int pbufferHeight = 512;

static const EGLint pbufferAttribs[] = {
    EGL_WIDTH, pbufferWidth,
    EGL_HEIGHT, pbufferHeight,
    EGL_NONE,
};


GLuint FBO = 0;
GLuint _ColorTextureObject = 0;
GLuint _DepthTextureObject = 0;


void logOpenGLError(const std::string & sourceFile ){

        // check OpenGL error
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::stringstream o;
        switch(err) {
            case GL_NO_ERROR:
                return;
                break;
            case GL_INVALID_ENUM:
                o <<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid enum!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_INVALID_VALUE:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid value!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_INVALID_OPERATION:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid operation!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_STACK_OVERFLOW:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Stack overflow!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_STACK_UNDERFLOW:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Stack underflow!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_OUT_OF_MEMORY:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Out Of memory!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            case GL_TABLE_TOO_LARGE:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Table too large!"<< std::endl;
                throw std::runtime_error(o.str());
                break;

            default:
                o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Unknown error!"<< std::endl;
                throw std::runtime_error(o.str());
                break;
        }
    }
}

void screenshot(const std::string & fileName){
    cv::Mat img(pbufferWidth, pbufferHeight, CV_8UC4);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    // glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    // glGetTexImage ( GL_TEXTURE_2D,
    //                 0,
    //                 GL_BGR, // GL will convert to this format
    //                 GL_UNSIGNED_BYTE,   // Using this data type per-pixel
    //                 img.data );

    glReadPixels(0, 0, img.cols, img.rows, GL_RGBA, GL_UNSIGNED_BYTE, img.data);
    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    cv::imwrite(fileName, img);
    std::cout << "screen shot!" << std::endl;
}

void DrawAQuad() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1., 1., -1., 1., 1., 20.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	glBegin(GL_QUADS);
	glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
	glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
	glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
	glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
	glEnd();

} 



void makeFrameBuffer(){

    GLint drawFboId = 0, readFboId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
    std::cout << "draw buffer in use: " << drawFboId << std::endl
          << "read buffer in use: " << readFboId << std::endl; 

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    std::cout << FBO << std::endl;
    logOpenGLError("genbuffer");

    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    logOpenGLError("Inside");
    // create a RGBA color texture

    glGenTextures(1, &_ColorTextureObject);
    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        pbufferWidth, pbufferHeight,
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);

    // create a depth texture
    glGenTextures(1, &_DepthTextureObject);
    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
                        pbufferWidth, pbufferHeight,
                        0, GL_DEPTH_COMPONENT, GL_FLOAT,
                        NULL);



    // attach color
    logOpenGLError("Inside2");
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorTextureObject, 0);
          logOpenGLError("Inside3");
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthTextureObject, 0);



    // check buffer status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error ( "Error! FrameBuffer is not complete" );


    //glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    GLint drawId = 0, readId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);


    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers


}


void printFramebufferInfo(GLenum target, GLuint fbo) {

    int res, i = 0;
    GLint buffer;

    glBindFramebuffer(target,fbo);

    do {
        glGetIntegerv(GL_DRAW_BUFFER0+i, &buffer);

        if (buffer != GL_NONE) {

            printf("Shader Output Location %d - color attachment %d\n",
                        i, buffer - GL_COLOR_ATTACHMENT0);

            glGetFramebufferAttachmentParameteriv(target, buffer,
                        GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &res);
            printf("\tAttachment Type: %s\n",
                        res==GL_TEXTURE?"Texture":"Render Buffer");
            glGetFramebufferAttachmentParameteriv(target, buffer,
                        GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &res);
            printf("\tAttachment object name: %d\n",res);
        }
        ++i;

    } while (buffer != GL_NONE);
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
  // 1. Initialize EGL
  EGLDisplay eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  EGLint major, minor;

  eglInitialize(eglDpy, &major, &minor);

  // 2. Select an appropriate configuration
  EGLint numConfigs;
  EGLConfig eglCfg;

  eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);

  // 3. Create a surface
  EGLSurface eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg, 
                                               pbufferAttribs);

  // 4. Bind the API
  eglBindAPI(EGL_OPENGL_API);

  // 5. Create a context and make it current
  EGLContext eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT, 
                                       NULL);

  eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);

  // from now on use your OpenGL context
  makeFrameBuffer();
  logOpenGLError("here");
  
  GLint drawFboId = 0, readFboId = 0;
  glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
  glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
  std::cout << "draw buffer in use: " << drawFboId << std::endl
        << "read buffer in use: " << readFboId << std::endl; 
  //printFramebufferInfo(GL_FRAMEBUFFER, drawFboId);
  glViewport(0, 0, pbufferWidth, pbufferHeight);
  std::cout << pbufferWidth << " " << pbufferHeight << std::endl;
  DrawAQuad();
  logOpenGLError("here2");
  screenshot("screenshot.png");

  

  // 6. Terminate EGL when finished
  eglTerminate(eglDpy);
  return 0;
}