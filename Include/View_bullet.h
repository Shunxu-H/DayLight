#ifndef VIEW_BULLET_H
#define VIEW_BULLET_H

#include "View.h"

class View_bullet: public View{
public:
    View_bullet(
            QWidget *parent = nullptr,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr )
         );
    virtual ~View_bullet(){}

protected:
    //virtual void initializeGL() override ;
    //virtual void resizeGL(int w, int h) override ;
    virtual void paintGL() override ;


    /**
     * @brief event filter fr hoverEnterm hoverLeave and hoverMove
     * @param event
     * @return
     */
    virtual bool event(QEvent *event) override ;
    void hoverEnter(QHoverEvent *event) ;
    void hoverLeave(QHoverEvent *event) ;
    void hoverMove(QHoverEvent *event) ;
private:


};

#endif // VIEW_BULLET_H
