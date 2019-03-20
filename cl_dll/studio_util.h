//========= Copyright (c) 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#pragma once
#if !defined( STUDIO_UTIL_H )
#define STUDIO_UTIL_H

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

void	AngleMatrix( const Vector &angles, vec_t matrix[3][4] );
bool	VectorCompare( const Vector &v1, const Vector &v2 );
void	CrossProduct( const Vector &v1, const Vector &v2, Vector &cross );
void	VectorTransform( const Vector &in1, vec_t in2[3][4], Vector &out );
void	ConcatTransforms( const vec_t in1[3][4], const vec_t in2[3][4], vec_t out[3][4] );
void	MatrixCopy( vec_t in[3][4], vec_t out[3][4] );
void	QuaternionMatrix( vec4_t quaternion, vec_t matrix[3][4] );
void	QuaternionSlerp( const vec4_t p, vec4_t q, vec_t t, vec4_t qt );
void	AngleQuaternion( const Vector &angles, vec4_t quaternion );
#endif // STUDIO_UTIL_H
