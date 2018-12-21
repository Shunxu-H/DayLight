#pragma once

#include <stdexcept>

namespace Daylight{

    class NotImplementedException : public std::logic_error
    {
    public:
        using std::logic_error::logic_error;
        NotImplementedException(std::string const& msg="Function not yet implemented.") : std::logic_error(msg) { } 
        // virtual char const * what() const throw() { return "Function not yet implemented."; }
    };

}