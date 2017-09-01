#include <iostream>
#include <GL/glut.h>
#include "Cabinet.h"
#include "Config.h"
#include "Shader.h"
#include "Geometry.h"
#include "Edge.h"
#include "Mouse.h"

extern Config progConfig; 
extern Lumos::Shader* shader;

/*
void Cabinet::updateWindow(){

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	clear();

	// draw coordinate
	drawAxis();

	shader->drawAll();
	View::drawOutline();

	if( progConfig.opMode == CLIPPING )
		mouse->viewClipLine();
	
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, PixelBuffer.get());
	
}


void Cabinet::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    clear();

    // draw coordinate
    drawAxis();

    shader->drawAll();
    View::drawOutline();

    if( progConfig.opMode == CLIPPING )
        mouse->viewClipLine();

    glDrawPixels(width, height, GL_RGB, GL_FLOAT, PixelBuffer.get());
}

void Cabinet::drawLineDDA(Vector v1, Vector v2, float const* color){

	Matrix cabinetMatrix;
	cabinetMatrix.makeCabinet();
	v1.transform(cabinetMatrix);
	v2.transform(cabinetMatrix);
	OrthoView::drawLineDDA(v1, v2, color );
}

void Cabinet::drawLineBSH(const std::shared_ptr<Vector> &v1, const std::shared_ptr<Vector> &v2, float const* color){

}

void Cabinet::drawAxis(){
	Vector origin(0, 0, 0);
	origin.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	drawVertical(origin[axis1], progConfig.COLOR_axis);
	drawHorizontal(origin[axis2], progConfig.COLOR_axis);
	
	Vector zMin (0, 0, -100);
	Vector zMax (0, 0, 100);

	drawLineDDA(zMin, zMax, progConfig.COLOR_axis);
}
*/
