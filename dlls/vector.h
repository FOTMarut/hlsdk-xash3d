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
#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef float		vec_t;
typedef vec_t		vec2_t[2];
#ifndef DID_VEC3_T_DEFINE
#define DID_VEC3_T_DEFINE
class Vector;
typedef Vector		vec3_t;
#endif
typedef vec_t		vec4_t[4];	// x,y,z,w

//=========================================================
// 2DVector - used for many pathfinding and many other 
// operations that are treated as planar rather than 3d.
//=========================================================
class Vector2D
{
public:
	inline Vector2D(void): x( 0.0f ), y( 0.0f )			{ }
	inline Vector2D(vec_t X, vec_t Y): x( X ), y( Y )	{ }
	inline Vector2D operator+(const Vector2D& v) const	{ return Vector2D( x + v.x, y + v.y ); }
	inline Vector2D operator-(const Vector2D& v) const	{ return Vector2D( x - v.x, y - v.y ); }
	inline Vector2D operator*(vec_t fl) const			{ return Vector2D( x * fl, y * fl ); }
	inline Vector2D operator/(vec_t fl) const			{ return Vector2D( x / fl, y / fl ); }

	inline vec_t Length(void) const						{ return sqrtf(x * x + y * y ); }

	inline Vector2D Normalize( void ) const
	{
		vec_t flLen = Length();
		if( flLen == 0 )
			return Vector2D( 0.0f, 0.0f );
		else
		{
			flLen = 1 / flLen;
			return Vector2D( x * flLen, y * flLen );
		}
	}

	vec_t	x, y;
};

inline vec_t DotProduct( const Vector2D& a, const Vector2D& b ) { return( a.x * b.x + a.y * b.y ); }
inline Vector2D operator*( vec_t fl, const Vector2D& v ) { return v * fl; }

//=========================================================
// 3D Vector
//=========================================================
class Vector						// same data-layout as engine's vec3_t,
{									// which is a vec_t[3]
public:
	// Constructors
	inline Vector( void ): x( 0.0f ), y( 0.0f ), z( 0.0f ) { }
	inline Vector( vec_t X, vec_t Y, vec_t Z ): x( X ), y( Y ), z( Z ) { }
	//inline Vector( double X, double Y, double Z ): x( X ), y( Y ), z( Z ) { }
	//inline Vector( int X, int Y, int Z) : x( X ), y( Y ), z( Z ) { }
	inline Vector( const Vector& v ): x( v.x ), y( v.y ), z( v.z ) { } 
	inline Vector( vec_t rgfl[3] ): x( rgfl[0] ), y( rgfl[1] ), z( rgfl[2] ) { }

	inline Vector& operator=( const Vector& v )	 { memcpy(this, v, sizeof(*this)); return *this; };
//	inline Vector& operator=( const vec_t v[3] ) { return operator=( *reinterpret_cast<const Vector*>(v) ); };
	inline Vector& operator=( const vec_t v[3] ) { memcpy(this, v, sizeof(*this)); return *this; };

	// Operators
	inline Vector operator-( void ) const				{ return Vector( -x, -y, -z ); }
	inline bool operator==( const Vector& v ) const		{ return x == v.x && y == v.y && z == v.z; }
	inline bool operator!=( const Vector& v ) const		{ return !( *this == v ); }
	inline Vector operator+( const Vector& v ) const	{ return Vector( x + v.x, y + v.y, z + v.z ); }
	inline Vector operator-( const Vector& v ) const	{ return Vector( x - v.x, y - v.y, z - v.z ); }
	inline Vector operator*( vec_t fl ) const			{ return Vector( x * fl, y * fl, z * fl ); }
	inline Vector operator/( vec_t fl ) const			{ return Vector( x / fl, y / fl, z / fl ); }
	inline Vector& operator+=( const Vector& v )		{ x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector& operator-=( const Vector& v )		{ x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline Vector& operator*=( vec_t fl )				{ x *= fl; y *= fl; z *= fl; return *this; }
	inline Vector& operator/=( vec_t fl )				{ x /= fl; y /= fl; z /= fl; return *this; }

	// Methods
	inline void CopyToArray( vec_t* rgfl ) const		{ rgfl[0] = x, rgfl[1] = y, rgfl[2] = z; }
	inline vec_t Length( void ) const					{ return sqrtf( x * x + y * y + z * z ); }
	inline vec_t Length2D( void ) const					{ return sqrtf( x * x + y * y ); }
	inline bool IsZero() const							{ return x == 0 && y == 0 && z == 0; }
	operator vec_t *()									{ return &x; } // Vectors will now automatically convert to float * when needed
	operator const vec_t *() const						{ return &x; } // Vectors will now automatically convert to float * when needed
	inline Vector Normalize( void ) const
	{
		float flLen = Length();
		if( flLen == 0 )
			return Vector( 0.0f, 0.0f, 1.0f ); // Can't normalize a zero vector, so we return an arbitrary normal vector
		else
		{
			flLen = 1 / flLen;
			return Vector( x * flLen, y * flLen, z * flLen );
		}
	}

	inline Vector2D Make2D( void ) const { return Vector2D(x, y); }
	inline void Clear( void ) { x = 0.0f; y = 0.0f; z = 0.0f; }

	// Members
	vec_t x, y, z;
};
static inline Vector operator*( vec_t fl, const Vector& v ) { return v * fl; }
static inline vec_t DotProduct( const Vector& a, const Vector& b ) { return( a.x * b.x + a.y * b.y + a.z * b.z); }
static inline Vector CrossProduct( const Vector& a, const Vector& b ) { return Vector( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x ); }
#endif // VECTOR_H
