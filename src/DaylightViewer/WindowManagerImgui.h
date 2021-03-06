#pragma once

#include <memory>
// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)


#include "Common/GL_include.h"


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually. 
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <gl3w/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif
// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h> 

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma. 
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif



#include "Common/Config.h"
 #include <IO/WindowManager.h>


namespace Daylight {
// struct GlResource{
//     Config progConfig;
//     Patronus::Shaper * shaper = nullptr;
//     Lumos::Program * program = nullptr;
//     Patronus::PhysicalWorld * physicalWorld = nullptr;
//     Lumos::Instance * selectedInstance = nullptr;
//     std::string SCENE_FILE_DIR = "./scene_file/";
//     std::string TEXTURE_DIR = "./scene_file/texture/";
//     std::string CAMERA_DIR = "./cameras/";
//     std::string OUTPUT_DIR = "./output/";
//     std::string RENDER_LIST = "./obj_list.txt";
// }; 

    namespace Patronus {
        class Shaper; 
        class PhysicalWorld; 
    }
    namespace Lumos {
        class Program; 
        class Instance; 
    }

    namespace IO{

        class WindowManagerImgui: public WindowManager{
        public:
            WindowManagerImgui(const size_t & w, const size_t & h); 
            WindowManagerImgui(); 
            ~WindowManagerImgui(); 

            virtual inline void show() override{}
            virtual int loop() override; 
        private:
            void _initImgui(); 
            void _initOpenGl(); 
            void showPort(bool* p_open); 

            GLFWwindow* window; 
            bool show_demo_window;
            bool show_another_window;
            
            //GlResource glResource; 
        }; 

    }

}
