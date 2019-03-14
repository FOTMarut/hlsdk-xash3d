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
#ifndef EVENT_API_H
#define EVENT_API_H

#include "pm_defs.h"

#define EVENT_API_VERSION	1

typedef const vec_t vec3_t_in[3];
typedef vec_t vec3_t_out[3];

typedef struct event_api_s
{
	int	version;
	void	( *EV_PlaySound )( int ent, vec3_t_in origin, int channel, const char *sample, float volume, float attenuation, int fFlags, int pitch );
	void	( *EV_StopSound )( int ent, int channel, const char *sample );
	int	( *EV_FindModelIndex )( const char *pmodel );
	int	( *EV_IsLocal )( int playernum );
	int	( *EV_LocalPlayerDucking )( void );
	void	( *EV_LocalPlayerViewheight )( vec3_t_out );
	void	( *EV_LocalPlayerBounds )( int hull, vec3_t_out mins, vec3_t_out maxs );
	int	( *EV_IndexFromTrace)( pmtrace_t *pTrace );
	physent_t *( *EV_GetPhysent )( int idx );
	void	( *EV_SetUpPlayerPrediction )( int dopred, int bIncludeLocalClient );
	void	( *EV_PushPMStates )( void );
	void	( *EV_PopPMStates )( void );
	void	( *EV_SetSolidPlayers )( int playernum );
	void	( *EV_SetTraceHull )( int hull );
	void	( *EV_PlayerTrace )( vec3_t_in start, vec3_t_in end, int traceFlags, int ignore_pe, pmtrace_t *tr );
	void	( *EV_WeaponAnimation )( int sequence, int body );
	unsigned short ( *EV_PrecacheEvent )( int type, const char* psz );
	void	( *EV_PlaybackEvent )( int flags, const edict_t *pInvoker, unsigned short eventindex, float delay, vec3_t_in origin, vec3_t_in angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );
	const char *( *EV_TraceTexture )( int ground, vec3_t_in vstart, vec3_t_in vend );
	void	( *EV_StopAllSounds )( int entnum, int entchannel );
	void	( *EV_KillEvents )( int entnum, const char *eventname );

	// Xash3D extension
	unsigned short (*EV_IndexForEvent)( const char *name );
	const char *(*EV_EventForIndex)( unsigned short index );
	void	( *EV_PlayerTraceExt )( vec3_t_in start, vec3_t_in end, int traceFlags, int (*pfnIgnore)( physent_t *pe ), pmtrace_t *tr );
	const char *(*EV_SoundForIndex)( int index );
	msurface_t *( *EV_TraceSurface )( int ground, vec3_t_in vstart, vec3_t_in vend );
} event_api_t;

#endif//EVENT_API_H
