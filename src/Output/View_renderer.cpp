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
#include <algorithm>
#include "View_renderer.h"
#include "Extern.h"
#include "Utility.h"


View_renderer::View_renderer(
        const size_t & x,
        const size_t & y,
        const size_t & w,
        const size_t & h,
		const std::shared_ptr<Patronus::Camera> & cam,
		const std::string & shaderId )
    : PerspectiveView(x, y, w, h, cam, shaderId)
    , _frameBuffer(w, h)
{
  _multisampledFrameBuffer = Lumos::MultisampledFrameBuffer(w, h);
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  _multisampledFrameBuffer.use();
  glGetError();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

}


View_renderer::~View_renderer(){

}


void View_renderer::resizeGL(const size_t & w, const size_t &h){
	_width = w;
	_height = h;
  _multisampledFrameBuffer.resize(w, h);
  _frameBuffer.resize(w, h);
  Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
}

void View_renderer::initializeGL(){
  _makeMultisampledBuffers();
  _makeOutTextures();
	PerspectiveView::initializeGL();
}


cv::Mat View_renderer::_saveColorImage(const std::string & fileName){

  // // blit frame buffer
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBindFramebuffer(GL_READ_FRAMEBUFFER, _Multisampled_FBO);
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _out_FBO);
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBlitFramebuffer(  0,
  //                     0,
  //                     _width,
  //                     _height,
  //                     0,
  //                     0,
  //                     _width,
  //                     _height,
  //                     GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
  //                     GL_NEAREST
  //                   );
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // cv::Mat img(_height, _width, CV_8UC3);
  // glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
  // glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
  // glBindTexture(GL_TEXTURE_2D, _out_ColorTextureObject);
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glGetTexImage ( GL_TEXTURE_2D,
  //                 0,
  //                 GL_BGR, // GL will convert to this format
  //                 GL_UNSIGNED_BYTE,   // Using this data type per-pixel
  //                 img.data );
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // cv::Mat flipped(img);
  // cv::flip(img, flipped, 0);
  // if (fileName.size() > 0){
  //     cv::imwrite(fileName, img);
  //     //Debug("save " << fileName);
  // }
  //
  // glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // return img;
  return cv::Mat();
}

cv::Mat View_renderer::_saveBitMap(const std::string & fileName){
  // cv::Mat compressed(_height, _width, IPL_DEPTH_1U);
  // cv::Mat colorImg = _saveColorImage("");
  //
  // //Grayscale matrix
  // cv::Mat grayscaleMat (colorImg.size(), CV_8UC1);
  //
  // //Convert BGR to Gray
  // cv::cvtColor( colorImg, grayscaleMat, CV_BGR2GRAY );
  //
  // //Binary image
  // cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());
  //
  // //Apply thresholding
  // cv::threshold(grayscaleMat, binaryMat, 100, 255, cv::THRESH_BINARY);
  //
  // if (fileName.size() > 0){
  //     cv::imwrite(fileName, binaryMat);
  //     //Debug("save " << fileName);
  // }
  // return binaryMat;
  return cv::Mat();
}


cv::Mat View_renderer::_saveDepthImage(const std::string & fileName){
  //
  // // blit frame buffer
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBindFramebuffer(GL_READ_FRAMEBUFFER, _Multisampled_FBO);
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _out_FBO);
  // glBlitFramebuffer(  0,
  //                     0,
  //                     _width,
  //                     _height,
  //                     0,
  //                     0,
  //                     _width,
  //                     _height,
  //                     GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
  //                     GL_NEAREST
  //                   );
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // cv::Mat img(_height, _width, CV_8UC1);
  // // glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
  // // glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBindTexture(GL_TEXTURE_2D, _out_DepthTextureObject);
  // glGetTexImage ( GL_TEXTURE_2D,
	//                 0,
	//                 GL_DEPTH_COMPONENT, // GL will convert to this format
	//                 GL_UNSIGNED_BYTE,   // Using this data type per-pixel
	//                 img.data );
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // //cv::Point min_loc, max_loc
  // // uint8_t min, max;
  // // cv::minMaxLoc(img, &min, &max, &min_loc, &max_loc);
  // // Debug()
  //
  // cv::Mat flipped(img);
  // cv::flip(img, flipped, 0);
  // if( fileName.size() > 0 ){
  //     cv::imwrite(fileName, img);
  //     //Debug("save " << fileName );
  // }
  //
  // glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // return img;
  return cv::Mat();
}



