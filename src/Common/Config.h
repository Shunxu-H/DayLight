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
#ifndef CONFIG_H
	#define CONFIG_H

#include "Color.h"


const int INITIAL_WIN_SIZE[] = {500, 500};

enum CurveType {
	BEZIER,
	BSPLINE
};

enum ObjType{
	VERTEX,
	EDGE,
	CURVE,
	POLYGON,
	POLYHEDRON,
	ELLIPSOID,
	LINE,
	OBJTYPE_COUNT
};

enum LineAlg
{
	DDA, // Digital Differential Analyzer
	BSH // Brosenham's algorithm
};

enum OpMode
{
    NAVIGATING,
	SELECTING,
	DRAWING,
	MOVING,
	INSERT,
	CLIPPING,
	EDITING,
	TRANSFORM
};

enum DrawMode
{
	DRAWCURVE,
	DRAWSHAPE
};

enum ColorMode
{
	RGB,
	RGBA
};

enum FillMode
{
	HALFTONE,
	OUTLINE,
	FILL,
	COUNT
};

enum RenderMode
{
	NORMAL,
	HIGHLIGHT
};

enum TransfromMode
{
	UNSET,
	TRANSLATE,
	SCALE,
	ROTATE
};

typedef ObjType SelectMode;

struct Config
{
	Color color;
	LineAlg lineAlg;
	OpMode opMode;
	FillMode fillMode;
	RenderMode renderMode;
	TransfromMode transMode;
	DrawMode drawMode;
	SelectMode selectMode;



    color4 COLOR_bg;
    color4 COLOR_outline;
    color4 COLOR_text;
    color4 COLOR_regStroke;
    color4 COLOR_hlStroke;
    color4 COLOR_fill;
    color4 COLOR_rotVec;
    color4 COLOR_axis;
    color4 COLOR_SELECTION_BOX;
    color4 COLOR_HIGHTLIGHTED_VERTEX;

	Config();

};


	#endif
