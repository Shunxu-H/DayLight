#include <cstddef>
#include "Utility.h"
#include "FrameBuffer.h"

namespace Lumos{

FrameBuffer::FrameBuffer(const size_t & width, const size_t & height )
  : FrameBuffer_base(width, height)
{
    _colorTexBuffer.makeColorTextureBuffer(_width, _height);
    _depthTexBuffer.makeDepthTextureBuffer(_width, _height);

}

FrameBuffer & FrameBuffer::operator = ( const FrameBuffer & that){
  FrameBuffer_base::operator=(that);
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

    //cv::Point min_loc, max_loc
    // uint8_t min, max;
    // cv::minMaxLoc(img, &min, &max, &min_loc, &max_loc);
    // Debug()

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






}
