#include <GL/glut.h>
#include <string>
#include <iostream>
#include <QDesktopWidget>
#include <QDockWidget>
#include "oglwidget.h"
#include "WindowManager.h"
#include "Keyboard.h"
#include "Cabinet.h"
#include "Shader.h"
#include "View.h"
#include "TextView.h"
#include "Face.h"
#include "Config.h"
#include "CVM.h"

extern Config progConfig;
extern Shader* shader;

void update();
void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);


int MARGIN = 20;

WindowManager::WindowManager(QWidget *parent)
    :QMainWindow(parent)
     //ui(new Ui::WindowManager)
{

    // Initialize Ui
    //ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);


    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
    dock->setWidget(new CVM(dock));
    //dock->setWidget(new OGLWidget());
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    // load Object
    shader.loadFile();


}



WindowManager::WindowManager(int argc, char** argv, const std::string& title, int window_width, int window_height){
	mainWindowWidth = window_width;
	mainWindowHeight = window_height;
	numOfWindows = 2;

    //glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_SINGLE);

	//set window size to 200*200 
    //glutInitWindowSize(window_width*2 + 3*MARGIN, window_height + 2*MARGIN);

	//set window position 
    //glutInitWindowPosition(400, 200);
	//create and set main window title 
    //mainWindowContex = glutCreateWindow(title.c_str());
    //glutDisplayFunc(::update);

    //glClear(GL_COLOR_BUFFER_BIT);


	views = new View*[numOfWindows];

    //views[0] 	= new CVM (PERSP, mainWindowContex, MARGIN, 					MARGIN, window_width, window_height);
    //views[1] 	= nullptr;// new TextView 	(TEXTVIEW, mainWindowContex, window_width + MARGIN*2, MARGIN, window_width, window_height);
    //views[2]    = nullptr;views[3] = nullptr;
	//viewss[4] = new views(mainWindowContex, 0, 0, window_width, window_height);



    //glClearColor(0, 0, 0, 0);
	//clears the buffer of OpenGL //sets views function 
}

WindowManager::~WindowManager(){
	if (views != nullptr){
        for (int i = 0; i < 0; i++)
			delete (views[i]);
        //delete[] (views);
	}
}

WindowManager::WindowManager(const WindowManager& rhs){
	mainWindowWidth = rhs.mainWindowWidth;
	mainWindowHeight = rhs.mainWindowHeight;
	views = rhs.views;
	mainWindowContex = rhs.mainWindowContex;
}

void WindowManager::updateWindow(const int & winID){
/*
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
    //glutPostRedisplay();
    */
}
/*
void WindowManager::reshapeWindows(){
	if( shader->size() < 1 )
		return;
	Vector min(shader->getMinX(), shader->getMinY(), shader->getMinZ());
	Vector max(shader->getMaxX(), shader->getMaxY(), shader->getMaxZ());

	for( int i = 0; i < numOfWindows; i++ )
		if(views[i]->viewType == XY || views[i]->viewType == XZ || views[i]->viewType == ZY)
			static_cast<OrthoView*>(views[i])->reshapeWindow(min, max);

}
*/

void WindowManager::fillPolygon(Geometry &geo, const float* color){

}


void WindowManager::fillPolygons(std::vector<std::shared_ptr<Geometry>> &geo){

}

void WindowManager::drawVertex(const Vector & v, float const* color){

}

void WindowManager::halfToning(Geometry &geometries){

}

void WindowManager::drawLineDDA(const Vector &v1, const Vector &v2, float const*color){


}

void WindowManager::drawLineBSH(const Vector &v1, const Vector &v2, float const*color){
	// for ( int i = 0; i < 4; i++)
	// 	views[i]->drawLineBSH(v1, v2, color);
}

void WindowManager::drawLine(const Vector &v1, const Vector &v2, float const*color){
	if (progConfig.lineAlg == DDA)
		drawLineDDA(v1, v2, color);
	else 
		drawLineBSH(v1, v2, color);
}

void WindowManager::setPix(const Vector* v,  float const* color){
	

}

void WindowManager::setPix(const int& x, const int& y,  float const* color){

}


void WindowManager::keyboardHandler(const unsigned char &key, const int &x, const int &y)const{
	keyboard->keyboardHandler(key, x, y);
    //((TextView*)views[TEXTVIEW])->updateWindow();
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


