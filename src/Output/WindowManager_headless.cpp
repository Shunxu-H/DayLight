
#include <iterator>
#include <experimental/filesystem>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>



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
// 

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
typedef Bool (*glXMakeContextCurrentARBProc)(Display*, GLXDrawable, GLXDrawable, GLXContext);
static glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
static glXMakeContextCurrentARBProc   glXMakeContextCurrentARB   = NULL;




WindowManager_headless::WindowManager_headless(const size_t &w, const size_t &h )
    :WindowManager_base(w, h)
    ,_x_display(nullptr)
    ,_win(0)
    ,_egl_display(0)
    ,_egl_context(0)
    ,_egl_surface(0)
{
    _headlessInitWithX11();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    
    glewExperimental = GL_TRUE;
    assert(GLEW_OK == glewInit());
    glGetError();
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
   
    _render_hidden_view = new View_renderer(w, h);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    _render_hidden_view->initializeGL();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

}


void WindowManager_headless::_headlessInitWithX11(){
    

    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );
    glXMakeContextCurrentARB   = (glXMakeContextCurrentARBProc)   glXGetProcAddressARB( (const GLubyte *) "glXMakeContextCurrent"      );

    const char *displayName = NULL;
    Display* display = XOpenDisplay( displayName );

    assert(display != nullptr);

    static int visualAttribs[] = { None };
    int numberOfFramebufferConfigurations = 0;
    GLXFBConfig* fbConfigs = glXChooseFBConfig( display, DefaultScreen(display), visualAttribs, &numberOfFramebufferConfigurations );


    int context_attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
        GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
        None
    };
     
    GLXContext openGLContext = glXCreateContextAttribsARB( display, fbConfigs[0], 0, True, context_attribs);

    int pbufferAttribs[] = {
        GLX_PBUFFER_WIDTH,  static_cast<int>( _width ),
        GLX_PBUFFER_HEIGHT, static_cast<int>( _height ),
        None
    };

    GLXPbuffer pbuffer = glXCreatePbuffer( display, fbConfigs[0], pbufferAttribs );
     
    // clean up:
    XFree( fbConfigs );
    XSync( display, False );
     
    if ( !glXMakeContextCurrent( display, pbuffer, pbuffer, openGLContext ) )
    {
        std::cerr << "Failed to acquire OpenGL context for headless setup. " << std::endl;
    }
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
   
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

    std::cout << "EGL version: " << major << "." << minor << std::endl;

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

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
	render();
    return EXIT_SUCCESS;
} /* this is the } which closes int main(int argc, char *argv[]) { */


void WindowManager_headless::render(){

    
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    double duration;
    int w = 1080, h = 720;
    clock_t start = std::clock();


    world->clearAll();
    shaper->clearAll();

    std::ifstream obj_file (RENDER_LIST);
    if(!obj_file.is_open())
        throw std::runtime_error("RENDER_LIST NOT FOUND.");
    std::vector<std::string> v_objs;
    std::copy(  std::istream_iterator<std::string>(obj_file),
                std::istream_iterator<std::string>(),
                back_inserter(v_objs));

    std::vector<std::experimental::filesystem::path> allobjpath;
    Utils::getAllDir(SCENE_FILE_DIR, allobjpath, v_objs);
    std::cout << "Start rendering " << allobjpath.size() << " files." << std::endl;
    //Utils::cleanAndMkdir("./output");

    _render_hidden_view->resizeGL(w, h);
    size_t  numToRender = allobjpath.size(),
            indx = 0;
    for (const std::experimental::filesystem::path & p : allobjpath){
        try{
            
            GLError( __PRETTY_FUNCTION__ , __LINE__ );

            std::cout << "[";
            std::cout << static_cast<int>(  static_cast<float> (++indx) / static_cast<float> (numToRender) * 100 );
            std::cout << std::setw(4) << std::right << std::setfill(' ')  ;
            std::cout << std::resetiosflags(std::ios::showbase)   << "%] Rendering: " << std::string(p).c_str() << std::endl;
            std::string curScope = p.stem();
            if (std::experimental::filesystem::exists(OUTPUT_DIR + curScope)){
                std::cerr << "Directory exists, skipped current set of data..." << std::endl;
                continue;
            }
            shaper->loadFile(std::string(p) + "/" + curScope + ".obj");
            Patronus::Camera::loadCamerasFromDir(CAMERA_DIR + curScope);
            gProgram->preDrawSetUp();

            Utils::cleanAndMkdir(OUTPUT_DIR + shaper->getCurFileName());

            GLError( __PRETTY_FUNCTION__ , __LINE__ );
            for( size_t camPtr = 0; camPtr < shaper->getNumOfCameras(); camPtr++){

                GLError( __PRETTY_FUNCTION__ , __LINE__ );
                _render_hidden_view->setCamInUse(shaper->getnCamera(camPtr));

                GLError( __PRETTY_FUNCTION__ , __LINE__ );
                _render_hidden_view->generateData();
            }

            world->clearAll();
            shaper->clearAll();
        }
        catch (const std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            std::cerr << "Cleaning unfinished data..." << std::endl;
            Utils::remove_all(OUTPUT_DIR + shaper->getCurFileName());
        } 
        catch (const std::string& ex) {
            std::cerr << ex << std::endl;
            std::cerr << "Cleaning unfinished data..." << std::endl;
            Utils::remove_all(OUTPUT_DIR + shaper->getCurFileName());  
        } 
        catch (...) {
            std::cerr << "Undefined Crash occured." << std::endl;
            std::cerr << "Cleaning unfinished data..." << std::endl;
            Utils::remove_all(OUTPUT_DIR + shaper->getCurFileName()); 
        }
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

