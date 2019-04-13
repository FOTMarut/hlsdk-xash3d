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
#ifndef TRIANGLEAPI_H
#define TRIANGLEAPI_H

#include "mathlib.h"
#include "com_model.h"

typedef enum 
{
	TRI_FRONT = 0,
	TRI_NONE = 1
} TRICULLSTYLE;

#define TRI_API_VERSION	1

#define TRI_TRIANGLES	0
#define TRI_TRIANGLE_FAN	1
#define TRI_QUADS		2
#define TRI_POLYGON		3
#define TRI_LINES		4
#define TRI_TRIANGLE_STRIP	5
#define TRI_QUAD_STRIP	6
#define TRI_POINTS		7	// Xash3D added

typedef struct triangleapi_s
{
	int	version;

	void	(*RenderMode)( int mode );
	void	(*Begin)( int primitiveCode );
	void	(*End)( void );

	void	(*Color4f)( float r, float g, float b, float a );
	void	(*Color4ub)( unsigned char r, unsigned char g, unsigned char b, unsigned char a );
	void	(*TexCoord2f)( float u, float v );
	void	(*Vertex3fv)( vec3_t_in worldPnt );
	void	(*Vertex3f)( float x, float y, float z );
	void	(*Brightness)( float brightness );
	void	(*CullFace)( TRICULLSTYLE style );	
	int		(*SpriteTexture)( const model_t *pSpriteModel, int frame );
	int		(*WorldToScreen)( vec3_t_in world, vec3_t_out screen );  // Returns 1 if it's z clipped
	void	(*Fog)( float flFogColor[3], float flStart, float flEnd, int bOn ); //Works just like GL_FOG, flFogColor is r/g/b.
	void	(*ScreenToWorld)( vec3_t_in screen, vec3_t_out world  );
	void	(*GetMatrix)( const int pname, float *matrix );
	int		(*BoxInPVS)( vec3_t_in mins, vec3_t_in maxs );
	void	(*LightAtPoint)( vec3_t_in pos, float *value );
	void	(*Color4fRendermode)( float r, float g, float b, float a, int rendermode );
	void	(*FogParams)( float flDensity, int iFogSkybox );
} triangleapi_t;

#endif//TRIANGLEAPI_H
