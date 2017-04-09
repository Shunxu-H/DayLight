#include <vector>
#include <deque>
#include <iostream>
#include <cstring>
#include <memory>
#include <ctime>
#include <cstdlib>
#include "AEL.h"


bool _compare(std::pair<int, std::shared_ptr<float>> p1, std::pair<int, std::shared_ptr<float>> p2){
	return p1.first > p2.first;  
}

std::shared_ptr<char> toChar(const std::string& str){
	std::shared_ptr<char> s (new char[str.size()+1], [](char* a){ delete[] a; });
	s.get()[str.size()] = '\0';
	memcpy(s.get(), str.c_str(), str.size());

	return s;

}

std::deque<std::string> mystrtok (const std::string& str, const char* delim)
{
	std::shared_ptr<char> s = toChar (str);
	std::deque<std::string> ret;
	char* token = strtok( s.get(), delim );

	while (token)
	{
		ret.push_back(std::string(token));
		token = strtok(NULL, delim);
	}
	return ret;
}


bool compare(AEL* a1, AEL* a2){ 
	return a1->getY() > a2->getY(); 
}


bool contain(int* a, const int & num2Check, const unsigned int & len){
	for (unsigned int i = 0; i < len; i++ )
		if (a[i] == num2Check)
			return true;


	return false;
}

int numOfSlotFilled(int* a, const int& len){
	int ret = 0;
	for (unsigned int i = 0; i < len; i++ )
		if (a[i] != -1)
			ret++;;

	return ret;
}


std::shared_ptr<int> generateUniqeInt(const int& numOfE){
	std::shared_ptr<int> ret(new int[numOfE], [](int* ptr) { delete[] ptr; });
	srand(time(NULL));
	for ( int i = 0; i < numOfE; i++)
		ret.get()[i] = -1;
	

	while (numOfSlotFilled(ret.get(), numOfE) < numOfE){
		int ran = rand() % numOfE;
		if (contain(ret.get(), ran, numOfE))
			continue;
		else 
			ret.get()[numOfSlotFilled(ret.get(), numOfE)] = ran;
	}

	return ret;
}