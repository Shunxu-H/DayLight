#include <string>
#include <iostream>


#include <opencv2/opencv.hpp>


#include <EGL/egl.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "WindowManager.h"

#include "Shaper.h"
#include "Program.h"
#include "WindowManager.h"
#include "WindowManager_headless.h"
#include "PhysicalWorld.h"
#include "Instance.h"
#include "Config.h"
#include "Utility.h"
Config progConfig;
Patronus::Shaper * shaper = nullptr;
Lumos::Program * gProgram = nullptr;
WindowManager_base * winMan = nullptr;
Patronus::PhysicalWorld * world = nullptr;
Lumos::Instance * selectedInstance = nullptr;
std::string SCENE_FILE_DIR = "./scene_file/";
std::string TEXTURE_DIR = "./scene_file/texture/ut/";
std::string CAMERA_DIR = "./cameras/";






int main(int argc, char *argv[])
{
  bool isHeadless = false;
  if (argc > 1 and strcmp(argv[1], "-hl") == 0)
    isHeadless = true;

  if (isHeadless)
    winMan = new WindowManager_headless{800, 600};
  else
    winMan = new WindowManager{800, 600};

  world = new Patronus::PhysicalWorld();
  gProgram = new Lumos::Program( );
  shaper = new Patronus::Shaper( );

  gProgram->loadShaders( "./GLSL" );
  gProgram->preDrawSetUp();

  winMan->show();
  
  return winMan->loop();
}