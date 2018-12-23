
#include <Common/GL_include.h>
#include <Common/Utility.h>
#include <Common/Config.h>

#include <Lumos/Program.h>

#include <Patronus/PhysicalWorld.h>
#include <Patronus/Shaper.h>

#include <DaylightViewer/WindowManagerImgui.h>

Daylight::Config progConfig;
Daylight::Patronus::Shaper * shaper = nullptr;
Daylight::Lumos::Program * gProgram = nullptr;
Daylight::Patronus::PhysicalWorld * world = nullptr;
Daylight::Lumos::Instance * selectedInstance = nullptr;
Daylight::IO::WindowManager * winMan = nullptr;
std::string SCENE_FILE_DIR = "./scene_file/";
std::string TEXTURE_DIR = "./scene_file/texture/";
std::string CAMERA_DIR = "./cameras/";
std::string OUTPUT_DIR = "./output/";
std::string RENDER_LIST = "./obj_list.txt";

int main(int, char**)
{

    winMan = new Daylight::IO::WindowManagerImgui{1280, 720}; 

    // for physical simulartion
    world = new Daylight::Patronus::PhysicalWorld();
    // openGL resource management
    gProgram = new Daylight::Lumos::Program( );
    shaper = new Daylight::Patronus::Shaper( "./data/indoor/0004dd3cb11e50530676f77b55262d38.obj" );
    Daylight::Patronus::Camera::loadCamerasFromDir("./data/camera", shaper); 
    gProgram->loadShaders( "./GLSL" );
    GLError( __PRETTY_FUNCTION__ , __LINE__ );

    gProgram->preDrawSetUp();

     
    return winMan->loop();
}
