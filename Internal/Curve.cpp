#include <cstddef>
#include <limits>
#include "Curve.h"
#include "WindowManager.h"
#include "Config.h"
#include "Shader.h"

extern WindowManager* winMan;
extern Config progConfig;
extern Shader* shader;

Curve::Curve():Object(CURVE){
	curveType = BSPLINE;
	k = 3;
	resolution = 1000;

	for (float i = 0.0f; i < vertices.size() + k - 1.0; i+=1.0f)
		u.push_back(i);

}

Curve::Curve(const std::vector<std::shared_ptr<Vector>>& v):Object(CURVE){
	vertices = v;
	k = 3;
	resolution = 1000;
	for (float i = 0.0f; i < vertices.size() + k - 1.0; i+=1.0f)
		u.push_back(i);
}


Vector Curve::getBezierHandle(const float & t)const{
	std::vector<std::shared_ptr<Vector>> prevGen = vertices;
	std::vector<std::shared_ptr<Vector>> curGen;

	while (prevGen.size() > 1){
		for ( int i = 0; i < prevGen.size()-1; i++)
		{
			curGen.push_back(std::make_shared<Vector>(*prevGen[i] + ( (*prevGen[i+1] - *prevGen[i])*t)));
		}
		prevGen = curGen;
		curGen.clear();
	}
	return *prevGen[0];
}

void Curve::draw(float const * color)const{
	float* c_hlPoint;
	float* c_regPoint;
	float* c_curve;

	// configure the color for different component
	if (shader->isSelected(this)){
		c_hlPoint	= progConfig.COLOR_HIGHTLIGHTED_VERTEX;
		c_regPoint	= progConfig.COLOR_hlStroke;
		c_curve		= progConfig.COLOR_hlStroke;
	}
	else
	{
		c_hlPoint	= progConfig.COLOR_regStroke;
		c_regPoint	= progConfig.COLOR_regStroke;
		c_curve		= progConfig.COLOR_regStroke;
	} 


	// connect the control points
	for (unsigned int i = 0; i < vertices.size()-1; i++)
	{
		winMan->drawLine(*vertices[i], *vertices[i+1], Color().LGREY);
	}

	if (curveType == BEZIER)
		drawBezier(c_curve);
	else 
		drawBSpline(c_curve);



	// draw vertices on top 
	for (auto v: vertices){
		if (!isSelected(v.get()))
			v->draw(c_regPoint);
		else
			v->draw(c_hlPoint);
	}

}

void Curve::drawBezier(const float * const c_curve)const{
	float t = 0;

	std::vector<Vector> points; 
	float stepSize = 1.0f/static_cast<float>(resolution);
	while (t <= 1){
		points.push_back(getBezierHandle(t));
		t+=stepSize;
	}
	
	// drawcurve()
	for (unsigned int i = 0; i < points.size()-1; i++)
	{
		winMan->drawLine(points[i], points[i+1], c_curve);
	}
}

Vector Curve::getSplinepoint(const float & t)const{

	int n = k + vertices.size() - 1;
	std::vector<std::shared_ptr<Vector>> prevGen;
	std::vector<std::shared_ptr<Vector>> curGen; 



	// configure I
	int I = 0;
	for (int i = 0; i < n ; i++){
		if ( t >= u[i] ){
			if ( i != 0 && u[i] == u[i-1] )
				break;
			I++;
		}
		else
			break;
	}
	I--;

	for ( int i = I - ( k - 1); i <= I + 1; i++)
		prevGen.push_back(vertices[i]);

	while (prevGen.size() > 1){

		for(int v_ptr = 0; v_ptr < prevGen.size() - 1; v_ptr++){
			int genNum = k - prevGen.size() + 1;
			float u_base = u[I - k + 1 + v_ptr + genNum];
			float curT = t - u_base;
			curT = curT/(u[I + v_ptr + 1] - u_base);
			curGen.push_back(std::make_shared<Vector>(*prevGen[v_ptr]+((*prevGen[v_ptr+1] 
				  									 - *prevGen[v_ptr])*curT) ) );
		}
		prevGen = curGen;
		curGen.clear();
	}

	return *prevGen[0];
}

void Curve::drawBSpline(const float * const c_curve)const{
	if( k < 1)
		return;
	if(vertices.size() < k + 1)
		return;

	float t = u[k-1];
	float stepSize = (u[k - 1 + (vertices.size() - k)] - u[k-1])/static_cast<float>(resolution);

	std::vector<Vector> points;


	while (t <= u[k - 1 + (vertices.size() - k) ]){

		points.push_back(getSplinepoint(t));
		t+=stepSize;
	}
	
	// drawcurve()
	for (unsigned int i = 0; i < points.size()-1; i++)
	{
		winMan->drawLine(points[i], points[i+1], c_curve);
	}
}


