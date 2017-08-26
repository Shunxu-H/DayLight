#include <iostream>
#include "TextView.h"
#include "Keyboard.h"
#include "View.h"


//extern Keyboard View::keyboard;

TextView::TextView(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height)
	:View(vt, mainContext, loc_x, loc_y, window_width, window_height){


}

void TextView::updateWindow(){
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();

	// draw coordinate
	keyboard.renderInput();
	keyboard.renderTips();

}


void TextView::drawLineDDA(Vector v1, Vector v2, const float* color){

}

void TextView::drawAxis(){

}
