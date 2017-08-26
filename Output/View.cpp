#include <cstring>
#include <GL/glut.h>
#include <utility>
#include <iostream>
#include <cmath>
#include <array>
#include <algorithm>
#include <queue>
#include <utility>
#include <cmath>
#include <memory>
#include "View.h"
#include "OrthoView.h"
#include "Vector.h"
#include "AEL.h"
#include "Geometry.h"
#include "Config.h"
#include "Shader.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Utility.h"
#include "Face.h"


extern Config progConfig; 
extern Shader* shader;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;

Keyboard View::keyboard;

void update();
void mouseClick(int button, int state, int x, int y);
void mouseHold(int x, int y);
void mouseHover(int x, int y);

void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);
void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);

View::View(const ViewType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height){ //, int canvas_width, int canvas_height){
	viewType = vt;
	//allocate new pixel buffer, need initialization!! 
	windPos[X] = loc_x;
	windPos[Y] = loc_y;

	PixelBuffer = std::unique_ptr<float> (new float[window_width * window_width * 3]);
	coordLoc[X] = 0.0f;
	coordLoc[Y] = 0.0f;
	coordLoc[Z] = 0.0f;

	width = window_width;
	height = window_height;
	pixelsPerUnit = 100;

	mouse = new Mouse(static_cast<OrthoView*>(this));
	//keyboard = Keyboard();

	for (int i = 0; i < window_width * window_width * 3; i++)
		PixelBuffer.get()[i] = 0.0f;
	
	windowContext = glutCreateSubWindow(mainContext, loc_x,loc_y, window_width, window_height);

	//glewInit()
	init();

}

View::~View(){
}

void View::init() {
    //glutDisplayFunc(update);
    //glutMouseFunc(::mouseClick);
    //glutMotionFunc(::mouseHold);
    //glutPassiveMotionFunc(::mouseHover);

    //glutKeyboardFunc(::keyboardHandler);
    //glutKeyboardUpFunc(::keyboardReleaseHandler);
    //glutIgnoreKeyRepeat(1);
	
}

void View::setPix(const Vector* v, const float *c)
{
	setPix(v->getX(), v->getY(), c);
}

void View::setPix(const int& x, const int& y, const float *c)
{

	if (c == nullptr)
		return;
	int w = getWidth();
	int h = getHeight();


	//v->toPixelPos();
	if ( x < 0 || y < 0 ||  x > w - 1 || y > h -1)
		return;


	memcpy (&(PixelBuffer.get()[static_cast<int>(( y*w + x)*3)]), c, sizeof(float[3]));
}

void View::clear()
{
	int totPix = getHeight()*getWidth();
	for (int i = 0; i < totPix; i++)
		memcpy(&( PixelBuffer.get() [i*3]), progConfig.COLOR_bg, sizeof(progConfig.COLOR_bg));
}

