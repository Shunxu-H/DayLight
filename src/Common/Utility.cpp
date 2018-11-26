 #include "Common/Utility.h"
#include <vector>
#include <experimental/filesystem>
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

    int numOfSlotFilled(int* a, const size_t & len){
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
            }
            else
                return curName;
        }
    }


    void printFramebufferInfo(GLenum target, GLuint fbo) {

        GLError( __PRETTY_FUNCTION__ , __LINE__ );
        int res, i = 0;
        GLint buffer;

        glBindFramebuffer(target,fbo);

        GLError( __PRETTY_FUNCTION__ , __LINE__ );
        do {
            glGetIntegerv(GL_DRAW_BUFFER0+i, &buffer);

            GLError( __PRETTY_FUNCTION__ , __LINE__ );
            if (buffer != GL_NONE) {

                printf("Shader Output Location %d - color attachment %d\n",
                            i, buffer - GL_COLOR_ATTACHMENT0);

                glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, buffer,
                            GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &res);
                GLError( __PRETTY_FUNCTION__ , __LINE__ );

                printf("\tAttachment Type: %s\n",
                            res==GL_TEXTURE?"Texture":"Render Buffer");
                glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, buffer,
                            GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &res);
                printf("\tAttachment object name: %d\n",res);
                GLError( __PRETTY_FUNCTION__ , __LINE__ );

            }
            ++i;

        } while (buffer != GL_NONE);
        GLError( __PRETTY_FUNCTION__ , __LINE__ );
        // get depth buffer info
        std::cout << "Depth buffer info: " << std::endl;
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                    GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &res);
        printf("\tAttachment Type: %s\n",
                    res==GL_TEXTURE?"Texture":"Render Buffer");
        glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                    GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &res);
        printf("\tAttachment object name: %d\n",res);
        std::cout << std::endl;
        GLError( __PRETTY_FUNCTION__ , __LINE__ );
    }

    namespace fs = std::experimental::filesystem;
    void cleanAndMkdir(const std::string & path){
        if( fs::exists(path) )
            Utils::remove_all(path);

        fs::create_directory(path);
    }


    void remove_all( const std::experimental::filesystem::path & path ){
        for(const std::experimental::filesystem::directory_entry& p: std::experimental::filesystem::directory_iterator(path)){
            //if (fs::path (p).is_)
            if( fs::is_directory(p) ){
                Utils::remove_all(fs::path(p));
            }
            else{
                fs::remove(p);
            }
        }
        fs::remove(path);

    }

    void getAllFileWithExtension(const std::string & path, const std::string & extension, std::vector<fs::path> & all_files ){
        if (!fs::exists(path)) return;

        all_files.clear();

        for(const fs::directory_entry& p: fs::directory_iterator(path)){
            //if (fs::path (p).is_)
            if( fs::is_regular_file(p) ){
                if(fs::path(p).extension().compare(extension) == 0)
                    all_files.push_back(fs::path(p));
            }
        }


    }

    void getAllDir(const std::string & path, std::vector<fs::path> & all_files, const std::vector<std::string> & obj_list ){
        if (!fs::exists(path)) return;
        //std::cout << path << std::endl;
        all_files.clear();
        if (obj_list.size() == 0){
            std::cerr << "No .obj list passed in, will render everything in the folder." << std::endl;
            for(const fs::directory_entry& p: fs::directory_iterator(path)){
                //if (fs::path (p).is_)
                if( fs::is_directory(p) ){
                    std::cout << fs::path(p).filename() << std::endl;
                    all_files.push_back(fs::path(p));
                }
            }
        }
        else{
            for (const std::string & f : obj_list){
                fs::path curP(std::string(path) + f);
                if (!fs::exists(curP) || !fs::is_directory(curP)){
                    std::cerr << (std::string(curP) + " does not exist of it is not a directory.") << std::endl;
                    continue;
                }
                all_files.push_back(curP);
            }
        }



    }

    int glExtCheckFramebufferStatus(char *errorMessage)
    {
        GLenum status;
        status=glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
        switch(status)
        {
            case GL_FRAMEBUFFER_COMPLETE_EXT:
            break;
            case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            //Choose different formats
            strcpy(errorMessage, "Framebuffer object format is unsupported by the video hardware. (GL_FRAMEBUFFER_UNSUPPORTED_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            strcpy(errorMessage, "Incomplete attachment. (GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            strcpy(errorMessage, "Incomplete missing attachment. (GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            strcpy(errorMessage, "Incomplete dimensions. (GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            strcpy(errorMessage, "Incomplete formats. (GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            strcpy(errorMessage, "Incomplete draw buffer. (GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            strcpy(errorMessage, "Incomplete read buffer. (GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT)(FBO - 820)");
            return -1;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT:
            strcpy(errorMessage, "Incomplete multisample buffer. (GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE_EXT)(FBO - 820)");
            return -1;
            default:
            //Programming error; will fail on all hardware
            strcpy(errorMessage, "Some video driver error or programming error occured. Framebuffer object status is invalid. (FBO - 823)");
            return -2;
        }
        return 1;
    }
}
