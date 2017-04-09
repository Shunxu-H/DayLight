#ifndef CURVE_H
	#define CURVE_H

#include <vector>
#include <memory>
#include "Object.h"
#include "Vector.h"
#include "Utility.h"


class Curve: public Object{

public:
	Curve();
	Curve(const std::vector<std::shared_ptr<Vector>>&);

	Vector getSplinepoint(const float & t)const;
	void draw(float const*)const;
	void drawBezier(const float * const c_curve)const;

	void drawBSpline(const float * const c_curve)const;

	std::string save()const;
	void clear();


	float getMaxX()const;
	float getMinX()const;
	float getMaxY()const;
	float getMinY()const;
	float getMaxZ()const;
	float getMinZ()const;

	void operator+=(std::shared_ptr<Vector> v);

	int size()const{return vertices.size();}
	void pop(){ if (vertices.size() > 0) vertices.pop_back();}
	void transform(const Matrix & m);

	Vector getBezierHandle(const float & t)const;
	void insert(std::shared_ptr<Vector> v);


	void selectVertices(const Vector & v1, const Vector & v2);

	Matrix getSelected()const;

	bool isSelected(Vector const* toCheck)const;

	friend std::ostream& operator<< (std::ostream& stream, const Curve & c){ return stream; };

	bool hasConsecutiveSelection();

	int vGetN(const Vector* const v);


	void push_front(std::shared_ptr<Vector> v);
	void push_back(std::shared_ptr<Vector> v);
	void deleteVertices();


	void setK(const int & k);
	void setUVector(const std::vector<float> & us);
	void setOneU(const int & index, const float & value);

	inline void toggleType(){ curveType = (curveType == BEZIER)? BSPLINE:BEZIER; };
	inline void setResolution( const int & res) { if (res > 0) resolution = res;}


	std::shared_ptr<Vector> getIntersection(const Line & line)const{};
	Vector getNormal(const Vector & v)const{};
protected:


private:
	CurveType curveType;
	std::vector<std::shared_ptr<Vector>> vertices;
	std::vector<std::shared_ptr<Vector>> selectedVertices;
	std::vector<float> u;
	int k;
	int resolution;

};





	#endif