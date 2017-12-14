/*
The MIT License (MIT)

Copyright (c) 2016-2017 Shunxu Huang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef UTILITY_H
	#define UTILITY_H

#include <vector>
#include <deque>
#include <memory>
#include <memory>
#include <iostream>
#include <set>
#include <experimental/filesystem>
#include "GL_include.h"
#include "btBulletDynamicsCommon.h"
class AEL;

#ifndef NDEBUG
#define Debug(x) std::cout << x << std::endl
#define GLError(func, line) Utils::logOpenGLError( std::string(func) + ":" + std::to_string(line) )
#else
#define Debug(x)
#define GLError(func, line)

#endif

namespace Utils {

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

    int numOfSlotFilled(int* a, const size_t& len);

    std::shared_ptr<int> generateUniqeInt(const int& numOfE);

    constexpr unsigned int str2int(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
    }

    std::string genUniqueName(const std::set<std::string> & nameList, const std::string & prefix );

    void logOpenGLError( const std::string & sourceFile = "unknown( check stack please ) ");

    template<typename From, typename To>
    void convert(const From & from, To & to, const size_t & size){
        for (size_t i = 0; i < size; i++ )
            to[i] = from[i];
    }

    void printFramebufferInfo(GLenum target, GLuint fbo);

    void cleanAndMkdir(const std::string & path);

    void remove_all( const std::experimental::filesystem::path & path );

    void getAllFileWithExtension(const std::string & path, const std::string & extension, std::vector<std::experimental::filesystem::path> & all_files );
    void getAllDir( const std::string & path,
                    std::vector<std::experimental::filesystem::path> & all_files,
                    const std::vector<std::string> & obj_list = std::vector<std::string>());
    int glExtCheckFramebufferStatus(char *errorMessage);
}
#endif
