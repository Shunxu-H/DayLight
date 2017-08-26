/* ************************************************************** 
TO DO:

1. STOKE FONT or https://learnopengl.com/#!In-Practice/Text-Rendering
2. Checkout glutIdleFunc()
************************************************************** */

#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <memory>
#include "OrthoView.h"
#include "Geometry.h"
#include "Shader.h"
#include "Config.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Matrix.h"
#include "WindowManager.h"
#include "TextView.h"
#include "Curve.h"


int CANVAS_WIDTH = 0;
int CANVAS_HEIGHT = 0;
int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;


WindowManager* winMan;
Shader* shader;
std::vector<std::shared_ptr<Vector>> vertexBuffer;
std::shared_ptr<Curve> curveBuffer;
Config progConfig;

void update(); 
//void mouseClick(int button, int state, int x, int y);
void mouseClick(int button, int state, int x, int y);
void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);
void mouseHold(int x, int y);
void mouseHover(int x, int y);
bool fexists(const std::string& filename);


int main(int argc, char *argv[]) {

Matrix m;
m.test();
	std::string fileName;
	int offset = 1;

	while ( offset < argc){
		if (0 == strcmp(argv[offset], "-d"))
		{
			offset++;
			if (1 != sscanf(argv[offset], "%d", &WINDOW_WIDTH) || WINDOW_WIDTH <= 0)
			{
				std::cerr << "Invalid parameters for -d" << std::endl;
				return 1;
			}
			else
				offset++;


			if (1 != sscanf(argv[offset], "%d", &WINDOW_HEIGHT) || WINDOW_HEIGHT <= 0)
			{
				std::cerr << "Invalid parameters for -d" << std::endl;
				return 1;
			}
			else
				offset++;
		}
		else if (0 == strcmp(argv[offset], "-f")){
			offset++;
			if ( fexists(std::string(argv[offset]))){
				//offset++;
				//std::cout << "!!!!!" << argv[offset] << std::endl;
				fileName = std::string(argv[offset]);
				offset++;
				//std::cout << "here" << std::endl;
			}
			else 
			{
				std::cerr << "Invalid parameters for -f" << std::endl;
				return 1;
			}

		}
		else 
		{
			std::cerr << "Invalid flags, pass '-h' to see manu" << std::endl;
			return 1;
		}
	}

	if ( WINDOW_HEIGHT == 0 && WINDOW_WIDTH == 0 )
	{
		std::cerr << " '-d' unset, windows dimensionality fall back to default(500, 500)" << std::endl;
		
		WINDOW_WIDTH  = 500;
		WINDOW_HEIGHT = 500;
	}

	winMan = new WindowManager(argc, argv, std::string("Ray Tracer"), WINDOW_WIDTH, WINDOW_HEIGHT);//, CANVAS_WIDTH, CANVAS_HEIGHT);

	if(fileName.size() > 0)	
		shader = new Shader(fileName);
	else 
		shader = new Shader();

	vertexBuffer = std::vector<std::shared_ptr<Vector>>();
	curveBuffer = std::make_shared<Curve>();
	
	shader->loadFile();


	glutMainLoop();//main OrthoView loop, will OrthoView until terminate 
	return 0;
}

bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}

//main OrthoView loop, this function will be called again and again by OpenGL 
void update() {
	//Misc.
	int curWin = glutGetWindow();
	//std::cout << curWin	<< std::endl;
	winMan->updateWindow(curWin); 
	//glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y){

	int curWin = glutGetWindow();
	(*winMan)[curWin]->mouseClick(button, state, x, y); 
}

void keyboardHandler(unsigned char key, int x, int y)
{
	//std::cout << key << std::endl;
	//winMan->keyboardHandler(key, x, y);
	int curWin = glutGetWindow();
	(*winMan)[curWin]->keyboardHandler(key, x, y); 
}

void keyboardReleaseHandler(unsigned char key, int x, int y)
{
	//winMan->keyboardReleaseHandler(key, x, y);
	int curWin = glutGetWindow();
	(*winMan)[curWin]->keyboardReleaseHandler(key, x, y);
}


void mouseHold(int x, int y)
{
	int curWin = glutGetWindow();
	(*winMan)[curWin]->mouseHold(x, y);
}


void mouseHover(int x, int y){
	int curWin = glutGetWindow();
	(*winMan)[curWin]->mouseHover(x, y);
}




