#include "Line.h"
#include "Ellipsoid.h"
#include "WindowManager.h"
#include "Shader.h"
#include "Config.h"

extern WindowManager* winMan;
extern Shader* shader;
extern Config progConfig;



Line::Line(const Vector & _origin, const Vector & _velocity){
	origin = _origin;
	velocity = _velocity;
}


void Line::transform(const Matrix & m){
	origin = m*origin;
}

void Line::normalize(){
	velocity.normalize();
}

void Line::draw(float const* color)const{
	winMan->drawLine(origin, velocity, color);
}