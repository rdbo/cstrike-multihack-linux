#include "../base.h"

void cstrike_rcs()
{
    if(enable_rcs == mem_true)
    {
        const float rcs_val = 2;
        vec3_t punch = p_cl->punchangle;
        punch._data[0] *= rcs_val;
        punch._data[1] *= rcs_val;

        if(p_g_ShellQueue->count > 0)
        {
            vec3_t new_angles = (vec3_t){
                p_cl->viewangles._data[0] + old_punchangle._data[0] - punch._data[0],
                p_cl->viewangles._data[1] + old_punchangle._data[1] - punch._data[1],
                p_cl->viewangles._data[2] + old_punchangle._data[2] - punch._data[2]
            };

            if(new_angles._data[0] < -89)     new_angles._data[0] = -89;
            if(new_angles._data[0] > 89)      new_angles._data[0] = 89;

            while(new_angles._data[1] < -180) new_angles._data[1] += 360;
            while(new_angles._data[1] > 180)  new_angles._data[1] -= 360;

            p_cl->viewangles = new_angles;
        }

        old_punchangle = punch;
    }
}