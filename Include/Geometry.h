#ifndef GEOMETRY_H
	#define GEOMETRY_H

#include <vector>
#include <string>
#include <memory>
#include "Vector.h"
#include "AEL.h"
#include "Object.h"

class Edge;
class Face;

enum UnitType
{
	COORDS,
	PXLPOS
};


class Geometry: public Object
{
public:

	//Geometry(std::vector<Vector*> v=std::vector<Vector*>(),std::vector<Edge*> e=std::vector<Edge*>(), GeoType gt=AUTO,UnitType ut=COORDS);
	Geometry();
	Geometry(const Geometry&);
	~Geometry();

	inline void pop(){vertices.pop_back();};
	inline bool isType(UnitType _t) const { return _t == unitType; }
	inline unsigned int size() const { return vertices.size(); }
	
	int getID()const;
	void clear();
	virtual void draw(float const*)const;
	void drawNormal()const;
	std::string save()const;
	void insert(std::shared_ptr<Vector> v){};


	void transpose();
	void transform(const Matrix&);
	void clip(const Vector&);


	void operator+=(std::shared_ptr<Vector> v);
	void operator+=(std::shared_ptr<Edge> e);
	void operator+=(std::shared_ptr<Face> f);
	std::vector<AEL*> getAELs(); 

	Vector getCentroid()const;
	void updateCentroid();
        
	Geometry inPXLCOORD(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z)const;

	int vGetN(const Vector &v)const;
	std::shared_ptr<Vector> nGetV(const unsigned int& index);

	Vector getNormalVector(const Vector& v)const;
	std::vector<std::shared_ptr<Face>>& getFaces(){ return faces;}

	float getMaxX()const;
	float getMinX()const;
	float getMaxY()const;
	float getMinY()const;
	float getMaxZ()const;
	float getMinZ()const;

	void computeColors(const Vector & lightSource, const Vector &viewPtr);
	std::vector<Vector> getColors(const Face & face)const ;
	std::vector<Vector> getColors()const{ return colors; } ;

	float getHighestColor()const;

	void normalizeColors(const float &colorRate);

	friend std::ostream& operator<< (std::ostream& stream, const Geometry& matrix);
	void print();

	void selectVertices(const Vector & v1, const Vector & v2){};


	std::shared_ptr<Vector> getIntersection(const Line & line)const;
	Vector getNormal(const Vector & v)const;
	
private:
	void toPXLPOS(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z);
	UnitType unitType;
	Vector centroid;
	std::vector<std::shared_ptr<Vector>> vertices;
	std::vector<Vector> colors;
	std::vector<std::shared_ptr<Edge>> edges;
	std::vector<std::shared_ptr<Face>> faces;

	void clipUP(const float&);
	void clipDOWN(const float&);
	void clipLEFT(const float&);
	void clipRIGHT(const float&);
	void drawLines(float const*)const;
	std::shared_ptr<Vector> getHorizontalIntersection(const Vector& v1, const Vector& v2, const float& y);
	std::shared_ptr<Vector> getVerticalIntersection(const Vector& v1, const Vector& v2, const float& x);

};




#endif 
