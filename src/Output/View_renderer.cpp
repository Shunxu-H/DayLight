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
    : View(x, y, w, h, cam, shaderId)
    , _Multisampled_FBO(0)
    , _Multisampled_ColorBuffer(0)
    , _Multisampled_DepthBuffer(0)
    , _out_FBO(0)
    , _out_ColorTextureObject(0)
    , _out_DepthTextureObject(0)
{
	

    glGenFramebuffers(1, &_Multisampled_FBO);
    glGenFramebuffers(1, &_out_FBO);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    
    glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
    glGetError();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    
    //QTimer::singleShot(1000, this, SLOT(_checkRendererReady()));
}


View_renderer::~View_renderer(){
	if (_out_ColorTextureObject != 0 and _out_ColorTextureObject != 0)
		_deleteOutTextures();
    if (_Multisampled_ColorBuffer != 0 and _Multisampled_DepthBuffer != 0)
        _deleteMultisampledBuffers();
    //Bind 0, which means render to back buffer, as a result, fb is unbound
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &_Multisampled_FBO);
    glDeleteFramebuffers(1, &_out_FBO);
}


void View_renderer::_deleteMultisampledBuffers(){
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    
    assert(_Multisampled_ColorBuffer != 0 and _Multisampled_DepthBuffer != 0);
    glDeleteRenderbuffers(1, &_Multisampled_ColorBuffer);
    _Multisampled_ColorBuffer = 0;
    glDeleteRenderbuffers(1, &_Multisampled_DepthBuffer);
    _Multisampled_DepthBuffer = 0;
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    

}

void View_renderer::_deleteOutTextures(){
	assert(_out_ColorTextureObject != 0 and _out_DepthTextureObject != 0);
	glDeleteTextures(1, &_out_ColorTextureObject);
    _out_ColorTextureObject = 0;
	glDeleteTextures(1, &_out_DepthTextureObject);
    _out_DepthTextureObject = 0;
}

void View_renderer::_remakeMultisampledBuffers(){
    _deleteMultisampledBuffers();
    _makeMultisampledBuffers();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
}

void View_renderer::_remakeOutTextures(){
	_deleteOutTextures();
	_makeOutTextures();
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
}

void View_renderer::resizeGL(const size_t & w, const size_t &h){
	_width = w; 
	_height = h;
	_remakeMultisampledBuffers();
    _remakeOutTextures();
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
}

void View_renderer::initializeGL(){
    _makeMultisampledBuffers();
    _makeOutTextures();
	View::initializeGL();
}


cv::Mat View_renderer::_saveColorImage(const std::string & fileName){

    // blit frame buffer 
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _Multisampled_FBO);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _out_FBO);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBlitFramebuffer(  0, 
                        0, 
                        _width, 
                        _height, 
                        0, 
                        0, 
                        _width, 
                        _height,
                        GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, 
                        GL_NEAREST
                      );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    cv::Mat img(_height, _width, CV_8UC3);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glBindTexture(GL_TEXTURE_2D, _out_ColorTextureObject);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_BGR, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    img.data );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    if (fileName.size() > 0){
        cv::imwrite(fileName, img);
        //Debug("save " << fileName);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    return img;
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

    // blit frame buffer 
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBindFramebuffer(GL_READ_FRAMEBUFFER, _Multisampled_FBO);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _out_FBO);
    glBlitFramebuffer(  0, 
                        0, 
                        _width, 
                        _height, 
                        0, 
                        0, 
                        _width, 
                        _height,
                        GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, 
                        GL_NEAREST
                      );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    cv::Mat img(_height, _width, CV_8UC1);
    // glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    // glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBindTexture(GL_TEXTURE_2D, _out_DepthTextureObject);
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
    if( fileName.size() > 0 ){
        cv::imwrite(fileName, img);
        //Debug("save " << fileName );
    }

    glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    return img;
}



void View_renderer::_makeMultisampledBuffers(){
    
    
    assert(_Multisampled_ColorBuffer == 0 and _Multisampled_DepthBuffer == 0 and _Multisampled_FBO != 0);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    
    glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);

    int samples;
    char ErrorMessage[1024];
    //We need to find out what the maximum supported samples is
    glGetIntegerv(GL_MAX_SAMPLES_EXT, &samples);
    //----------------------
    //If for example, 16 is returned, then you can attempt to make a FBO with samples=0 to 16
    //0 means no multisample. This is like using glFramebufferRenderbufferEXT instead of glRenderbufferStorageMultisampleEXT
    //You can attempt to make sample from 1 to 16, but some of them might fail
    //Now, let's make a FBO
    assert( samples >= 4);
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    //----------------------
    //Now make a multisample color buffer
    glGenRenderbuffers(1, &_Multisampled_ColorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_ColorBuffer);
    //samples=4, format=GL_RGBA8, width=256, height=256
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_RGBA8, _width, _height);
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    //----------------------
    //Make a depth multisample depth buffer
    //You must give it the same samples as the color RB, same width and height as well
    //else you will either get a GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT or some other error

    glGenRenderbuffers(1, &_Multisampled_DepthBuffer);
    // glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 
    //                         samples, 
    //                         GL_DEPTH_COMPONENT32F, 
    //                         _width, _height, GL_FALSE);

    glBindRenderbuffer(GL_RENDERBUFFER, _Multisampled_DepthBuffer);
    //samples=4, format=GL_DEPTH_COMPONENT24, width=256, height=256
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT32F, _width, _height);
    //----------------------
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    //It's time to attach the RBs to the FBO
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _Multisampled_ColorBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _Multisampled_DepthBuffer);
    //----------------------
    //Make sure FBO status is good
    
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    assert(Utils::glExtCheckFramebufferStatus(ErrorMessage) == 1);

    
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

}


