/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

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
		void render_infintitely();
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
