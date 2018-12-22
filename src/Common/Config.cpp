#include <cstring>
#include "Config.h"
#include "Color.h"

using namespace Daylight; 

Config::Config()
{
	lineAlg = DDA;
    opMode = NAVIGATING;
	fillMode = OUTLINE;
    renderMode = NORMAL;
	drawMode = DRAWCURVE;
	selectMode = VERTEX;

    COLOR_bg                    = color.DGREY;
    COLOR_outline               = color.WHITE;
    COLOR_axis                  = color.LGREY;
    COLOR_text                  = color.DGREEN;
    COLOR_regStroke             = color.WHITE;
    COLOR_hlStroke              = color.BLUE;
    COLOR_fill                  = color.BLACK;
    COLOR_rotVec                = color.BLUE;
    COLOR_SELECTION_BOX         = color.GREY;
    COLOR_HIGHTLIGHTED_VERTEX   = color.GREEN;


	
}

	
