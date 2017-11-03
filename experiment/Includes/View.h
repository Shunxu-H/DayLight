#ifndef VIEW_H
	#define VIEW_H

#include <memory>
#include "Shader.h"

class WindowManager;

namespace Patronus {
    class Camera;
}

namespace Lumos{
    class Instance;
}

class Renderer;

class View
{
public:
    View(
            const size_t & w = 500,
            const size_t & h = 500,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
            const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
        );

    //View(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~View(){}

    inline void
        setCamInUse( Patronus::Camera * cam) { _camInUse = cam; }
    inline Patronus::Camera*
        getCamInUse() const { return _camInUse; }

    inline void
        setShaderId( const std::string & id) { _shaderId = id; }
    inline std::string
        getShaderId() const { return _shaderId; }


    void fitSphere(const point3 & position, const float & radius);
    void loadAttribsAndUniform() const;

    inline size_t getWidth() const {return _width;}
    inline size_t getHeight() const {return _height;}

    virtual void initializeGL() ;
    virtual void resizeGL(const size_t & w, const size_t & h) ;
    virtual void paintGL() ;
protected:



    void getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const;

    Patronus::Camera * _camInUse;
    GLuint _VAO;
    std::string _shaderId;
    std::vector< Lumos::Instance * > _visibles;
    size_t _width;
    size_t _height;
private:
    friend class WindowManager;

};



#endif 
