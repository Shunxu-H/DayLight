#ifndef VIEW_H
  #define VIEW_H

#include <string>
#include "Widget.h"

class View: public Widget{
public:
    View(
          const std::string & title = "",
          const size_t & x = 0,
          const size_t & y = 0,
          const size_t & w = 0,
          const size_t & h = 0
      );

    virtual void paintGL() = 0;
    virtual void initializeGL() = 0;
    virtual void resizeGL(const size_t & w, const size_t & h) = 0;

    inline bool isExposed() const {return _isExposed; }
protected:
    virtual void _expose() override;
private:
    bool _isExposed;
};




#endif
