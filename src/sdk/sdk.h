#pragma once
#ifndef CSTRIKE_MULTIHACK_SDK_H
#define CSTRIKE_MULTIHACK_SDK_H
#include "../main.h"

typedef struct { float _data[3]; } vec3_t;
typedef int qboolean;
typedef unsigned char byte;

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

typedef struct _Element
{
    float flTimeCreated;
    struct _Element *next;
    struct _Element *previous;
}Element;

typedef struct _Queue
{
    int count;
    int maxelements;
    float m_flDuration;
    Element *first;
    Element *last;
    Element *current;
}Queue;

typedef enum _resourcetype_t {t_sound, t_skin, t_model, t_decal, t_generic, t_eventscript, t_world} resourcetype_t;

typedef struct _resource_s
{
    char szFileName[64];
    resourcetype_t type;
    int nIndex;
    int nDownloadSize;
    unsigned char ucFlags;
    unsigned char rgucMD5_hash[16];
    unsigned char playernum;
    unsigned char rguc_reserved[32];
    struct _resource_s *pNext;
    struct _resource_s *pPrev;
}resource_s, resource_t;

typedef struct _screenfade_s
{
    float fadeSpeed;
    float fadeEnd;
    float fadeTotalEnd;
    float fadeReset;
    byte fader;
    byte fadeg;
    byte fadeb;
    byte fadealpha;
    int fadeFlags;
}screenfade_s, screenfade_t;

typedef struct _color24 {
    byte r;
    byte g;
    byte b;
}color24;

typedef struct _entity_state_s
{
    int entityType;
    int number;
    float msg_time;
    int messagenum;
    vec3_t origin;
    vec3_t angles;
    int modelindex;
    int sequence;
    float frame;
    int colormap;
    short skin;
    short solid;
    int effects;
    float scale;
    byte eflags;
    int rendermode;
    int renderamt;
    color24 rendercolor;
    int renderfx;
    int movetype;
    float animtime;
    float framerate;
    int body;
    unsigned char controller[4];
    unsigned char blending[4];
    vec3_t velocity;
    vec3_t mins;
    vec3_t maxs;
    int aiment;
    int owner;
    float friction;
    float gravity;
    int team;
    int playerclass;
    int health;
    qboolean spectator;
    int weaponmodel;
    int gaitsequence;
    vec3_t basevelocity;
    int usehull;
    int oldbuttons;
    int onground;
    int iStepLeft;
    float flFallVelocity;
    float fov;
    int weaponanim;
    vec3_t startpos;
    vec3_t endpos;
    float impacttime;
    float starttime;
    int iuser1;
    int iuser2;
    int iuser3;
    int iuser4;
    float fuser1;
    float fuser2;
    float fuser3;
    float fuser4;
    vec3_t vuser1;
    vec3_t vuser2;
    vec3_t vuser3;
    vec3_t vuser4;
}entity_state_s, entity_state_t;

typedef struct _clientdata_s
{
    vec3_t origin;
    vec3_t velocity;
    int viewmodel;
    vec3_t punchangle;
    int flags;
    int waterlevel;
    int watertype;
    vec3_t view_ofs;
    float health;
    int bInDuck;
    int weapons;
    int flTimeStepSound;
    int flDuckTime;
    int flSwimTime;
    int waterjumptime;
    float maxspeed;
    float fov;
    int weaponanim;
    int m_iId;
    int ammo_shells;
    int ammo_nails;
    int ammo_cells;
    int ammo_rockets;
    float m_flNextAttack;
    int tfstate;
    int pushmsec;
    int deadflag;
    char physinfo[256];
    int iuser1;
    int iuser2;
    int iuser3;
    int iuser4;
    float fuser1;
    float fuser2;
    float fuser3;
    float fuser4;
    vec3_t vuser1;
    vec3_t vuser2;
    vec3_t vuser3;
    vec3_t vuser4;
}clientdata_s, clientdata_t;

