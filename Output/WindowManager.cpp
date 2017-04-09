#include <GL/glut.h>
#include <string>
#include <iostream>

#include "WindowManager.h"
#include "ui_windowmanager.h"
#include "Keyboard.h"
#include "Cabinet.h"
#include "Shader.h"
#include "View.h"
#include "TextView.h"
#include "Face.h"
#include "Config.h"
#include "CVM.h"


#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <memory>
#include <QDebug>
#include "OrthoView.h"
#include "Geometry.h"
#include "Shader.h"
#include "Config.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TextView.h"
#include "Curve.h"

#include <QOpenGLWidget>
#include <QDesktopWidget>
#include <QDockWidget>
#include <oglwidget.h>


int CANVAS_WIDTH = 0;
int CANVAS_HEIGHT = 0;
int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;


WindowManager* winMan;
Shader* shader;
std::vector<std::shared_ptr<Vector>> vertexBuffer;
std::shared_ptr<Curve> curveBuffer;
Config progConfig;

bool fexists(const std::string& filename);

/*
 *
int main(int argc, char *argv[]) {

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



    if(fileName.size() > 0)
        shader = new Shader(fileName);
    else
        shader = new Shader();

    vertexBuffer = std::vector<std::shared_ptr<Vector>>();
    curveBuffer = std::make_shared<Curve>();

    shader->loadFile();

    return 0;
}
 */



bool fexists(const std::string& filename);

int MARGIN = 20;


WindowManager::WindowManager(){
    views = nullptr;
}

WindowManager::WindowManager(int argc, char** argv, QMainWindow * parent, const std::string& title, int window_width, int window_height)
    :QMainWindow(parent),
     ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);

    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
    dock->setWidget(new OGLWidget());
    addDockWidget(Qt::LeftDockWidgetArea, dock);

	mainWindowWidth = window_width;
	mainWindowHeight = window_height;
	numOfWindows = 2;

	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE); 

	//set window size to 200*200 
	glutInitWindowSize(window_width*2 + 3*MARGIN, window_height + 2*MARGIN); 

	//set window position 
	glutInitWindowPosition(400, 200);
	//create and set main window title 
    mainWindowContex = glutCreateWindow(title.c_str());

	glClear(GL_COLOR_BUFFER_BIT); 


	views = new View*[numOfWindows];

	views[0] 	= new CVM (PERSP, mainWindowContex, MARGIN, 					MARGIN, window_width, window_height);
    // views[1] 	= new TextView 	(TEXTVIEW, mainWindowContex, window_width + MARGIN*2, MARGIN, window_width, window_height);

    // viewss[4] = new views(mainWindowContex, 0, 0, window_width, window_height);



	glClearColor(0, 0, 0, 0); 
	//clears the buffer of OpenGL //sets views function 
}

WindowManager::~WindowManager(){
	if (views != nullptr){
		for (int i = 0; i < 4; i++)
			delete (views[i]);
		delete[] (views);
	}
}

WindowManager::WindowManager(const WindowManager& rhs){
	mainWindowWidth = rhs.mainWindowWidth;
	mainWindowHeight = rhs.mainWindowHeight;
	views = rhs.views;
	mainWindowContex = rhs.mainWindowContex;
}

void WindowManager::updateWindow(const int & winID){

	View* curD = (*this)[winID];
	if (curD != nullptr){
		if ( curD->viewType == CABINET)
			dynamic_cast<Cabinet*>(curD)->updateWindow();
		else if ( curD->viewType == TEXTVIEW){
			//std::cout << "here" << std::endl;
			dynamic_cast<TextView*>(curD)->updateWindow();
		}
		else if ( curD->viewType == XY || curD->viewType == ZY || curD->viewType == XZ)
			dynamic_cast<OrthoView*>(curD)->updateWindow();
		else if ( curD->viewType == PERSP)
			dynamic_cast<CVM*>(curD)->updateWindow();
	}
	//viewss[4]->updateWindow()
	glutPostRedisplay();
}


void WindowManager::fillPolygon(Geometry &geo, const float* color){
	for ( int i = 0; i < numOfWindows; i++)
		views[i]->fillPolygon(geo, color);
}


void WindowManager::fillPolygons(std::vector<std::shared_ptr<Geometry>> &geo){
	for ( int i = 0; i < numOfWindows; i++)
		views[i]->fillPolygons(geo);
}

void WindowManager::drawVertex(const Vector & v, float const* color){
	for ( int i = 0; i < numOfWindows; i++)
		views[0]->drawVertex(v, color);
}

void WindowManager::halfToning(Geometry &geometries){
	for ( int i = 0; i < numOfWindows; i++)
		views[i]->halfToning(geometries);
}

void WindowManager::drawLineDDA(const Vector &v1, const Vector &v2, float const*color){

	for ( int i = 0; i < numOfWindows - 1; i++){
		if (views[i]->viewType == CABINET)
			(dynamic_cast<Cabinet*>(views[i]))->drawLineDDA(v1, v2, color);
		else if (views[i]->viewType == PERSP)
			(dynamic_cast<CVM*>(views[i]))->drawLineDDA(v1, v2, color);
	}
}

void WindowManager::drawLine(const Vector &v1, const Vector &v2, float const*color){
	if (progConfig.lineAlg == DDA)
        drawLineDDA(v1, v2, color);
}


void WindowManager::setPix(const Vector* v,  float const* color){
	
	for ( int i = 0; i < 4; i++)
		views[i]->setPix( v, color);
}

void WindowManager::setPix(const int& x, const int& y,  float const* color){

	for ( int i = 0; i < 4; i++)
		views[i]->setPix(x, y, color);
}


void WindowManager::keyboardHandler(const unsigned char &key, const int &x, const int &y)const{
	keyboard->keyboardHandler(key, x, y);
	((TextView*)views[TEXTVIEW])->updateWindow();
}
void WindowManager::keyboardReleaseHandler(const unsigned char &key, const int &x, const int &y)const{
	keyboard->keyboardReleaseHandler(key, x, y);
}


int WindowManager::getWindowID(View* d) {
	for (int i = 1; i < 4; i++)
		if (d == views[i])
			return i;

	return -1;
}

View* WindowManager::operator[](const int& windowID)const { 
	for ( int i = 0; i < numOfWindows; i++) 
		if (views[i]->windowContext == windowID) 
			return views[i];  

	return nullptr; 
}



bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
}
