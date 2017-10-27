#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl31.h>
#include <assert.h>
#include <fcntl.h>
#include <gbm.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>
 
/* a dummy compute shader that does nothing */
#define COMPUTE_SHADER_SRC "          \
#version 310 es\n                                                       \
                                                                        \
layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;       \
                                                                        \
void main(void) {                                                       \
   /* awesome compute code here */                                      \
}                                                                       \
"
 
void screenshot(const std::string & fileName){
   cv::Mat img(100, 100, CV_8UC4);
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



int32_t
main (int32_t argc, char* argv[])
{
   bool res;
 
   int32_t fd = open ("/dev/dri/renderD128", O_RDWR);
   assert (fd > 0);
 
   struct gbm_device *gbm = gbm_create_device (fd);
   assert (gbm != NULL);
 
   /* setup EGL from the GBM device */
   EGLDisplay egl_dpy = eglGetPlatformDisplay (EGL_PLATFORM_GBM_MESA, gbm, NULL);
   assert (egl_dpy != NULL);
 
   res = eglInitialize (egl_dpy, NULL, NULL);
   assert (res);
 
   const char *egl_extension_st = eglQueryString (egl_dpy, EGL_EXTENSIONS);
   assert (strstr (egl_extension_st, "EGL_KHR_create_context") != NULL);
   assert (strstr (egl_extension_st, "EGL_KHR_surfaceless_context") != NULL);
 
   static const EGLint config_attribs[] = {
      EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
      EGL_NONE
   };
   EGLConfig cfg;
   EGLint count;
 
   res = eglChooseConfig (egl_dpy, config_attribs, &cfg, 1, &count);
   assert (res);
 
   res = eglBindAPI (EGL_OPENGL_ES_API);
   assert (res);
 
   static const EGLint attribs[] = {
      EGL_CONTEXT_CLIENT_VERSION, 3,
      EGL_NONE
   };
   EGLContext core_ctx = eglCreateContext (egl_dpy,
                                           cfg,
                                           EGL_NO_CONTEXT,
                                           attribs);
   assert (core_ctx != EGL_NO_CONTEXT);
 
   res = eglMakeCurrent (egl_dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, core_ctx);
   assert (res);
 
   /* setup a compute shader */
   GLuint compute_shader = glCreateShader (GL_COMPUTE_SHADER);
   assert (glGetError () == GL_NO_ERROR);
 
   const char *shader_source = COMPUTE_SHADER_SRC;
   glShaderSource (compute_shader, 1, &shader_source, NULL);
   assert (glGetError () == GL_NO_ERROR);
 
   glCompileShader (compute_shader);
   assert (glGetError () == GL_NO_ERROR);
 
   GLuint shader_program = glCreateProgram ();
 
   glAttachShader (shader_program, compute_shader);
   assert (glGetError () == GL_NO_ERROR);
 
   glLinkProgram (shader_program);
   assert (glGetError () == GL_NO_ERROR);
 
   glDeleteShader (compute_shader);
 
   glUseProgram (shader_program);
   assert (glGetError () == GL_NO_ERROR);
 
   /* dispatch computation */
   glDispatchCompute (1, 1, 1);
   assert (glGetError () == GL_NO_ERROR);
 
   printf ("Compute shader dispatched and finished successfully\n");


   glClearColor(1.0, 1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   screenshot("ScreenShot.png");

 
   /* free stuff */
   glDeleteProgram (shader_program);
   eglDestroyContext (egl_dpy, core_ctx);
   eglTerminate (egl_dpy);
   gbm_device_destroy (gbm);
   close (fd);
 
   return 0;
}