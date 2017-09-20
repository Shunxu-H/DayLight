
#include <QDebug>
#include <QMouseEvent>
#include <QGLWidget>
#include <cmath>
#include <experimental/filesystem>
//#include "GL_include.h"
#include "View.h"
#include "Utility.h"
#include "Camera.h"
#include "Renderer.h"

#include "Extern.h"


View::View(QWidget *parent, const std::shared_ptr<Patronus::Camera> & cam, const std::string & shaderId )
    : QOpenGLWidget(parent)
    , _VAO( 0 )
    , _shaderId( shaderId )
    , _ColorTextureObject( 0 )
    , _DepthTextureObject( 0 )
    , _isRequestingTexture( 0 )
{
    if ( cam == nullptr )
        _camInUse = Patronus::Camera::pers;

    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(0);
    format.setDepthBufferSize(24);
    format.setSamples(4);
    setFormat(format);


    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);

    QSurfaceFormat fmt;
    fmt.setSamples(8);
    setFormat(fmt);

    //_renderer = new Renderer(this, nullptr, QSize(width(), height()));

    //initializeGL();
    //QOpenGLWidget::setRenderHint(QPainter::Antialiasing);
}


void View::getColorAndDepthTexture(){

    GLuint FBO;

    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    GLint drawFboId = 0, readFboId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

    Utils::logOpenGLError();
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    Utils::logOpenGLError();

    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);


    // create a RGBA color texture

    glGenTextures(1, &_ColorTextureObject);
    glBindTexture(GL_TEXTURE_2D, _ColorTextureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        width(), height(),
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);

    // create a depth texture
    glGenTextures(1, &_DepthTextureObject);
    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                        width(), height(),
                        0, GL_DEPTH_COMPONENT, GL_FLOAT,
                        NULL);



    Utils::logOpenGLError();
    // attach color
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorTextureObject, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,  GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthTextureObject, 0);


    // Set the list of draw buffers.
    Utils::logOpenGLError();

    // check buffer status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error ( "Error! FrameBuffer is not complete" );



    Utils::logOpenGLError();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);


    GLint drawId = 0, readId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);

    Utils::logOpenGLError();

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );
    glClearColor(0,0,0,1);

    Utils::logOpenGLError();
    _camInUse->loadUniforms(width(), height());
    Utils::logOpenGLError();
    shaper->loadAttribsAndUniform();
    Lumos::Material * materialInUse = nullptr;
    for(Lumos::Instance const * i : world->getInstances()){
        i->renderMesh(materialInUse);
    }
    Utils::logOpenGLError();
    //glViewport(0,0,width,height);
    glFlush();
    //glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    Utils::logOpenGLError();


    glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFboId);
    //glDeleteTextures(1, &DepthTextureObject);
    glDeleteFramebuffers(1, &FBO);

    Utils::logOpenGLError();
}

void View::sendTextureRequest(){
    assert(_ColorTextureObject == 0 && _DepthTextureObject == 0);
    _isRequestingTexture = true;
    repaint();
}

void View::getVisibleObjects(){
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
    sendTextureRequest();
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
    for (size_t pixelItr = 0; pixelItr < width*height; pixelItr++){
        size_t initPos = pixelItr*3;
        pickedInstanceIndices.insert(Color::toUniqueInt(pixels[initPos], pixels[initPos+1], pixels[initPos+2]));
    }
    _visibles.clear();
    for (const int & index: pickedInstanceIndices){
        if ( index > 0 )
            _visibles.push_back(worldInstances[index-1]);
    }

    glDeleteTextures(1, &_ColorTextureObject);
    _ColorTextureObject = 0;
}

void View::generateMasks(){
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
        repaint();
        QImage image = grabFramebuffer();
        image.save( std::string( "./" + shaper->getCurFileName() + "/" + _camInUse->getId() + "/mask_" + ins->getId() + ".png" ).c_str() );
    }
    for (Lumos::Instance * ins : world->getInstances())
    {
        ins->turnOn();
    }

    _shaderId = tempShaderId;
}

void View::generateData(){
    std::string parentDir = "./" + shaper->getCurFileName() + "/";
    Utils::cleanAndMkdir(parentDir + _camInUse->getId());


    generateMasks();
    toImageFile_color( parentDir + _camInUse->getId() + "/color.png" );
    toImageFile_depth( parentDir + _camInUse->getId() + "/depth.png");
}




void View::toImageFile_color( const std::string & fileName ){

    repaint();
    if (!grabFramebuffer().save(QString(fileName.c_str())))
        throw std::runtime_error("Can't save image");

}

void View::toImageFile_depth( const std::string & fileName ) {
    assert(_DepthTextureObject != 0);



    glBindTexture(GL_TEXTURE_2D, _DepthTextureObject);
    int w = 0, h = 0;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);

    GLfloat * pixels = new GLfloat [w*h*sizeof(GLfloat)];
    QImage image(w, h, QImage::Format_Grayscale8);
    Utils::logOpenGLError();
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_DEPTH_COMPONENT, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    image.bits() );
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

    if (!image.mirrored().save(fileName.c_str()))
        throw std::runtime_error("Save depth image failed.");

    glDeleteTextures(1, &_DepthTextureObject);
    _DepthTextureObject = 0;

}


void View::loadAttribsAndUniform() const{

}

void View::initializeGL(){
    //qDebug() << context() << " " << global_glContext;
    //context()->setShareContext(global_glContext);

    initializeOpenGLFunctions();
    //renderer->initializeGL();
    _renderer = new Renderer(this, nullptr, QSize(width(), height()) );
    makeCurrent();

    //assert(QOpenGLContext::areSharing(context(), _renderer->context()) );


    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);


    glGenVertexArrays(1, &_VAO);




}

