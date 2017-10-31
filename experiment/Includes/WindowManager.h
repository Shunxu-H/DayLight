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


*/
    void positionAllViewsToFitAllInstances();
    
    inline size_t 
    getWidth() const { return _width; }
    inline  void
    setWidth( const size_t & w) {  _width = w; }
    inline size_t 
    getHeight() const { return _height; }
    inline  void
    setHeight( const size_t & h) {  _height = h; }
protected:

private:
    size_t _width;
    size_t _height;
    std::vector< View* > _views;
    // View * _render_hidden_view;
    

    void _headlessInit();

};




	#endif
