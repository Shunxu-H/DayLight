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
#ifndef VIEW_RENDERER_H
#define VIEW_RENDERER_H

#include "View.h"

class View_renderer : public View{
public:
    View_renderer(
            const size_t & x = 0,
            const size_t & y = 0,
            const size_t & w = 500,
            const size_t & h = 500,
	        const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
	        const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
         );
    virtual ~View_renderer();

    void toImageFile_color( const std::string & fileName );
    void toImageFile_depth( const std::string & fileName );
    void getVisibleObjects();
    void generateMasks();
    void generateData();

    virtual void initializeGL() override;
    virtual void resizeGL(const size_t & w, const size_t &h) override;

protected:


private:
    GLuint _Multisampled_FBO;
    GLuint _Multisampled_ColorBuffer;
    GLuint _Multisampled_DepthBuffer;
    GLuint _out_FBO;
    GLuint _out_ColorTextureObject;
    GLuint _out_DepthTextureObject;

    cv::Mat _saveColorImage(const std::string & fileName);
    cv::Mat _saveDepthImage(const std::string & fileName);
    cv::Mat _saveBitMap(const std::string & fileName);

    void _saveColorBuffer(const std::string & fileName);
    void _saveDepthBuffer(const std::string & fileName);
    void _deleteMultisampledBuffers();
    void _deleteOutTextures();
    void _makeMultisampledBuffers();
    void _makeOutTextures();
    void _remakeMultisampledBuffers();
    void _remakeOutTextures();
};

#endif // VIEW_RENDERER_H
