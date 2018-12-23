#pragma once 

#include  <X11/Xlib.h> // to deal with XEvent

#include <Common/Exception.h>

namespace Daylight{
    
    namespace IO
    {
        enum class Holding{
            NONE = 0, 
            ALT  = 1, 
            CTRL = 2, 
            SHIFT= 4
        }; 
        
        enum class Action{
            KEY_UP = 0, 
            KEY_DOWN = 1, 
        }; 

        struct KeyboardEvent{
            Holding holding; 
            Action action; 
            unsigned char code; 
            inline KeyboardEvent(const unsigned char & _code, const Holding & _holding, const Action & _action )
                : holding(_holding)
                , action (_action)
                , code (_code) {}
            inline KeyboardEvent(const XEvent & xenv){
                throw new Daylight::NotImplementedException(); 
            }
            inline KeyboardEvent() = default; 
            inline KeyboardEvent(const KeyboardEvent & that) = default;
        }; 
    } // IO
    

}