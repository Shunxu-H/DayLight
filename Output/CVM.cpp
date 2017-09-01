#include <cstring>
#include <GL/glut.h>
#include <utility>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <queue>
#include <utility>
#include <memory>
#include "View.h"
#include "CVM.h"
#include "Vector.h"
#include "AEL.h"
#include "Geometry.h"
#include "Config.h"
#include "Shader.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Curve.h"
#include "Utility.h"
#include "WindowManager.h"
#include "Line.h"

extern Config progConfig; 
extern Lumos::Shader* shader;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;
extern std::shared_ptr<Curve> curveBuffer;
extern WindowManager* winMan;


CVM::CVM(QWidget *parent):View(parent){

//    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
//    dock->setWidget(new OGLWidget());
}

void CVM::initializeGL(){
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void CVM::resizeGL(int w, int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);

}

void CVM::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glDrawArrays( GL_TRIANGLES, 0, NumOfVertices);

    //swapBuffer();
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.0,  0.5, 0);
    glEnd();
}

/*
CVM::CVM(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height)
:View(vt,mainContext, loc_x, loc_y, window_width, window_height)
{ 
	
	fromPoint = Vector(0, 0, 6);
	atPoint = Vector(0, 0, 5);
	UpVector = Vector(0, 1, 0);	
	mouse = new Mouse(this);
	float r = height/width;
	verticalViewAngle = M_PI / 3;
	horizontalViewAngle = 2*asin(sin(0.5*verticalViewAngle)/r);


}

CVM::~CVM(){

}

void CVM::initializeGL(){

}

void CVM::resizeGL(int w, int h){

}

void CVM::paintGL(){

}


void CVM::drawLineDDA(Vector v1, Vector v2, const float *color){

	v1 = translateFromWorldToViewPort(v1);
	v2 = translateFromWorldToViewPort(v2);

	// v1.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	// v2.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	View::drawLineDDA(v1[X], v1[Y], v2[X], v2[Y], color );

}

Vector CVM::translateFromWorldToViewPort(Vector v)const{
	Matrix mt;
	mt.makeTranslationMatrix(-fromPoint[X], -fromPoint[Y], -fromPoint[Z]);
	v = mt*v;

	Matrix mr(4, 0);
	Vector c = atPoint - fromPoint;
	Vector a = c.cross(UpVector);
	
	c.normalize();
	a.normalize();

	// does not have to unify because it is the cross product of two unit vectors 
	// also because they are perpendicular to each other.
	Vector b = a.cross(c); 
	mr.concatenate(a);
	mr.concatenate(b);
	mr.concatenate(c);
	mr.concatenate(Vector(0, 0, 0));

	mr = mr.transpose();
	mr[3][0] = 0;
	mr[3][1] = 0;
	mr[3][2] = 0;
	mr[3][3] = 1;

	v = mr*v;

	int xCenter = 0.5*width;
	int yCenter = 0.5*height;
	Vector ret;
	ret[X] = xCenter + (v[X] / v[Z]*width) / (2*tan(horizontalViewAngle / 2) );
	ret[Y] = yCenter + (v[Y] / v[Z]*height) / (2*tan(verticalViewAngle / 2) );
	return ret;
}


Vector CVM::translateFromViewPortToWorld(Vector v)const{

	float viewPort_width = 2*tan(0.5*verticalViewAngle);
	float viewPort_height = 2*tan(0.5*horizontalViewAngle);
	float viewPort_i = (v[X] / width)*viewPort_width;
	float viewPort_j = (v[Y] / height)*viewPort_height;
	Vector a = ((atPoint - fromPoint).cross(UpVector)).makeUnitVector();
	Vector v_i = a * ( -(0.5*viewPort_width - viewPort_i) );
	Vector v_j = UpVector.makeUnitVector() * ( - (0.5*viewPort_height - viewPort_j));
	return (fromPoint + (atPoint - fromPoint).makeUnitVector() ) + (v_i + v_j);

	// Matrix mt;
	// mt.makeTranslationMatrix(-fromPoint[X], -fromPoint[Y], -fromPoint[Z]);
	// v = mt*v;

	// Matrix mr(4, 0);
	// Vector c = atPoint - fromPoint;
	// Vector a = c.cross(UpVector);
	
	// c.normalize();
	// a.normalize();

	// // does not have to unify because it is the cross product of two unit vectors 
	// // also because they are perpendicular to each other.
	// Vector b = a.cross(c); 
	// mr.concatenate(a);
	// mr.concatenate(b);
	// mr.concatenate(c);
	// mr.concatenate(Vector(0, 0, 0));
	// mr[3][3] = 1;

	// mr = mr.transpose();

	// v = mr*v;

	// int xCenter = 0.5*width;
	// int yCenter = 0.5*height;
	// Vector ret;
	// ret[X] = xCenter + (v[X] / v[Z]*width) / (2*tan(horizontalViewAngle / 2) );
	// ret[Y] = yCenter + (v[Y] / v[Z]*height) / (2*tan(verticalViewAngle / 2) );
	// return ret;


}

void CVM::translateCamera(Vector v){
	toCOORDS(v);

	Vector transY = UpVector;
	Vector transX = UpVector.cross(atPoint-fromPoint);
	Vector transZ = (atPoint - fromPoint).makeUnitVector();
	transX.makeUnitVector();
	transY.makeUnitVector();
	transX = transX * v[X];
	transY = transY * v[Y];
	transZ = transZ * v[Z];
	fromPoint = fromPoint + ( transX + transY + transZ );
	atPoint = atPoint + ( transX + transY + transZ);
	// std::cout << fromPoint << std::endl;
	// std::cout << atPoint << std::endl << std::endl;

}


void CVM::rotateCamera(Vector v){
	toCOORDS(v);
	v = v/10;
	Matrix m1;

	m1.makeTranslationMatrix(fromPoint[X],fromPoint[Y],fromPoint[Z]);


	Vector transY = UpVector;
	Vector transX = UpVector.cross(atPoint-fromPoint);
	Vector transZ = (atPoint - fromPoint).makeUnitVector();
	transX.makeUnitVector();
	transY.makeUnitVector();
	transX = transX * v[X];
	transY = transY * v[Y];
	transZ = transZ * v[Z];
	atPoint = atPoint + ( transX + transY + transZ);
	// std::cout << fromPoint << std::endl;
	// std::cout << atPoint << std::endl << std::endl;

}


void CVM::updateWindow(){

	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();
	clear();

	// draw coordinate
	drawAxis();

	//drawLineDDA(*shader->rotationVector.getHead(), *shader->rotationVector.getTail(), progConfig.COLOR_rotVec);
	

	if(progConfig.fillMode == FILL)
		rayTrace();
	else	
		shader->drawAll();

	if( progConfig.opMode == CLIPPING )
		mouse->viewClipLine();
	else if ( progConfig.opMode == EDITING)
		mouse->drawSelectionBox();

	// draw buffers
	if (curveBuffer->size() > 0)
		curveBuffer->draw(progConfig.COLOR_regStroke);

	View::drawOutline();
	
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, PixelBuffer.get());
	
    //glutPostRedisplay();
}

void CVM::reshapeWindow(const Vector& min, const Vector& max){
	// float minX = min[axis1], maxX = max[axis1], minY = min[axis2], maxY = max[axis2];

	// float dx = maxX - minX, 
	// 	  dy = maxY - minY;

	// pixelsPerUnit = (((height < width)? height:width) - 2*PADDING ) / ((dx > dy)? dx: dy); 
	// float shift = PADDING / pixelsPerUnit;

	// coordLoc[axis1] = min[axis1] - shift;
	// coordLoc[axis2] = min[axis2] - shift;	
}


void CVM::drawAxis(){
	// Vector origin(0, 0, 0);
	// origin.toPXLPOS(pixelsPerUnit, coordLoc[X], coordLoc[Y], coordLoc[Z]);
	// drawVertical(origin[axis1], progConfig.COLOR_axis);
	// drawHorizontal(origin[axis2], progConfig.COLOR_axis);
}	

void CVM::drawOutline(const Face & face, const float * color){

	for (unsigned int i = 0; i < face.getVerticesCnt() ; i++)
		drawLineDDA(*face.getV(i), *face.getV((i+1) % face.getVerticesCnt() ), color);


}

void CVM::fillPolygon(Geometry &geo){


}

void CVM::halfToning(Geometry &geo){

}




void CVM::fillPolygons(std::vector<std::shared_ptr<Geometry>> &geos){
	// sort(geos.begin(), geos.end(),  
	// 	[&, this](const std::shared_ptr<Geometry> & g1, const std::shared_ptr<Geometry> & g2 ) -> bool{
	// 		//return f1 > f2;
	// 		return g1->getCentroid()[getDeptAxis()] > 
	// 				g2->getCentroid()[getDeptAxis()];
	// 	});

	// for (auto geo: geos)
	// 	fillPolygon(*geo);
}

Vector oldV;


void CVM::rayTrace(){
	// Vector v = translateFromViewPortToWorld(Vector(width / 2 + 71, height / 2));
	// Vector curColor = shader->rayTrace(Line(fromPoint, v - fromPoint));
	
	
	float maxColor = -std::numeric_limits<float>::max();
	for (int x = 0; x < width; x++){
		for( int y = 0; y < height; y ++){
			Vector v = translateFromViewPortToWorld(Vector(x, y));
			Vector curColor = shader->rayTrace(Line(fromPoint, v - fromPoint));
			if (curColor[R] != -1 ){
				for(int i = 0; i < 3; i++){
					if (maxColor < curColor[i])
						maxColor = curColor[i];
				}

				setPix(x, y, static_cast<Matrix>(curColor)[0] );
			}
		}
			if(x % static_cast<int>(width / 20) == 0)
				std::cout << (x/width)*100 << "\% finished." << std::endl;  
	}

	// Vector dColor = maxColor - minColor;
	// for (int x = 0; x < width; x++){
	// 	for( int y = 0; y < height; y ++){
	// 		float* curPixel = &(PixelBuffer.get()[int((y*width + x)*3)]);
	// 		curPixel[R] = (curPixel[R] )/maxColor[R];
	// 		curPixel[G] = (curPixel[G] )/maxColor[G];
	// 		curPixel[B] = (curPixel[B] )/maxColor[B];
	// 	}
	// }

	for(int i = 0; i < width*height*3; i++){
		PixelBuffer.get()[i] = PixelBuffer.get()[i] / maxColor;
	}

}
*/
