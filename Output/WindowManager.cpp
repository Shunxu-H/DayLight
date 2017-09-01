#include <GL/glut.h>
#include <string>
#include <iostream>
#include <QDesktopWidget>
#include <QDockWidget>
#include <experimental/filesystem>
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

void update();
void keyboardHandler(unsigned char key, int x, int y);
void keyboardReleaseHandler(unsigned char key, int x, int y);

namespace Lumos {


int MARGIN = 20;

WindowManager::WindowManager(QWidget *parent)
    :QMainWindow(parent),
     gProgram( nullptr )
     //ui(new Ui::WindowManager)
{

    // Initialize Ui
    //ui->setupUi(this);
    resize( INITIAL_WIN_SIZE[0], INITIAL_WIN_SIZE[1] );


    QDockWidget *dock = new QDockWidget(tr("Canvas"), this);
    dock->setWidget(new CVM(dock));
    //dock->setWidget(new OGLWidget());
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    // load Object
    // shader.loadFile();

}


WindowManager::~WindowManager(){

}

void WindowManager::setUpProgram( const std::string & shaderDir ){
    std::vector<Lumos::Shader> shaders;

    {
        namespace fs = std::experimental::filesystem;

        for (const auto & p : fs::directory_iterator(shaderDir))
        {

            //std::cout << fs::path(p).extension() << std::endl;
            if ( std::string( fs::path(p).extension() ).compare(".vert") == 0 )
                shaders.push_back(Shader::readFromFile( fs::path( p ), GL_VERTEX_SHADER ));
            else if ( std::string( fs::path(p).extension() ).compare(".frag") == 0 )
                shaders.push_back(Shader::readFromFile( fs::path( p ), GL_FRAGMENT_SHADER ));
        }

    }
    gProgram = new Program(shaders);

}

void WindowManager::setUpProgram( const std::vector<Lumos::Shader> & shader ){

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
//	keyboard->keyboardHandler(key, x, y);
    //((TextView*)views[TEXTVIEW])->updateWindow();
}
void WindowManager::keyboardReleaseHandler(const unsigned char &key, const int &x, const int &y)const{
    //keyboard->keyboardReleaseHandler(key, x, y);
}


int WindowManager::getWindowID(View* d) {
	for (int i = 1; i < 4; i++)
		if (d == views[i])
			return i;

	return -1;
}

View* WindowManager::operator[](const int& windowID)const { 
/*
    for ( int i = 0; i < numOfWindows; i++)
		if (views[i]->windowContext == windowID) 
			return views[i];  

	return nullptr; 
    */
}

}
