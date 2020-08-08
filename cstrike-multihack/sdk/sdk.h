#pragma once
#ifndef CSTRIKE_MULTIHACK_SDK_H
#define CSTRIKE_MULTIHACK_SDK_H
#include "../main.h"

typedef struct { float _data[3]; } vec3_t;
typedef int qboolean;

typedef struct _usercmd_s
{
    short lerp_msec;
    mem_byte_t msec;
    vec3_t viewangles;
    float forwardmove;
    float sidemove;
    float upmove;
    mem_byte_t lightlevel;
    unsigned short buttons;
    mem_byte_t impulse;
    mem_byte_t weaponselect;
    int impact_index;
    vec3_t impact_position;
}usercmd_s, usercmd_t;

typedef struct _movevars_s
{
    float gravity;
    float stopspeed;
    float maxspeed;
    float spectatormaxspeed;
    float accelerate;
    float airaccelerate;
    float wateraccelerate;
    float friction;
    float edgefriction;
    float waterfriction;
    float entgravity;
    float bounce;
    float stepsize;
    float maxvelocity;
    float zmax;
    float waveHeight;
    qboolean footsteps;
    char skyName[32];
    float rollangle;
    float rollspeed;
    float skycolor_r;
    float skycolor_g;
    float skycolor_b;
    float skyvec_x;
    float skyvec_y;
    float skyvec_z;
}movevars_s, movevars_t;

typedef struct _ref_params_s
{
    float vieworg[3];
    float viewangles[3];
    float forward[3];
    float right[3];
    float up[3];
    float frametime;
    float time;
    int intermission;
    int paused;
    int spectator;
    int onground;
    int waterlevel;
    float simvel[3];
    float simorg[3];
    float viewheight[3];
    float idealpitch;
    float cl_viewangles[3];
    int health;
    float crosshairangle[3];
    float viewsize;
    float punchangle[3];
    int maxclients;
    int viewentity;
    int playernum;
    int max_entities;
    int demoplayback;
    int hardware;
    int smoothing;
    usercmd_s *cmd;
    movevars_s *movevars;
    int viewport[4];
    int nextView;
    int onlyClientDraw;
}ref_params_s, ref_params_t;

typedef struct _demo_info_s
{
    float timestamp;
    ref_params_t rp;
    usercmd_t cmd;
    movevars_t movevars;
    vec3_t view;
    int viewmodel;
}demo_info_s, demo_info_t;

typedef struct _kbutton_s
{
    int down[2];
    int state;
}kbutton_s, kbutton_t;

#endif