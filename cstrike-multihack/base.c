#include "base.h"

//data
mem_module_t m_hw;
mem_module_t m_client;
mem_module_t m_libSDL2;

mem_voidptr_t p_SDL_GL_SwapWindow;
mem_voidptr_t p_SDL_GetKeyboardState;
mem_bytearray_t a_SDL_GL_SwapWindow;

demo_info_t*    p_g_rp;
kbutton_t*      p_in_jump;

mem_bool_t       enable_bunnyhop = mem_true;
cstrike_key_t    key_bunnyhop    = SDL_SCANCODE_SPACE;

mem_size_t       sz_hk_SDL_GL_SwapWindow = 5;
mem_detour_int_t di_hk_SDL_GL_SwapWindow = method5;

//functions
cstrike_keystate_t cstrike_get_keystate(cstrike_key_t key)
{
    return (cstrike_keystate_t)(((t_SDL_GetKeyboardState)p_SDL_GetKeyboardState)(NULL)[key]);
}