std::string Curve::save()const{
	std::string str="";

	// dump type
	str.append(std::to_string(type) + "\n");

	// int k;
	// int resolution;
	// std::vector<float> u;

	// dump k
	str.append(std::to_string(k) + "\n");
	// dump resolution 
	str.append(std::to_string(resolution) + "\n");
	// dump u vector
	str.append(std::to_string(u.size()) + "\n");
	for(const float & num: u)
		str.append(std::to_string(num) + " ");
	str.append("\n");
		
	str.append(std::to_string(size()) + "\n" );
	for (auto vertex : vertices){
		str.append(std::to_string(vertex->getX()) + " " );
		str.append(std::to_string(vertex->getY()) + " " );
		str.append(std::to_string(vertex->getZ()) + "\n" );
	}
	str.append("\n" );
	return str;
}

void Curve::clear(){

}



float Curve::getMaxX()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto v: vertices)
		if (v->getX() > ret)
			ret = v->getX();

	return ret;
}

float Curve::getMinX()const{
	float ret = std::numeric_limits<float>::max();
	for (auto v: vertices)
		if (v->getX() < ret)
			ret = v->getX();

	return ret;
}

float Curve::getMaxY()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto v: vertices)
		if (v->getY() > ret)
			ret = v->getY();

	return ret;
}

float Curve::getMinY()const{
	float ret = std::numeric_limits<float>::max();
	for (auto v: vertices)
		if (v->getY() < ret)
			ret = v->getY();

	return ret;
}

float Curve::getMaxZ()const{
	float ret = std::numeric_limits<float>::lowest();
	for (auto v: vertices)
		if (v->getZ() > ret)
			ret =v->getZ();

	return ret;
}

float Curve::getMinZ()const{
	float ret = std::numeric_limits<float>::max();
	for (auto v: vertices)
		if (v->getZ() < ret)
			ret = v->getZ();

	return ret;
}

void Curve::operator+=(std::shared_ptr<Vector> v)
{
	vertices.push_back( v );
	u.push_back(u.size());

	//concatenate(*v);
}

bool Curve::isSelected(Vector const* toCheck)const{
	for(auto v: selectedVertices)
		if(v.get() == toCheck)
			return true;

	return false;
}

void Curve::selectVertices(const Vector & v1, const Vector & v2){
	selectedVertices.clear();

	float minX, maxX, minY, maxY, minZ, maxZ;

	minX = std::min(v1[X], v2[X]);
	maxX = std::max(v1[X], v2[X]);
	minY = std::min(v1[Y], v2[Y]);
	maxY = std::max(v1[Y], v2[Y]);
	minZ = std::min(v1[Z], v2[Z]);
	maxZ = std::max(v1[Z], v2[Z]);

	for (auto v: vertices){
		float x = v->getX();
		float y = v->getY();
		float z = v->getZ();
		if (x >= minX && x <= maxX &&
			y >= minY && y <= maxY &&
			z >= minZ && z <= maxZ){
			selectedVertices.push_back(v);
		}
	}

}

void Curve::transform(const Matrix & m){
	if (progConfig.selectMode == VERTEX){
		if(selectedVertices.size() == 0){
			for(auto v:vertices)
				v->transform(m);
		}
		else
			for (auto v: selectedVertices)
				v->transform(m);
	}
}

bool Curve::hasConsecutiveSelection(){
	if (selectedVertices.size() != 2)
		return false;
	else
		return std::abs( vGetN(selectedVertices[0].get()) - vGetN(selectedVertices[1].get()) ) == 1; 
}

int Curve::vGetN(const Vector * const v){
	for(int i = 0; i < vertices.size(); i++){
		if(vertices[i].get() == v)
			return i;
	}
	return -1;
}

void Curve::push_front(std::shared_ptr<Vector> v){
	vertices.insert(vertices.begin(), v);
}

void Curve::push_back(std::shared_ptr<Vector> v){
	vertices.push_back(v);
}

void Curve::insert(std::shared_ptr<Vector> v){
	if(selectedVertices.size() == 0)
		return;
	if(selectedVertices.size() == 1){
		if(selectedVertices[0] == vertices[0])
			push_front(v);
		else if(selectedVertices[0] == vertices[vertices.size() - 1])
			push_back(v);
	}

	if(selectedVertices.size() == 2 && hasConsecutiveSelection())
		vertices.insert( vertices.begin()+ std::max(vGetN(selectedVertices[0].get()), vGetN(selectedVertices[1].get())), v);
}


void Curve::deleteVertices(){
	if (selectedVertices.size() <= 0)
		return;
	for (auto v: selectedVertices){
		vertices.erase(vertices.begin()+vGetN(v.get()));
		u.pop_back();
	}
	if(vertices.size() == 0)
		shader->deleteObj(this);
}


void Curve::setK(const int & k){
	this->k = k;
}

void Curve::setUVector(const std::vector<float> & us){
	for (int i = 0; i < std::min(u.size(), us.size()); i++){
		u[i] = us[i];
	}
}

void Curve::setOneU(const int & index, const float & value){
	if(index >= u.size()){
		std::cerr << "Invalid index, please provide a valid index." << std::endl;
		return;
	}
	else if (index > 0 && u[index-1] > value ){
		std::cerr << "Invalid value, please provide a value greater than or equal to " << u[index-1] << std::endl;
		return;
	}
	else if (index < u.size() - 1 && u[index+1] < value ){
		std::cerr << "Invalid value, please provide a value smaller or equal to " << u[index+1] << std::endl;
		return;
	}

	u[index] = value;
}