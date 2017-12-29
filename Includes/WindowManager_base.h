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


class PerspectiveView;

class WindowManager_base
{
public:
	WindowManager_base(
						const size_t & w = 500,
						const size_t & h = 500
						);
	virtual ~WindowManager_base(){};



	inline size_t
    	getWidth() const { return _width; }
    inline  void
    	setWidth( const size_t & w) {  _width = w; }
    inline size_t
    	getHeight() const { return _height; }
    inline  void
    	setHeight( const size_t & h) {  _height = h; }

		// move the camera so the all the meshes are shown
    void positionAllViewsToFitAllInstances();

    virtual int loop() = 0;
    virtual void show() = 0;

protected:

    std::vector< PerspectiveView* > _views;

	size_t _width;
	size_t _height;

private:

};




#endif
