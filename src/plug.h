#ifndef PLUG_H
#define PLUG_H

#include "env.h"

extern void(*plugInit)();
extern void*(*plugSaveState)();
extern void(*plugLoadState)(void*);
extern void(*plugUpdate)(Env*);
extern bool(*plugFinished)();

#endif // PLUG_H