typedef struct _weapon_data_s
{
    int m_iId;
    int m_iClip;
    float m_flNextPrimaryAttack;
    float m_flNextSecondaryAttack;
    float m_flTimeWeaponIdle;
    int m_fInReload;
    int m_fInSpecialReload;
    float m_flNextReload;
    float m_flPumpTime;
    float m_fReloadTime;
    float m_fAimedDamage;
    float m_fNextAimBonus;
    int m_fInZoom;
    int m_iWeaponState;
    int iuser1;
    int iuser2;
    int iuser3;
    int iuser4;
    float fuser1;
    float fuser2;
    float fuser3;
    float fuser4;
}weapon_data_s;

typedef struct _packet_entities_t
{
    int num_entities;
    unsigned char flags[32];
    entity_state_s *entities;
}packet_entities_t;

typedef struct _frame_t {
    double receivedtime;
    double latency;
    qboolean invalid;
    qboolean choked;
    entity_state_s playerstate[32];
    double time;
    clientdata_t clientdata;
    weapon_data_s weapondata[64];
    packet_entities_t packet_entities;
    unsigned short clientbytes;
    unsigned short playerinfobytes;
    unsigned short packetentitybytes;
    unsigned short tentitybytes;
    unsigned short soundbytes;
    unsigned short eventbytes;
    unsigned short usrbytes;
    unsigned short voicebytes;
    unsigned short msgbytes;
}frame_t;

typedef struct _cmd_t {
    usercmd_t cmd;
    float senttime;
    float receivedtime;
    float frame_lerp;
    qboolean processedfuncs;
    qboolean heldback;
    int sendsize;
}cmd_t;

typedef struct _local_state_s
{
    entity_state_t playerstate;
    clientdata_t client;
    weapon_data_s weapondata[64];
}local_state_s, local_state_t;

typedef struct _event_s
{
    unsigned short index;
    const char *filename;
    int filesize;
    const char *pszScript;
}event_s;

typedef enum _modtype_t  {mod_brush, mod_sprite, mod_alias, mod_studio} modtype_t;
typedef enum _synctype_t {ST_SYNC, ST_RAND} synctype_t;

typedef struct _dmodel_t
{
    float mins[3];
    float maxs[3];
    float origin[3];
    int headnode[4];
    int visleafs;
    int firstface;
    int numfaces;
}dmodel_t;

typedef struct _mplane_s
{
    vec3_t normal;
    float dist;
    byte type;
    byte signbits;
    unsigned char pad[2];
}mplane_s, mplane_t;

typedef struct _mnode_s
{
    int contents;
    int visframe;
    float minmaxs[6];
    struct _mnode_s *parent;
    mplane_t *plane;
    struct _mnode_s *children[2];
    unsigned short firstsurface;
    unsigned short numsurfaces;
}mnode_s, mnode_t;

typedef struct _position_history_t {
    float animtime;
    vec3_t origin;
    vec3_t angles;
}position_history_t;

typedef struct _mouth_t
{
    byte mouthopen;
    byte sndcount;
    int sndavg;
}mouth_t;

typedef struct _latchedvars_t {
    float prevanimtime;
    float sequencetime;
    unsigned char prevseqblending[2];
    vec3_t prevorigin;
    vec3_t prevangles;
    int prevsequence;
    float prevframe;
    unsigned char prevcontroller[4];
    unsigned char prevblending[2];
}latchedvars_t;

typedef struct _colorVec
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
}colorVec;

typedef struct _glpoly_s
{
    struct _glpoly_s *next;
    struct _glpoly_s *chain;
    int numverts;
    int flags;
    float verts[4][7];
}glpoly_s, glpoly_t;

struct _msurface_s;

typedef struct _texture_s
{
    char name[16];
    unsigned int width;
    unsigned int height;
    int gl_texturenum;
    struct _msurface_s *texturechain;
    int anim_total;
    int anim_min;
    int anim_max;
    struct _texture_s *anim_next;
    struct _texture_s *alternate_anims;
    unsigned int offsets[4];
    byte *pPal;
}texture_s, texture_t;

