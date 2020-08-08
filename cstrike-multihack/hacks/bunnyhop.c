#include "../base.h"

void cstrike_bunnyhop()
{
    if(
        enable_bunnyhop == mem_true &&
        cstrike_get_keystate(key_bunnyhop) == cstrike_key_down &&
        p_g_rp->rp.health > 0 &&
        p_g_rp->rp.onground
    ) p_in_jump->state = 6; //force jump
}