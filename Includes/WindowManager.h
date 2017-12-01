#ifndef WINDOWMANAGER_H
	#define WINDOWMANAGER_H

//#include "Renderer.h"


#include <opencv2/opencv.hpp>
/**
 * X11 for window management
 */
#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>


#include <EGL/egl.h>
#include "WindowManager_base.h"

class View;

class WindowManager : public WindowManager_base
{
public:
    // Disable copy constructor
    WindowManager( const WindowManager& ) = delete;
    // Disable assignment operator
    WindowManager& operator = ( const WindowManager& ) = delete;

    WindowManager(  const size_t &w = 500, 
                    const size_t &h = 500 );
    virtual ~WindowManager();
    void render();
/*
    void updateAllViews();

    void setUpProgram( const std::string & shaderDir );
    void setUpProgram( const std::vector<Lumos::Shader> & shader );

    void createMenus();


*/
    virtual void show() override;
    virtual int loop() override;
protected:

private:

    Display    *_x_display;
    Window      _win;
    EGLDisplay  _egl_display;
    EGLContext  _egl_context;
    EGLSurface  _egl_surface;
    GLXContext  _xContex;

    // View * _render_hidden_view;
    
    void _X11WindowInit();
    void _eglInitWithWindow();

    void _headlessInit();
    void _render();
    void _keyboard_handle(const XEvent & event);

};




	#endif
