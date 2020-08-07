#include "../hack.h"

mem_void_t cstrike_bunnyhop()
{
    if(cstrike_get_key_state(cstrike_key_bhop) == cstrike_key_down && g_rp->rp.health > 0 && g_rp->rp.onground)
        in_jump->state = 6;
}