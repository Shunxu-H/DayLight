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

enum ClipMode
{
	UP,
	RIGHT,
	DOWN,
	LEFT
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
	ClipMode clipMode;
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