void View_renderer::_makeMultisampledBuffers(){
  //
  //
  // assert(_Multisampled_ColorBuffer == 0 and _Multisampled_DepthBuffer == 0 and _Multisampled_FBO != 0);
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
  //
  // int samples;
  // char ErrorMessage[1024];
  // //We need to find out what the maximum supported samples is
  // glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
  // //----------------------
  // //If for example, 16 is returned, then you can attempt to make a FBO with samples=0 to 16
  // //0 means no multisample. This is like using glFramebufferRenderbufferEXT instead of glRenderbufferStorageMultisampleEXT
  // //You can attempt to make sample from 1 to 16, but some of them might fail
  // //Now, let's make a FBO
  // assert( samples >= 4);
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // //----------------------
  // //Now make a multisample color buffer
  // //glGenRenderbuffers(1, &_Multisampled_ColorBuffer);
  // //glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_ColorBuffer);
  // //samples=4, format=GL_RGBA8, width=256, height=256
  // //glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA8, _width, _height);
  // glGenTextures(1, &_Multisampled_ColorBuffer);
  // glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _Multisampled_ColorBuffer);
  // glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
  //                         samples,
  //                         GL_RGBA,
  //                         _width,
  //                         _height,
  //                         GL_FALSE);
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // //----------------------
  // //Make a depth multisample depth buffer
  // //You must give it the same samples as the color RB, same width and height as well
  // //else you will either get a GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT or some other error
  //
  // //glGenRenderbuffers(1, &_Multisampled_DepthBuffer);
  // // glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
  // //                         samples,
  // //                         GL_DEPTH_COMPONENT32F,
  // //                         _width, _height, GL_FALSE);
  //
  // //glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_DepthBuffer);
  // //samples=4, format=GL_DEPTH_COMPONENT24, width=256, height=256
  // //glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT32F, _width, _height);
  // //----------------------
  // glGenTextures(1, &_Multisampled_DepthBuffer);
  // glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _Multisampled_DepthBuffer);
  // glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE,
  //                         samples,
  //                         GL_DEPTH_COMPONENT32F,
  //                         _width,
  //                         _height,
  //                         GL_FALSE);
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // //It's time to attach the RBs to the FBO
  // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _Multisampled_ColorBuffer, 0);
  // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _Multisampled_DepthBuffer, 0);
  // //----------------------
  // //Make sure FBO status is good
  //
  // GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  // glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
  // if(Utils::glExtCheckFramebufferStatus(ErrorMessage) != 1){
  //     std::cerr << ErrorMessage << std::endl;
  //     exit(EXIT_FAILURE);
  // }
  //
  //
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );

}


void View_renderer::_makeOutTextures(){

  // assert(_out_ColorTextureObject == 0 and _out_DepthTextureObject == 0 and _out_FBO != 0);
  //
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // glGenTextures(1, &_out_ColorTextureObject);
  // glBindTexture(GL_TEXTURE_2D, _out_ColorTextureObject);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
  //                     _width, _height,
  //                     0, GL_RGBA, GL_UNSIGNED_BYTE,
  //                     NULL);
  //
  // // create a depth texture
  // glGenTextures(1, &_out_DepthTextureObject);
  // glBindTexture(GL_TEXTURE_2D, _out_DepthTextureObject);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F,
  //                     _width, _height,
  //                     0, GL_DEPTH_COMPONENT, GL_FLOAT,
  //                     NULL);
  //
  //
  //
  //
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  // glBindFramebuffer(GL_FRAMEBUFFER, _out_FBO);
  // // attach color
  // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _out_ColorTextureObject, 0);
  // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_TEXTURE_2D, _out_DepthTextureObject, 0);
  //
  //
  // // Set the list of draw buffers.
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // // check buffer status
  // if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  //     throw std::runtime_error ( "Error! FrameBuffer is not complete" );
  //
  //
  //
  // // GLint drawId = 0, readId = 0;
  // // glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
  // // glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);
  //
  //
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
  //
  // GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  // glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
  //
  // //glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
  //
  //
  // glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
  // GLError( __PRETTY_FUNCTION__ , __LINE__ );
}




