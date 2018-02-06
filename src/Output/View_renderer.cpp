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
    , _multisampledFrameBuffer(w, h)
{

  _multisampledFrameBuffer.use();
  glGetError();
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  //QTimer::singleShot(1000, this, SLOT(_checkRendererReady()));
}


View_renderer::~View_renderer(){}

void View_renderer::resizeGL(const size_t & w, const size_t &h){
	_width = w;
	_height = h;
  _multisampledFrameBuffer.resize(w, h);
  _frameBuffer.resize(w, h);
  Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
}

cv::Mat View_renderer::_saveColorImage(const std::string & fileName){
    _multisampledFrameBuffer.use();
    paintGL();
    return _multisampledFrameBuffer.saveColorBuffer2file(fileName);
}

cv::Mat View_renderer::_saveBitMap(const std::string & fileName){
    cv::Mat compressed(_height, _width, IPL_DEPTH_1U);
    cv::Mat colorImg = _saveColorImage("");

    //Grayscale matrix
    cv::Mat grayscaleMat (colorImg.size(), CV_8UC1);

    //Convert BGR to Gray
    cv::cvtColor( colorImg, grayscaleMat, CV_BGR2GRAY );

    //Binary image
    cv::Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());

    //Apply thresholding
    cv::threshold(grayscaleMat, binaryMat, 100, 255, cv::THRESH_BINARY);

    if (fileName.size() > 0){
        cv::imwrite(fileName, binaryMat);
        //Debug("save " << fileName);
    }
    return binaryMat;
}


cv::Mat View_renderer::_saveDepthImage(const std::string & fileName){
    _multisampledFrameBuffer.use();
    paintGL();
    return _multisampledFrameBuffer.saveDepthBuffer2file(fileName);
}

void View_renderer::getVisibleObjects(const std::string & path){
    // color code objects
    size_t numOfInstances = world->getInstances().size();
    std::vector< Lumos::Instance * > worldInstances = world->getInstances();

    // use mask shader temperarily
    // use non multisampled frame buffer to avoid averaging pixel valie on the
    // edges
    std::string temp = _shaderId;
    _shaderId = Lumos::Shader::mask_shader_id;
    _frameBuffer.use();
    paintGL();
    _shaderId = temp;
    //GLubyte * pixels = new GLubyte [width*height*4*sizeof(GLuint)];
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );

    cv::Mat img = _frameBuffer.saveColorBuffer2file(path + "colorCodedScene.png");

    _multisampledFrameBuffer.use();
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );

    std::set<size_t> pickedInstanceIndices;
    for (size_t rowItr = 0; rowItr < static_cast<size_t>(_height); rowItr++){
        for (size_t colItr = 0; colItr < static_cast<size_t>(_width); colItr++){
            cv::Vec3b p = img.at<cv::Vec3b>(rowItr, colItr);
            pickedInstanceIndices.insert(Color::toUniqueInt(p.val[2], p.val[1], p.val[0]));
        }
    }

    // make sure the result we get is reasonable
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

    // make everythign invisible
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOff();
    }
    _frameBuffer.use();
    std::string tempShaderId = _shaderId;
    _shaderId = Lumos::Shader::mask_shader_id;
    Lumos::Instance * curOn = nullptr;

    // render instances one by one and save it to a file 
    for (Lumos::Instance * ins : _visibles)
    {
        if (curOn != nullptr)
            curOn->turnOff();
        ins->turnOn();
        curOn = ins;
        ins->setPickingColor(color3(1, 1, 1));
        paintGL();
        _frameBuffer.saveBitMap2file( savePath + "mask_" + ins->getId() + ".png" );
    }

    // turn visibility back on for all instances
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOn();
    }

    _shaderId = tempShaderId;

    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );

}

void View_renderer::generateData(){
    std::string parentDir = OUTPUT_DIR + shaper->getCurFileName() + "/";
    Utils::cleanAndMkdir(parentDir + _camInUse->getId());

    world->saveColor2InstanceMapping(parentDir + "Color2InstanceMapping.txt");
    generateMasks();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    toImageFile_color( parentDir + _camInUse->getId() + "/color.png" );
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    toImageFile_depth( parentDir + _camInUse->getId() + "/depth.png");

    GLError( __PRETTY_FUNCTION__ , __LINE__ );

}




void View_renderer::toImageFile_color( const std::string & fileName ){

    paintGL();
    _saveColorImage(fileName);

}

void View_renderer::toImageFile_depth( const std::string & fileName ) {
    int w = 0, h = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);


    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    paintGL();
    _saveDepthImage(fileName);
}
