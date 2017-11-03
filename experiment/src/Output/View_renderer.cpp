#include "View_renderer.h"
#include "Extern.h"
#include "Utility.h"


View_renderer::View_renderer(
		const size_t & w, 
		const size_t & h, 
		const std::shared_ptr<Patronus::Camera> & cam, 
		const std::string & shaderId )
    : View(w, h, cam, shaderId)
    , _FBO(0)
    , _ColorTextureObject( 0 )
    , _DepthTextureObject( 0 )
    , _ColorBuffer( 0 )
    , _DepthBuffer( 0 )
{
	
    glGenFramebuffersEXT(1, &_FBO);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _FBO);
    Utils::logOpenGLError();
    //QTimer::singleShot(1000, this, SLOT(_checkRendererReady()));
}


View_renderer::~View_renderer(){
	if (_ColorTextureObject != 0 and _DepthTextureObject != 0)
		_deleteTextures();
    if (_ColorBuffer != 0 and _DepthBuffer != 0)
        _deleteBuffers();
    //Bind 0, which means render to back buffer, as a result, fb is unbound
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    glDeleteFramebuffersEXT(1, &_FBO);
}

void View_renderer::_deleteBuffers(){

    assert(_ColorBuffer != 0 and _DepthBuffer != 0);
    glDeleteRenderbuffersEXT(1, &_ColorBuffer);
    _ColorBuffer = 0;
    glDeleteRenderbuffersEXT(1, &_DepthBuffer);
    _DepthBuffer = 0;

}

void View_renderer::_deleteTextures(){
	assert(_ColorTextureObject != 0 and _DepthTextureObject != 0);
	glDeleteTextures(1, &_ColorTextureObject);
    _ColorTextureObject = 0;
	glDeleteTextures(1, &_DepthTextureObject);
    _DepthTextureObject = 0;
}

void View_renderer::_remakeBuffers(){
    _deleteBuffers();
    _getColorAndDepthBuffers();
}

void View_renderer::_remakeTextureObjects(){
	_deleteTextures();
	_getColorAndDepthTexture();
}

void View_renderer::resizeGL(const size_t & w, const size_t &h){
	_width = w; 
	_height = h;
	_remakeTextureObjects();
}

void View_renderer::initializeGL(){
	_getColorAndDepthTexture();
	View::initializeGL();
}


void View_renderer::_saveColorTexture(const std::string & fileName){
    cv::Mat img(_height, _width, CV_8UC3);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_BGR, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    img.data );

    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    cv::imwrite(fileName, img);
    Debug("save " << fileName << std::endl);
}

void View_renderer::_saveDepthTexture(const std::string & fileName){
    cv::Mat img(_height, _width, CV_8UC1);
    glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3)?1:4);
    glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
	glGetTexImage ( GL_TEXTURE_2D,
	                0,
	                GL_DEPTH_COMPONENT, // GL will convert to this format
	                GL_UNSIGNED_BYTE,   // Using this data type per-pixel
	                img.data );

    cv::Mat flipped(img);
    cv::flip(img, flipped, 0);
    cv::imwrite(fileName, img);
    Debug("save " << fileName << std::endl);
}

void View_renderer::_getColorAndDepthBuffers(){
    assert(_ColorTextureObject == 0 and _DepthTextureObject == 0 and _FBO != 0);

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
    //----------------------
    //Now make a multisample color buffer
    glGenRenderbuffersEXT(1, &_ColorBuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _ColorBuffer);
    //samples=4, format=GL_RGBA8, width=256, height=256
    glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, 4, GL_RGBA8, _width, _height);
    //----------------------
    //Make a depth multisample depth buffer
    //You must give it the same samples as the color RB, same width and height as well
    //else you will either get a GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT or some other error
    glGenRenderbuffersEXT(1, &_DepthBuffer);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _DepthBuffer);
    //samples=4, format=GL_DEPTH_COMPONENT24, width=256, height=256
    glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER_EXT, 4, GL_DEPTH_COMPONENT24, _width, _height);
    //----------------------
    //It's time to attach the RBs to the FBO
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_RENDERBUFFER_EXT, _ColorBuffer);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _DepthBuffer);
    //----------------------
    //Make sure FBO status is good
    assert(Utils::glExtCheckFramebufferStatus(ErrorMessage) == 1);
}


