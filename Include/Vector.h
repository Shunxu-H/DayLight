#ifndef VECTOR_H
	#define VECTOR_H


#include <iostream>
#include <cstring>
#include <memory>
#include <cmath>
#include "Index.h"
#include "Matrix.h"
//class Geometry;
//#include "OrthoView.h"
class Geometry;

class Vector: public Matrix
{
public:
	//Vector():Matrix(3, 1){data[0][0] = 0.0f; data[0][1] = 0.0f; data[0][2] = 0.0f; };
	Vector(const float &_x=0.0f, const float &_y=0.0f, const float &_z=0.0f);
	Vector(const Matrix &rhs):Matrix(rhs){};
	// Vector(const Vector &rhs);
	// //Vector operator=(const Vector& rhs){ return Vector(rhs); }
	// ~Vector();
	// //inline std::pair<int, int> toOrthoViewUnit();

	inline float getX()const { return data[0][X]; };
	inline float getY()const { return data[0][Y]; };
	inline float getZ()const { return data[0][Z]; };
	inline void setX(const float& _x){ data[0][X] = _x; };
	inline void setY(const float& _y){ data[0][Y] = _y; };
	inline void setZ(const float& _z){ data[0][Z] = _z; };

	void normalize();


	double length()const;
	Vector makeUnitVector()const;


	inline bool operator==(const Vector& rhs)const{return (fabs(data[0][0] - rhs[0]) < 0.0001) && (fabs(data[0][1] - rhs[1]) < 0.0001) && (fabs(data[0][2] - rhs[2]) < 0.0001);}
	inline bool operator!=(const Vector& rhs)const{return !((*this) == rhs) ;}
	inline float& operator[](const INDEX & index){return data[0][static_cast<int>(index)];};
	inline float operator[](const INDEX & index)const {return data[0][static_cast<int>(index)];};
	inline float& operator[](const unsigned int & index){return data[0][index];};
	inline float operator[](const unsigned int & index)const {return data[0][index];};


 
	Vector operator*(const Vector& rhs)const;
	Vector operator*(const float& n)const;
	Vector operator/(const float& n)const;
	Vector operator+(const Vector& rhs)const;
	Vector operator+(const float& n)const;
	Vector operator-(const Vector& rhs)const;
	Vector operator-(const float& n)const;
	Vector operator-()const;
	Vector transpose()const;
	float dot(const Vector& v)const;
	Vector times(const Vector& rhs)const { return static_cast<Matrix>(*this).times( static_cast<Matrix>(rhs) ); }


	Vector cross(const Vector& that)const;

	void toCOORDS(const float&, const float&, const float&, const float&);
	void toPXLPOS(const float&, const float&, const float&, const float&);
	
	Vector inCOORDS(const float& pixelUnit, const float &w_x, const float& w_y, const float& w_z)const;
	Vector inPXLPOS(const float& pixelUnit, const float &w_x, const float& w_y, const float& w_z)const;


	friend std::ostream& operator<< (std::ostream& stream, const Vector& matrix);
        
    Vector getColor()const;
    void setColor(const float& r , const float& g, const float& b);
	void setColor(const Vector& c);


	void transform(const Matrix & m);
	void draw(float const*)const;

	Vector getReflectionVector(const Vector & normal)const;
	Vector getRefractionVector(const Vector & normal, const float & nRatio)const;




	

	//std::shared_ptr<Vector> normal;
protected:


private:
	friend Geometry;
	//Vector* color;
	//int test;
	//UnitType type;
};



	#endif 