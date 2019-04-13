//========= Copyright (c) 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#pragma once
#if !defined( STUDIO_UTIL_H )
#define STUDIO_UTIL_H

#include "vector.h"
#include "mathlib.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

#ifndef PITCH
// MOVEMENT INFO
// up / down
#define	PITCH	0
// left / right
#define	YAW		1
// fall over
#define	ROLL	2
#endif

#define FDotProduct( a, b ) ( fabs( ( a[0] ) * ( b[0] ) ) + fabs( ( a[1] ) * ( b[1] ) ) + fabs( ( a[2] ) * ( b[2] ) ) )

void	AngleMatrix( const Vector &angles, matrix3x4 matrix );
bool	VectorCompare( const Vector &v1, const Vector &v2 );
void	CrossProduct( const Vector &v1, const Vector &v2, Vector &cross );
void	VectorTransform( const Vector &in1, matrix3x4 in2, Vector &out );
void	ConcatTransforms( const matrix3x4 in1, const matrix3x4 in2, matrix3x4 out );
void	MatrixCopy( matrix3x4 in, matrix3x4 out );
void	QuaternionMatrix( vec4_t quaternion, matrix3x4 matrix );
void	QuaternionSlerp( const vec4_t p, vec4_t q, vec_t t, vec4_t qt );
void	AngleQuaternion( const Vector &angles, vec4_t quaternion );
#endif // STUDIO_UTIL_H
