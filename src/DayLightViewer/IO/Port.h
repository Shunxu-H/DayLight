/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef PORT_H
	#define PORT_H

#include <memory>
#include <Output/View.h>
#include <Lumos/Shader.h>

namespace Patronus {
    class Camera;
};

namespace Lumos{
    class Instance;
};

class GLFWwindow; 
namespace DayLight::IO{


class Port 
{
public:
    Port(
        const size_t & w = 500,
        const size_t & h = 500,
        const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
        const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
    );

    //View(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~Port(){}

    /**
     * START OF GETTERS AND SETTERS
     */
    inline void
        setCamInUse( Patronus::Camera * cam) { _camInUse = cam; }
    inline Patronus::Camera*
        getCamInUse() const { return _camInUse; }

    inline void
        setShaderId( const std::string & id) { _shaderId = id; }
    inline std::string
        getShaderId() const { return _shaderId; }

    /**
     * END OF GETTERS AND SETTERS
     */

    void fitSphere(const point3 & position, const float & radius);
    void loadAttribsAndUniform() const;
    virtual void initialize();
    virtual void resize(const size_t & w, const size_t & h);
    virtual void paint();
    
    void cursorPosHandle(GLFWwindow *, double, double); 
    void cursorScrollHandle (GLFWwindow *, double, double); 



protected:
    void getMouseBeam(const int & mouseX, const int & moustY, point3 * start, point3 * direction ) const ;


    Patronus::Camera * _camInUse;
    GLuint _VAO;
    std::string _shaderId;
    std::vector< Lumos::Instance * > _visibles;
private:
    size_t _width; 
    size_t _height; 
    bool _isExposed; 

};

}

#endif
