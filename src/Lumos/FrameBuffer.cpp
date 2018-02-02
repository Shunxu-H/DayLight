#include <cstddef>
#include "Utility.h"
#include "FrameBuffer.h"

namespace Lumos{

FrameBuffer::FrameBuffer(const size_t & width, const size_t & height )
  : FrameBuffer_base()
  , _colorTexBuffer(width, height)
  , _depthTexBuffer(width, height)
{
  assert(_colorTexBuffer.isInitialized() and _depthTexBuffer.isInitialized()
        and "_colorTexBuffer or _depthTexBuffer is not initialized properly");

  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  use();
  // attach color
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_COLOR_ATTACHMENT0,
                         GL_TEXTURE_2D,
                         _colorTexBuffer.getGlObjId(),
                         0);
  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         GL_DEPTH_ATTACHMENT,
                         GL_TEXTURE_2D,
                         _depthTexBuffer.getGlObjId(),
                         0);


  // Set the list of draw buffers.
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  // check buffer status
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
      throw std::runtime_error ( "Error! FrameBuffer is not complete" );



  // GLint drawId = 0, readId = 0;
  // glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
  // glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);


  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

  //glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right


  stopUsing();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
}

FrameBuffer & FrameBuffer::operator = ( const FrameBuffer & that){
  FrameBuffer_base::operator=(that);
  _colorTexBuffer = that._colorTexBuffer;
  _depthTexBuffer = that._depthTexBuffer;
  return *this;
}

FrameBuffer::~FrameBuffer()
{

}


cv::Mat FrameBuffer::saveColorBuffer2file(const std::string & filename){

  _colorTexBuffer.use();

  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  cv::Mat img(_height, _width, CV_8UC3);
  glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
  glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());

  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  glGetTexImage ( GL_TEXTURE_2D,
                  0,
                  GL_BGR, // GL will convert to this format
                  GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                  img.data );

  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  cv::Mat flipped(img);
  cv::flip(img, flipped, 0);
  if (filename.size() > 0){
      cv::imwrite(filename, img);
      //Debug("save " << fileName);
  }

  _colorTexBuffer.stopUsing();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );
  return img;
}


cv::Mat FrameBuffer::saveDepthBuffer2file(const std::string & filename){

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _depthTexBuffer.use();

    cv::Mat img(_height, _width, CV_8UC1);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
	  glGetTexImage ( GL_TEXTURE_2D,
  	                0,
  	                GL_DEPTH_COMPONENT, // GL will convert to this format
  	                GL_UNSIGNED_BYTE,   // Using this data type per-pixel
  	                img.data );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );


    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    if( filename.size() > 0 ){
        cv::imwrite(filename, img);
        //Debug("save " << fileName );
    }

    _depthTexBuffer.stopUsing();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    return img;
}

void FrameBuffer::resize(const size_t & width, const size_t & height)
{
  assert("You will eventually have to build this, buddy");
}




}
