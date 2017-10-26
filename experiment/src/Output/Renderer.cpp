#include <QPainter>
#include "Renderer.h"
#include "GL_include.h"
#include "Camera.h"
#include "Utility.h"
#include "View.h"

#include "Extern.h"

Renderer::Renderer(
        View *  connectedScreen,
        QScreen*     targetScreen,
        const QSize& size)
    : OpenGlOffscreenSurface(targetScreen, size, connectedScreen)
    , _camInUse( Patronus::Camera::pers )
    , _VAO( 0 )
    , _connectedScreen( connectedScreen )
{

    //initializeOpenGLFunctions();


}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &_VAO);
}


void Renderer::toImageFile_color( const std::string & fileName ){

    render();
    if (!grabFramebuffer().save(QString(fileName.c_str())))
        throw std::runtime_error("Can't save image");

}

void Renderer::toImageFile_depth( const std::string & fileName ) {
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


    if (!image.mirrored().save(fileName.c_str()))
        throw std::runtime_error("Save depth image failed.");

    glDeleteTextures(1, &_DepthTextureObject);
    _DepthTextureObject = 0;

}



void Renderer::initializeGL() {
    /*
    makeCurrent();
    context()->setShareContext(_connectedScreen->context());
    context()->create();
     *///resize(curSize);]
    makeCurrent();
    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);


    glGenVertexArrays(1, &_VAO);


    GLboolean hasDepth = false;
    glGetBooleanv(GL_DEPTH_TEST, &hasDepth );
}


void Renderer::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);

}


void Renderer::paintGL()
{

    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glViewport(0, 0, size().width(), size().height());
    GLboolean hasDepth = false;
    glGetBooleanv(GL_DEPTH_TEST, &hasDepth );

    gProgram->use();

    Utils::logOpenGLError();
    gProgram->enableShadingPipe(Lumos::Shader::default_mesh_shader_id);

    Utils::logOpenGLError();
    glBindVertexArray(_VAO);

    Utils::logOpenGLError();
    _camInUse->loadUniforms(bufferSize().width(), bufferSize().height());
    point3 test = _camInUse->getTranslate();

    Utils::logOpenGLError();
    shaper->loadAttribsAndUniform();

    Utils::logOpenGLError();
    Lumos::Material * materialInUse = nullptr;
    for(Lumos::Instance const * i : world->getInstances()){
        i->renderMesh(materialInUse);
    }
    Utils::logOpenGLError();

    gProgram->disableShadingPipe(Lumos::Shader::default_mesh_shader_id);
}