void View_renderer::_makeOutTextures(){

    assert(_out_ColorTextureObject == 0 and _out_DepthTextureObject == 0 and _out_FBO != 0);


    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    glGenTextures(1, &_out_ColorTextureObject);
    glBindTexture(GL_TEXTURE_2D, _out_ColorTextureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        _width, _height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);

    // create a depth texture
    glGenTextures(1, &_out_DepthTextureObject);
    glBindTexture(GL_TEXTURE_2D, _out_DepthTextureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F,
                        _width, _height,
                        0, GL_DEPTH_COMPONENT, GL_FLOAT,
                        NULL);
    



    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glBindFramebuffer(GL_FRAMEBUFFER, _out_FBO);
    // attach color
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _out_ColorTextureObject, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_TEXTURE_2D, _out_DepthTextureObject, 0);


    // Set the list of draw buffers.
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    // check buffer status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error ( "Error! FrameBuffer is not complete" );



    // GLint drawId = 0, readId = 0;
    // glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    // glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);

    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    //glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    

    glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
}




void View_renderer::getVisibleObjects(){
    // color code objects
    size_t numOfInstances = world->getInstances().size();
    std::vector< Lumos::Instance * > worldInstances = world->getInstances();
    // 0 is reserved for empty space
    for (size_t instanceItr = 0; instanceItr < numOfInstances; instanceItr++){
        // get color coded material
        worldInstances[instanceItr]->setPickingColor( Color::toUniqueColor(instanceItr+1) / 255.0f );
        // color3 c3 = Color::toUniqueColor(instanceItr+1);
        // Debug(c3[0] << " " << c3[1] << " " << c3[2] << "#" << Color::toUniqueInt(c3[0], c3[1], c3[2]));
    }

    std::string temp = _shaderId;
    _shaderId = Lumos::Shader::mask_shader_id;
    glBindFramebuffer(GL_FRAMEBUFFER, _out_FBO);
    paintGL();
    _shaderId = temp;

    //GLubyte * pixels = new GLubyte [width*height*4*sizeof(GLuint)];
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
    

    GLint drawId = 0, readId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);
    //glMapBufferRange(_ColorBuffer, 0, GLsizeiptr length​, GLbitfield access​);
    
    cv::Mat img(_height, _width, CV_8UC3);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glBindTexture(GL_TEXTURE_2D, _out_ColorTextureObject);

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_BGR, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    img.data );

    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    cv::imwrite("temp.png", img);


    glBindFramebuffer(GL_FRAMEBUFFER, _Multisampled_FBO);

    //cv::Mat img = _saveColorImage("temp.png");
    //glMapBufferRange(_ColorBuffer, 0, GLsizeiptr length​, GLbitfield access​);
    // glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    // glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());

    // glReadPixels(0, 0, img.cols, img.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, img.data);
    // glGetTextureImage ( GL_TEXTURE_2D,
    //                     0,
    //                     GL_BGR, // GL will convert to this format
    //                     GL_UNSIGNED_BYTE,   // Using this data type per-pixel
    //                     img.data );
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
    
    std::set<size_t> pickedInstanceIndices;
    // for (size_t pixelItr = 0; pixelItr < static_cast<size_t>(_width*_height); pixelItr++){
    //     size_t initPos = pixelItr*3;
    //     cv::Point img.at<uint8_t>(initPos+2)
    //     pickedInstanceIndices.insert(Color::toUniqueInt(img.at<uint8_t>(initPos+2), img.at<uint8_t>(initPos+1), img.at<uchar>(initPos)));
    // }

    for (size_t rowItr = 0; rowItr < static_cast<size_t>(_height); rowItr++){
        for (size_t colItr = 0; colItr < static_cast<size_t>(_width); colItr++){
            cv::Vec3b p = img.at<cv::Vec3b>(rowItr, colItr);
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
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
    
    getVisibleObjects();
    Utils::logOpenGLError( std::string(__PRETTY_FUNCTION__) + ":" + std::to_string(__LINE__) );
    
    // make everythign invisible
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOff();
    }
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
        _saveBitMap(std::string(  OUTPUT_DIR + shaper->getCurFileName() + 
        							  "/" + _camInUse->getId() + 
        							  "/mask_" + ins->getId() + ".png" ));
    }
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

    //unsigned int * pixels = new unsigned int [w*h*sizeof(unsigned int)];
    //QImage image(w, h, QImage::Format_RGBA8888 );
    
    GLError( __PRETTY_FUNCTION__ , __LINE__ );
    paintGL();
    _saveDepthImage(fileName);
}

