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
#ifndef COLOR_H
	#define COLOR_H

#include "GL_include.h"

class Color
{
public:
	Color();

    static int toUniqueInt( const int & r, const int & g, const int & b );
    static color3 toUniqueColor ( const int & i);


    const static color4 BLACK ;
    const static color4 DGREY ;
    const static color4 GREY  ;
    const static color4 LGREY ;
    const static color4 WHITE ;
    const static color4 RED   ;
    const static color4 GREEN ;
    const static color4 DGREEN;
    const static color4 BLUE  ;

	float* getColor(const float&,const float&, const float&);
	void print (float*);


protected:

private:
};


    #endif
