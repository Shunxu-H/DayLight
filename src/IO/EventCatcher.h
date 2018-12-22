#pragma once 

#include  <X11/Xlib.h>


namespace Daylight::IO{

class EventCatcher{

public:
  void catchEvent(const XEvent & event);
protected:
  virtual void _expose()=0;
  virtual void _keyboard_handle(const XEvent & xev)=0;
  virtual void _button_handle(const XEvent & xev)=0;
private:

};

}
