/*
The MIT License (MIT)

Copyright (c) 2016-2018, Shunxu Huang, shunxuhuang@gmail.com

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
#include <fstream>


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
#include "InputParser.h"
Config progConfig;
Patronus::Shaper * shaper = nullptr;
Lumos::Program * gProgram = nullptr;
WindowManager_base * winMan = nullptr;
Patronus::PhysicalWorld * world = nullptr;
Lumos::Instance * selectedInstance = nullptr;
std::string SCENE_FILE_DIR = "./scene_file/";
std::string TEXTURE_DIR = "./scene_file/texture/";
std::string CAMERA_DIR = "./cameras/";
std::string OUTPUT_DIR = "./output/";
std::string RENDER_LIST = "./obj_list.txt";

size_t WINDOW_HEIGHT = 600, WINDOW_WIDTH = 800;

/**
 * [displayHelp display help menu]
 */
void displayHelp(){
  std::ifstream ifs("./help.txt");
  if (ifs.is_open())
  {
    std::string line;
    while ( std::getline (ifs,line) )
    {
      std::cout << line << std::endl;
    }
    ifs.close();
  }
}

template <typename T>
void set(T & arg, T setTo, const std::string & var_name){
  std::cout << "Setting " << var_name << " to " << setTo << std::endl;
  arg = setTo;
}

/**
 * [parseCmdLn parase command line]
 * @param argc [argc from main()]
 * @param argv [argv from main()]
 */
void parseCmdLn(int argc, char *argv[]){
  InputParser parser(argc, argv);
  std::vector<std::string> vargs;

  if (parser.has(Flag::HELP)){
      displayHelp();
      exit( EXIT_SUCCESS );
  }

  if (parser.has(Flag::WINDOW_DIMENTSION)){
     vargs = parser.get(Flag::WINDOW_DIMENTSION).getArgs();
     if (vargs.size() != 2){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     set(WINDOW_WIDTH, (size_t)std::stoi(vargs[0].c_str()), "WINDOW_WIDTH");
     set(WINDOW_HEIGHT, (size_t)std::stoi(vargs[1].c_str()), "WINDOW_HEIGHT");
  }
  else
    std::cout << "Default WINDOW_HEIGHT is " << WINDOW_HEIGHT << std::endl
              << "Default WINDOW_HEIGHT is " << WINDOW_WIDTH << std::endl;


  if (parser.has(Flag::SCENE_DIRECTORY)){
     vargs = parser.get(Flag::SCENE_DIRECTORY).getArgs();
     if (vargs.size() != 1){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     set(SCENE_FILE_DIR, vargs[0], "SCENE_DIRECTORY");
  }
  else {
    std::cout << "Default SCENE_DIRECTORY is " << SCENE_FILE_DIR << std::endl;
  }

  if (parser.has(Flag::TEXTURE_DIRECTORY)){
     vargs = parser.get(Flag::TEXTURE_DIRECTORY).getArgs();
     if (vargs.size() != 1){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     set(TEXTURE_DIR, vargs[0], "TEXTURE_DIRECTORY");
  }
  else {
    std::cout << "Default TEXTURE_DIRECTORY is " << TEXTURE_DIR << std::endl;
  }

  if (parser.has(Flag::CAMERA_DIRECTORY)){
     vargs = parser.get(Flag::CAMERA_DIRECTORY).getArgs();
     if (vargs.size() != 1){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     set(CAMERA_DIR, vargs[0], "CAMERA_DIRECTORY");
  }
  else {
    std::cout << "Default CAMERA_DIRECTORY is " << CAMERA_DIR << std::endl;
  }

  if (parser.has(Flag::OUTPUT_DIRECTORY)){
     vargs = parser.get(Flag::OUTPUT_DIRECTORY).getArgs();
     if (vargs.size() != 1){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     set(OUTPUT_DIR, vargs[0], "OUTPUT_DIRECTORY");
  }
  else {
    std::cout << "Default OUTPUT_DIRECTORY is " << OUTPUT_DIR << std::endl;
  }

  if (parser.has(Flag::RENDER_LIST)){
     vargs = parser.get(Flag::RENDER_LIST).getArgs();
     if (vargs.size() != 1){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     set(RENDER_LIST, vargs[0], "RENDER_LIST");
  }
  else {
    std::cout << "Default RENDER_LIST is " << RENDER_LIST << std::endl;
  }

  if (parser.has(Flag::HEADLEASS))
    winMan = new WindowManager_headless{WINDOW_WIDTH, WINDOW_HEIGHT};
  else
    winMan = new WindowManager{WINDOW_WIDTH, WINDOW_HEIGHT};

  if (parser.has(Flag::LOAD_FILE)){
     vargs = parser.get(Flag::WINDOW_DIMENTSION).getArgs();
     if (vargs.size() != 1){
      displayHelp();
      exit( EXIT_FAILURE );
     }
     shaper = new Patronus::Shaper(vargs[0]);
  }
  else
    std::cout << "Load File unspecified, Loaded default" << std::endl;
}



#include "ArrayBuffer.h"

void test_within_test(const Lumos::ArrayBuffer & ab){
  Lumos::ArrayBuffer inner_ab(ab);
  int a = 1;
  a = a;
}

void test(){
  Lumos::ArrayBuffer ab1{};
  Lumos::ArrayBuffer ab2(ab1);
  Lumos::ArrayBuffer ab3 = ab2;
  Lumos::ArrayBuffer different_ab{};
  ab2 = different_ab;
  test_within_test(ab1);
}

int main(int argc, char *argv[])
{
  parseCmdLn(argc, argv);
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  // for physical simulartion
  world = new Patronus::PhysicalWorld();
  // openGL resource management
  gProgram = new Lumos::Program( );
  shaper = new Patronus::Shaper( "./data/indoor/0004dd3cb11e50530676f77b55262d38.obj" );

  gProgram->loadShaders( "./GLSL" );
  GLError( __PRETTY_FUNCTION__ , __LINE__ );

  gProgram->preDrawSetUp();

  winMan->show();
  // test();
  return winMan->loop();
}
