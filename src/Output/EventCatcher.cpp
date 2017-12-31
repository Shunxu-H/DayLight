#include "EventCatcher.h"
#include <iostream>

void EventCatcher::catchEvent(const XEvent & xev){

    if(xev.type == Expose && xev.xexpose.count==0) {
        
    }

    else if(xev.type == KeyPress) {

        _keyboard_handle(xev);
    }
    else if (xev.type==ButtonPress) {
        /* tell where the mouse Button was Pressed */
        _button_handle(xev);
    }
    else
      std::cout << "Unrecognized events" << std::endl;

}
