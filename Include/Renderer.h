#ifndef RENDERER_H
#define RENDERER_H

#include "OpenGlOffscreenSurface.h"

namespace Patronus {
    class Camera;
}

namespace Lumos {
    class Instance;
}

class View;

class Renderer
    : public OpenGlOffscreenSurface
{
public:
    explicit Renderer(
            View *  connectedScreen = nullptr,
            QScreen* targetScreen = nullptr,
            const QSize& size = QSize (1, 1) );

    virtual ~Renderer() override;


    void toImageFile_color( const std::string & fileName );
    void toImageFile_depth( const std::string & fileName );
    void getVisibleObjects();
    void generateMasks();
    void generateData();
    void sendTextureRequest();
    void loadAttribsAndUniform() const;

protected:
    virtual void initializeGL() override;

    virtual void resizeGL(
            int width,
            int height) override;

    virtual void paintGL() override;

private:
    Patronus::Camera * _camInUse;
    GLuint _VAO;
    View * _connectedScreen;
    std::string _shaderId;
    GLuint _ColorTextureObject;
    GLuint _DepthTextureObject;
    std::vector< Lumos::Instance * > _visibles;
    bool _isRequestingTexture;
};

#endif // RENDERER_H
