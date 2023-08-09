#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdbool.h>
#include <string.h> /* CLONE_VMT: memcpy */
#include <stdlib.h> /* CLONE_VMT: malloc */
#include <SDL2/SDL.h>
#include "util.h"
#include "sdk.h"

/* Module names for handlers */
#define CLIENT_SO     "./tf/bin/client.so"
#define ENGINE_SO     "./bin/engine.so"
#define MATSURFACE_SO "./bin/vguimatsurface.so"
#define SDL_SO        "./bin/libSDL2-2.0.so.0"

/* Signatures */
#define SIG_StartDrawing                                                    \
    "\xF3\x0F\x2A\xC0\xF3\x0F\x59\x45?\xF3\x0F\x2C\xC0\x89\x85????\xE8????" \
    "\x8D\x4D\xE4"

#define SIG_FinishDrawing \
    "\x89\x04\x24\xFF\x92????\x89\x34\x24\xE8????\x80\x7D\x97?\x0F\x85????"

/*
 * NOTE: For commented version, see:
 *   https://github.com/8dcc/hl-cheat/blob/main/src/include/hooks.h
 *   https://github.com/8dcc/bms-cheat/blob/main/src/include/hooks.h
 *
 * prefix  | meaning
 * --------+-------------------------------
 * h_*     | handler ptr (global scope)
 * i_*     | interface ptr (global scope)
 * oVMTi_* | original vmt pointer (will be replaced with our own vmt)
 * nVMTi_* | new vmt pointer allocated by us
 */
#define DECL_INTF(type, name)        \
    type* i_##name           = NULL; \
    VMT_##type* oVMTi_##name = NULL; \
    VMT_##type* nVMTi_##name = NULL;

#define DECL_INTF_EXTERN(type, name) \
    extern type* i_##name;           \
    extern VMT_##type* oVMTi_##name; \
    extern VMT_##type* nVMTi_##name;

#define DECL_SDL_FUNC(retType, name, ...)     \
    typedef retType (*name##_t)(__VA_ARGS__); \
    extern name##_t* name##Ptr;

#define CLONE_VMT(class, name)                                                \
    oVMT##name = name->vmt;                                                   \
    nVMT##name = malloc(vmt_size(name->vmt));                                 \
    if (!nVMT##name) {                                                        \
        fprintf(stderr, "CLONE_VMT: Could not allocate vmt for %s\n", #name); \
        return false;                                                         \
    }                                                                         \
    memcpy(nVMT##name, name->vmt, vmt_size(name->vmt));                       \
    name->vmt = nVMT##name;

#define RESTORE_VMT(class, name) \
    name->vmt = oVMT##name;      \
    free(nVMT##name);

/*----------------------------------------------------------------------------*/
/* Global variables */

extern void* h_client;
extern void* h_engine;
extern void* h_matsurface;
extern void* h_sdl2;

extern Entity* localplayer;

typedef void (*StartDrawing_t)(MatSurface*);
extern StartDrawing_t StartDrawing;
typedef void (*FinishDrawing_t)(MatSurface*);
extern FinishDrawing_t FinishDrawing;

DECL_SDL_FUNC(void, SwapWindow, SDL_Window* window);
DECL_SDL_FUNC(int, PollEvent, SDL_Event* event);

DECL_INTF_EXTERN(BaseClient, baseclient);
DECL_INTF_EXTERN(EngineClient, engine);
DECL_INTF_EXTERN(EntityList, entitylist);
DECL_INTF_EXTERN(EngineVGui, enginevgui);
DECL_INTF_EXTERN(MatSurface, surface);
DECL_INTF_EXTERN(ClientMode, clientmode);

/*----------------------------------------------------------------------------*/
/* Functions from globals.c */

bool globals_init(void);
bool resore_vtables(void);

#endif /* GLOBALS_H_ */
