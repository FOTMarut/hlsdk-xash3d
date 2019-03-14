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
#ifndef R_EFX_H
#define R_EFX_H

// particle_t
#if !defined( PARTICLEDEFH )  
#include "particledef.h"
#endif

// BEAM
#if !defined( BEAMDEFH )
#include "beamdef.h"
#endif

// dlight_t
#if !defined ( DLIGHTH )
#include "dlight.h"
#endif

// cl_entity_t
#if !defined( CL_ENTITYH )
#include "cl_entity.h"
#endif

/*
// FOR REFERENCE, These are the built-in tracer colors.  Note, color 4 is the one
// that uses the tracerred/tracergreen/tracerblue and traceralpha cvar settings
color24 gTracerColors[] =
{
	{ 255, 255, 255 },		// White
	{ 255, 0, 0 },		// Red
	{ 0, 255, 0 },		// Green
	{ 0, 0, 255 },		// Blue
	{ 0, 0, 0 },		// Tracer default, filled in from cvars, etc.
	{ 255, 167, 17 },		// Yellow-orange sparks
	{ 255, 130, 90 },		// Yellowish streaks (garg)
	{ 55, 60, 144 },		// Blue egon streak
	{ 255, 130, 90 },		// More Yellowish streaks (garg)
	{ 255, 140, 90 },		// More Yellowish streaks (garg)
	{ 200, 130, 90 },		// More red streaks (garg)
	{ 255, 120, 70 },		// Darker red streaks (garg)
};
*/

// Temporary entity array
#define TENTPRIORITY_LOW	0
#define TENTPRIORITY_HIGH	1

// TEMPENTITY flags
#define FTENT_NONE			0x00000000
#define FTENT_SINEWAVE		0x00000001
#define FTENT_GRAVITY		0x00000002
#define FTENT_ROTATE		0x00000004
#define FTENT_SLOWGRAVITY		0x00000008
#define FTENT_SMOKETRAIL		0x00000010
#define FTENT_COLLIDEWORLD		0x00000020
#define FTENT_FLICKER		0x00000040
#define FTENT_FADEOUT		0x00000080
#define FTENT_SPRANIMATE		0x00000100
#define FTENT_HITSOUND		0x00000200
#define FTENT_SPIRAL		0x00000400
#define FTENT_SPRCYCLE		0x00000800
#define FTENT_COLLIDEALL		0x00001000 // will collide with world and slideboxes
#define FTENT_PERSIST		0x00002000 // tent is not removed when unable to draw 
#define FTENT_COLLIDEKILL		0x00004000 // tent is removed upon collision with anything
#define FTENT_PLYRATTACHMENT		0x00008000 // tent is attached to a player (owner)
#define FTENT_SPRANIMATELOOP		0x00010000 // animating sprite doesn't die when last frame is displayed
#define FTENT_SPARKSHOWER		0x00020000
#define FTENT_NOMODEL		0x00040000 // Doesn't have a model, never try to draw ( it just triggers other things )
#define FTENT_CLIENTCUSTOM		0x00080000 // Must specify callback.  Callback function is responsible for killing tempent and updating fields ( unless other flags specify how to do things )
#define FTENT_SCALE			0x00100000 // An experiment

typedef struct tempent_s TEMPENTITY;
struct tempent_s
{
	int		flags;
	float		die;
	float		frameMax;
	float		x;
	float		y;
	float		z;
	float		fadeSpeed;
	float		bounceFactor;
	int		hitSound;
	void		(*hitcallback)( TEMPENTITY *ent, pmtrace_t *ptr );
	void		(*callback)( TEMPENTITY *ent, float frametime, float currenttime );
	TEMPENTITY	*next;
	int		priority;
	short		clientIndex;	// if attached, this is the index of the client to stick to
					// if COLLIDEALL, this is the index of the client to ignore
					// TENTS with FTENT_PLYRATTACHMENT MUST set the clientindex! 

	vec3_t		tentOffset;	// if attached, client origin + tentOffset = tent origin.
	cl_entity_t	entity;

	// baseline.origin		- velocity
	// baseline.renderamt	- starting fadeout intensity
	// baseline.angles		- angle velocity
};

