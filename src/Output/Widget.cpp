#include <iostream>
#include "Widget.h"

/**
 * Static functions
 */




Widget::Widget( const std::string & title,
                const size_t & x,
                const size_t & y,
                const size_t & w,
                const size_t & h
              )
  : _title(title)
  , _x(x)
  , _y(y)
  , _width(w)
  , _height(h)
{

}

bool Widget::isClick(const size_t & x, const size_t & y)const{
    return  (_x <= x && x <= _x + _width ) &&
            (_y <= y && y <= _y + _height);
}

void Widget::addChild(Widget* w){
    _children.push_back(w);
}

void Widget::_catchEvent(const XEvent & xev){


    for (Widget * w : _children){
        if(xev.type==ButtonPress && w->isClick(xev.xbutton.x, xev.xbutton.y)){
            XEvent curEv(xev);
            curEv.xbutton.x -= w->_x;
            curEv.xbutton.y -= w->_y;
            w->_catchEvent(curEv);
        }
        else
          w->_catchEvent(xev);
    }

    if(xev.type == Expose
        && xev.xexpose.count==0) { // only render immediate exposures
        _expose();
    }
    else if(xev.type == KeyPress) {
        _keyboard_handle(xev);
    }
    else if (xev.type==ButtonPress) {
        _button_handle(xev);
    }
    else
      std::cout << "Unrecognized events" << std::endl;


}
