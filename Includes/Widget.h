#ifndef WIDGET_H
  #define WIDGET_H

#include <vector>
#include <string>
#include "EventCatcher.h"

class Widget {
public:

  Widget( const std::string & title ="",
          const size_t & x = 0,
          const size_t & y = 0,
          const size_t & w = 500,
          const size_t & h = 500
        );
  /**
  * SETTERS AND GETTERS
  */
  inline std::string getTitle() const {return _title;}
  inline size_t getX() const {return _x;}
  inline size_t getY() const {return _y;}
  inline size_t getWidth() const {return _width;}
  inline size_t getHeight() const {return _height;}

  inline void setTitle(const std::string & t) { _title = t;}
  inline void setX(const size_t & x) { _x = x;}
  inline void setY(const size_t & y) { _y = y;}
  inline void setWidth(const size_t & w) { _width = w;}
  inline void setHeight(const size_t & h) { _height = h;}

  /**
   * [isClick see if a widget is clicked]
   * @param  x [clicking position x in parent widget]
   * @param  y [clicking position y in parent widget]
   * @return   [description]
   */
  bool isClick(const size_t & x, const size_t & y) const;
  void addChild(Widget* w);
protected:
  virtual void _catchEvent(const XEvent & xev);
  virtual void _expose()=0;
  virtual void _keyboard_handle(const XEvent & xev)=0;
  virtual void _button_handle(const XEvent & xev)=0;
  std::string _title;
  size_t _x, _y;
  size_t _width, _height;
  std::vector<Widget * > _children;
private:

};



#endif
