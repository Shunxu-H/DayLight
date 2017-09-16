#include <QPoint>
#include <experimental/filesystem>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "GL_include.h"
#include "Utility.h"

#include "Camera.h"
#include "Extern.h"
using namespace Patronus ;
using namespace std::experimental;
Camera * Camera::pers = new Camera{};



void Camera::loadCamerasFromDir( const std::string & dir ){
    if ( shaper == nullptr )
        throw std::runtime_error( "Shaper object is uninitialized!");
    filesystem::path p ( dir );
    if ( p.empty() )
       throw std::runtime_error( " invalid directory in Camera::loadCamerasFromDir()");

    std::string camNameFile = std::string( p ) + "/room_camera_name.txt";
    std::string camStatFile = std::string( p ) + "/room_camera.txt";

    std::ifstream f (camNameFile.c_str());
    if ( !f.is_open() )
        throw std::runtime_error( "Camera name file does not exist! ");
    std::stringstream ss;

    // load camera names
    std::string fileNameStr;
    ss << f.rdbuf();
    f.close();
    std::deque< std::string > camNames = Utils::mystrtok(ss.str(), "\n ");


    // iterate through camera stat file
    std::string line;
    f.open(camStatFile.c_str());
    if ( !f.is_open() )
        throw std::runtime_error( "Camera stat file does not exist! ");
    while(std::getline(f, line)){
        std::deque< std::string > tokens = Utils::mystrtok(line, " ");
        Camera * newCamera = new Camera();
        newCamera->setTranslate (point3(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2])));
        newCamera->setAt        (point3(std::stof(tokens[4]), std::stof(tokens[5]), std::stof(tokens[6])));
        newCamera->setUp        (point3(std::stof(tokens[8]), std::stof(tokens[9]), std::stof(tokens[10])));
        newCamera->setId(camNames[0]);
        camNames.pop_front();
        shaper->addCamera( newCamera );
    }


 }



Camera::Camera(const CameraType & type,
               const float      & fov,
               const float      & near,
               const float      & far,
               const point3     & pos,
               const glm::vec3  & up,
               const glm::vec3  & at)
    :Transformable( pos )
    ,_type( type )
    ,_fov( fov )
    ,_near( near )
    ,_far( far )
    ,_up( up )
    ,_at( at )
    ,_FBO( 0 )
    ,_ColorBufferObject( 0 )
    ,_DepthBufferObject( 0 )
    ,_ColorTexObj( 0 )
    ,_DepthTexObj( 0 )
    ,_bufferHeight( 0 )
    ,_bufferWidth( 0 )
{

}

Camera::~Camera(){

    if (_FBO != 0){
        glDeleteTextures(1, &_ColorBufferObject);
        glDeleteTextures(1, &_DepthBufferObject);
        _DepthBufferObject = 0;
        glDeleteFramebuffers(1, &_FBO);
        _FBO = 0;
    }
}



void Camera::loadUniforms( const unsigned int & width, const unsigned int & height ) const{

    GLuint uniformId;
    if (gProgram->hasUniform("camera"))
        gProgram->setUniform("camera", getPerspectiveMatrix());
    if (gProgram->hasUniform("cameraPosition"))
        gProgram->setUniform("cameraPosition", getTranslate() );
    if (gProgram->hasUniform("projection"))
        gProgram->setUniform("projection", getProjectionMatrix(static_cast<float>(width)/static_cast<float>(height)));
    if (gProgram->hasUniform("ModelViewProjectionMatrix"))
        gProgram->setUniform("ModelViewProjectionMatrix",
                             getProjectionMatrix( static_cast<float>(width)/static_cast<float>(height) )*
                             getPerspectiveMatrix()*
                             getModelMatrix());


}

