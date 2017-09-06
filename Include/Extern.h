#ifndef EXTERN_H
#define EXTERN_H

#include "Config.h"
#include "Shaper.h"
#include "Program.h"

extern Config progConfig;
extern Patronus::Shaper shaper;
extern Lumos::Program *gProgram;
extern std::vector<Lumos::Instance> drawingInstances;

#endif // EXTERN_H
