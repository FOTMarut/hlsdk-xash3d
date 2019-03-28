/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#pragma once
#ifndef PM_DEFS_H
#define PM_DEFS_H

#define MAX_PHYSENTS	600		// Must have room for all entities in the world.
#define MAX_MOVEENTS	64
#define MAX_CLIP_PLANES	5

#define PM_NORMAL		0x00000000
#define PM_STUDIO_IGNORE	0x00000001	// Skip studio models
#define PM_STUDIO_BOX	0x00000002	// Use boxes for non-complex studio models (even in traceline)
#define PM_GLASS_IGNORE	0x00000004	// Ignore entities with non-normal rendermode
#define PM_WORLD_ONLY	0x00000008	// Only trace against the world
#define PM_CUSTOM_IGNORE	0x00000010	// Ignore entities with SOLID_CUSTOM mode

// Values for flags parameter of PM_TraceLine
#define PM_TRACELINE_PHYSENTSONLY	0
#define PM_TRACELINE_ANYVISIBLE	1

#include "pm_info.h"

// PM_PlayerTrace results.
#include "pmtrace.h"
#include "pm_movevars.h"

#include "com_model.h"
#include "usercmd.h"
#include "mathlib.h"


// physent_t
typedef struct physent_s
{
	char		name[32];		// Name of model, or "player" or "world".
	int		player;
	vec3_t		origin;		// Model's origin in world coordinates.
	model_t	*model;		// only for bsp models
	model_t	*studiomodel;	// SOLID_BBOX, but studio clip intersections.
	vec3_t		mins, maxs;	// only for non-bsp models
	int		info;		// For client or server to use to identify (index into edicts or cl_entities)
	vec3_t		angles;		// rotated entities need this info for hull testing to work.

	int		solid;		// Triggers and func_door type WATER brushes are SOLID_NOT
	int		skin;		// BSP Contents for such things like fun_door water brushes.
	int		rendermode;	// So we can ignore glass

	// Complex collision detection.
	float		frame;
	int		sequence;
	byte		controller[4];
	byte		blending[2];

	int		movetype;
	int		takedamage;
	int		blooddecal;
	int		team;
	int		classnumber;

	// For mods
	int		iuser1;
	int		iuser2;
	int		iuser3;
	int		iuser4;
	float		fuser1;		// also contains pev->scale when "sv_allow_studio_scaling" is "1"
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;
} physent_t;

