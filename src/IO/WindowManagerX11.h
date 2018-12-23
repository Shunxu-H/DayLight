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
#pragma once

//#include "Renderer.h"


#include <opencv2/opencv.hpp>
/**
 * X11 for window management
 */
#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>


#include <EGL/egl.h>

#include <IO/WindowManager.h>
#include <IO/Event/CursorEvent.h>
#include <IO/Event/KeyboardEvent.h>


namespace Daylight::IO{

class WindowManagerX11 : public WindowManager
{
public:
    // Disable copy constructor
    WindowManagerX11( const WindowManagerX11& ) = delete;
    // Disable assignment operator
    WindowManagerX11& operator = ( const WindowManagerX11& ) = delete;

    WindowManagerX11(  const size_t &w = 500,
                    const size_t &h = 500 );
    virtual ~WindowManagerX11();
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
		virtual bool _expose() override;
		virtual bool _keyboard_handle(const KeyboardEvent & event)override;
		virtual bool _cursor_handle (const CursorEvent & event)override;
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

};

}