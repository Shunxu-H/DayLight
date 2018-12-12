#ifndef CURSOREVENT_H
    #define CURSOREVENT_H

#include <cstddef>

enum CUROSR_EVENT_TYPE{
    SCROLL, 
    PRESS,
    RELEASE,
    ENTER, 
    LEAVE, EVENT
}; 

enum CURSOR_BUTTON{
    LEFT, 
    RIGHT, 
    WHEEL, 
}; 

struct ClickData {
    size_t x; 
    size_t y; 
    inline ClickData(const size_t & _x, const size_t & _y) : x(_x), y(_y){}
}; 

union CursorEventData {
    float forScroll; 
    ClickData forClick; 
};

struct CursorEvent{
    CUROSR_EVENT_TYPE eventType; 
    CURSOR_BUTTON button; 
    CursorEventData data; 
    CursorEvent(const CursorEvent & event) = default; 
    inline CursorEvent(const CUROSR_EVENT_TYPE & _eventType, const CURSOR_BUTTON & _button, const CursorEventData & _data)
        :eventType(_eventType), button(_button), data(_data){}
}; 






#endif