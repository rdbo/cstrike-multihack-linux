#pragma once
#ifndef CSTRIKE_MULTIHACK_BASE_H
#define CSTRIKE_MULTIHACK_BASE_H
#include "main.h"
#include "sdk/sdk.h"

//defines
//-- strings/symbols
//---- modules
#define s_m_hw                 "/hw.so\n"
#define s_m_client             "/client.so\n"
#define s_m_libSDL2            "/libSDL2"
//---- hw.so
#define s_g_rp                 "g_rp"
//---- client.so
#define s_in_jump              "in_jump"
#define s_in_duck              "in_duck"
#define s_g_ShellQueue         "g_ShellQueue" //iShotsFired
#define s_cl                   "cl" //client state
//---- libSDL2*.so*
#define s_SDL_GeyKeyboardState "SDL_GetKeyboardState"
#define s_SDL_GL_SwapWindow    "SDL_GL_SwapWindow"
//-- etc
#define cstrike_key_up   0
#define cstrike_key_down 1

//types
typedef Uint8      cstrike_key_t;
typedef mem_bool_t cstrike_keystate_t;
typedef const Uint8*(* t_SDL_GetKeyboardState)(int* numkeys);

//data
extern mem_module_t m_hw;
extern mem_module_t m_client;
extern mem_module_t m_libSDL2;

extern mem_voidptr_t   p_SDL_GL_SwapWindow;
extern mem_voidptr_t   p_SDL_GetKeyboardState;
extern mem_bytearray_t a_SDL_GL_SwapWindow;

extern demo_info_t*    p_g_rp;
extern kbutton_t*      p_in_jump;
extern kbutton_t*      p_in_duck;
extern client_state_t* p_cl;
extern Queue*          p_g_ShellQueue;
extern int             old_shots_count;
extern vec3_t          old_punchangle;

extern mem_size_t       sz_hk_SDL_GL_SwapWindow;
extern mem_detour_t     di_hk_SDL_GL_SwapWindow;

extern mem_bool_t       enable_bunnyhop;
extern mem_bool_t       enable_rcs;
extern mem_bool_t       enable_duck_hack;
extern cstrike_key_t    key_bunnyhop;
extern cstrike_key_t    key_duck_hack;
//functions
//-- startup/shutdown
__attribute__((constructor)) void cstrike_multihack_startup();
__attribute__((destructor))  void cstrike_multihack_shutdown();

//-- hooks
void cstrike_hooks_startup();
void cstrike_hooks_shutdown();
void hk_SDL_GL_SwapWindow(void);

//-- hacks
void cstrike_hacks();
void cstrike_bunnyhop();
void cstrike_rcs();
void cstrike_duck_hack();
void cstrike_no_recoil();

//-- etc
cstrike_keystate_t cstrike_get_keystate(cstrike_key_t key);

#endif