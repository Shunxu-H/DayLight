#include <QPoint>
#include <experimental/filesystem>
#include <fstream>
#include <sstream>
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
    :Transformable( pos ),
     _type( type ), _fov( fov ), _near( near ), _far( far ), _up( up ), _at( at )
{

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

void Camera::render(const unsigned int & width, const unsigned int & height )const{
    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
    GLuint FramebufferName = 0;
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);



    // The texture we're going to render to
    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, renderedTexture);

    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // The depth buffer
    GLuint depthrenderbuffer;
    glGenRenderbuffers(1, &depthrenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);

    Utils::logOpenGLError();
    // Set "renderedTexture" as our colour attachement #0
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);
    Utils::logOpenGLError();

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

    // Always check that our framebuffer is ok
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error(" Buffer creation failed ");



    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    Utils::logOpenGLError();


    loadUniforms(width, height);
    Lumos::Material * materialInUse = nullptr;
    for(Lumos::Instance const * i : world->getInstances()){
        i->renderMesh(materialInUse);
    }

    glViewport(0,0,width,height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
    GLubyte * pixels = new GLubyte [height*width*4];
    size_t size = sizeof(GLubyte);
    glGetTexImage (GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    Utils::logOpenGLError();

    // save the image
    QImage image (width, height, QImage::Format_RGB32);

    for ( size_t rowPtr = 0; rowPtr < height; rowPtr++ ){
        for ( size_t colPtr = 0; colPtr < width; colPtr++ ){
            int pos = (rowPtr*width + colPtr)*4;
            int r = pixels[pos];
            int g = pixels[pos + 1];
            int b = pixels[pos + 2];
            int a = pixels[pos + 3];

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

    delete[] pixels;
    glDeleteRenderbuffers(1, &depthrenderbuffer);
    glDeleteTextures(1, &renderedTexture);
    glDeleteFramebuffers(1, &FramebufferName);
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

