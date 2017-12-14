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
#ifndef EXTERN_H
#define EXTERN_H

#include "Config.h"
#include "Shaper.h"
#include "Program.h"
#include "WindowManager_base.h"
#include "PhysicalWorld.h"

extern Config progConfig;
extern Patronus::Shaper * shaper;
extern Lumos::Program *gProgram;
//extern std::vector<Lumos::Instance> drawingInstances;
extern WindowManager_base * winMan;
extern Patronus::PhysicalWorld * world;
extern Lumos::Instance * selectedInstance;
extern std::string SCENE_FILE_DIR;
extern std::string TEXTURE_DIR;
extern std::string CAMERA_DIR;
extern std::string OUTPUT_DIR;
extern std::string RENDER_LIST;

#endif // EXTERN_H