void View::resizeGL(int w, int h){

}


void View::getMouseBeam(const int & mouseX, const int & mouseY, point3 * start, point3 * direction )const{
    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
        ((float)mouseX/(float)width()  - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
        ((float)(height() - mouseY)/(float)height() - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
        -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
        1.0f
    );
    glm::vec4 lRayEnd_NDC(
        ((float)mouseX/(float)width()  - 0.5f) * 2.0f,
        ((float)(height() - mouseY)/(float)height() - 0.5f) * 2.0f,
        0.0,
        1.0f
    );

    // Faster way (just one inverse)
    glm::mat4 M = glm::inverse(_camInUse->getProjectionMatrix( static_cast<float>(width())/static_cast<float>(height()) ) *
                               _camInUse->getPerspectiveMatrix());
    glm::vec4 lRayStart_world = M * lRayStart_NDC;
    lRayStart_world/=lRayStart_world.w;
    glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ;
    lRayEnd_world  /=lRayEnd_world.w;

    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);
    *start = point3(lRayStart_world);
    *direction = lRayDir_world;
}

void View::paintGL(){

    if( gProgram == nullptr )
        return;
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    //shaper->getnCamera(0)->genFrameBuffer(1080, 720);
    gProgram->use();
    gProgram->enableShadingPipe(_shaderId);

    loadAttribsAndUniform();

    glBindVertexArray(_VAO);
    if(_isRequestingTexture){
        _isRequestingTexture = false;
        getColorAndDepthTexture( );
    }

    _camInUse->loadUniforms(width(), height());
    shaper->loadAttribsAndUniform();
    Lumos::Material * materialInUse = nullptr;
    for(Lumos::Instance const * i : world->getInstances()){
        if (i->isOn())
            i->renderMesh(materialInUse);
    }

    gProgram->disableShadingPipe(_shaderId);
}


void View::fitSphere(const point3 & position, const float & radius){
    float z_y = radius / sin(_camInUse->getFovy()/2.0f),
          z_x = radius / sin( static_cast<float>(width()) /
                               static_cast<float>(height()) /
                               _camInUse->getFovy()/2.0f);
    _camInUse->setTranslate(position + point3(0.0f, 0.0f, std::fmax(z_y, z_x)));

}


void View::mousePressEvent(QMouseEvent *event){
    switch(event->button()){
    case Qt::LeftButton:
    {
        glm::vec3 out_origin, out_direction;
        getMouseBeam(event->pos().x(), event->pos().y(), &out_origin, &out_direction);
        glm::vec3 out_end = out_origin + out_direction*_camInUse->getFarClipDist();
        btVector3 start(out_origin.x, out_origin.y, out_origin.z ), end(out_end.x, out_end.y, out_end.z);

        Lumos::Instance * selected = world->selectWithBean( start, end );
        if (selected){
            _camInUse->setAtGlobal( (selected->getMeshPtr()->getMaxPos() +
                                   selected->getMeshPtr()->getMinPos()) / 2.0f ) ;
            selectedInstance = selected;
            //qDebug() << selected->getMeshPtr()->getMaxPos().x << selected->getMeshPtr()->getMaxPos().y << selected->getMeshPtr()->getMaxPos().z << "\n"
            //         << selected->getMeshPtr()->getMinPos().x << selected->getMeshPtr()->getMinPos().y << selected->getMeshPtr()->getMinPos().z << "\n"
            //         ;
        }
        else
            selectedInstance = nullptr;

    }
        break;
    case Qt::MiddleButton:
    {
        /*
        float rgba[4]
               , depth_z = 0.0f;
        glReadPixels(event->pos().x(), height() - event->pos().y(), 1, 1, GL_RGBA, GL_FLOAT, rgba);
        std::cout << rgba[0] << " " << rgba[1] << " " << rgba[2] << " " << rgba[3] <<std::endl;;

        toImageFile_color( "color.png");
        toImageFile_depth( "depth.png");

*/
        break;
    }
    case Qt::RightButton:

        break;
    }
    _prevMousePos = event->pos();
    winMan->updateAllViews();
}



void View::mouseMoveEvent(QMouseEvent *event){
    //qDebug() << event->pos();
    QPoint diff = _prevMousePos - event->pos();

    switch(progConfig.opMode){


    case NAVIGATING:
        switch(event->buttons()){
        case Qt::LeftButton:
            _camInUse->rotateAroundFocus(static_cast<float>(diff.x())/100.0f,
                                      static_cast<float>(diff.y())/100.0f
                                      );
            //_camInUse->setAtGlobal(point3(0, 0, 0));
            break;
        case Qt::MiddleButton:
            _camInUse->panAndPadestal(static_cast<float>(diff.x())/100.0f,
                                      -static_cast<float>(diff.y())/100.0f
                                      );


            break;
        case Qt::RightButton:

            break;
        }
        break;

    }
    _prevMousePos = event->pos();

    winMan->updateAllViews();
}

void View::mouseReleaseEvent(QMouseEvent *event){

}

void View::wheelEvent ( QWheelEvent * event ){
    //qDebug() << _camInUse->getPos().x << " " << _camInUse->getPos().y << " " << _camInUse->getPos().z << " " ;
    bool isUp = event->angleDelta().y() > 0? true : false;
    if ( isUp )
        _camInUse->moveForward(0.1f);
    else
        _camInUse->moveForward(-0.1f);

    winMan->updateAllViews();
}
