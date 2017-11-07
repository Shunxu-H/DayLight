
/**
 * TO DO
 * x. TRY X11 HEADLESS SETUP 
 * x. BLIT THE MULTI SAMPLE BUFFER TO A REFULAR ONE AND READ FROM THERE
 * x. Anti aliasing for RGB images
 *  . Depth image -> more precise from 255
 * x. Compress the mask images
 *  . save the results to a new folder under ./build  --> experiments/build/results
 *  . skip the folders already existed  
 */
#include <string>
#include <iostream>


#include <opencv2/opencv.hpp>


#include "GL_include.h"
#include <EGL/egl.h>
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
std::string OUTPUT_DIR = "./output/";






int main(int argc, char *argv[])
{
  bool isHeadless = false;
  if (argc > 1 and strcmp(argv[1], "-hl") == 0)
    isHeadless = true;

  if (isHeadless)
    winMan = new WindowManager_headless{800, 600};
  else
    winMan = new WindowManager{800, 600};

  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  world = new Patronus::PhysicalWorld();
  gProgram = new Lumos::Program( );
  shaper = new Patronus::Shaper( );
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  gProgram->loadShaders( "./GLSL" );
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  gProgram->preDrawSetUp();

  winMan->show();
  
  return winMan->loop();
}