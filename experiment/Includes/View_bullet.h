#ifndef VIEW_BULLET_H
#define VIEW_BULLET_H

#include "View.h"
#include "LinearMath/btIDebugDraw.h"

class View_bullet: public View, public btIDebugDraw{
public:
    View_bullet(
            QWidget *parent = nullptr,
            const std::shared_ptr< Patronus::Camera > & cam = std::shared_ptr<Patronus::Camera>( nullptr )
         );
    virtual ~View_bullet(){}


    virtual void   drawLine(const btVector3& from,const btVector3& to,const btVector3& color);

    virtual void   drawContactPoint(const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color);

    virtual void   reportErrorWarning(const char* warningString);

    virtual void   draw3dText(const btVector3& location,const char* textString);

    virtual void   setDebugMode(int debugMode);

    virtual int getDebugMode() const { return m_debugMode;}

protected:
    //virtual void initializeGL() override ;
    virtual void resizeGL(int w, int h) override ;
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
    int m_debugMode;

};

#endif // VIEW_BULLET_H
