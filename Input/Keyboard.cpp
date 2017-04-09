/*
TO DO:
1. make moving objects default

*/
#include <string>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <vector>
#include <memory>
#include "Keyboard.h"
#include "Config.h"
#include "Shader.h"
#include "Geometry.h"
#include "WindowManager.h"
#include "Object.h"
#include "Utility.h"
#include "Curve.h"


extern Config progConfig;
extern Shader *shader;
extern WindowManager* winMan;
extern std::vector<std::shared_ptr<Vector>> vertexBuffer;
extern std::shared_ptr<Curve> curveBuffer;


std::vector<std::string>drawTips = {"Click to draw, drag for more precision.", "'Enter' to finish"};
std::vector<std::string>clipTips = {"Click to clip, scroll to change dimension.", "'ESC' to finish"};
std::vector<std::string>translateTips = {"Drag to move selection, scroll to change selection.", "'ESC' to finish"};
std::vector<std::string>rotateTips = {"Drag to rotate selection, scroll to change selection.", "'ESC' to finish"};
std::vector<std::string>moveTips = {"Drag to move the canvas.", "Wheel to zoon in or zoon out.", "Left click to invoke NDC procedures."};
std::vector<std::string>scaleTips = {"Drag to scale selection, scroll to change selection.", "'ESC' to finish"};
std::vector<std::string>insertTips = {"Refer to menu for list of commands.", "'ESC' to finish"};
std::vector<std::string>editTips = {"Left mouse button drag to select point(s).",
									"With End point seleted, ",
									"    middle button click to extend ",
									"    curve from the corresponding endpoint.",
									"With two CONSECUTIVE points seleted, ",
									"    middle button click to insert a control", 
									"    point in between.",
									"Drag with right button to move selected points",
									"'ESC' to finish"};
std::vector<std::string>filler = {"   "};
std::vector<std::string> menu = { "'1' to draw with DDA", 
					  "'2' to draw with Bresenham",
					  "hold 'space bar' to move drawing board'",
					  "'s' to select",
					  "'ESCAPE' to go back to DRAW mode"};



void Keyboard::keyboardHandler(unsigned char key, int x, int y){

	std::cout << "pressed " << key << std::endl;
	if ( progConfig.opMode == INSERT )
	{
		switch(key){
			case 13 : 
				history.push_back(curStr);
				execute();
				curStr.clear();
				progConfig.opMode = prevMode;
				
				progConfig.opMode = MOVING;	
				glutIgnoreKeyRepeat(1);

			break;
			// 'ESCAPE' 
			case 27:
				progConfig.opMode = MOVING;	

				glutIgnoreKeyRepeat(1);
			break;

			// BACKSPACE
			case 8:
				if (curStr.size() > 0){
					curStr.pop_back();
				}
			break;

			default:
				curStr.push_back(key);
		}		

	}
	else 
	{

		switch (key)
		{
			// when 'ENTER' is hit
			case 13 : 
				if (curveBuffer->size() > 0){
					if (progConfig.opMode == DRAWING){
						if (progConfig.drawMode == DRAWCURVE)
						{
							shader->addObj(curveBuffer);
							curveBuffer = std::make_shared<Curve>();
							
						}
					}
				}

			break;

			// 'ESP' key
			case 27:
				progConfig.opMode = DRAWING;
				progConfig.transMode = UNSET;

			break;

			// use DDA
			case '1':
				progConfig.lineAlg = DDA;

			break;

			// use Brosenham's algorithm
			case '2':
				progConfig.lineAlg = BSH;

			case 's':
				progConfig.opMode = SELECTING;
				progConfig.renderMode = HIGHLIGHT;


			break;

			// to quit
			case 'q':
				std::cout << "Saveing file" << std::endl;
				shader->save("data/temp.gmt");
				std::cout << "Exiting..." << std::endl;
				exit(0);
			break;


			case 'i':
				prevMode = progConfig.opMode; 
				progConfig.opMode = INSERT;

				glutIgnoreKeyRepeat(0);
			break;
			
			case 'd':
			{
				if (progConfig.selectMode == VERTEX){
					shader->deleteVertices();
				} 
				else{

					std::shared_ptr<Object> curS(shader->getCurSelection());
					if ( curS == nullptr)
						progConfig.curSelected = -1;
					else{
						shader->deleteObj(shader->getCurSelection().get());
					}
				}
			}
			break;

			// delete all
			case 'D':
				shader->clear();
				progConfig.curSelected = -1;
			break;


			// cliping
			case 'c':
				progConfig.opMode = DRAWING;
				progConfig.drawMode = DRAWCURVE;

				// progConfig.opMode = CLIPPING;
				// progConfig.clipMode = UP;
			break;

			// toggle fill mode and outline mode 
			case 'f':
				if(progConfig.fillMode == FILL)
					progConfig.fillMode = OUTLINE;
				else
					progConfig.fillMode = FILL;

			break;

			// translation:
			case 'w':
				if (progConfig.opMode != TRANSFORM && progConfig.transMode != TRANSLATE){
					progConfig.opMode = TRANSFORM;
					progConfig.transMode = TRANSLATE;
				}
				else{
					progConfig.opMode = MOVING;
					progConfig.transMode = UNSET;
				}


			break;

			// rotation
			case 'e':
				progConfig.opMode = EDITING;

				// if (progConfig.opMode != TRANSFORM && progConfig.transMode != SCALE){
				// 	progConfig.opMode = TRANSFORM;
				// 	progConfig.transMode = SCALE;
				// }
				// else{
				// 	progConfig.opMode = MOVING;
				// 	progConfig.transMode = UNSET;
				// }

			break;

			// rotate 
			case 'r':
				if (progConfig.opMode != TRANSFORM && progConfig.transMode != ROTATE){
					progConfig.opMode = TRANSFORM;
					progConfig.transMode = ROTATE;
				}
				else{
					progConfig.opMode = MOVING;
					progConfig.transMode = UNSET;
				}



			break;

			// move mode
			case ' ':
				prevMode = progConfig.opMode;
				progConfig.opMode = MOVING;
			break;

		}
	}

	glutPostRedisplay();
	
}