typedef const vec_t vec3_t_in[3];
typedef vec_t vec3_t_out[3];

typedef struct efx_api_s
{
	particle_t	*(*R_AllocParticle)( void (*callback)( particle_t *particle, float frametime ));
	void		(*R_BlobExplosion)( vec3_t_in org );
	void		(*R_Blood)( vec3_t_in org, vec3_t_in dir, int pcolor, int speed );
	void		(*R_BloodSprite)( vec3_t_in org, int colorindex, int modelIndex, int modelIndex2, float size );
	void		(*R_BloodStream)( vec3_t_in org, vec3_t_in dir, int pcolor, int speed );
	void		(*R_BreakModel)( vec3_t_in pos, vec3_t_in size, vec3_t_in dir, float random, float life, int count, int modelIndex, char flags );
	void		(*R_Bubbles)( vec3_t_in mins, vec3_t_in maxs, float height, int modelIndex, int count, float speed );
	void		(*R_BubbleTrail)( vec3_t_in start, vec3_t_in end, float height, int modelIndex, int count, float speed );
	void		(*R_BulletImpactParticles)( vec3_t_in pos );
	void		(*R_EntityParticles)( cl_entity_t *ent );
	void		(*R_Explosion)( vec3_t_in pos, int model, float scale, float framerate, int flags );
	void		(*R_FizzEffect)( cl_entity_t *pent, int modelIndex, int density );
	void		(*R_FireField)( vec3_t_in org, int radius, int modelIndex, int count, int flags, float life );
	void		(*R_FlickerParticles)( vec3_t_in org );
	void		(*R_FunnelSprite)( vec3_t_in org, int modelIndex, int reverse );
	void		(*R_Implosion)( vec3_t_in end, float radius, int count, float life );
	void		(*R_LargeFunnel)( vec3_t_in org, int reverse );
	void		(*R_LavaSplash)( vec3_t_in org );
	void		(*R_MultiGunshot)( vec3_t_in org, vec3_t_in dir, vec3_t_in noise, int count, int decalCount, int *decalIndices );
	void		(*R_MuzzleFlash)( vec3_t_in pos1, int type );
	void		(*R_ParticleBox)( vec3_t_in mins, vec3_t_in maxs, unsigned char r, unsigned char g, unsigned char b, float life );
	void		(*R_ParticleBurst)( vec3_t_in pos, int size, int color, float life );
	void		(*R_ParticleExplosion)( vec3_t_in org );
	void		(*R_ParticleExplosion2)( vec3_t_in org, int colorStart, int colorLength );
	void		(*R_ParticleLine)( vec3_t_in start, vec3_t_in end, unsigned char r, unsigned char g, unsigned char b, float life );
	void		(*R_PlayerSprites)( int client, int modelIndex, int count, int size );
	void		(*R_Projectile)( vec3_t_in origin, vec3_t_in velocity, int modelIndex, int life, int owner, void (*hitcallback)( TEMPENTITY *ent, pmtrace_t *ptr ) );
	void		(*R_RicochetSound)( vec3_t_in pos );
	void		(*R_RicochetSprite)( vec3_t_in pos, model_t *pmodel, float duration, float scale );
	void		(*R_RocketFlare)( vec3_t_in pos );
	void		(*R_RocketTrail)( vec3_t_out start, vec3_t_in end, int type );
	void		(*R_RunParticleEffect)( vec3_t_in org, vec3_t_in dir, int color, int count );
	void		(*R_ShowLine)( vec3_t_in start, vec3_t_in end );
	void		(*R_SparkEffect)( vec3_t_in pos, int count, int velocityMin, int velocityMax );
	void		(*R_SparkShower)( vec3_t_in pos );
	void		(*R_SparkStreaks)( vec3_t_in pos, int count, int velocityMin, int velocityMax );
	void		(*R_Spray)( vec3_t_in pos, vec3_t_in dir, int modelIndex, int count, int speed, int spread, int rendermode );
	void		(*R_Sprite_Explode)( TEMPENTITY *pTemp, float scale, int flags );
	void		(*R_Sprite_Smoke)( TEMPENTITY *pTemp, float scale );
	void		(*R_Sprite_Spray)( vec3_t_in pos, vec3_t_in dir, int modelIndex, int count, int speed, int iRand );
	void		(*R_Sprite_Trail)( int type, vec3_t_in start, vec3_t_in end, int modelIndex, int count, float life, float size, float amplitude, int renderamt, float speed );
	void		(*R_Sprite_WallPuff)( TEMPENTITY *pTemp, float scale );
	void		(*R_StreakSplash)( vec3_t_in pos, vec3_t_in dir, int color, int count, float speed, int velocityMin, int velocityMax );
	void		(*R_TracerEffect)( vec3_t_in start, vec3_t_in end );
	void		(*R_UserTracerParticle)( vec3_t_in org, vec3_t_in vel, float life, int colorIndex, float length, unsigned char deathcontext, void (*deathfunc)( particle_t *particle ));
	particle_t	*(*R_TracerParticles)( vec3_t_in org, vec3_t_in vel, float life );
	void		(*R_TeleportSplash)( vec3_t_in org );
	void		(*R_TempSphereModel)( vec3_t_in pos, float speed, float life, int count, int modelIndex );
	TEMPENTITY	*(*R_TempModel)( vec3_t_in pos, vec3_t_in dir, vec3_t_in angles, float life, int modelIndex, int soundtype );
	TEMPENTITY	*(*R_DefaultSprite)( vec3_t_in pos, int spriteIndex, float framerate );
	TEMPENTITY	*(*R_TempSprite)( vec3_t_in pos, vec3_t_in dir, float scale, int modelIndex, int rendermode, int renderfx, float a, float life, int flags );
	int		(*Draw_DecalIndex)( int id );
	int		(*Draw_DecalIndexFromName)( char *name );
	void		(*R_DecalShoot)( int textureIndex, int entity, int modelIndex, vec3_t_in position, int flags );
	void		(*R_AttachTentToPlayer)( int client, int modelIndex, float zoffset, float life );
	void		(*R_KillAttachedTents)( int client );
	BEAM		*(*R_BeamCirclePoints)( int type, vec3_t_in start, vec3_t_in end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b );
	BEAM		*(*R_BeamEntPoint)( int startEnt, vec3_t_in end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b );
	BEAM		*(*R_BeamEnts)( int startEnt, int endEnt, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b );
	BEAM		*(*R_BeamFollow)( int startEnt, int modelIndex, float life, float width, float r, float g, float b, float brightness );
	void		(*R_BeamKill)( int deadEntity );
	BEAM		*(*R_BeamLightning)( vec3_t_in start, vec3_t_in end, int modelIndex, float life, float width, float amplitude, float brightness, float speed );
	BEAM		*(*R_BeamPoints)( vec3_t_in start, vec3_t_in end, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b );
	BEAM		*(*R_BeamRing)( int startEnt, int endEnt, int modelIndex, float life, float width, float amplitude, float brightness, float speed, int startFrame, float framerate, float r, float g, float b );
	dlight_t		*(*CL_AllocDlight)( int key );
	dlight_t		*(*CL_AllocElight)( int key );
	TEMPENTITY	*(*CL_TempEntAlloc)( vec3_t_in org, model_t *model );
	TEMPENTITY	*(*CL_TempEntAllocNoModel)( vec3_t_in org );
	TEMPENTITY	*(*CL_TempEntAllocHigh)( vec3_t_in org, model_t *model );
	TEMPENTITY	*(*CL_TentEntAllocCustom)( vec3_t_in origin, model_t *model, int high, void (*callback)( TEMPENTITY *ent, float frametime, float currenttime ));
	void		(*R_GetPackedColor)( short *packed, short color );
	short		(*R_LookupColor)( unsigned char r, unsigned char g, unsigned char b );
	void		(*R_DecalRemoveAll)( int textureIndex ); // textureIndex points to the decal index in the array, not the actual texture index.
	void		(*R_FireCustomDecal)( int textureIndex, int entity, int modelIndex, vec3_t_in position, int flags, float scale );
} efx_api_t;

#endif//R_EFX_H
