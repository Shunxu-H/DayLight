#ifndef WINDOWMANAGER_H
	#define WINDOWMANAGER_H

//#include "Renderer.h"


class View;
namespace Lumos {
    class Shader;
}

class Keyboard;
class WindowManager
{
public:
    // Disable copy constructor
    WindowManager( const WindowManager& ) = delete;
    // Disable assignment operator
    WindowManager& operator = ( const WindowManager& ) = delete;

    WindowManager();
    virtual ~WindowManager();
    void render();
/*
    void updateAllViews();

    void setUpProgram( const std::string & shaderDir );
    void setUpProgram( const std::vector<Lumos::Shader> & shader );

    void createMenus();

    void positionAllViewsToFitAllInstances();

*/
protected:

private:


    // std::vector< View* > _views;
    // View * _render_hidden_view;


};




	#endif