typedef struct playermove_s
{
	int		player_index;	// So we don't try to run the PM_CheckStuck nudging too quickly.
	qboolean		server;		// For debugging, are we running physics code on server side?

	qboolean		multiplayer;	// 1 == multiplayer server
	float		time;		// realtime on host, for reckoning duck timing
	float		frametime;	// Duration of this frame

	vec3_t		forward, right, up;	// Vectors for angles

	// player state
	vec3_t		origin;		// Movement origin.
	vec3_t		angles;		// Movement view angles.
	vec3_t		oldangles;	// Angles before movement view angles were looked at.
	vec3_t		velocity;		// Current movement direction.
	vec3_t		movedir;		// For waterjumping, a forced forward velocity so we can fly over lip of ledge.
	vec3_t		basevelocity;	// Velocity of the conveyor we are standing, e.g.
	
	// For ducking/dead
	vec3_t		view_ofs;		// Our eye position.
	float		flDuckTime;	// Time we started duck
	qboolean		bInDuck;		// In process of ducking or ducked already?
	
	// For walking/falling
	int		flTimeStepSound;	// Next time we can play a step sound
	int		iStepLeft;

	float		flFallVelocity;
	vec3_t		punchangle;

	float		flSwimTime;
	float		flNextPrimaryAttack;

	int		effects;		// MUZZLE FLASH, e.g.

	int		flags;		// FL_ONGROUND, FL_DUCKING, etc.
	int		usehull;		// 0 = regular player hull, 1 = ducked player hull, 2 = point hull
	float		gravity;		// Our current gravity and friction.
	float		friction;
	int		oldbuttons;	// Buttons last usercmd
	float		waterjumptime;	// Amount of time left in jumping out of water cycle.
	qboolean		dead;		// Are we a dead player?
	int		deadflag;
	int		spectator;	// Should we use spectator physics model?
	int		movetype;		// Our movement type, NOCLIP, WALK, FLY

	int		onground;
	int		waterlevel;
	int		watertype;
	int		oldwaterlevel;

	char		sztexturename[256];
	char		chtexturetype;

	float		maxspeed;
	float		clientmaxspeed;	// Player specific maxspeed

	// For mods
	int		iuser1;
	int		iuser2;
	int		iuser3;
	int		iuser4;
	float		fuser1;
	float		fuser2;
	float		fuser3;
	float		fuser4;
	vec3_t		vuser1;
	vec3_t		vuser2;
	vec3_t		vuser3;
	vec3_t		vuser4;

	// world state

	// Number of entities to clip against.
	int		numphysent;    
	physent_t		physents[MAX_PHYSENTS];

	// Number of momvement entities (ladders)
	int		nummoveent;
	// just a list of ladders
	physent_t		moveents[MAX_MOVEENTS];	

	// All things being rendered, for tracing against things you don't actually collide with
	int		numvisent;
	physent_t		visents[MAX_PHYSENTS];

	// input to run through physics.
	usercmd_t		cmd;

	// Trace results for objects we collided with.
	int		numtouch;
	pmtrace_t		touchindex[MAX_PHYSENTS];

	char		physinfo[MAX_PHYSINFO_STRING]; // Physics info string

	movevars_t	*movevars;
	vec3_t		player_mins[4];
	vec3_t		player_maxs[4];
	
	// Common functions
	const char	*(*PM_Info_ValueForKey) ( const char *s, const char *key );
	void		(*PM_Particle)( vec3_t_in origin, int color, float life, int zpos, int zvel );
	int		(*PM_TestPlayerPosition)( vec3_t_in pos, pmtrace_t *ptrace );
	void		(*Con_NPrintf)( int idx, char *fmt, ... );
	void		(*Con_DPrintf)( char *fmt, ... );
	void		(*Con_Printf)( char *fmt, ... );
	double		(*Sys_FloatTime)( void );
	void		(*PM_StuckTouch)( int hitent, pmtrace_t *ptraceresult );
	int		(*PM_PointContents)( vec3_t_in p, int *truecontents /*filled in if this is non-null*/ );
	int		(*PM_TruePointContents)( vec3_t_in p );
	int		(*PM_HullPointContents)( hull_t *hull, int num, vec3_t_in p );
#ifdef __MINGW32__
	pmtrace_t		*(*PM_PlayerTrace_real)( pmtrace_t * retvalue, vec3_t_in start, vec3_t_in end, int traceFlags, int ignore_pe );

#else
	pmtrace_t		(*PM_PlayerTrace)( vec3_t_in start, vec3_t_in end, int traceFlags, int ignore_pe );
#endif
	pmtrace_t	*(*PM_TraceLine)( vec3_t_in start, vec3_t_in end, int flags, int usehulll, int ignore_pe );
	int		(*RandomLong)( int lLow, int lHigh );
	float		(*RandomFloat)( float flLow, float flHigh );
	int		(*PM_GetModelType)( model_t *mod );
	void		(*PM_GetModelBounds)( model_t *mod, vec3_t_out mins, vec3_t_out maxs );
	void		*(*PM_HullForBsp)( physent_t *pe, vec3_t_out offset );
	float		(*PM_TraceModel)( physent_t *pEnt, vec3_t_in start, vec3_t_in end, trace_t *trace );
	int		(*COM_FileSize)( char *filename );
	byte		*(*COM_LoadFile)( char *path, int usehunk, int *pLength );
	void		(*COM_FreeFile)( void *buffer );
	char		*(*memfgets)( byte *pMemFile, int fileSize, int *pFilePos, char *pBuffer, int bufferSize );

	// Functions
	// Run functions for this frame?
	qboolean		runfuncs;
	void		(*PM_PlaySound)( int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch );
	const char	*(*PM_TraceTexture)( int ground, vec3_t_in vstart, vec3_t_in vend );
	void		(*PM_PlaybackEventFull)( int flags, int clientindex, unsigned short eventindex, float delay, vec3_t_in origin, vec3_t_in angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );
#ifdef __MINGW32__
	pmtrace_t		*(*PM_PlayerTraceEx_real) (pmtrace_t *retvalue, vec3_t_in start, vec3_t_in end, int traceFlags, int (*pfnIgnore)( physent_t *pe ));
#else
	pmtrace_t		(*PM_PlayerTraceEx) (vec3_t_in start, vec3_t_in end, int traceFlags, int (*pfnIgnore)( physent_t *pe ));
#endif
	int		(*PM_TestPlayerPositionEx) (vec3_t_in pos, pmtrace_t *ptrace, int (*pfnIgnore)( physent_t *pe ));
	pmtrace_t	*(*PM_TraceLineEx)( vec3_t_in start, vec3_t_in end, int flags, int usehulll, int (*pfnIgnore)( physent_t *pe ));
	msurface_t	*(*PM_TraceSurface)( int ground, vec3_t_in vstart, vec3_t_in vend );
} playermove_t;

#ifdef __MINGW32__
static pmtrace_t _pm_globalresult, _pm_globaltmp;
	static inline pmtrace_t PM_PlayerTrace_wrap( vec3_t_in start, vec3_t_in end, int traceFlags, int ignore_pe, playermove_t *pmove )
	{
		_pm_globaltmp = pmove->touchindex[MAX_PHYSENTS -1];
		pmove->PM_PlayerTrace_real( &_pm_globalresult, start, end, traceFlags, ignore_pe );
		return _pm_globalresult;
	}
	static inline pmtrace_t PM_PlayerTraceEx_wrap( vec3_t_in start, vec3_t_in end, int traceFlags, int (*pfnIgnore)( physent_t *pe ), playermove_t *pmove )
	{
		_pm_globaltmp = pmove->touchindex[MAX_PHYSENTS -1];
		pmove->PM_PlayerTraceEx_real( &_pm_globalresult, start, end, traceFlags, pfnIgnore );
		return _pm_globalresult;
	}
#define PM_PlayerTrace(a,b,c,d) touchindex[MAX_PHYSENTS -1] = PM_PlayerTrace_wrap( a, b, c, d, pmove );pmove->touchindex[MAX_PHYSENTS -1] = _pm_globaltmp
#define PM_PlayerTraceEx(a,b,c,d) touchindex[MAX_PHYSENTS -1] = PM_PlayerTraceEx_wrap( a, b, c, d, pmove );pmove->touchindex[MAX_PHYSENTS -1] = _pm_globaltmp
#endif

#endif//PM_DEFS_H