void Keyboard::keyboardReleaseHandler(unsigned char key, int x, int y){
	//std::cout << "Holding " << key << std::endl;
	
	if ( progConfig.opMode == MOVING)
	{

		switch (key)
		{
			// when ' ' is hit
			case ' ':
				progConfig.opMode = prevMode;
			break;
		}
	}
	
	glutPostRedisplay();
}

void Keyboard::drawBitmapText(const char*string,float x,float y)
{
    const char *c;

    glRasterPos2f(x, y);
  
    for (c=string; *c != '\0'; c++)
    {
        //std::cout << c << std::endl;
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 , *c);
    }

}

void Keyboard::renderInput(void)
{ 
	//glClear(GL_COLOR_BUFFER_BIT); 
	//	std::cout << "printing tips on " << glutGetWindow() <<  std::endl;
	glLoadIdentity();


	float offset = 0.10;

	for (int i = history.size() - 1; i >= 0; i--){
		//std::cout << i << std::endl;

		glColor3f(progConfig.COLOR_text[R]*(0.95 - offset*1.2),progConfig.COLOR_text[G]*(0.95 - offset*1.2),progConfig.COLOR_text[B]*(0.95 - offset*1.2));
		drawBitmapText(history[i].c_str(),-0.95, -0.95 + offset);
		offset += 0.10;
	}

	glColor3f(progConfig.COLOR_text[R],progConfig.COLOR_text[G],progConfig.COLOR_text[B]);
	drawBitmapText(curStr.c_str(),-0.95, -0.95);
	glRasterPos2i(-1, -1);
	//glutSwapBuffers(); 
}

void Keyboard::renderTips(void)
{ 
  //glClear(GL_COLOR_BUFFER_BIT); 
  glLoadIdentity();
 
  glColor3f(progConfig.COLOR_text[R],progConfig.COLOR_text[G],progConfig.COLOR_text[B]);
  float offset = 0.10;
  std::vector<std::string> tips = getTips();
  for (auto str: tips){
  	drawBitmapText(str.c_str(),-0.95,1-offset);
  	offset += 0.10;
  }
  glRasterPos2i(-1, -1);
  //glutSwapBuffers(); 
}

