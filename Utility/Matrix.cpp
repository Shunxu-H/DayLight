#include <iostream>
#include <cstring>
#include <ctgmath>
#include <vector>
#include <cstring>
#include <limits>
#include <cstddef>
#include "Matrix.h"
#include "Index.h"




Matrix::Matrix(const Matrix& m){
	//if (this->data == nullptr);
	//	return;
	numOfRow = m.numOfRow;
	numOfCol = m.numOfCol;
	makeData(numOfRow, numOfCol);

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			data[colPtr][rowPtr] = m.data[colPtr][rowPtr]; 
		}
	}
}

// move constructor
Matrix::Matrix( Matrix && m):Matrix(){
	swap(*this, m);
}

void swap(Matrix & m1, Matrix& m2){
	using std::swap;

	swap(m1.numOfCol, m2.numOfCol);
	swap(m1.numOfRow, m2.numOfRow);
	m1.data.swap(m2.data);
}

void Matrix::makeData(const int& _numOfRow, const int& _numOfCol){
	if ( _numOfCol <= 0){
		data.clear();
	}

	for (int colCnt = 0; colCnt < numOfCol; colCnt++)
		data.push_back(new float[numOfRow]);

}


Matrix& Matrix::operator=(Matrix that){
	
	swap(*this, that);
	return *this;
}


Matrix::~Matrix(){
	destroyData();
	
	//std::cout << "~Matrix() " << this << std::endl;
	data.clear();
	numOfCol = 0;
	numOfRow = 0;
}

void Matrix::destroyData(){
	
	if (data.size() != 0){
		for (int colCnt = 0; colCnt < numOfCol; colCnt++){
			delete[] data[colCnt];
			data[colCnt] = nullptr;
		}
	}

}

void Matrix::clearData(){
	if (data.size() != 0)
		for (int rowCnt = 0; rowCnt < numOfRow; rowCnt++)
			for (int colCnt = 0; colCnt < numOfCol; colCnt++)
				data[colCnt][rowCnt] = 0;
}

Matrix Matrix::operator*(const Matrix& rhs)const{
	if ( numOfCol != rhs.numOfRow){
		std::cerr << "matrixes' formats do not match in * operator" << std::endl;
		return Matrix();
	}

	Matrix m(this->numOfRow, rhs.numOfCol);

	for ( int thisRowPtr = 0; thisRowPtr < numOfRow; thisRowPtr++){
		for ( int rhsColPtr = 0; rhsColPtr < rhs.numOfCol; rhsColPtr++){
			float temp = 0;
			for ( int rhsRowPtr = 0; rhsRowPtr < rhs.numOfRow; rhsRowPtr++){
				temp += data[rhsRowPtr][thisRowPtr]*rhs[rhsColPtr][rhsRowPtr];
			}
			m[rhsColPtr][thisRowPtr] = temp;
		}
	}
	//m.print();
	return m;
}


Matrix Matrix::operator*(const float& n)const{
	Matrix m(numOfRow, numOfCol);

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			m[colPtr][rowPtr] = data[colPtr][rowPtr] * n; 
		}
	}
	
	return m;
}

Matrix Matrix::operator/(const float& n)const{
	return (*this)*(1/n);
}

Matrix Matrix::operator+(const float& n)const{
	Matrix m(numOfRow, numOfCol);

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			m[colPtr][rowPtr] = data[colPtr][rowPtr] + n; 
		}
	}

	return m;
}

 
 
Matrix Matrix::operator+(const Matrix& rhs)const{
	if ( numOfCol != rhs.numOfCol || numOfRow != rhs.numOfRow){
		std::cerr << "matrixes' formats do not match in + operator" << std::endl;
		return Matrix();
	}

	Matrix m(numOfRow, numOfCol);

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			m[colPtr][rowPtr] = data[colPtr][rowPtr] + rhs[colPtr][rowPtr]; 
		}
	}

	return m;
}

