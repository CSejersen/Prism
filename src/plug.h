#ifndef PLUG_H
#define PLUG_H

extern void(*plugInit)();
extern void*(*plugSaveState)();
extern void(*plugLoadState)(void*);
extern void(*plugUpdate)();

#endif // PLUG_H

