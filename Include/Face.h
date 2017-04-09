#ifndef FACE_H
	#define FACE_H

#include <vector>
#include <memory>
#include "Geometry.h"
#include "Index.h"
class Edge;
class AEL;

class Face
{
public:
	Face();
	Face(const Face& f);
	void addV(std::shared_ptr<Vector> v);

	std::shared_ptr<Vector> getV(const unsigned int & index)const;
	~Face();

	bool hasVector(const Vector&)const;
	int getVerticesCnt()const{return vertices.size();}

	std::vector<AEL*> getAELs(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z, const INDEX &, const INDEX &)const;

	Face inPXLCOORD(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z)const;
	void print();
	Vector getNormalVector()const;
	Vector getCentroid();
	const std::vector<std::shared_ptr<Vector>>& getVertices()const{ return vertices;};

	
	std::shared_ptr<Vector> getIntersection(const Line & line)const;


	std::string save()const;
	void clear();
	void transform(const Matrix & m);
	void draw(float const*)const;
	void insert(std::shared_ptr<Vector> v){};
	void deleteVertices(){};

	friend std::ostream& operator<< (std::ostream& stream, const Face & f);
	
	void push_front(std::shared_ptr<Vector> v){};
	void push_back(std::shared_ptr<Vector> v){};

	void selectVertices(const Vector & v1, const Vector & v2){};

	bool contain(const Vector & point)const;
	float getDistance(const Vector & point)const;

protected:

private:
	void toPXLPOS(const float& pixelUnit, const float& w_x, const float& w_y, const float& w_z);
	std::vector<std::shared_ptr<Vector>> vertices;

};



	#endif
