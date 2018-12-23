#include <iostream>
#include "Widget.h"

/**
 * Static functions
 */

using namespace Daylight::IO; 


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

Widget::~Widget(){
    for(Widget *& w: _children)
        delete w;
}

bool Widget::isClick(const size_t & x, const size_t & y)const{
    return  (_x <= x && x <= _x + _width ) &&
            (_y <= y && y <= _y + _height);
}

void Widget::addChild(Widget* w){
    _children.push_back(w);
}


void Widget::_internal_keyboard_handle(const KeyboardEvent & event){
    if(_keyboard_handle(event))
    {
        for (Widget * w : _children){
            w->_internal_keyboard_handle(event);
        }
    }
}

void Widget::_internal_cursor_handle(const CursorEvent & event){
    if(_cursor_handle(event))
    {
        for (Widget * w : _children)
        {
            if(event.isPressEvent() && w->isClick(event.loc.x, event.loc.y)){
                CursorEvent curEv(event);
                curEv.loc.x -= w->_x;
                curEv.loc.y -= w->_y;
                w->_internal_cursor_handle(curEv);
            }
            else if (event.isWheelingEvent())
            {
                w->_internal_cursor_handle(event);
            }
        }
    }
}

void Widget::_internal_expose_handle(){
    if(_expose()){
        for (Widget * w : _children){
            w->_internal_expose_handle();
        }
    }
}
