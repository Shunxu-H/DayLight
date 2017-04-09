#ifndef UTILITY_H
	#define UTILITY_H

#include <vector>
#include <deque>
#include <memory>
#include <memory>
class AEL;

template <typename T>
void printDebug(T obj){
	// std::cout << obj << std::endl;
}



template <typename T>
void remove(std::vector<T>* v, unsigned int &index){
	if(v == nullptr || v->size() <= index )
		return;

	typename std::vector<T>::iterator itr = v->begin();
	for (unsigned int i = 0; i < index; i++ )
		itr++;

	v->erase(itr);
}

template <typename T>
void print(T obj)
{
	std::cout <<  obj << std::endl;
}

template <typename T>
T min(T a, T b){
	return (a < b)? a:b;
}

template <typename T>
T max(T a, T b){
	return (a > b)? a:b;
}

bool _compare(int n1, int n2);



std::shared_ptr<char> toChar(const std::string& str);

std::deque<std::string> mystrtok (const std::string& str, const char* delim);

bool compare(AEL* a1, AEL* a2);

bool contain(int* a, const int & num2Check, const unsigned int & len);

int numOfSlotFilled(int* a, const int& len);

std::shared_ptr<int> generateUniqeInt(const int& numOfE);

#endif