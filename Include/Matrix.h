#ifndef MATRIX_H
	#define MATRIX_H
#include <vector>
#include "Index.h"

enum SpecialMatrix{
	TRANSLATION,
	ROTATION,
	SCALING
};

class Matrix{
public:
	Matrix(){numOfCol=0; numOfRow=0; };

	inline Matrix(const int& _numOfRow, const int& _numOfCol): numOfRow(_numOfRow), numOfCol(_numOfCol){
			makeData(numOfRow, numOfCol);
	}


	Matrix(Matrix && m);
	Matrix& operator=(Matrix rhs);

	friend void swap(Matrix & m1, Matrix& m2);

	Matrix(const Matrix& m);
	//float get(const int& rowPtr, const int& colPtr);
	//void set(const int& rowPtr, const int& colPtr);


	Matrix(const SpecialMatrix& type);
	void makeData(const int& _numOfCol, const int& _numOfRow);

	virtual ~Matrix();

	inline int getRowNum(){ return numOfRow; };
	inline int getColNum(){ return numOfCol; };

	void makeTranslationMatrix(const float& x, const float& y, const float &z);
	void makeRotationMatrix(const float& alpha, const float& x, const float& y);
	void makeScalingMatrix(const float& alpha_x, const float& alpha_y , const float& alpha_z);
	void makeBaseRotMatrix(const float& alpha, const INDEX& index);
	void makeCabinet();

	Matrix operator*(const Matrix& rhs)const; 
	Matrix operator*(const float& n)const; 
	Matrix operator/(const float& n)const; 
	Matrix operator+(const Matrix& rhs)const; 
	Matrix operator+(const float& n)const; 
	Matrix operator-(const Matrix& rhs)const;
	Matrix operator-(const float& n)const; 
	Matrix operator-()const;
	Matrix transpose()const;
	Matrix times(const Matrix& m)const;
	void concatenate(const Matrix& m);
	virtual inline float* operator[](const int& index){return data[index]; }
	virtual inline float* operator[](const int& index)const {return data[index]; }


	void rowAssignment(const unsigned int& r, const std::vector<float>& d);


	float threeByThreeDeterminant()const;

	float max()const;
	float min()const;
	// for debugging
	void print()const;
	void test()
	{
		
	    Matrix a(4, 3);
	    for ( int i = 0; i < 3; i++)
	            for ( int j = 0; j < 4; j++)
	                    a[i][j] = i*3 + j + 1;
	    a.print();

	    Matrix b(3, 4);
	    for ( int i = 0; i < 4; i++)
	            for ( int j = 0; j < 3; j++)
	                    b[i][j] = i*4 + j + 1;
	    b.print();

	    (a*b).print();

	}

	Matrix shallowCopy();


	
protected:
	std::vector<float*> data;

private:
	int numOfRow;
	int numOfCol;

	void clearData();
	void destroyData();
	void makeIdentiy();
};



	#endif