#include "Utility.h"
#include <vector>
#include <deque>
#include <iostream>
#include <cstring>
#include <memory>
#include <ctime>
#include <cstdlib>
#include <sstream>

namespace Utils {

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



    void logOpenGLError(const std::string & sourceFile ){

        // check OpenGL error
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::stringstream o;
            switch(err) {
                case GL_NO_ERROR:
                    return;
                    break;
                case GL_INVALID_ENUM:
                    o <<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid enum!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;

                case GL_INVALID_VALUE:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid value!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;

                case GL_INVALID_OPERATION:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Invalid operation!"<< std::endl;
                     throw std::runtime_error(o.str());
                    break;

                case GL_STACK_OVERFLOW:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Stack overflow!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;

                case GL_STACK_UNDERFLOW:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Stack underflow!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;

                case GL_OUT_OF_MEMORY:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Out Of memory!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;

                case GL_TABLE_TOO_LARGE:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Table too large!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;

                default:
                    o<<"OpenGL Error in "<<sourceFile<<" at line "<<": Unknown error!"<< std::endl;
                    throw std::runtime_error(o.str());
                    break;
            }
        }
    }





    std::string genUniqueName(const std::set<std::string> & nameList, const std::string & prefix ){
        int i = 1;
        while ( true ){
            std::string curName = prefix + std::to_string(i);
            if (nameList.find(curName) != nameList.end()){ // name exist
                i++;
                break;
            }
            else
                return curName;
        }
    }

}
