#include <QPainter>
#include "Renderer.h"
#include "GL_include.h"
#include "Camera.h"
#include "Utility.h"

#include "Extern.h"

Renderer::Renderer(
        QScreen*     targetScreen,
        const QSize& size,
        QOpenGLContext * context)
    : OpenGlOffscreenSurface(targetScreen, size, context)
    , _camInUse( Patronus::Camera::pers )
    , _VAO( 0 )
{



}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &_VAO);
}


void Renderer::initializeGL() {
    makeCurrent();
    global_glContext = context();
    glEnable(GL_DEPTH_TEST);

    // draw line and polygon together
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1, 0);

    // antialiasing
    glEnable(GL_MULTISAMPLE);


    glGenVertexArrays(1, &_VAO);
}


void Renderer::resizeGL(int width, int height) {
    glViewport(0, 0, width, height);

}


void Renderer::paintGL()
{

    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    qDebug() << context()->areSharing(context(), global_glContext);
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
    glViewport(0, 0, size().width(), size().height());

    gProgram->disableShadingPipe(Lumos::Shader::default_mesh_shader_id);
}
