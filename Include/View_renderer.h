#ifndef VIEW_RENDERER_H
#define VIEW_RENDERER_H

#include "View.h"

class View_renderer : public View{
public:
    View_renderer(
            QWidget *parent = nullptr,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr )
         );

protected:
    virtual void paintGL() override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent ( QWheelEvent * event ) override;


};

#endif // VIEW_RENDERER_H
