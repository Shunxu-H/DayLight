#include "View.h"


View::View(
      const std::string & title ,
      const size_t & x ,
      const size_t & y ,
      const size_t & w ,
      const size_t & h
    )
    : Widget(title, x, y, w, h)
    , _isExposed(false)
{

}



bool View::_expose()
{
    if(_isExposed)
    {
        paintGL();
    }
    else
    {
        _isExposed = true;
        initializeGL();
        paintGL();
    }
    return true;
}
