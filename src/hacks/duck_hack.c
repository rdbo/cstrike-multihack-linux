#include "../base.h"

mem_bool_t b_jumped = mem_false;
mem_bool_t b_duck   = mem_false;

void cstrike_duck_hack()
{
    if(
        enable_duck_hack &&
        p_g_rp->rp.health > 0 &&
        cstrike_get_keystate(key_duck_hack) == cstrike_key_down &&
        cstrike_get_keystate(key_bunnyhop)      == cstrike_key_up
    ) {


        if(b_jumped == mem_false && b_duck == mem_false && p_g_rp->rp.onground)
        {
            if(p_in_duck->state != 4)
            {
                p_in_duck->state = 4;    
                return;
            }

            p_in_duck->state = 6;
            b_jumped = mem_true;
            return;
        }

        if(b_jumped == mem_true && !p_g_rp->rp.onground)
        {
            p_in_duck->state = 5;
            b_duck = mem_true;
            return;
        }

        if(b_jumped == mem_true && b_duck == mem_true && p_g_rp->rp.onground)
        {
            p_in_duck->state = 4;
            b_jumped         = mem_false;
            b_duck           = mem_false;
            return;
        }
    }

    else if(b_jumped == mem_true || b_duck == mem_true || p_g_rp->rp.health <= 0)
    {
        p_in_duck->state = 4;
        b_jumped = mem_false;
        b_duck   = mem_false;
    }
}