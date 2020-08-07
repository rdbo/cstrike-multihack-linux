#include "hack.h"

mem_void_t cstrike_hack()
{
    cstrike_bunnyhop();
}

const mem_byte_t gw_hk_SDL_GL_SwapWindow[] = {
    0x60,                     //pusha
    0xB8, 0x0, 0x0, 0x0, 0x0, //mov eax, 0x00000000
    0xFF, 0xD0,               //call eax
    0x61,                     //popa
    //original code
    0x8b, 0x1c, 0x24,         //mov ebx, [esp]
    0xc3                      //ret
};

mem_void_t cstrike_hack_init()
{
    m_hw      = mem_in_get_module(mem_string_new(s_m_hw));
    m_client  = mem_in_get_module(mem_string_new(s_m_client));
    m_libSDL2 = mem_in_get_module(mem_string_new(s_m_libSDL2));
    if(
        !mem_module_is_valid(&m_hw)     || 
        !mem_module_is_valid(&m_client) || 
        !mem_module_is_valid(&m_libSDL2)
    ) return;


    //definitions

    f_SDL_GL_GetProcAddress = (t_SDL_GL_GetProcAddress)dlsym(m_libSDL2.handle, s_SDL_GL_GetProcAddress);
    f_SDL_GetKeyboardState  = (t_SDL_GetKeyboardState)dlsym(m_libSDL2.handle, s_SDL_GetKeyboardState);
    p_SDL_GL_SwapWindow     = (mem_voidptr_t)dlsym(m_libSDL2.handle, s_SDL_GL_SwapWindow);
    p_SDL_GL_SwapWindow = (mem_voidptr_t)((mem_uintptr_t)p_SDL_GL_SwapWindow + 4);

    g_rp = (demo_info_t*)dlsym(m_hw.handle, s_g_rp);
    in_jump = (kbutton_t*)dlsym(m_client.handle, s_in_jump);

    //hooks

    mem_in_protect((mem_voidptr_t)gw_hk_SDL_GL_SwapWindow, (mem_size_t)sizeof(gw_hk_SDL_GL_SwapWindow), PROT_EXEC | PROT_READ | PROT_WRITE);
    *(mem_uint32_t*)((mem_uintptr_t)gw_hk_SDL_GL_SwapWindow + 2) = (mem_uint32_t)&cstrike_hack;
    mem_in_detour(p_SDL_GL_SwapWindow, (mem_voidptr_t)gw_hk_SDL_GL_SwapWindow, sz_hk_SDL_GL_SwapWindow, di_hk_SDL_GL_SwapWindow, NULL);
}

cstrike_key_state_t cstrike_get_key_state(cstrike_key_t key)
{
    const Uint8 *state = f_SDL_GetKeyboardState(NULL);
    return (cstrike_key_state_t)state[key];
}