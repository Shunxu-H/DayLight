#include <experimental/filesystem>
#include <iostream>
#include <ctime>


#include <opencv2/opencv.hpp>
#include <EGL/egl.h>
#include "GL_include.h"
#include "WindowManager.h"
#include "Shaper.h"

// #include "View.h"
// #include "View_bullet.h"
// #include "Shader.h"
// #include "Renderer.h"
// #include "View_renderer.h"
// #include "Utility.h"
// #include "Extern.h"


namespace fs = std::experimental::filesystem;



WindowManager::WindowManager()
{

}



WindowManager::~WindowManager()
{

}

void WindowManager::_headlessInit(){

    static const EGLint configAttribs[] = {
    EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_DEPTH_SIZE, 8,
    EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
    EGL_NONE
    };  

    static const EGLint pbufferAttribs[] = {
        EGL_WIDTH, static_cast<int>(_width),
        EGL_HEIGHT, static_cast<int>(_height),
        EGL_NONE,
    };
  

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
}

void WindowManager::render(){
    /*
    double duration;
    int w = 1080, h = 720;
    clock_t start = std::clock();


    world->clearAll();
    shaper->clearAll();

    std::vector<std::experimental::filesystem::path> allobjpath;
    Utils::getAllDir(SCENE_FILE_DIR, allobjpath);

    for (const std::experimental::filesystem::path & p : allobjpath){
        qDebug() << "Rendering: " << std::string(p).c_str();
        std::string curScope = p.stem();
        shaper->loadFile(std::string(p) + "/" + curScope + ".obj");
        Patronus::Camera::loadCamerasFromDir(CAMERA_DIR + curScope);
        gProgram->preDrawSetUp();

        Utils::cleanAndMkdir("./" + shaper->getCurFileName());

        for( size_t camPtr = 0; camPtr < shaper->getNumOfCameras(); camPtr++){
            _render_hidden_view->setCamInUse(shaper->getnCamera(camPtr));
            _render_hidden_view->resize(w, h);
            _render_hidden_view->generateData();
        }

        world->clearAll();
        shaper->clearAll();
    }

    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    qDebug() << "Time passed: " << duration;

    */
}
/*

void WindowManager::updateAllViews(){
    for(View* & v : _views )
        v->update();
}

*/

void WindowManager::positionAllViewsToFitAllInstances(){
    // compute bounding circle
    point3 position;
    float radius;
    Patronus::Shaper::getBoundingSphere(Patronus::Shaper::global_vertices, &position, &radius);

    for( View * v: _views )
        v->fitSphere(position, radius);

}

