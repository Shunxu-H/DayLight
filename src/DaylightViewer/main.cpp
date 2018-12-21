
#include <Common/GL_include.h>
#include <Common/Utility.h>
#include <Common/Config.h>

#include <Lumos/Program.h>

#include <Patronus/PhysicalWorld.h>
#include <Patronus/Shaper.h>

#include <DaylightViewer/Canvas.h>

Config progConfig;
Patronus::Shaper * shaper = nullptr;
Lumos::Program * gProgram = nullptr;
Patronus::PhysicalWorld * world = nullptr;
Lumos::Instance * selectedInstance = nullptr;
Daylight::Canvas * canvas = nullptr; 
WindowManager_base * winMan = nullptr;
std::string SCENE_FILE_DIR = "./scene_file/";
std::string TEXTURE_DIR = "./scene_file/texture/";
std::string CAMERA_DIR = "./cameras/";
std::string OUTPUT_DIR = "./output/";
std::string RENDER_LIST = "./obj_list.txt";

int main(int, char**)
{

    winMan = new Daylight::Canvas{1280, 720}; 

    // for physical simulartion
    world = new Patronus::PhysicalWorld();
    // openGL resource management
    gProgram = new Lumos::Program( );
    shaper = new Patronus::Shaper( "./data/indoor/0004dd3cb11e50530676f77b55262d38.obj" );

    gProgram->loadShaders( "./GLSL" );
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    gProgram->preDrawSetUp();

     
    return winMan->loop();
}