void View::drawLineDDA(float x1, float y1, float x2, float y2, float const* color){

	if(x1 == x2 && y1 == y2){
		setPix(x1, y1, color);
		return;
	}

	if (y1 - y2 == 0)
	{
		//std::cout << "horizonatl" << std::endl;
		drawHorizontal(y1, x1, x2, color);
		return;
	}
	else if (x1 - x2 == 0){
		drawVertical(x1,y1,y2,color );
		return;
	}

	float m = (y1 - y2) / (x1 - x2);

	if ( fabs(m) < 0.5 ){	
		if (x1 > x2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		m = (y2 - y1) / (x2 - x1);
		for (int i = 0; i < x2 - x1; i++){
			setPix(i + x1, floor(y1 + 0.5 + static_cast<float>(i)*m), color);
		}
	}
	else {
		
		if (y1 > y2)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		m =  (x2- x1) / (y2 - y1);
		for (int i = 0; i < y2 - y1; i++){
			//std::cout << "|" << (float)left->getX() + 0.5 + (float)i*m << " " <<  i + left->getY() << "| ";
			setPix(floor(x1 + 0.5 + static_cast<float>(i)*m ), i + y1, color);
		}	
	}

}


void View::drawLineBSH(const std::shared_ptr<Vector> &v1, const std::shared_ptr<Vector> &v2, float *color){
	if ((v1->getY() - v2->getY()) == 0)
	{
		drawHorizontal(v1->getY(), v1->getX(), v2->getX(), color);
		return;
	}
	else if (v1->getX() - v2->getX() == 0){
		drawVertical(v1->getX(),v1->getY(),v2->getY(),color );
		return;
	}

	std::vector<Vector> toFill;


	Vector* right, *left;
	float m = (float)(v1->getY() - v2->getY()) / (float)(v1->getX() - v2->getX());

	if ( fabs(m) < 0.5 ){	
		
		if (v1->getX() < v2->getX())
		{
			right = v2.get();
			left = v1.get();
		}
		else
		{
			right = v1.get();
			left = v2.get();
		}

		float dx = right->getX() - left->getX();
		float dy = right->getY() - left->getY();
		int y = left->getY();
		//toFill.push_back( Vector( i + left->getX(), y));

		m = (float)(right->getY() - left->getY()) / (float)(right->getX() - left->getX());
		
		int d = 0;
		if ( m > 0 )
			d = 2*dy - dx;
		else
			d = -2*dy - dx;

		for (int i = 0; i < right->getX() - left->getX(); i++){
			//std::cout << "|" << i + left->getX() << " " <<  y << " ";
		
			toFill.push_back( Vector(i + left->getX(), y, 0));
		
			if ( m > 0 )
			{

				if (d > 0)
				{
					y = y + 1;
					d = d - dx;
				}
				d = d + dy;
			}
			else {

				if (d < 0)
				{
					y = y - 1;
					d = d + dx;
				}
				d = d + dy;
				//std::cout << d << std::endl;
			}
		}
			
	}
	else {
		
		if (v1->getY() < v2->getY())
		{
			right = v2.get();
			left = v1.get();
		}
		else
		{
			right = v1.get();
			left = v2.get();
		}

		float dx = right->getX() - left->getX();
		float dy = right->getY() - left->getY();
		int x = left->getX();

		int d = 0;
		m =  (float)(right->getX() - left->getX()) / (float)(right->getY() - left->getY());
		
		if ( m > 0)
			d = 2*dx - dy;
		else
			d = -2*dx - dy;
		for (int i = 0; i < right->getY() - left->getY(); i++){
			//std::cout << "|" << i + left->getX() << " " <<  floor((float)left->getX() + 0.5 + (float)(i +  right->getX())*m ) << " ";
		
			toFill.push_back( Vector(x,  left->getY() + i, 0));
		
			if ( m > 0 )
			{
				if (d > 0)
				{
					x = x + 1;
					d = d - dy;
				}
				d = d + dx;	
			}
			else
			{
				if (d < 0)
				{
					x = x - 1;
					d = d + dy;
				}
				d = d + dx;	
			}

			//std::cout << d << std::endl;
		}
	}


	drawLine(toFill, color);
}

void View::drawLine( const std::vector<Vector> &vertexBuffer, const float *color){
	for (unsigned int i = 0; i < vertexBuffer.size(); i++ )
	{
	 	setPix(&vertexBuffer[i], color);
	}
}

void View::fillPolygon(Geometry &geo, const float* color){

}


void View::halfToning(Geometry &geometries){

}


void View::drawHorizontal(const int &y, const float *c){
	int w = getWidth();
	drawHorizontal(y, 0, w - 1, c);
}

void View::drawVertical(const int &x, const float *c){
	int h = getHeight();

	drawVertical(x, 0, h-1, c);
}


void View::drawHorizontal(const int &y, const int &x1, const int &x2, const float* c){
	int minX, maxX;

	if (c == nullptr)
		c = progConfig.COLOR_fill;

	if (x1 < x2){
		minX = x1;
		maxX = x2;
	}
	else
	{
		minX = x2;
		maxX = x1;
	}

	for ( int x_i = minX; x_i <= maxX; x_i++){
		setPix(x_i, y, c);
	}
	//std::cout <<"finished"<< std::endl;


}

void View::drawVertical(const int &x,const int &y1, const int &y2, const float* c){
	int minY, maxY;

	if (c == nullptr)
		c = progConfig.COLOR_fill;

	if (y1 < y2){
		minY = y1;
		maxY = y2;
	}
	else
	{
		minY = y2;
		maxY = y1;
	}

	for ( int y_i = minY; y_i <= maxY; y_i++){
		setPix(x, y_i, c);
	}
}


void View::mouseClick(const int& button, const int& state, const int& x, const int& y){
	mouse->mouseClick(button, state, x, height - y);
}


void View::mouseHold(int x, int y){
	mouse->mouseHold(x, height - y);
}

void View::mouseHover(int x, int y){
	mouse->mouseHover(x, height - y);
}

void View::keyboardHandler(unsigned char key, int x, int y){
	keyboard.keyboardHandler( key, x, y);
}

void View::keyboardReleaseHandler(unsigned char key, int x, int y){
	keyboard.keyboardReleaseHandler( key, x, y);
}

void View::drawOutline(){
	drawHorizontal(0, progConfig.COLOR_outline);
	drawHorizontal(height - 1, progConfig.COLOR_outline);
	drawVertical(0, progConfig.COLOR_outline);
	drawVertical(width - 1, progConfig.COLOR_outline);
}	


Vector View::interpolate(const float& startPt, const float& endPt, const float& x, const Vector& startColor, const Vector &endColor)const{
	Vector ret(0.0f, 0.0f, 0.0f);
	float maxPt = max(startPt, endPt);
	float minPt = min(startPt, endPt);
	float intensity = (x - minPt) / (maxPt - minPt);

	if (std::isnan(intensity))
		intensity = 0.0f;
	for (int i = 0; i < 3; i++){
		float _min = startColor[i];
		float _max = endColor[i];
		float d = _max - _min;
		ret[i] = _min + d*intensity;
	}
	return ret;

}


void View::drawRect(const float & minX, const float & minY, const float & maxX, const float & maxY, float const* color){
	drawLineDDA(minX, minY, minX, maxY, color);
	drawLineDDA(minX, minY, maxX, minY, color);
	drawLineDDA(minX, maxY, maxX, maxY, color);
	drawLineDDA(maxX, maxY, maxX, minY, color);
}


void View::drawVertex(const Vector & v, float const* color){
	Vector position = translateFromWorldToViewPort(v);
	float x = position[X];
	float y = position[Y];
	drawRect(x-2, y-2, x+2, y+2, color);
	setPix(x, y, color);
}