Matrix Matrix::operator-(const Matrix& rhs)const{
	if ( numOfCol != rhs.numOfCol || numOfRow != rhs.numOfRow){
		std::cerr << "matrixes' formats do not match in - operator" << std::endl;
		return Matrix();
	}

	return (*this) + (-rhs);
}


Matrix Matrix::operator-(const float& n)const{
	return (*this)+ -n;
}

Matrix Matrix::operator-()const{
	Matrix m(numOfRow, numOfCol);
	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			m[colPtr][rowPtr] = -data[colPtr][rowPtr]; 
		}
	}
	return m;
}


Matrix Matrix::transpose()const{
	Matrix ret(numOfCol, numOfRow);

	for (int colPtr = 0; colPtr < numOfCol; colPtr++)
		for( int rowPtr = 0; rowPtr < numOfRow; rowPtr++)
			ret[rowPtr][colPtr] = data[colPtr][rowPtr];

	return ret;
		
}

void Matrix::makeIdentiy(){
	if (numOfCol != numOfRow){
		std::cerr << "Non square matrix defined in Matrix::makeIdentiy();" << std::endl;
		return;
	}
	else if (data.size() == 0){
		makeData(numOfCol, numOfRow);
	}

	for ( int i = 0; i < numOfCol; i++)
		data[i][i] = 1;
}

void Matrix::makeTranslationMatrix(const float& x, const float& y, const float &z){
	destroyData();
	numOfCol = 4;
	numOfRow = 4;

	makeData(numOfCol, numOfRow);
	clearData();
	makeIdentiy();

	data[3][0] = x;
	data[3][1] = y;
	data[3][2] = z;
	
}

void Matrix::makeRotationMatrix(const float& alpha, const float& x, const float& y){
	destroyData();
	numOfCol = 3;
	numOfRow = 3;

	makeData(numOfCol, numOfRow);
	clearData();
	//makeIdentiy();

	float cosAlpha = cos(alpha);
	float sinAlpha = sin(alpha);

	data[0][0] = cosAlpha; 
	data[1][0] = -sinAlpha;
	data[3][0] = -x*cosAlpha + y*sinAlpha + x;

	data[0][1] = sinAlpha; 
	data[1][1] = cosAlpha;
	data[2][1] = -x*sinAlpha - y*cosAlpha + y;
	
	data[0][2] = 0;
	data[1][2] = 0;
	data[2][2] = 1;


}

void Matrix::makeCabinet()
{
	destroyData();
	numOfCol = 4;
	numOfRow = 4;

	makeData(numOfCol, numOfRow);
	clearData();
	makeIdentiy();

	data[2][0] = - sqrt(2.0f)/4.0f;
	data[2][1] = - sqrt(2.0f)/4.0f;
	data[2][2] = 0;
}


void Matrix::makeBaseRotMatrix(const float& alpha, const INDEX &axis){
	destroyData();
	numOfCol = 4;
	numOfRow = 4;

	makeData(numOfCol, numOfRow);
	clearData();
	makeIdentiy();

	float cosAlpha = cos(alpha);
	float sinAlpha = sin(alpha);

	if (axis == X){
		rowAssignment(0, std::vector<float> {1.0f, 0.0f, 0.0f, 0.0f });
		rowAssignment(1, std::vector<float> {0.0f, cosAlpha, -sinAlpha, 0.0f });
		rowAssignment(2, std::vector<float> {0.0f, sinAlpha, cosAlpha, 0.0f });
		rowAssignment(3, std::vector<float> {0.0f, 0.0f, 0.0f, 1.0f });
	}
	else if (axis == Y){
		rowAssignment(0, std::vector<float> {cosAlpha, 0.0f, sinAlpha, 0.0f });
		rowAssignment(1, std::vector<float> {0.0f, 1.0f, 0.0f, 0.0f });
		rowAssignment(2, std::vector<float> {-sinAlpha, 0.0f, cosAlpha, 0.0f });
		rowAssignment(3, std::vector<float> {0.0f, 0.0f, 0.0f, 1.0f });
	}
	else if (axis == Z){
		rowAssignment(0, std::vector<float> {cosAlpha, -sinAlpha, 0.0f, 0.0f });
		rowAssignment(1, std::vector<float> {sinAlpha, cosAlpha, 0.0f, 0.0f });
		rowAssignment(2, std::vector<float> {0.0f, 0.0f, 1.0f, 0.0f });
		rowAssignment(3, std::vector<float> {0.0f, 0.0f, 0.0f, 1.0f });
	}


}

