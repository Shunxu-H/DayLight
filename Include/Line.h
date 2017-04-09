#ifndef LINE_H
	#define LINE_H

#include <string>
#include "Vector.h"
class Line{
public:
	Line(){};
	Line(const Vector & _origin, const Vector & _veolocity);
	inline Vector getOrigin()const{return origin;}
	inline void setOrigin(const Vector _origin){ origin = _origin;}
	inline Vector getVelocity()const{return velocity;}
	inline void setVelocity(const Vector _velocity){ velocity = _velocity;}

	inline std::string save()const{return std::string();};


	void transform(const Matrix & m);
	void draw(float const*)const;
	void normalize();

protected:


private:
	Vector origin;
	Vector velocity;

};




	#endif