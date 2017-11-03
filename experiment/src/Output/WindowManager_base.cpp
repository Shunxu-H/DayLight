#include "GL_include.h"
#include "WindowManager_base.h"
#include "Extern.h"
WindowManager_base::WindowManager_base( const size_t & w, const size_t & h )
	:_width(w)
	,_height(h)
{


}


void WindowManager_base::positionAllViewsToFitAllInstances(){
    // compute bounding circle
    point3 position;
    float radius;
    Patronus::Shaper::getBoundingSphere(Patronus::Shaper::global_vertices, &position, &radius);

    for( View * v: _views )
        v->fitSphere(position, radius);

}