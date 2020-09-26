#include "../base.h"

mem_byte_t gw_hk_SDL_GL_SwapWindow[] =
{
    0x60,                     //pusha
    0xB8, 0x0, 0x0, 0x0, 0x0, //mov eax, 0x00000000
    0xFF, 0xD0,               //call eax
    0x61,                     //popa
    //original code
    0x8b, 0x1c, 0x24,         //mov ebx, [esp]
    0xc3                      //ret
};

void cstrike_hooks_startup()
{
    p_SDL_GL_SwapWindow = (mem_voidptr_t)((mem_uintptr_t)p_SDL_GL_SwapWindow + 4);
    mem_in_protect((mem_voidptr_t)gw_hk_SDL_GL_SwapWindow, sizeof(gw_hk_SDL_GL_SwapWindow), PROT_EXEC | PROT_READ | PROT_WRITE);
    *(mem_uint32_t*)((mem_uintptr_t)gw_hk_SDL_GL_SwapWindow + 2) = (mem_uint32_t)&hk_SDL_GL_SwapWindow;

    mem_in_detour((mem_voidptr_t)p_SDL_GL_SwapWindow, (mem_voidptr_t)gw_hk_SDL_GL_SwapWindow, sz_hk_SDL_GL_SwapWindow, di_hk_SDL_GL_SwapWindow, &a_SDL_GL_SwapWindow);
}

void cstrike_hooks_shutdown()
{
    mem_in_detour_restore((mem_voidptr_t)p_SDL_GL_SwapWindow, a_SDL_GL_SwapWindow, sz_hk_SDL_GL_SwapWindow);
}