typedef struct _mtexinfo_t
{
    float vecs[2][4];
    float mipadjust;
    texture_t *texture;
    int flags;
}mtexinfo_t;

typedef struct _decal_s
{
    struct _decal_s *pnext;
    struct _msurface_s *psurface;
    float dx;
    float dy;
    float scale;
    short texture;
    short flags;
    short entityIndex;
}decal_s, decal_t;

typedef struct _msurface_s
{
    int visframe;
    mplane_t *plane;
    int flags;
    int firstedge;
    int numedges;
    short texturemins[2];
    short extents[2];
    int light_s;
    int light_t;
    glpoly_t *polys;
    struct _msurface_s *texturechain;
    mtexinfo_t *texinfo;
    int dlightframe;
    int dlightbits;
    int lightmaptexturenum;
    unsigned char styles[4];
    int cached_light[4];
    qboolean cached_dlight;
    color24 *samples;
    decal_t *pdecals;
}msurface_s, msurface_t;

typedef struct _cache_user_s
{
    void *data;
}cache_user_s, cache_user_t;

typedef struct _sfx_s
{
    char name[64];
    cache_user_t cache;
    int servercount;
}sfx_s, sfx_t;

typedef struct _consistency_s
{
    char *filename;
    int issound;
    int orig_index;
    int value;
    int check_type;
    float mins[3];
    float maxs[3];
}consistency_s, consistency_t;

typedef unsigned int CRC32_t;

struct _efrags_s;

typedef struct _mleaf_s
{
    int contents;
    int visframe;
    float minmaxs[6];
    mnode_s *parent;
    byte *compressed_vis;
    struct _efrag_s *efrags;
    msurface_t **firstmarksurface;
    int nummarksurfaces;
    int key;
    unsigned char ambient_sound_level[4];
}mleaf_s, mleaf_t;

struct _cl_entity_s;

typedef struct _efrag_s
{
    mleaf_s *leaf;
    struct _efrag_s *leafnext;
    struct _cl_entity_s *entity;
    struct _efrag_s *entnext;
}efrag_s, efrag_t;

typedef struct _mvertex_t
{
    vec3_t position;
}mvertex_t;

typedef struct _medge_t
{
    unsigned short v[2];
    unsigned int cachededgeoffset;
}medge_t;

typedef struct _dclipnode_t
{
    int planenum;
    short children[2];
}dclipnode_t;

typedef struct _hull_s {
    dclipnode_t *clipnodes;
    mplane_t *planes;
    int firstclipnode;
    int lastclipnode;
    vec3_t clip_mins;
    vec3_t clip_maxs;
}hull_s, hull_t;

typedef struct _model_s
{
    char name[64];
    qboolean needload;
    modtype_t type;
    int numframes;
    synctype_t synctype;
    int flags;
    vec3_t mins;
    vec3_t maxs;
    float radius;
    int firstmodelsurface;
    int nummodelsurfaces;
    int numsubmodels;
    dmodel_t *submodels;
    int numplanes;
    mplane_t *planes;
    int numleafs;
    mleaf_t *leafs;
    int numvertexes;
    mvertex_t *vertexes;
    int numedges;
    medge_t *edges;
    int numnodes;
    mnode_t *nodes;
    int numtexinfo;
    mtexinfo_t *texinfo;
    int numsurfaces;
    msurface_t *surfaces;
    int numsurfedges;
    int *surfedges;
    int numclipnodes;
    dclipnode_t *clipnodes;
    int nummarksurfaces;
    msurface_t **marksurfaces;
    hull_s hulls[4];
    int numtextures;
    texture_t **textures;
    byte *visdata;
    color24 *lightdata;
    char *entities;
    cache_user_t cache;
}model_s, model_t;

