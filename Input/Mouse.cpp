#include <iostream>
#include <vector>
#include <cstdio>
#include <ctgmath>
#include <memory>
#include <cstddef>
#include <limits>
#include "Mouse.h"
#include "Config.h"
#include "Geometry.h"
#include "Shader.h"
#include "Matrix.h"
#include "WindowManager.h"
#include "Index.h"
#include "Object.h"
#include "Edge.h"
#include "Curve.h"
#include "OrthoView.h"
#include "CVM.h"

extern WindowManager* winMan;
extern Config progConfig;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;
extern std::shared_ptr<Curve> curveBuffer;
extern Shader* shader;

#define _USE_MATH_DEFINES
/*
Mouse::Mouse(){
	view = nullptr;
	isTranslating = false;
	isSelecting = false;
	isAddingVertex = false;
	isRotatingCamera = false;
	selectedArea[0] = Vector(-1, -1, 0);
	selectedArea[1] = Vector(-1, -1, 0);
	//isDragging = false;
	for ( int i = 0; i < 2; i++){
		curPos[i] = 0.0f;
		prevPos[i] = 0.0f;
	}
}

Mouse::Mouse( View* _v):view(_v){
	//isDragging = false;
	isTranslating = false;
	isRotatingCamera = false;
	selectedArea[0] = Vector(-1, -1, 0);
	selectedArea[1] = Vector(-1, -1, 0);
	for ( int i = 0; i < 2; i++){
		curPos[i] = 0.0f;
		prevPos[i] = 0.0f;
	}
}


void Mouse::mouseHold(int x, int y)
{
	//std::cout << x << " " << y << std::endl;


	if(progConfig.opMode == DRAWING){
		if (progConfig.drawMode == DRAWCURVE)
		{
			// if(curveBuffer->size() > 0)
			// {
			// 	curveBuffer->pop();
			// 	std::shared_ptr<Vector> v = std::make_shared<Vector>(); // (new Vector(x, h- y, 0));
			// 	(*v)[view->axis1] = x;
			// 	(*v)[view->axis2] = y;
			// 	v->toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
			// 	*curveBuffer += v;
			// }
		}
		// if ( vertexBuffer->size() > 0){
		// 	vertexBuffer->pop();
		// 	std::shared_ptr<Vector> v (new Vector(x, h- y, 0));
		// 	v->toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
		// 	*vertexBuffer += v;
		// }
	}
	else if (progConfig.opMode == MOVING){

		if(view->isOrthoView()){
			// view->coordLoc[view->axis1] -= (x - prevPos[X])/view->pixelsPerUnit;
			// view->coordLoc[view->axis2] -= (y - prevPos[Y])/view->pixelsPerUnit;
			// prevPos[view->axis1] = x;
			// prevPos[view->axis2] = y; 
		}
		else if(view->isCVM()){
			if (isRotatingCamera){
                //dynamic_cast<CVM*>(view)->rotateCamera(Vector(prevPos[X] - x,y - prevPos[Y], 0));
			}			
			else {
                //dynamic_cast<CVM*>(view)->translateCamera(Vector(x - prevPos[X], - (y - prevPos[Y]), 0));
			}
			prevPos[X] = x;
			prevPos[Y] = y; 
		}
	}
	else if (progConfig.opMode == EDITING)
	{

		if (isTranslating){

			// Vector v1(prevPos[X], prevPos[Y], prevPos[Z]);
			// Vector v2;

			// v2[view->axis1] = x;
			// v2[view->axis2] = y;
			
			// Matrix m;
			// v1.toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
			// v2.toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
			// m.makeTranslationMatrix(v2.getX() - v1.getX(), v2.getY() - v1.getY(),  v2.getZ() - v1.getZ());
			// std::shared_ptr<Object> obj = shader->getCurSelection();
			// if(obj != nullptr){
			// 	obj->transform(m);
			// }
		}
		else if (isSelecting){
		// update new endpoint for selection area 
			// selectedArea[1][view->axis1] = x;
			// selectedArea[1][view->axis2] = y;
			// Vector v1 = selectedArea[0].inCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
			// Vector v2 = selectedArea[1].inCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
			// v1[view->getDeptAxis()] = std::numeric_limits<float>::max();
			// v2[view->getDeptAxis()] = -std::numeric_limits<float>::max();
			// shader->selectVertices(v1, v2);
		
        }

		prevPos[X] = x;
		prevPos[Y] = y; 
	}
	else if (progConfig.opMode == SELECTING)
	{
		// selectedArea[1][view->axis1] = x;
		// selectedArea[1][view->axis2] = y;
		// Vector v1 = selectedArea[0].inCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
		// Vector v2 = selectedArea[1].inCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
		// v1[view->getDeptAxis()] = std::numeric_limits<float>::max();
		// v2[view->getDeptAxis()] = -std::numeric_limits<float>::max();
		// shader->selectVertices(v1, v2);
	}

    //glutPostRedisplay();
}

void Mouse::drawSelectionBox(){
	// if (selectedArea[0] == Vector(-1, -1, 0) || selectedArea[1] == Vector(-1, -1, 0))
	// 	return;


	// Vector corner1 = selectedArea[0].inCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
	// Vector corner2 = selectedArea[1].inCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
	// float minX = std::min(corner1[view->axis1], corner2[view->axis1]);
	// float minY = std::min(corner1[view->axis2], corner2[view->axis2]);

	// float maxX = std::max(corner1[view->axis1], corner2[view->axis1]);
	// float maxY = std::max(corner1[view->axis2], corner2[view->axis2]);
	// Vector v1, v2;
	// v1[view->axis1] = minX;
	// v1[view->axis2] = minY;
	// v2[view->axis1] = minX;
	// v2[view->axis2] = maxY;
	// dynamic_cast<OrthoView*>(view)->drawLineDDA(v1, v2, progConfig.COLOR_SELECTION_BOX);

	// v1[view->axis1] = minX;
	// v1[view->axis2] = minY;
	// v2[view->axis1] = maxX;
	// v2[view->axis2] = minY;
	// dynamic_cast<OrthoView*>(view)->drawLineDDA(v1, v2, progConfig.COLOR_SELECTION_BOX);


	// v1[view->axis1] = minX;
	// v1[view->axis2] = maxY;
	// v2[view->axis1] = maxX;
	// v2[view->axis2] = maxY;
	// dynamic_cast<OrthoView*>(view)->drawLineDDA(v1, v2, progConfig.COLOR_SELECTION_BOX);

	// v1[view->axis1] = maxX;
	// v1[view->axis2] = maxY;
	// v2[view->axis1] = maxX;
	// v2[view->axis2] = minY;
	// dynamic_cast<OrthoView*>(view)->drawLineDDA(v1, v2, progConfig.COLOR_SELECTION_BOX);
}

void Mouse::mouseClick(int button, int state, int x, int y) {
	if(glutGetWindow() == TEXTVIEW)
		return;
	
	//  GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON
	// GLUT_UP or GLUT_DOWN
	if (state == GLUT_UP) {
		if (button == GLUT_LEFT_BUTTON){
			if (progConfig.opMode == SELECTING){
				selectedArea[0] = Vector(-1, -1, 0);
				selectedArea[1] = Vector(-1, -1, 0);
			}
			else if (progConfig.opMode == EDITING){
				selectedArea[0] = Vector(-1, -1, 0);
				selectedArea[1] = Vector(-1, -1, 0);
			}
		}
		else if (button == GLUT_RIGHT_BUTTON){
			if (progConfig.opMode == EDITING){
				isTranslating = false;
			}
		}
		else if (button == GLUT_MIDDLE_BUTTON){
			if(progConfig.opMode == MOVING){
				isRotatingCamera = false;
			}
		}


        //glutPostRedisplay();
	}
	// buddon pressing down
	else {
		if (button == GLUT_LEFT_BUTTON){

			if (progConfig.opMode == DRAWING){
				if (state == GLUT_DOWN){
					if( view->isOrthoView() ){
					 // 	std::shared_ptr<Vector> newV = std::make_shared<Vector>();
						// (*newV)[view->axis1] = x;
						// (*newV)[view->axis2] = y;
					 // 	newV->toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
					 // 	if (progConfig.drawMode == DRAWCURVE){
					 // 		*curveBuffer += newV;
					 // 	}
					}
				}
			}
			else if(progConfig.opMode == MOVING){

				prevPos[X] = x;
				prevPos[Y] = y;

			}
			if(progConfig.opMode == EDITING){
				// selectedArea[0][view->axis1] = x;
				// selectedArea[0][view->axis2] = y;
				// isSelecting = true;

			}
			else if(progConfig.opMode == CLIPPING){

			}
			else if (progConfig.opMode == TRANSFORM)
			{

				// prevPos[view->axis1] = x;
				// prevPos[view->axis2] = y;
			}
			else if (progConfig.opMode == SELECTING){
				// selectedArea[0][view->axis1] = x;
				// selectedArea[0][view->axis2] = y;
				//selectedArea[0].toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
			}
		}
		else if (button == GLUT_MIDDLE_BUTTON){
			if(progConfig.opMode == EDITING){
				// std::shared_ptr<Vector> v = std::make_shared<Vector>();
				// (*v)[view->axis1] = x;
				// (*v)[view->axis2] = y;
				// v->toCOORDS(view->getPixelPerUnit(), view->getX(), view->getY(), view->getZ());
				// shader->insert(v);
			}
			else if(progConfig.opMode == MOVING){
				isRotatingCamera = true;

				prevPos[X] = x;
				prevPos[Y] = y; 
			}
		}
		
		else if (button == GLUT_RIGHT_BUTTON){
			if(progConfig.opMode == EDITING){
				// isTranslating = true;

				// prevPos[view->axis1] = x;
				// prevPos[view->axis2] = y;
			}
			else if(progConfig.opMode == MOVING){
				//winMan->reshapeWindows();
			}

		}
		else if (button == 3 || button == 4) // It's a wheel up
		{
			if(progConfig.opMode == MOVING && view->isCVM()){
				// /std::cout << "what: " << button << std::endl;
//				if (button == 3)
//					dynamic_cast<CVM*>(view)->translateCamera(Vector(0, 0, 10));
//				else if (button == 4)
//					dynamic_cast<CVM*>(view)->translateCamera(Vector(0, 0, -10));
			}

			std::cout << "button: " << button << std::endl;
			if (progConfig.opMode == CLIPPING){
				progConfig.clipMode = static_cast<ClipMode>
					((button == 3)? (static_cast<int>(progConfig.clipMode + 1 ) % 4) : 
						(progConfig.clipMode == UP)? LEFT : ((static_cast<int>(progConfig.clipMode) - 1 ) )); 
			}
			else if(progConfig.opMode == EDITING){
				if (button == 3)
					shader->shiftSelectionUp();
				else if (button == 4)
					shader->shiftSelectionDown();
			}
			else if(progConfig.opMode == MOVING){
				// if wheel up
				if( button == 3 )
					view->pixelsPerUnit *= 1.05;
				else
					view->pixelsPerUnit *= 0.95;

			}
		}
		// right click
		else if (button == GLUT_RIGHT_BUTTON)
		{
			if(progConfig.opMode == MOVING){
				//winMan->reshapeWindows();
			}
		}
	}
    //glutPostRedisplay();

}


void Mouse::mouseHover(int x, int y){
	curPos[X] = x;
	curPos[Y] = y;
	//std::cout << x << " " << y << std::endl;
	if (progConfig.opMode == CLIPPING)
		glutPostRedisplay();
}


void Mouse::viewClipLine(){
	if (progConfig.opMode != CLIPPING)
		return;

	//std::cout << glutGetWindow() << std::endl;

	if(progConfig.clipMode == UP)
		clipUP();
	else if(progConfig.clipMode == DOWN)
		clipDOWN();
	else if(progConfig.clipMode == LEFT)
		clipLEFT();
	else if(progConfig.clipMode == RIGHT)
		clipRIGHT();
	
}


void Mouse::clipUP(){
	int h = view->getHeight();

	progConfig.clipMode = UP;

	view->drawHorizontal(h-curPos[Y]+30, progConfig.color.getColor(0.75f,0.75f,0.75f));
	view->drawHorizontal(h-curPos[Y]+20, progConfig.color.getColor(0.5f,0.5f,0.5f));
	view->drawHorizontal(h-curPos[Y]+10, progConfig.color.getColor(0.25f,0.25f,0.25f));
	view->drawHorizontal(h-curPos[Y]);

}

void Mouse::clipDOWN(){

	int h = view->getHeight();

	progConfig.clipMode = DOWN;
	view->drawHorizontal(h-curPos[Y]-30, progConfig.color.getColor(0.75f,0.75f,0.75f));
	view->drawHorizontal(h-curPos[Y]-20, progConfig.color.getColor(0.5f,0.5f,0.5f));
	view->drawHorizontal(h-curPos[Y]-10, progConfig.color.getColor(0.25f,0.25f,0.25f));
	view->drawHorizontal(h-curPos[Y]);


}


void Mouse::clipLEFT(){


	progConfig.clipMode = LEFT;
	view->drawVertical(curPos[X]-30, progConfig.color.getColor(0.75f,0.75f,0.75f));
	view->drawVertical(curPos[X]-20, progConfig.color.getColor(0.5f,0.5f,0.5f));
	view->drawVertical(curPos[X]-10, progConfig.color.getColor(0.25f,0.25f,0.25f));
	view->drawVertical(curPos[X]);

}

void Mouse::clipRIGHT(){


	progConfig.clipMode = RIGHT;
	view->drawVertical(curPos[X]+30, progConfig.color.getColor(0.75f,0.75f,0.75f));
	view->drawVertical(curPos[X]+20, progConfig.color.getColor(0.5f,0.5f,0.5f));
	view->drawVertical(curPos[X]+10, progConfig.color.getColor(0.25f,0.25f,0.25f));
	view->drawVertical(curPos[X]);

}
*/
