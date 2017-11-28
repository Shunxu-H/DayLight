#ifndef WINDOWMANAGER_HEADLESS_H
	#define WINDOWMANAGER_HEADLESS_H

//#include "Renderer.h"


#include <opencv2/opencv.hpp>
/**
 * X11 for window management
 */



#include <EGL/egl.h>
#include "WindowManager_base.h"

class View_renderer;
namespace Lumos {
    class Shader;
}

class Keyboard;
class WindowManager_headless : public WindowManager_base
{
public:
    // Disable copy constructor
    WindowManager_headless( const WindowManager_headless& ) = delete;
    // Disable assignment operator
    WindowManager_headless& operator = ( const WindowManager_headless& ) = delete;

    WindowManager_headless(  const size_t &w = 500, 
                        const size_t &h = 500 );
    virtual ~WindowManager_headless();
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
    View_renderer * _render_hidden_view;

    // View * _render_hidden_view;
    

    void _headlessInit();
    void _headlessInitWithX11();
    void _render();
    void _keyboard_handle(const XEvent & event);

};




	#endif
