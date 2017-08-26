#ifndef EDGE_H
	#define EDGE_H
#include <memory>
#include "Vector.h"
#include "Matrix.h"

class Edge{
public:
	Edge(){};
	Edge(const Edge& e);
	inline Edge(std::shared_ptr<Vector> h, std::shared_ptr<Vector> t):head(h), tail(t){};
	inline std::shared_ptr<Vector> getHead()const {return head;}
	inline std::shared_ptr<Vector> getTail()const {return tail;}
	
	inline void setHead(const float &x, const float &y, const float &z ) { head->setX(x);head->setY(y); head->setZ(z);}
	inline void setTail(const float &x, const float &y, const float &z ) { tail->setX(x);tail->setY(y); tail->setZ(z);}


	std::string save()const;
	void clear();
	void transform(const Matrix & m);
	void draw(float const*)const;
	void insert(std::shared_ptr<Vector> v){};

	void makeUnitVector();
	double length();


	float getMaxX()const;
	float getMinX()const;
	float getMaxY()const;
	float getMinY()const;
	float getMaxZ()const;
	float getMinZ()const;

	void selectVertices(const Vector & v1, const Vector & v2){}
	void deleteVertices(){};

	void push_front(std::shared_ptr<Vector> v){};
	void push_back(std::shared_ptr<Vector> v){};
	friend std::ostream& operator<< (std::ostream& stream, const Edge & edge);



protected:

private:
	std::shared_ptr<Vector> head;
	std::shared_ptr<Vector> tail;
};
	#endif