std::vector<std::string> Keyboard::getTips(){
	if(progConfig.opMode == DRAWING)
		return drawTips;
	else if (progConfig.opMode == CLIPPING)
		return clipTips;

	else if (progConfig.opMode == TRANSFORM){
		if(progConfig.transMode == TRANSLATE)
			return translateTips;
		else if(progConfig.transMode == ROTATE)
			return rotateTips;
		else 
			return scaleTips;
	}
	else if (progConfig.opMode == MOVING)
		return moveTips;
	else if (progConfig.opMode == EDITING)
		return editTips;
	else if (progConfig.opMode == INSERT)
		return insertTips;
	else 
		return filler;
} 


void Keyboard::execute()const{
	std::deque<std::string> tokens = mystrtok(curStr, " ");

	if(tokens.size() <= 0)
		return;

	if (tokens[0].compare("setRotation") == 0)
		changeRotAxis(tokens);
	else if (tokens[0].compare("moveLight") == 0)
		moveLight(tokens);
	else if (tokens[0].compare("moveView") == 0)
		moveView(tokens);
	else if (tokens[0].compare("hideNormal") == 0)
		progConfig.showNormal = false;
	else if (tokens[0].compare("showNormal") == 0)
		progConfig.showNormal = true;
	else if (tokens[0].compare("hideEdge") == 0)
		progConfig.showEdge = false;
	else if (tokens[0].compare("showEdge") == 0)
		progConfig.showEdge = true;
	else if (tokens[0].compare("setK") == 0)
		setK(tokens);
	else if (tokens[0].compare("setOneU") == 0)
		setOneU(tokens);
	else if (tokens[0].compare("setUVector") == 0)
		setUVector(tokens);
	else if (tokens[0].compare("toggle") == 0)
		shader->toggleCurveType();
	else if (tokens[0].compare("setResolution") == 0)
		setResolution(tokens);
}

void Keyboard::setResolution(std::deque<std::string>& tokens)const{

	if(tokens.size() != 2)
		return;

	tokens.pop_front();

	int resolution;

	shader->setResolution(std::stoi(tokens[0]));
}


void Keyboard::changeRotAxis(std::deque<std::string>& tokens)const{

	if(tokens.size() != 7)
		return;

	tokens.pop_front();

	float data[6];

	for ( int i = 0; i < 6; i++ )
		data[i] = std::stof(tokens[i]);

	shader->rotationVector.setHead(data[0], data[1], data[2]);
	shader->rotationVector.setTail(data[3], data[4], data[5]);

}


void Keyboard::moveLight(std::deque<std::string>& tokens)const{

	int dataCnt = 3;
	if(tokens.size() != dataCnt + 1)
		return;

	tokens.pop_front();

	float data[dataCnt];

	for ( int i = 0; i < dataCnt; i++ )
		data[i] = std::stof(tokens[i]);

	shader->moveLight(Vector( data[0], data[1], data[2] ));

}

void Keyboard::setK(std::deque<std::string>& tokens)const{
std::cout << "set k" << std::endl;
	int dataCnt = 1;
	if(tokens.size() != dataCnt + 1)
		return;

	tokens.pop_front();

	int data;

	data = std::stoi(tokens[0]);

	shader->setK(data);

}


void Keyboard::setUVector(std::deque<std::string>& tokens)const{
	std::cout << "set u vector" << std::endl;
	if(tokens.size() <= 1)
		return;

	tokens.pop_front();
	std::vector<float> uvector;
	for(const std::string & str: tokens){
		uvector.push_back(std::stof(str));
	}
	shader->setUVector(uvector);
}

void Keyboard::setOneU(std::deque<std::string>& tokens)const{
	// setOneU num value
	std::cout << "set one u" << std::endl;
	int dataCnt = 2;
	if(tokens.size() != dataCnt + 1)
		return;

	tokens.pop_front();


	int num;
	float u;

	num = std::stoi(tokens[0]);
	tokens.pop_front();
	u = std::stof(tokens[0]);
	tokens.pop_front();

	shader->setOneU(num, u);
}

void Keyboard::moveView(std::deque<std::string>& tokens)const{

	int dataCnt = 3;
	if(tokens.size() != dataCnt + 1)
		return;

	tokens.pop_front();

	float data[dataCnt];

	for ( int i = 0; i < dataCnt; i++ )
		data[i] = std::stof(tokens[i]);

	shader->moveView(Vector( data[0], data[1], data[2] ));

}