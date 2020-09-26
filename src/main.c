#include "main.h"
#include "base.h"

__attribute__((constructor))
void cstrike_multihack_startup()
{
    m_hw = mem_in_get_module(mem_string_new(s_m_hw));
    m_client = mem_in_get_module(mem_string_new(s_m_client));
    m_libSDL2 = mem_in_get_module(mem_string_new(s_m_libSDL2));
    if(
        mem_module_is_valid(&m_hw)      == mem_false ||
        mem_module_is_valid(&m_client)  == mem_false ||
        mem_module_is_valid(&m_libSDL2) == mem_false
    ) return;

    p_SDL_GL_SwapWindow    = mem_in_get_symbol(m_libSDL2, s_SDL_GL_SwapWindow);
    p_SDL_GetKeyboardState = mem_in_get_symbol(m_libSDL2, s_SDL_GeyKeyboardState);

    p_g_rp = (demo_info_t*)mem_in_get_symbol(m_hw, s_g_rp);
    p_in_jump = (kbutton_t*)mem_in_get_symbol(m_client, s_in_jump);
    p_in_duck = (kbutton_t*)mem_in_get_symbol(m_client, s_in_duck);
    p_g_ShellQueue = (Queue*)mem_in_get_symbol(m_client, s_g_ShellQueue);
    p_cl = (client_state_t*)mem_in_get_symbol(m_hw, s_cl);

    cstrike_hooks_startup();
}

__attribute__((destructor))
void cstrike_multihack_shutdown()
{
    cstrike_hooks_shutdown();
}