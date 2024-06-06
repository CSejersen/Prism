#include "plug.h"
#include <dlfcn.h>

void (*plugInit)() = nullptr;
void *(*plugSaveState)() = nullptr;
void (*plugLoadState)(void *) = nullptr;
void (*plugUpdate)() = nullptr;

