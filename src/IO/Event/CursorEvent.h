#pragma once 

#include <cstddef>
#include <Common/Exception.h>
#include  <X11/Xlib.h> // to deal with XEvent

namespace Daylight::IO{

enum CursorEventType{
    EVENT_UNKNOWN       = 0x000000000000,
    EVENT_CURSORMOVE    = 0x000000000001, 
    EVENT_LBUTTONDOWN   = 0x000000000010, 
    EVENT_RBUTTONDOWN   = 0x000000000100, 
    EVENT_MBUTTONDOWN   = 0x000000001000, 
    EVENT_LBUTTONUP     = 0x000000010000, 
    EVENT_RBUTTONUP     = 0x000000100000, 
    EVENT_MBUTTONUP     = 0x000001000000, 
    EVENT_LBUTTONDBLCLK = 0x000010000000, 
    EVENT_RBUTTONDBLCLK = 0x000100000000, 
    EVENT_MBUTTONDBLCLK = 0x001000000000, 
    EVENT_CURSORWHEEL   = 0x010000000000, 
    EVENT_CURSORHWHEEL  = 0x100000000000, 
}; 

struct CursorLocation {
    const static size_t INVALID_DATA; 
    size_t x; 
    size_t y; 
    inline CursorLocation(const size_t & _x=INVALID_DATA, const size_t & _y=INVALID_DATA) : x(_x), y(_y){}
    inline CursorLocation(const CursorLocation & that) = default; 
    inline bool isValid() const { return x != INVALID_DATA && y != INVALID_DATA; }
}; 


struct CursorEvent{
    CursorEventType type;
    CursorLocation loc;  
    CursorEvent(const CursorEvent & event) = default; 
    inline CursorEvent(const XEvent & xenv){
        throw new Daylight::NotImplementedException(); 
    }
    inline bool is(CursorEventType thatType) const { return (this->type & thatType) != 0;}
    inline CursorEvent(const CursorEventType & _eventType, const CursorLocation & _loc)
        :type(_eventType), loc(_loc){}
    inline bool isPressEvent() const { return type & (EVENT_LBUTTONDBLCLK | EVENT_RBUTTONDBLCLK | EVENT_MBUTTONDBLCLK); }
    inline bool isWheelingEvent() const { return type & (EVENT_CURSORWHEEL | EVENT_CURSORHWHEEL); }
}; 



}


