#ifndef ELLIPSOID_H
	#define ELLIPSOID_H
#include <memory>
#include <string>
#include "Vector.h"

class Ellipsoid{
public:
    //Ellipsoid(){}	Ellipsoid(const Vector & _center, const Vector & _offset);
	inline void setCenter(const Vector & _center){center = _center;}
	inline void setOffset(const Vector & _offset){offset = _offset;}
	inline Vector getCenter()const{return center;}
	inline Vector getOffset()const{return offset;}

	std::string save()const;

	void transform(const Matrix & m);
	void draw(float const*)const;

	Vector getNormal(const Vector & v)const;
protected:


private:
	Vector center;
	Vector offset;

};



	#endif
