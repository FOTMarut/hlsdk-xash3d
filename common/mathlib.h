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
// mathlib.h
#pragma once
#ifndef MATHLIB_H
#define MATHLIB_H
#include <math.h>
#include <string.h>

typedef float vec_t;
typedef vec_t vec2_t[2];
#ifdef __cplusplus
//class Vector;
extern "C++" {
#include "../dlls/vector.h" // TODO: sort this out
}
typedef Vector vec3_t;
#else
typedef vec_t vec3_t[3];
#endif
typedef vec_t vec4_t[4];	// x,y,z,w

typedef const vec_t vec3_t_in[3];
typedef vec_t vec3_t_out[3];
typedef vec_t matrix3x4[3][4];

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

extern const vec3_t vec3_origin;

#ifdef isfinite
#define	IS_NAN(x) (!isfinite(x))
#else
#define	nanmask (255<<23)
#define	IS_NAN(x) (((*(int *)&x)&nanmask)==nanmask)
#endif

static __inline vec_t DotProduct( const vec_t a[3], const vec_t b[3] ) { return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]); }
static __inline vec_t DotProduct4d( const vec_t a[4], const vec_t b[4] ) { return(a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]); }

static __inline void VectorSubtract( const vec_t a[3], const vec_t b[3], vec_t c[3]) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
static __inline void VectorAdd( const vec_t a[3], const vec_t b[3], vec_t c[3]) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
static __inline void VectorCopy( const vec_t a[3], vec_t b[3] ) { memcpy( b, a, 3 * sizeof(vec_t)); }
static __inline void VectorClear( vec_t a[3] ) { a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; }

void VectorMA (const vec_t veca[3], float scale, const vec_t vecb[3], vec_t vecc[3]);

int VectorCompare (const vec_t v1[3], const vec_t v2[3]);
float Length (const vec_t v[3]);
void CrossProduct (const vec_t v1[3], const vec_t v2[3], vec_t cross[3]);
float VectorNormalize (vec_t v[3]);		// returns vector length
void VectorInverse (vec_t v[3]);
void VectorScale (const vec_t in[3], vec_t scale, vec_t out[3]);

void R_ConcatRotations (float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms (matrix3x4 in1, matrix3x4 in2, matrix3x4 out);

void AngleVectors (const vec_t angles[3], vec_t forward[3], vec_t right[3], vec_t up[3]);
void AngleVectorsTranspose (const vec_t angles[3], vec_t forward[3], vec_t right[3], vec_t up[3]);
#define AngleIVectors	AngleVectorsTranspose

void AngleMatrix (const vec_t angles[3], matrix3x4 matrix );
void AngleIMatrix (const vec_t angles[3], matrix3x4 matrix );
void VectorTransform (const vec_t in1[3], matrix3x4 in2, vec_t out[3]);

//void NormalizeAngles( vec_t angles[3] );
//void InterpolateAngles( vec_t start[3], vec_t end[3], vec_t output[3], float frac );
//float AngleBetweenVectors( const vec_t v1[3], const vec_t v2[3] );

void VectorMatrix( vec_t forward[3], vec_t right[3], vec_t up[3]);
void VectorAngles( const vec_t forward[3], vec_t angles[3] );

//int InvertMatrix( const float * m, float *out );

//int BoxOnPlaneSide (vec_t emins[3], vec_t emaxs[3], mplane_t *plane);
float	anglemod(float a);

/*
#define BOX_ON_PLANE_SIDE(emins, emaxs, p)	\
	(((p)->type < 3)?						\
	(										\
		((p)->dist <= (emins)[(p)->type])?	\
			1								\
		:									\
		(									\
			((p)->dist >= (emaxs)[(p)->type])?\
				2							\
			:								\
				3							\
		)									\
	)										\
	:										\
		BoxOnPlaneSide( (emins), (emaxs), (p)))
*/

#endif // MATHLIB_H
