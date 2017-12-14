/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

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
            const size_t & x = 0,
            const size_t & y = 0,
            const size_t & w = 500,
            const size_t & h = 500,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
            const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
        );

    //View(const Patronus::CameraType &vt, const int& mainContext, const int& loc_x, const int& loc_y, const int& window_width, const int& window_height);//, int canvas_width, int canvas_height);
    virtual ~View(){}

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

    inline size_t getWidth() const {return _width;}
    inline size_t getHeight() const {return _height;}
    inline size_t getX() const {return _x;}
    inline size_t getY() const {return _y;}
    /**
     * END OF GETTERS AND SETTERS
     */

    bool isClick(const size_t & x, const size_t & y);
    void fitSphere(const point3 & position, const float & radius);
    void loadAttribsAndUniform() const;
    virtual void initializeGL() ;
    virtual void resizeGL(const size_t & w, const size_t & h) ;
    virtual void paintGL() ;
protected:
    void getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const;

    size_t _x, _y;
    size_t _width, _height;

    Patronus::Camera * _camInUse;
    GLuint _VAO;
    std::string _shaderId;
    std::vector< Lumos::Instance * > _visibles;
private:
    friend class WindowManager;

};



#endif
