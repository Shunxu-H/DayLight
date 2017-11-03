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
#define Debug(x) std::cout << x
#else
#define Debug(x) 
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
    void getAllDir(const std::string & path, std::vector<std::experimental::filesystem::path> & all_files );
    int glExtCheckFramebufferStatus(char *errorMessage);
}
#endif
