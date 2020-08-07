#include "hack.h"

//variables

//--modules
mem_module_t     m_libSDL2;
mem_module_t     m_client;
mem_module_t     m_hw;

//--game
demo_info_t*     g_rp;
kbutton_t*       in_jump;

//--functions
t_SDL_GL_GetProcAddress f_SDL_GL_GetProcAddress;
t_SDL_GetKeyboardState  f_SDL_GetKeyboardState;

//--etc
mem_voidptr_t    p_SDL_GL_SwapWindow     = (mem_voidptr_t)MEM_BAD_RETURN;
mem_size_t       sz_hk_SDL_GL_SwapWindow = 5;
mem_detour_int_t di_hk_SDL_GL_SwapWindow = method5;
cstrike_key_t    cstrike_key_bhop = SDL_SCANCODE_SPACE;