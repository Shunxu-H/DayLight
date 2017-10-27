#ifndef EXTERN_H
#define EXTERN_H

#include "Config.h"
#include "Shaper.h"
#include "Program.h"
#include "WindowManager.h"
#include "PhysicalWorld.h"

extern Config progConfig;
extern Patronus::Shaper * shaper;
extern Lumos::Program *gProgram;
//extern std::vector<Lumos::Instance> drawingInstances;
extern WindowManager * winMan;
extern Patronus::PhysicalWorld * world;
extern Lumos::Instance * selectedInstance;
extern std::string SCENE_FILE_DIR;
extern std::string TEXTURE_DIR;
extern std::string CAMERA_DIR;

#endif // EXTERN_H
