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
#ifndef WINDOWMANAGER_BASE_H
#define WINDOWMANAGER_BASE_H

#include <cstddef>
#include <vector>

#include "Widget.h"
class PerspectiveView;

class WindowManager_base : public Widget
{
public:
	WindowManager_base(
						const size_t & w = 500,
						const size_t & h = 500
						);
	virtual ~WindowManager_base(){};




		// move the camera so the all the meshes are shown
    void positionAllViewsToFitAllInstances();

    virtual int loop() = 0;
    virtual void show() = 0;

protected:

		virtual void _expose()=0;
		virtual void _keyboard_handle(const XEvent & xev)=0;
		virtual void _button_handle(const XEvent & xev)=0;
    std::vector< PerspectiveView* > _views;


private:

};




#endif
