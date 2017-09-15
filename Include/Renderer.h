#ifndef RENDERER_H
#define RENDERER_H

#include "OpenGlOffscreenSurface.h"

namespace Patronus {
    class Camera;
}

class Renderer
    : public OpenGlOffscreenSurface
{
public:
    explicit Renderer(
            QScreen* targetScreen = nullptr,
            const QSize& size = QSize (1, 1),
            QOpenGLContext * context = nullptr );

    virtual ~Renderer() override;

protected:
    virtual void initializeGL() override;

    virtual void resizeGL(
            int width,
            int height) override;

    virtual void paintGL() override;

private:
    Patronus::Camera * _camInUse;
    GLuint _VAO;
};

#endif // RENDERER_H
