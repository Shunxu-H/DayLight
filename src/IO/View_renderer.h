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
#pragma once 

#include <IO/PerspectiveView.h>
#include <Lumos/FrameBuffer.h>
#include <Lumos/MultisampledFrameBuffer.h>
// #include "FrameBuffer_base.h"


namespace Daylight::IO
{
  


class View_renderer : public PerspectiveView {
public:
  View_renderer(
    const size_t & x = 0,
    const size_t & y = 0,
    const size_t & w = 500,
    const size_t & h = 500,
    const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr ),
    const std::string & shaderId = Lumos::Shader::default_mesh_shader_id
  );
  View_renderer(const View_renderer & that) = delete;
  View_renderer operator = ( const View_renderer & that) = delete;
  virtual ~View_renderer();

  void toImageFile_color( const std::string & fileName );
  void toImageFile_depth( const std::string & fileName );
  void getVisibleObjects( const std::string & path );
  void generateMasks();
  void generateData();


  virtual void resizeGL(const size_t & w, const size_t &h) override;

protected:


private:
  Lumos::FrameBuffer _frameBuffer;
  Lumos::MultisampledFrameBuffer _multisampledFrameBuffer;

  cv::Mat _saveColorImage(const std::string & fileName);
  cv::Mat _saveDepthImage(const std::string & fileName);
  cv::Mat _saveBitMap(const std::string & fileName);

  void _saveColorBuffer(const std::string & fileName);
  void _saveDepthBuffer(const std::string & fileName);
};

} // Daylight::IO