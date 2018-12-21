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
#include <typeinfo>
#include <Common/GL_include.h>
#include <IO/WindowManager.h>
#include <Common/Extern.h>
#include <Patronus/Shaper.h>

WindowManager_base::WindowManager_base( const size_t & w, const size_t & h )
	: Widget("Main", 0, 0, w, h)
{


}


void WindowManager_base::positionAllViewsToFitAllInstances(){
    // compute bounding circle
    point3 position;
    float radius;
    Patronus::Shaper::getBoundingSphere(Patronus::Shaper::global_vertices, &position, &radius);

    for( auto  w: _children ){
        dynamic_cast<PerspectiveView*>(w)->fitSphere(position, radius);
    }

}
