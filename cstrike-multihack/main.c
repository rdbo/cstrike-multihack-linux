#include "hack.h"

__attribute__((constructor))
void dl_main()
{
    cstrike_hack_init();
}