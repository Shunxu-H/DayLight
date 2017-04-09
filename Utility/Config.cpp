#include <cstring>
#include "Config.h"
#include "Color.h"
#include "Shader.h"


extern Shader* shader;

Config::Config()
{
	lineAlg = DDA;
	opMode = DRAWING;
	fillMode = OUTLINE;
	renderMode = NORMAL;
	curSelected = 0;
	showNormal = true;
	showEdge = false;
	drawMode = DRAWCURVE;
	selectMode = VERTEX;
	memcpy(COLOR_bg, color.DGREY, sizeof(COLOR_bg));
	memcpy(COLOR_outline, color.WHITE, sizeof(COLOR_bg));
	memcpy(COLOR_axis, color.LGREY, sizeof(COLOR_bg));
	memcpy(COLOR_text, color.DGREEN, sizeof(COLOR_text));
	memcpy(COLOR_regStroke, color.WHITE, sizeof(COLOR_regStroke));
	memcpy(COLOR_hlStroke, color.BLUE, sizeof(COLOR_hlStroke));
	memcpy(COLOR_fill, color.BLACK, sizeof(COLOR_fill));
	memcpy(COLOR_rotVec, color.BLUE, sizeof(COLOR_fill));
	memcpy(COLOR_SELECTION_BOX, color.GREY, sizeof(COLOR_fill));
	memcpy(COLOR_HIGHTLIGHTED_VERTEX, color.GREEN, sizeof(COLOR_fill));


	
}


bool Config::isValidSelection(){
	return shader->nGetGeo(curSelected) != nullptr;
}		
