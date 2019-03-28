//========= Copyright (c) 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

// eventscripts.h
#pragma once
#ifndef EVENTSCRIPTSH
#define EVENTSCRIPTSH

#include "vector.h"
#include "cl_util.h"

// defaults for clientinfo messages
#define	DEFAULT_VIEWHEIGHT	28
#define VEC_DUCK_VIEW 12

#define FTENT_FADEOUT			0x00000080

// Some of these are HL/TFC specific?
void EV_EjectBrass( const Vector &origin, const Vector &velocity, float rotation, int model, int soundtype );
void EV_GetGunPosition( event_args_t *args, Vector& pos, const Vector& origin );
void EV_GetDefaultShellInfo( event_args_t *args, const Vector &origin, const Vector &velocity, Vector &ShellVelocity, Vector &ShellOrigin, const Vector &forward, const Vector &right, const Vector &up, float forwardScale, float upScale, float rightScale );
qboolean EV_IsLocal( int idx );
qboolean EV_IsPlayer( int idx );
void EV_CreateTracer( const Vector &start, const Vector &end );

cl_entity_t *GetEntity( int idx );
cl_entity_t *GetViewEntity( void );
void EV_MuzzleFlash( void );
#endif // EVENTSCRIPTSH