void Matrix::rowAssignment(const unsigned int& r,const std::vector<float>& d){
	if (r > static_cast<unsigned int>(numOfRow) || d.size() > static_cast<unsigned int>(numOfCol)){
		std::cerr << "Invalid parameters in Matrix::rowAssignment(unsigned int&, std::vector<float>()" << std::endl;
		exit(1);
	}

	for (unsigned int i = 0; i < d.size(); i++)
		data[i][r] = d[i];

}


void Matrix::makeScalingMatrix(const float& alpha_x, const float& alpha_y, const float& alpha_z ){
	destroyData();
	numOfCol = 4;
	numOfRow = 4;

	makeData(numOfCol, numOfRow);
	clearData();
	//makeIdentiy();

	data[0][0] = alpha_x; 
	data[1][1] = alpha_y;
	data[2][2] = alpha_z;
	data[3][3] = 1;
}

Matrix::Matrix(const SpecialMatrix& type){
	if (type == TRANSLATION){

	}
	else if (type == SCALING){

	}
	else if (type == ROTATION){

	}
} 

void Matrix::print()const
{
	if (data.size() != 0)
		for (int rowCnt = 0; rowCnt < numOfRow; rowCnt++){
			for (int colCnt = 0; colCnt < numOfCol; colCnt++){
				std::cout << data[colCnt][rowCnt] << " ";
			}
			std::cout << std::endl;
		}

	std::cout << std::endl;
}


Matrix Matrix::times(const Matrix& rhs)const{
	if ( numOfCol != rhs.numOfCol || numOfRow != rhs.numOfRow){
		std::cerr << "matrixes' formats do not match in Matrix::times()" << std::endl;
		return Matrix();
	}

	Matrix m(numOfRow, numOfCol);

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			m[colPtr][rowPtr] = data[colPtr][rowPtr] * rhs[colPtr][rowPtr]; 
		}
	}

	return m;
}

float Matrix::max()const{
	float max = -std::numeric_limits<float>::max();

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			if (data[colPtr][rowPtr] > max)
				max = data[colPtr][rowPtr];
		}
	}

	return max;
}

float Matrix::min()const{
	float min = std::numeric_limits<float>::max();

	for ( int colPtr = 0; colPtr < numOfCol; colPtr++){
		for ( int rowPtr = 0; rowPtr < numOfRow; rowPtr++){
			if (data[colPtr][rowPtr] < min)
				min = data[colPtr][rowPtr];
		}
	}

	return min;
}

// this function will only make a shallow copy of the columns
void Matrix::concatenate(const Matrix& m){
	if( numOfRow != m.numOfRow )
	{
		std::cerr << "matrixes' formats do not match in Matrix::concatenate()" << std::endl;
		return;
	}

	for (int i = 0; i < m.numOfCol; i++){
		numOfCol++;
		float* newCol = new float[this->numOfRow];
		for (int rowPtr = 0; rowPtr < this->numOfRow; rowPtr ++)
			newCol[rowPtr] = m[i][rowPtr];

		data.push_back(newCol);
	} 
}

Matrix Matrix::shallowCopy(){

}


float Matrix::threeByThreeDeterminant()const{
	return data[0][0]*(data[1][1]*data[2][2] - data[2][1]*data[1][2]) -
		   data[1][0]*(data[0][1]*data[2][2] - data[2][1]*data[0][2]) +
		   data[2][0]*(data[0][1]*data[1][2] - data[1][1]*data[0][2]);
}
