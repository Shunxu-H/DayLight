#ifndef CONFIG_H
	#define CONFIG_H

#include "Color.h"
class Geometry;

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


	int curSelected;
	bool showNormal;
	bool showEdge;
	float COLOR_bg[4];
	float COLOR_outline[4];
	float COLOR_text[4];
	float COLOR_regStroke[4];
	float COLOR_hlStroke[4];
	float COLOR_fill[4];
	float COLOR_rotVec[4];
	float COLOR_axis[4];
	float COLOR_SELECTION_BOX[4];
	float COLOR_HIGHTLIGHTED_VERTEX[4];

	Config();
	bool isValidSelection();
};


	#endif 
