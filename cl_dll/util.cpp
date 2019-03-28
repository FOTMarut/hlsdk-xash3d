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
//
// util.cpp
//
// implementation of class-less helper functions
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "hud.h"
#include "cl_util.h"
#include <string.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

extern const vec3_t vec3_origin;

#ifdef _MSC_VER
#	if _MSC_VER < 1400
#		define strnlen(s,n) strlen(s)
#	endif

#	define strtof strtod
#else
#	include <stdint.h>
#endif

float Length( const Vector &v ) { return v.Length(); }

void VectorAngles( const Vector &forward, Vector &angles )
{
	float &pitch = angles.x, &yaw = angles.y, &roll = angles.z;

	if( forward.y == 0.0f && forward.x == 0.0f )
	{
		yaw = 0.0f;
		if( forward.z > 0.0f )
			pitch = 90.0f;
		else
			pitch = 270.0f;
	}
	else
	{
		yaw = ( atan2f( forward.y, forward.x ) * 180.0f / M_PI );
		if( yaw < 0.0f )
			yaw += 360.0f;

		float tmp = sqrtf( forward.x * forward.x + forward.y * forward.y );
		pitch = ( atan2f( forward.z, tmp ) * 180.0f / M_PI );
		if( pitch < 0.0f )
			pitch += 360.0f;
	}

	roll = 0.0f;
}

float VectorNormalize( Vector &v )
{
	vec_t length = v.Length();
	v = v.Normalize();
	return length;
//	float length, ilength;
//
//	length = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
//	length = sqrt( length );		// FIXME
//
//	if( length )
//	{
//		ilength = 1 / length;
//		v[0] *= ilength;
//		v[1] *= ilength;
//		v[2] *= ilength;
//	}
//
//	return length;
}

void VectorInverse( Vector &v )
{
	v = -v;
//	v[0] = -v[0];
//	v[1] = -v[1];
//	v[2] = -v[2];
}

void VectorScale( const Vector &in, vec_t scale, Vector &out )
{
	out = in * scale;
//	out[0] = in[0] * scale;
//	out[1] = in[1] * scale;
//	out[2] = in[2] * scale;
}

void VectorMA( const Vector &veca, vec_t scale, const Vector &vecb, Vector &vecc )
{
	vecc = veca + scale * vecb;
//	vecc[0] = veca[0] + scale * vecb[0];
//	vecc[1] = veca[1] + scale * vecb[1];
//	vecc[2] = veca[2] + scale * vecb[2];
}

HSPRITE LoadSprite( const char *pszName )
{
	int i;
	char sz[256];

	if( ScreenWidth < 640 )
		i = 320;
	else
		i = 640;

	sprintf( sz, pszName, i );

	return SPR_Load( sz );
}
