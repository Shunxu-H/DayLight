

#include <experimental/filesystem>
#include <iostream>
#include <ctime>



#include "GL_include.h"
#include "WindowManager_headless.h"
#include "Shaper.h"
#include "Extern.h"
#include "Utility.h"


#include <unistd.h>
 

// #include "View.h"
// #include "View_bullet.h"
// #include "Shader.h"
// #include "Renderer.h"
// #include "View_renderer.h"
// #include "Utility.h"
// #include "Extern.h"


namespace fs = std::experimental::filesystem;

// GLfloat
//    norm_x    =  0.0,
//    norm_y    =  0.0,
//    offset_x  =  0.0,
//    offset_y  =  0.0,
//    p1_pos_x  =  0.0,
//    p1_pos_y  =  0.0;

// bool update_pos = false;


WindowManager_headless::WindowManager_headless(const size_t &w, const size_t &h )
    :WindowManager_base(w, h)
    ,_x_display(nullptr)
    ,_win(0)
    ,_egl_display(0)
    ,_egl_context(0)
    ,_egl_surface(0)
{
	_headlessInit();
    _render_hidden_view = new View_renderer(w, h);
    _render_hidden_view->initializeGL();

}



WindowManager_headless::~WindowManager_headless()
{

    ////  cleaning up...
    // eglDestroyContext ( _egl_display, _egl_context );
    // eglDestroySurface ( _egl_display, _egl_surface );
    // eglTerminate      ( _egl_display );
    glXMakeCurrent( _x_display, 0, 0 );
    //glXDestroyContext( _x_display, _xContex );

    XDestroyWindow( _x_display, _win );
    //XFreeColormap( _x_display, cmap );
    XCloseDisplay( _x_display );
}



void WindowManager_headless::_headlessInit(){

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
    _egl_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    EGLint major, minor;

    eglInitialize(_egl_display, &major, &minor);

    // 2. Select an appropriate configuration
    EGLint numConfigs;
    EGLConfig eglCfg;
    
    eglChooseConfig(_egl_display, configAttribs, &eglCfg, 1, &numConfigs);

    // 3. Create a surface
    _egl_surface = eglCreatePbufferSurface(_egl_display, eglCfg, 
                                               pbufferAttribs);

    // 4. Bind the API
    eglBindAPI(EGL_OPENGL_API);

    // 5. Create a context and make it current
    _egl_context = eglCreateContext(_egl_display, eglCfg, EGL_NO_CONTEXT, 
                                       NULL);

    eglMakeCurrent(_egl_display, _egl_surface, _egl_surface, _egl_context);
}


int WindowManager_headless::loop()
{
	render();
    return EXIT_SUCCESS;
} /* this is the } which closes int main(int argc, char *argv[]) { */


void WindowManager_headless::render(){

    
    
    double duration;
    int w = 1080, h = 720;
    clock_t start = std::clock();


    world->clearAll();
    shaper->clearAll();

    std::vector<std::experimental::filesystem::path> allobjpath;
    Utils::getAllDir(SCENE_FILE_DIR, allobjpath);

    for (const std::experimental::filesystem::path & p : allobjpath){
        std::cout << "Rendering: " << std::string(p).c_str() << std::endl;
        std::string curScope = p.stem();
        shaper->loadFile(std::string(p) + "/" + curScope + ".obj");
        Patronus::Camera::loadCamerasFromDir(CAMERA_DIR + curScope);
        gProgram->preDrawSetUp();

        Utils::cleanAndMkdir("./" + shaper->getCurFileName());

        for( size_t camPtr = 0; camPtr < shaper->getNumOfCameras(); camPtr++){
            _render_hidden_view->setCamInUse(shaper->getnCamera(camPtr));
            _render_hidden_view->resizeGL(w, h);
            _render_hidden_view->generateData();
        }

        world->clearAll();
        shaper->clearAll();
    }

    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << "Time passed: " << duration << std::endl;
     
}


void WindowManager_headless::show(){
	// _render_hidden_view->initializeGL();
}
/*

void WindowManager::updateAllViews(){
    for(View* & v : _views )
        v->update();
}

*/