void View_renderer::_getColorAndDepthTexture(){
	assert(_ColorTextureObject == 0 and _DepthTextureObject == 0 and _FBO != 0);


    Utils::logOpenGLError();
    

    glGenTextures(1, &_ColorTextureObject);
    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        _width, _height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);

    // create a depth texture
    glGenTextures(1, &_DepthTextureObject);
    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32,
                        _width, _height,
                        0, GL_DEPTH_COMPONENT, GL_FLOAT,
                        NULL);
    




    Utils::logOpenGLError();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _FBO);
    // attach color
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorTextureObject, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,  GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthTextureObject, 0);


    // Set the list of draw buffers.
    Utils::logOpenGLError();

    // check buffer status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error ( "Error! FrameBuffer is not complete" );





    GLint drawId = 0, readId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);

    Utils::logOpenGLError();

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    //glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    Utils::logOpenGLError();


}




void View_renderer::getVisibleObjects(){
    // color code objects
    size_t numOfInstances = world->getInstances().size();
    std::vector< Lumos::Instance * > worldInstances = world->getInstances();
    // 0 is reserved for empty space
    for (size_t instanceItr = 0; instanceItr < numOfInstances; instanceItr++){
        // get color coded material
        worldInstances[instanceItr]->setPickingColor( Color::toUniqueColor(instanceItr+1) / 255.0f );
    }

    std::string temp = _shaderId;
    _shaderId = Lumos::Shader::mask_shader_id;
    paintGL();
    _shaderId = temp;

    GLint width = 0, height = 0;

    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    //GLubyte * pixels = new GLubyte [width*height*4*sizeof(GLuint)];
    GLubyte * pixels = new GLubyte [width*height*3*sizeof(GLubyte)];

    Utils::logOpenGLError();
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_RGB, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    pixels );

    std::set<int> pickedInstanceIndices;
    for (size_t pixelItr = 0; pixelItr < static_cast<size_t>(width*height); pixelItr++){
        size_t initPos = pixelItr*3;
        pickedInstanceIndices.insert(Color::toUniqueInt(pixels[initPos], pixels[initPos+1], pixels[initPos+2]));
    }
    _visibles.clear();
    for (const int & index: pickedInstanceIndices){
        if ( index > 0 )
            _visibles.push_back(worldInstances[index-1]);
    }


}

void View_renderer::generateMasks(){
    getVisibleObjects();
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
        _saveColorTexture(std::string( "./" + shaper->getCurFileName() + 
        							  "/" + _camInUse->getId() + 
        							  "/mask_" + ins->getId() + ".png" ));
    }
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOn();
    }

    _shaderId = tempShaderId;
}

void View_renderer::generateData(){
    std::string parentDir = "./" + shaper->getCurFileName() + "/";
    Utils::cleanAndMkdir(parentDir + _camInUse->getId());


    generateMasks();
    toImageFile_color( parentDir + _camInUse->getId() + "/color.png" );
    toImageFile_depth( parentDir + _camInUse->getId() + "/depth.png");
}




void View_renderer::toImageFile_color( const std::string & fileName ){

    paintGL();
    _saveColorTexture(fileName);

}

void View_renderer::toImageFile_depth( const std::string & fileName ) {
    assert(_DepthTextureObject != 0);



    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
    int w = 0, h = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    //unsigned int * pixels = new unsigned int [w*h*sizeof(unsigned int)];
    //QImage image(w, h, QImage::Format_RGBA8888 );
    Utils::logOpenGLError();
    paintGL();
    _saveDepthTexture(fileName);
    // glGetTexImage ( GL_TEXTURE_2D,
    //                 0,
    //                 GL_DEPTH_COMPONENT, // GL will convert to this format
    //                 GL_FLOAT,   // Using this data type per-pixel
    //                 image.bits() );

    // save a binary file
    //fwrite(image.bits(), sizeof(GLfloat), w*h, file);
/*
    std::ofstream toFile(fileName +  ".txt");
    for (int i = 0; i < width() * height(); i++)
        toFile << std::to_string(pixels[i]) << " ";

    toFile.close();
*/
/*
    float max = 0, min = std::numeric_limits<float>::max();
    for (size_t i = 0; i < w*h ; i++){
        min = std::min(pixels[i], min);
        max = std::max(pixels[i], max );
    }

    for (size_t i = 0; i < w*h ; i++)
        pixels[i] = (pixels[i] - min) / (max - min);

    memccpy(image.bits(), pixels, w*h*sizeof(GLfloat), w*h*sizeof(GLfloat));
*/

    // if (!image.mirrored().save(fileName.c_str()))
    //     throw std::runtime_error("Save depth image failed.");

}