void Camera::genFrameBuffer( const unsigned int & width, const unsigned int & height ){
    // check if we already have a frame buffer
    if (_FBO != 0)
        return;

    _bufferHeight = height;
    _bufferWidth = width;

    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    GLint drawFboId = 0, readFboId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

    Utils::logOpenGLError();
    glGenFramebuffers(1, &_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
    Utils::logOpenGLError();

    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);

    // create a RGBA color texture

    glGenTextures(1, &_ColorBufferObject);
    glBindTexture(GL_TEXTURE_2D, _ColorBufferObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        width, height,
                        0, GL_RGBA, GL_UNSIGNED_BYTE,
                        NULL);

    // create a depth texture
    glGenTextures(1, &_DepthBufferObject);
    glBindTexture(GL_TEXTURE_2D, _DepthBufferObject);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                        width, height,
                        0, GL_DEPTH_COMPONENT, GL_FLOAT,
                        NULL);



    Utils::logOpenGLError();
    // attach color
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _ColorBufferObject, 0);

    Utils::logOpenGLError();
    glFramebufferTexture2D(GL_FRAMEBUFFER,  GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _DepthBufferObject, 0);


    // Set the list of draw buffers.
    Utils::logOpenGLError();

    // check buffer status
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error ( "Error! FrameBuffer is not complete" );


    Utils::logOpenGLError();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFboId);

    Utils::logOpenGLError();
}


void Camera::render(const unsigned int & width, const unsigned int & height )const{

    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.

    GLint drawFboId = 0, readFboId = 0;
    Utils::logOpenGLError();
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

    Utils::logOpenGLError();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _FBO);

    Utils::printFramebufferInfo(GL_DRAW_FRAMEBUFFER, _FBO);
    Utils::printFramebufferInfo(GL_READ_FRAMEBUFFER, _FBO);

    GLint drawId = 0, readId = 0;
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);



    Utils::logOpenGLError();


    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT  );
    glClearColor(0,0,0,1);

    Utils::logOpenGLError();
    loadUniforms(width, height);
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

    glBindFramebuffer(GL_READ_FRAMEBUFFER, _FBO);
    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawId);
    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readId);

    GLubyte * pixels = new GLubyte [height*width*4*sizeof(GLubyte)];
    size_t size = sizeof(GLubyte);

    glBindTexture(GL_TEXTURE_2D, _ColorBufferObject);
    //glReadBuffer(GL_COLOR_ATTACHMENT0);


    Utils::logOpenGLError();
    glGetTexImage ( GL_TEXTURE_2D,
                    0,
                    GL_RGBA, // GL will convert to this format
                    GL_UNSIGNED_BYTE,   // Using this data type per-pixel
                    pixels );
    //glGetTextureImage ( _ColorBufferObject, 0, GL_RGBA, GL_UNSIGNED_BYTE, height*width*4*sizeof(GLubyte), pixels);
    Utils::logOpenGLError();
    // save the image
    QImage image (width, height, QImage::Format_RGB32);

    for ( size_t rowPtr = 0; rowPtr < height; rowPtr++ ){
        for ( size_t colPtr = 0; colPtr < width; colPtr++ ){
            int pos = (rowPtr*width + colPtr)*4;
            int r = pixels[pos];
            int g = pixels[pos + 1];
            int b = pixels[pos + 2];

            image.setPixelColor(QPoint(colPtr, rowPtr),
                                QColor( r, g, b));
        }

    }
    /*
    for (int y = 0; y < image.height(); y++)
    {
        memcpy(image.scanLine(y), &(pixels[y*width]), image.bytesPerLine());
    }
    */
    image.save("temp.jpg");

    Utils::logOpenGLError();
    delete[] pixels;

    glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, drawFboId);
}


void Camera::moveForward( const float & sensitivity ){
    point3 temp = _translate + _at;
    _translate += _at*sensitivity;
    setAtGlobal(temp);
}




void Camera::panAndPadestal( const float & x_axis, const float & y_axis ){
    glm::vec3 right = glm::normalize(glm::cross(_at, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _at));
    _translate += (right*x_axis + up*y_axis);
}


void Camera::rotateAroundFocus( const float & x_axis, const float & y_axis){
    glm::vec3 right = glm::normalize(glm::cross(_at, _up));
    glm::vec3 up = glm::normalize(glm::cross(right, _at));
    glm::mat4 m(1);
    m = glm::rotate(m, y_axis, right);
    m = glm::rotate(m, x_axis, up);
    glm::vec4 newMinusA = m * glm::vec4(-_at, 1.0);
    setTranslatev4(getTranslatev4()+point4(_at, 1.0)+newMinusA);
    _at = -point3(newMinusA);
    //_up = glm::normalize(glm::cross(right, _at));

}

glm::mat4 Camera::getPerspectiveMatrix()const{

    return glm::lookAt	(  _translate, // eye
                           _translate + _at,
                           _up);

}

glm::mat4 Camera::getProjectionMatrix(const float & aspect_ratio )const {
    return glm::perspective	( _fov, aspect_ratio, _near, _far);
}