void View_renderer::getVisibleObjects(const std::string & path){
    // color code objects
    size_t numOfInstances = world->getInstances().size();
    std::vector< Lumos::Instance * > worldInstances = world->getInstances();

    std::string temp = _shaderId;
    _shaderId = Lumos::Shader::mask_shader_id;
    _frameBuffer.use();
    paintGL();
    _shaderId = temp;
    //GLubyte * pixels = new GLubyte [width*height*4*sizeof(GLuint)];
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );


    cv::Mat colorCodedScene = _frameBuffer.saveColorBuffer2file(path + "colorCodedScene.png");

    _frameBuffer.stopUsing();
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );

    std::set<size_t> pickedInstanceIndices;
    // for (size_t pixelItr = 0; pixelItr < static_cast<size_t>(_width*_height); pixelItr++){
    //     size_t initPos = pixelItr*3;
    //     cv::Point img.at<uint8_t>(initPos+2)
    //     pickedInstanceIndices.insert(Color::toUniqueInt(img.at<uint8_t>(initPos+2), img.at<uint8_t>(initPos+1), img.at<uchar>(initPos)));
    // }

    for (size_t rowItr = 0; rowItr < static_cast<size_t>(_height); rowItr++){
        for (size_t colItr = 0; colItr < static_cast<size_t>(_width); colItr++){
            cv::Vec3b p = colorCodedScene.at<cv::Vec3b>(rowItr, colItr);
            pickedInstanceIndices.insert(Color::toUniqueInt(p.val[2], p.val[1], p.val[0]));
        }
    }

    assert(*std::max_element(pickedInstanceIndices.begin(), pickedInstanceIndices.end()) <= numOfInstances);
    assert(*std::min_element(pickedInstanceIndices.begin(), pickedInstanceIndices.end()) >= 0);
    //cv::imshow("test", img);
    _visibles.clear();
    for (const int & index: pickedInstanceIndices){
        if ( index > 0 )
            _visibles.push_back(worldInstances[index-1]);
    }

}

void View_renderer::generateMasks(){
    const std::string savePath =  OUTPUT_DIR + shaper->getCurFileName() +
                    "/" + _camInUse->getId() + "/";
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
    getVisibleObjects(savePath);
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );

    // make everything invisible
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOff();
    }

    // disable anti-aliasing
    _frameBuffer.use();
    // save the original shader
    std::string tempShaderId = _shaderId;
    _shaderId = Lumos::Shader::mask_shader_id;
    Lumos::Instance * curOn = nullptr;
    for (Lumos::Instance * ins : _visibles)
    {
        if (curOn != nullptr)
            curOn->turnOff();
        ins->turnOn();
        curOn = ins;
        ins->setPickingColor(color3(1, 1, 1));
        paintGL();
        _saveBitMap(  savePath + "mask_" + ins->getId() + ".png" );
    }
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOn();
    }

    _shaderId = tempShaderId;

    _frameBuffer.stopUsing();
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );

}

void View_renderer::generateData(){
    std::string parentDir = OUTPUT_DIR + shaper->getCurFileName() + "/";
    Utils::cleanAndMkdir(parentDir + _camInUse->getId());

    world->saveColor2InstanceMapping(parentDir + "Color2InstanceMapping.txt");
    generateMasks();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    _multisampledFrameBuffer.use();
    paintGL();
    _multisampledFrameBuffer.saveColorBuffer2file(parentDir + _camInUse->getId() + "/color.png");
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    _multisampledFrameBuffer.saveDepthBuffer2file(parentDir + _camInUse->getId() + "/depth.png");

    GLError( __PRETTY_FUNCTION__ , __LINE__ );

}
