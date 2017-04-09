#ifndef OBJECT_H
	#define OBJECT_H


#include <string>
#include <memory>
#include "Matrix.h"
#include "Config.h"
#include "Vector.h"
#include "Line.h"
class Vector;


class Object: public Matrix
{
public:
	Object(const ObjType & type=VERTEX);
	Object(const Matrix & m, const ObjType & _t);
	~Object(){}

	inline ObjType getType()const {return type;}
	inline bool isType (const ObjType & t)const { return type == t; }

	//virtual void clear();
	void deleteVertices();
	virtual std::string save()const=0;
	virtual void clear(){};

	virtual void transform(const Matrix &);

	virtual void draw(float const*)const=0;
	void insert(std::shared_ptr<Vector> v);


	virtual std::shared_ptr<Vector> getIntersection(const Line & line)const=0;
	virtual Vector getNormal(const Vector & v)const=0;


	void push_front(std::shared_ptr<Vector> v);
	void push_back(std::shared_ptr<Vector> v);


	void setColor(const float& r, const float& g, const float& b);
	Vector getColor()const;

	void selectVertices(const Vector & v1, const Vector & v2);

	inline float getReflectionCoefficient()const{return reflectionCoefficient;}
	inline float getRefractionCoefficient()const{return refractionCoefficient;}
	
	inline float getReflectionCoefficient(const float & n){ reflectionCoefficient = n;}
	inline float getRefractionCoefficient(const float & n){ refractionCoefficient = n;}
	

	friend std::ostream& operator<< (std::ostream& stream, Object const* obj);
protected:
	ObjType type;
	Vector color;
	float reflectionCoefficient;
	float refractionCoefficient;

private:
};



	#endif
