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
#include <experimental/filesystem>
#include <iostream>
#include <ctime>

#include <Common/GL_include.h>
#include <Common/Extern.h>
#include <Common/Utility.h>

#include <IO/WindowManagerX11.h>
#include <IO/PerspectiveView.h>

#include <Patronus/Shaper.h>

#include  <sys/time.h>

#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>

#include <unistd.h>


// #include "View.h"
// #include "View_bullet.h"
// #include "Shader.h"
// #include "Renderer.h"
// #include "View_renderer.h"
//  #include "Common/Utility.h"
// #include "Common/Extern.h"

using namespace Daylight::IO; 

namespace fs = std::experimental::filesystem;

// GLfloat
//    norm_x    =  0.0,
//    norm_y    =  0.0,
//    offset_x  =  0.0,
//    offset_y  =  0.0,
//    p1_pos_x  =  0.0,
//    p1_pos_y  =  0.0;

// bool update_pos = false;


#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

// Helper to check for extension string presence.  Adapted from:
//   http://www.opengl.org/resources/features/OGLextensions/
static bool isExtensionSupported(const char *extList, const char *extension)
{
    const char *start;
    const char *where, *terminator;

    /* Extension names should not have spaces. */
    where = strchr(extension, ' ');
    if (where || *extension == '\0')
        return false;

    /* It takes a bit of care to be fool-proof about parsing the
    OpenGL extensions string. Don't be fooled by sub-strings,
    etc. */
    for (start=extList;;) {
        where = strstr(start, extension);

        if (!where)
            break;

        terminator = where + strlen(extension);

        if ( where == start || *(where - 1) == ' ' )
            if ( *terminator == ' ' || *terminator == '\0' )
                return true;

        start = terminator;
    }

    return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler( Display *dpy, XErrorEvent *ev )
{
    ctxErrorOccurred = true;
    return 0;
}

WindowManagerX11::WindowManagerX11(const size_t &w, const size_t &h )
    :WindowManager(w, h)
    ,_x_display(nullptr)
    ,_win(0)
    ,_egl_display(0)
    ,_egl_context(0)
    ,_egl_surface(0)
    ,_xContex(0)
{

    _X11WindowInit();
    // gl3wExperimental = GL_TRUE;
    // assert(GLEW_OK == glewInit());

    glGetError();
    addChild(new PerspectiveView(0, 0, w, h));

}



WindowManagerX11::~WindowManagerX11()
{

    ////  cleaning up...
    // eglDestroyContext ( _egl_display, _egl_context );
    // eglDestroySurface ( _egl_display, _egl_surface );
    // eglTerminate      ( _egl_display );
    glXMakeCurrent( _x_display, 0, 0 );
    //glXDestroyContext( _x_display, ctx );

    XDestroyWindow( _x_display, _win );
    //XFreeColormap( _x_display, cmap );
    XCloseDisplay( _x_display );
}


void WindowManagerX11::_X11WindowInit(){
    _x_display = XOpenDisplay(NULL);

    if (!_x_display)
    {
        printf("Failed to open X _x_display\n");
        exit(EXIT_FAILURE);
    }

    // Get a matching FB config
    static int visual_attribs[] =
    {
        GLX_X_RENDERABLE    , True,
        GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
        GLX_RENDER_TYPE     , GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
        GLX_RED_SIZE        , 8,
        GLX_GREEN_SIZE      , 8,
        GLX_BLUE_SIZE       , 8,
        GLX_ALPHA_SIZE      , 8,
        GLX_DEPTH_SIZE      , 24,
        GLX_STENCIL_SIZE    , 8,
        GLX_DOUBLEBUFFER    , True,
        GLX_SAMPLE_BUFFERS  , 1,
        GLX_SAMPLES         , 4,
        None
    };

    int glx_major, glx_minor;

    // FBConfigs were added in GLX version 1.3.
    if ( !glXQueryVersion( _x_display, &glx_major, &glx_minor ) ||
    ( ( glx_major == 1 ) && ( glx_minor < 3 ) ) || ( glx_major < 1 ) )
    {
        printf("Invalid GLX version");
        exit(EXIT_FAILURE);
    }

    printf( "Getting matching framebuffer configs\n" );
    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(_x_display, DefaultScreen(_x_display), visual_attribs, &fbcount);
    if (!fbc)
    {
        printf( "Failed to retrieve a framebuffer config\n" );
        exit(EXIT_FAILURE);
    }
    printf( "Found %d matching FB configs.\n", fbcount );

    // Pick the FB config/visual with the most samples per pixel
    printf( "Getting XVisualInfos\n" );
    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    int i;
    for (i=0; i<fbcount; ++i)
    {
        XVisualInfo *vi = glXGetVisualFromFBConfig( _x_display, fbc[i] );
        if ( vi )
        {
            int samp_buf, samples;
            glXGetFBConfigAttrib( _x_display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf );
            glXGetFBConfigAttrib( _x_display, fbc[i], GLX_SAMPLES       , &samples  );

            std::cout << "  Matching fbconfig" << i
                 << ", visual ID 0x" << vi -> visualid
                 << ": SAMPLE_BUFFERS = "
                 << samp_buf <<
                 ", SAMPLES = " << samples
                 << std::endl;

            if ( (best_fbc < 0 || samp_buf) && (samples > best_num_samp) )
                best_fbc = i, best_num_samp = samples;
            if ( worst_fbc < 0 || !samp_buf || (samples < worst_num_samp) )
                worst_fbc = i, worst_num_samp = samples;
        }
        XFree( vi );
    }

    GLXFBConfig bestFbc = fbc[ best_fbc ];

    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
    XFree( fbc );

    // Get a visual
    XVisualInfo *vi = glXGetVisualFromFBConfig( _x_display, bestFbc );
    std::cout << "Chosen visual ID = 0x"
        << vi->visualid << std::endl;

    printf( "Creating colormap\n" );
    XSetWindowAttributes swa;
    Colormap cmap;
    swa.colormap = cmap = XCreateColormap(  _x_display,
                                            RootWindow( _x_display, vi->screen ),
                                            vi->visual,
                                            AllocNone );
    swa.background_pixmap = None ;
    swa.border_pixel      = 0;
    swa.event_mask        = ExposureMask | KeyPressMask | ButtonPress;

    printf( "Creating window\n" );
    _win = XCreateWindow( _x_display, RootWindow( _x_display, vi->screen ),
                      0, 0, _width, _height, 0, vi->depth, InputOutput,
                      vi->visual,
                      CWBorderPixel|CWColormap|CWEventMask, &swa );
    if ( !_win )
    {
        printf( "Failed to create window.\n" );
        exit(EXIT_FAILURE);
    }

    // Done with the visual info data
    XFree( vi );

    XStoreName( _x_display, _win, "Daylight" );

    printf( "Mapping window\n" );
    XMapWindow( _x_display, _win );

    // Get the default screen's GLX extension list
    const char *glxExts = glXQueryExtensionsString( _x_display,
                                                    DefaultScreen( _x_display ) );

    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
    glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB" );


    // Install an X error handler so the application won't exit if GL 3.0
    // context allocation fails.
    //
    // Note this error handler is global.  All _x_display connections in all threads
    // of a process use the same error handler, so be sure to guard against other
    // threads issuing X commands while this code is running.
    ctxErrorOccurred = false;
    int (*oldHandler)(Display*, XErrorEvent*) =
    XSetErrorHandler(&ctxErrorHandler);

    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
    if ( !isExtensionSupported( glxExts, "GLX_ARB_create_context" ) ||
    !glXCreateContextAttribsARB )
    {
        printf( "glXCreateContextAttribsARB() not found"
        " ... using old-style GLX context\n" );
        _xContex = glXCreateNewContext( _x_display, bestFbc, GLX_RGBA_TYPE, 0, True );
    }

    // If it does, try to get a GL 3.0 context!
    else
    {
        int context_attribs[] =
        {
            GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
            GLX_CONTEXT_MINOR_VERSION_ARB, 0,
            //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
            None
        };

        printf( "Creating context\n" );
        _xContex = glXCreateContextAttribsARB( _x_display, bestFbc, 0,
                                  True, context_attribs );

        // Sync to ensure any errors generated are processed.
        XSync( _x_display, False );
        if ( !ctxErrorOccurred && _xContex )
            printf( "Created GL 3.0 context\n" );
        else
        {
            // Couldn't create GL 3.0 context.  Fall back to old-style 2.x context.
            // When a context version below 3.0 is requested, implementations will
            // return the newest context version compatible with OpenGL versions less
            // than version 3.0.
            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
            context_attribs[1] = 1;
            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
            context_attribs[3] = 0;

            ctxErrorOccurred = false;

            printf( "Failed to create GL 3.0 context"
                    " ... using old-style GLX context\n" );
            _xContex = glXCreateContextAttribsARB( _x_display, bestFbc, 0,
                                        True, context_attribs );
        }
    }

    // Sync to ensure any errors generated are processed.
    XSync( _x_display, False );

    // Restore the original error handler
    XSetErrorHandler( oldHandler );

    if ( ctxErrorOccurred || !_xContex )
    {
        printf( "Failed to create an OpenGL context\n" );
        exit(EXIT_FAILURE);
    }

    // Verifying that context is a direct context
    if ( ! glXIsDirect ( _x_display, _xContex ) )
        printf( "Indirect GLX rendering context obtained\n" );
    else
        printf( "Direct GLX rendering context obtained\n" );



    printf( "Making context current\n" );
    glXMakeCurrent( _x_display, _win, _xContex );


}


bool WindowManagerX11::_expose(){
    render();
    return true;
}


void WindowManagerX11::show(){

}


void WindowManagerX11::_eglInitWithWindow(){

    ///////  the egl part  //////////////////////////////////////////////////////////////////
    //  egl provides an interface to connect the graphics related functionality of openGL ES
    //  with the windowing interface and functionality of the native operation system (X11
    //  in our case.

    _egl_display  =  eglGetDisplay( (EGLNativeDisplayType) _x_display );
    if ( _egl_display == EGL_NO_DISPLAY ) {
        std::cerr << "Got no EGL _x_display." << std::endl;
        exit (EXIT_FAILURE);
    }

    if ( !eglInitialize( _egl_display, NULL, NULL ) ) {
        std::cerr << "Unable to initialize EGL" << std::endl;
        exit (EXIT_FAILURE);
    }

    EGLint attr[] = {       // some attributes to set up our egl-interface
        EGL_BUFFER_SIZE, 16,
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLConfig  ecfg;
    EGLint     num_config;
    if ( !eglChooseConfig( _egl_display, attr, &ecfg, 1, &num_config ) ) {
        std::cerr << "Failed to choose config (eglError: " << eglGetError() << ")" << std::endl;
        exit (EXIT_FAILURE);
    }

    if ( num_config != 1 ) {
        std::cerr << "Didn't get exactly one config, but " << num_config << std::endl;
        exit (EXIT_FAILURE);
    }

    _egl_surface = eglCreateWindowSurface ( _egl_display, ecfg, _win, NULL );
    if ( _egl_surface == EGL_NO_SURFACE ) {
        std::cerr << "Unable to create EGL surface (eglError: " << eglGetError() << ")" << std::endl;
        exit (EXIT_FAILURE);
    }

    //// egl-contexts collect all state descriptions needed required for operation
    EGLint ctxattr[] = {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE
    };
    _egl_context = eglCreateContext ( _egl_display, ecfg, EGL_NO_CONTEXT, ctxattr );
        if ( _egl_context == EGL_NO_CONTEXT ) {
        std::cerr << "Unable to create EGL context (eglError: " << eglGetError() << ")" << std::endl;
        exit (EXIT_FAILURE);
    }

    //// associate the egl-context with the egl-surface
    eglMakeCurrent( _egl_display, _egl_surface, _egl_surface, _egl_context );

}

void WindowManagerX11::_headlessInit(){

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


bool WindowManagerX11::_keyboard_handle(const KeyboardEvent & event){

    if (event.action == Action::KEY_DOWN)
    {
        printf( "KeyPress: %x\n", event.code );


        /* exit on ESC key press */
        if(event.code == 0x09){
            glXMakeCurrent(_x_display, None, NULL);
            glXDestroyContext(_x_display, _xContex);
            XDestroyWindow(_x_display, _win);
            XCloseDisplay(_x_display);

            exit(EXIT_SUCCESS);

        }
        else if (event.code == 0x27) // press 's' for SCREEN SHOT
        {
            //screenshot("snapshot.png");
            printf("screen shot!\n" );
        }
    }
    else if (event.action == Action::KEY_UP)
    {
        printf( "KeyRelease: %x\n", event.code );
    }
    return true;
}

bool WindowManagerX11::_cursor_handle(const CursorEvent & event){

    // if (event.isPressEvent())
    // {
    //     Debug( "Buton presses at " << event.loc.x << ", "
    //               << event.loc.y  );
    //     switch (event.type) {
    //       case Button1: // left
    //       Debug("Button1");
    //       break;
    //       case Button2: // middle
    //       Debug("Button2");
    //       break;
    //       case Button3: // right
    //       Debug("Button3");
    //       break;
    //       case Button4:// wheel up
    //       Debug("Button4");
    //       break;
    //       case Button5: // wheel down
    //       Debug("Button5");
    //       break;
    //       default:
    //       Debug("Unknow button " << event.xbutton.button);
    //     }
    // }
    // else if (event.xbutton.type == ButtonRelease) // press 's' for SCREEN SHOT
    // {
    //     Debug("Release at " << event.xbutton.x << ", "
    //               << event.xbutton.y);
    // }

    return true;
}



int WindowManagerX11::loop()
{
    std::cout << "Start looping" << std::endl;
    XEvent xev;
    while(true) {
        XNextEvent(_x_display, &xev);

        if(xev.type == Expose
            && xev.xexpose.count==0) { // only render immediate exposures
            _internal_expose_handle();
        }
        else if(xev.type == KeyPress) {
            _internal_keyboard_handle(xev);
        }
        else if (xev.type==ButtonPress) {
            _internal_cursor_handle(CursorEvent(xev));
        }
        else
          std::cout << "Unrecognized events" << std::endl;
          
        glXSwapBuffers(_x_display, _win);
    } /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */


void WindowManagerX11::render(){

}

/*
void WindowManagerX11::updateAllViews(){
    for(View* & v : _views )
        v->update();
}

*/