typedef struct _cl_entity_s
{
    int index;
    qboolean player;
    entity_state_t baseline;
    entity_state_t prevstate;
    entity_state_t curstate;
    int current_position;
    position_history_t ph[64];
    mouth_t mouth;
    latchedvars_t latched;
    float lastmove;
    vec3_t origin;
    vec3_t angles;
    float attachment[4][3];
    int trivial_accept;
    model_s *model;
    efrag_s *efrag;
    mnode_s *topnode;
    float syncbase;
    int visframe;
    colorVec cvFloorColor;
}cl_entity_s, cl_entity_t;

typedef struct _dlight_s
{
    vec3_t origin;
    float radius;
    color24 color;
    float die;
    float decay;
    float minlight;
    int key;
    qboolean dark;
}dlight_s, dlight_t;

typedef unsigned long long uint64;

typedef struct _customization_s
{
    qboolean bInUse;
    resource_t resource;
    qboolean bTranslated;
    int nUserData1;
    int nUserData2;
    void *pInfo;
    void *pBuffer;
    struct _customization_s *pNext;
}customization_s, customization_t;

typedef struct _player_info_s
{
    int userid;
    char userinfo[256];
    char name[32];
    int spectator;
    int ping;
    int packet_loss;
    char model[64];
    int topcolor;
    int bottomcolor;
    int renderframe;
    int gaitsequence;
    float gaitframe;
    float gaityaw;
    vec3_t prevgaitorigin;
    customization_t customdata;
    char hashedcdkey[16];
    uint64 m_nSteamID;
}player_info_s, player_info_t;

typedef struct _event_args_s
{
    int flags;
    int entindex;
    float origin[3];
    float angles[3];
    float velocity[3];
    int ducking;
    float fparam1;
    float fparam2;
    int iparam1;
    int iparam2;
    int bparam1;
    int bparam2;
}event_args_s, event_args_t;

typedef struct _event_info_s {
    unsigned short index;
    short packet_index;
    short entity_index;
    float fire_time;
    event_args_t args;
    int flags;
}event_info_s, event_info_t;

typedef struct _event_state_s
{
    event_info_s ei[64];
}event_state_s, event_state_t;

typedef struct _client_state_t
{
    int max_edicts;
    resource_t resourcesonhand;
    resource_t resourcesneeded;
    resource_s resourcelist[1280];
    int num_resources;
    qboolean need_force_consistency_response;
    char serverinfo[512];
    int servercount;
    int validsequence;
    int parsecount;
    int parsecountmod;
    int stats[32];
    int weapons;
    usercmd_t cmd;
    vec3_t viewangles;
    vec3_t punchangle;
    vec3_t crosshairangle;
    vec3_t simorg;
    vec3_t simvel;
    vec3_t simangles;
    float predicted_origins[64][3];
    vec3_t prediction_error;
    float idealpitch;
    vec3_t viewheight;
    screenfade_t sf;
    qboolean paused;
    int onground;
    int moving;
    int waterlevel;
    int usehull;
    float maxspeed;
    int pushmsec;
    int light_level;
    int intermission;
    double mtime[2];
    double time;
    double oldtime;
    frame_t frames[64];
    cmd_t commands[64];
    local_state_s predicted_frames[64];
    int delta_sequence;
    int playernum;
    event_s event_precache[256];
    model_s *model_precache[512];
    int model_precache_count;
    sfx_s *sound_precache[512];
    consistency_s consistency_list[512];
    int num_consistency;
    int highentity;
    char levelname[40];
    int maxclients;
    int gametype;
    int viewentity;
    model_s *worldmodel;
    efrag_s *free_efrags;
    int num_entities;
    int num_statics;
    cl_entity_t viewent;
    int cdtrack;
    int looptrack;
    CRC32_t serverCRC;
    unsigned char clientdllmd5[16];
    float weaponstarttime;
    int weaponsequence;
    int fPrecaching;
    dlight_t *pLight;
    player_info_s players[32];
    entity_state_s instanced_baseline[64];
    int instanced_baseline_number;
    CRC32_t mapCRC;
    event_state_t events;
    char downloadUrl[128];
}client_state_t;

#endif