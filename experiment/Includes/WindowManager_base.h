#ifndef WINDOWMANAGER_BASE_H
#define WINDOWMANAGER_BASE_H

#include <cstddef>
#include <vector>


class View;

class WindowManager_base
{
public:
	WindowManager_base(
						const size_t & w = 500,
						const size_t & h = 500
						);
	virtual ~WindowManager_base(){};



	inline size_t 
    	getWidth() const { return _width; }
    inline  void
    	setWidth( const size_t & w) {  _width = w; }
    inline size_t 
    	getHeight() const { return _height; }
    inline  void
    	setHeight( const size_t & h) {  _height = h; }


    void positionAllViewsToFitAllInstances();

    virtual int loop() = 0;
    virtual void show() = 0;

protected:

    std::vector< View* > _views;

	size_t _width;
	size_t _height;

private:

};




#endif