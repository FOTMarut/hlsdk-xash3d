/*
com_model.h - cient model structures
Copyright (C) 2010 Uncle Mike

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#pragma once
#ifndef COM_MODEL_H
#define COM_MODEL_H

#include "bspfile.h"	// we need some declarations from it

typedef struct efrag_s	efrag_t;

#ifndef MATHLIB_H
typedef vec_t		vec2_t[2];
typedef vec_t		vec4_t[4];
#endif

/*
==============================================================================

	ENGINE MODEL FORMAT
==============================================================================
*/
#define STUDIO_RENDER	1
#define STUDIO_EVENTS	2

#define ZISCALE		((float)0x8000)

#define MIPLEVELS		4
#define VERTEXSIZE		7
#define MAXLIGHTMAPS	4
#define NUM_AMBIENTS	4		// automatic ambient sounds

typedef struct mplane_s				mplane_t;
typedef struct msurface_s			msurface_t;
typedef struct decal_s				decal_t;
typedef struct texture_s			texture_t;
typedef struct glvert_s				glvert_t;
typedef struct glpoly_s				glpoly_t;
typedef struct mnode_s				mnode_t;
typedef struct mleaf_s				mleaf_t;
typedef struct msurfmesh_s			msurfmesh_t;
typedef struct mextrasurf_s			mextrasurf_t;
typedef struct hull_s				hull_t;
typedef struct cache_user_s			cache_user_t;
typedef struct model_s				model_t;
typedef struct alight_s				alight_t;
typedef struct auxvert_s			auxvert_t;
typedef struct player_info_s 		player_info_t;
typedef struct mspriteframe_s		mspriteframe_t;
typedef struct mspritegroup_s		mspritegroup_t;
typedef struct mspriteframedesc_s	mspriteframedesc_t;
typedef struct msprite_s			msprite_t;

// model types
typedef enum
{
	mod_bad = -1,
	mod_brush, 
	mod_sprite, 
	mod_alias, 
	mod_studio
} modtype_t;

struct mplane_s
{
	vec3_t		normal;
	float		dist;
	byte		type;		// for fast side tests
	byte		signbits;		// signx + (signy<<1) + (signz<<1)
	byte		pad[2];
};

typedef struct
{
	vec3_t		position;
} mvertex_t;

typedef struct
{
	unsigned short	v[2];
	unsigned int	cachededgeoffset;
} medge_t;

struct texture_s
{
	char		name[16];
	unsigned int	width, height;
	int		gl_texturenum;
	msurface_t	*texturechain;	// for gl_texsort drawing
	int		anim_total;	// total tenths in sequence ( 0 = no)
	int		anim_min, anim_max;	// time for this frame min <=time< max
	texture_t	*anim_next;	// in the animation sequence
	texture_t	*alternate_anims;	// bmodels in frame 1 use these
	unsigned short	fb_texturenum;	// auto-luma texturenum
	unsigned short	dt_texturenum;	// detail-texture binding
	unsigned int	unused[3];	// reserved 
};

typedef struct
{
	float		vecs[2][4];	// [s/t] unit vectors in world space.
					// [i][3] is the s/t offset relative to the origin.
					// s or t = dot( 3Dpoint, vecs[i] ) + vecs[i][3]
	float		mipadjust;	// mipmap limits for very small surfaces
	texture_t		*texture;
	int		flags;		// sky or slime, no lightmap or 256 subdivision
} mtexinfo_t;

// 73 bytes per VBO vertex
// FIXME: align to 32 bytes
struct glvert_s
{
	vec3_t		vertex;		// position
	vec3_t		normal;		// normal
	vec2_t		stcoord;		// ST texture coords
	vec2_t		lmcoord;		// ST lightmap coords
	vec2_t		sccoord;		// ST scissor coords (decals only) - for normalmap coords migration
	vec3_t		tangent;		// tangent
	vec3_t		binormal;		// binormal
	byte		color[4];		// colors per vertex
};

struct glpoly_s
{
	glpoly_t	*next;
	glpoly_t	*chain;
	int		numverts;
	int		flags;          		// for SURF_UNDERWATER
	float		verts[4][VERTEXSIZE];	// variable sized (xyz s1t1 s2t2)
};

struct mnode_s
{
// common with leaf
	int		contents;		// 0, to differentiate from leafs
	int		visframe;		// node needs to be traversed if current

	float		minmaxs[6];	// for bounding box culling
	mnode_t	*parent;

// node specific
	mplane_t		*plane;
	mnode_t	*children[2];	

	unsigned short	firstsurface;
	unsigned short	numsurfaces;
};

// JAY: Compress this as much as possible
struct decal_s
{
	decal_t		*pnext;		// linked list for each surface
	msurface_t	*psurface;	// Surface id for persistence / unlinking
	float		dx;		// local texture coordinates
	float		dy;		// 
	float		scale;		// Pixel scale
	short		texture;		// Decal texture
	byte		flags;		// Decal flags  FDECAL_*
	short		entityIndex;	// Entity this is attached to
// Xash3D added
	vec3_t		position;		// location of the decal center in world space.
	vec3_t		saxis;		// direction of the s axis in world space
	msurfmesh_t	*mesh;		// decal mesh in local space
	int		reserved[4];	// for future expansions
};

struct mleaf_s
{
// common with node
	int		contents;
	int		visframe;		// node needs to be traversed if current

	float		minmaxs[6];	// for bounding box culling

	mnode_t	*parent;
// leaf specific
	byte		*compressed_vis;
	efrag_t	*efrags;

	msurface_t	**firstmarksurface;
	int		nummarksurfaces;
	byte		*compressed_pas;
	byte		ambient_sound_level[NUM_AMBIENTS];

};

struct msurface_s
{
	int		visframe;		// should be drawn when node is crossed

	mplane_t		*plane;		// pointer to shared plane
	int		flags;		// see SURF_ #defines

	int		firstedge;	// look up in model->surfedges[], negative numbers
	int		numedges;		// are backwards edges

	short		texturemins[2];
	short		extents[2];

	int		light_s, light_t;	// gl lightmap coordinates

	glpoly_t		*polys;		// multiple if warped
	msurface_t	*texturechain;

	mtexinfo_t	*texinfo;

	// lighting info
	int		dlightframe;	// last frame the surface was checked by an animated light
	int		dlightbits;	// dynamically generated. Indicates if the surface illumination
					// is modified by an animated light.

	int		lightmaptexturenum;
	byte		styles[MAXLIGHTMAPS];
	int		cached_light[MAXLIGHTMAPS];	// values currently used in lightmap
	msurface_t	*lightmapchain;		// for new dlights rendering (was cached_dlight)

	color24		*samples;		// note: this is the actual lightmap data for this surface
	decal_t		*pdecals;
};

struct msurfmesh_s
{
	unsigned short	numVerts;
	unsigned short	numElems;		// ~ 20 000 vertex per one surface. Should be enough
	unsigned int	startVert;	// user-variable. may be used for construct world single-VBO
	unsigned int	startElem;	// user-variable. may be used for construct world single-VBO

	glvert_t		*verts;		// vertexes array
	unsigned short	*elems;		// indices		

	msurface_t	*surf;		// pointer to parent surface. Just for consistency
	msurfmesh_t	*next;		// temporary chain of subdivided surfaces
};

// surface extradata stored in cache.data for all brushmodels
struct mextrasurf_s
{
	vec3_t		mins, maxs;
	vec3_t		origin;		// surface origin
	msurfmesh_t	*mesh;		// VBO\VA ready surface mesh. Not used by engine but can be used by mod-makers

	int		dlight_s, dlight_t;	// gl lightmap coordinates for dynamic lightmaps

	int		mirrortexturenum;	// gl texnum
	float		mirrormatrix[4][4];
	mextrasurf_t	*mirrorchain;	// for gl_texsort drawing
	mextrasurf_t	*detailchain;	// for detail textures drawing
	color24		*deluxemap;	// note: this is the actual deluxemap data for this surface

	int		reserved[32];	// just for future expansions or mod-makers
};

struct hull_s
{
	dclipnode_t	*clipnodes;
	mplane_t		*planes;
	int		firstclipnode;
	int		lastclipnode;
	vec3_t		clip_mins;
	vec3_t		clip_maxs;
};

#ifndef CACHE_USER
#define CACHE_USER
struct cache_user_s
{
	void		*data;		// extradata
};
#endif

struct model_s
{
	char		name[64];		// model name
	qboolean		needload;		// bmodels and sprites don't cache normally

	// shared modelinfo
	modtype_t		type;		// model type
	int		numframes;	// sprite's framecount
	byte		*mempool;		// private mempool (was synctype)
	int		flags;		// hl compatibility

//
// volume occupied by the model
//
	vec3_t		mins, maxs;	// bounding box at angles '0 0 0'
	float		radius;
    
	// brush model
	int		firstmodelsurface;
	int		nummodelsurfaces;

	int		numsubmodels;
	dmodel_t		*submodels;	// or studio animations

	int		numplanes;
	mplane_t		*planes;

	int		numleafs;		// number of visible leafs, not counting 0
	mleaf_t		*leafs;

	int		numvertexes;
	mvertex_t		*vertexes;

	int		numedges;
	medge_t		*edges;

	int		numnodes;
	mnode_t		*nodes;

	int		numtexinfo;
	mtexinfo_t	*texinfo;

	int		numsurfaces;
	msurface_t	*surfaces;

	int		numsurfedges;
	int		*surfedges;

	int		numclipnodes;
	dclipnode_t	*clipnodes;

	int		nummarksurfaces;
	msurface_t	**marksurfaces;

	hull_t		hulls[MAX_MAP_HULLS];

	int		numtextures;
	texture_t		**textures;

	byte		*visdata;

	color24		*lightdata;
	char		*entities;
//
// additional model data
//
	cache_user_t	cache;		// only access through Mod_Extradata
};

struct alight_s
{
	int		ambientlight;	// clip at 128
	int		shadelight;	// clip at 192 - ambientlight
	vec3_t		color;
	float			*plightvec;
};

struct auxvert_s
{
	float		fv[3];		// viewspace x, y
};

#define MAX_SCOREBOARDNAME	32
#define MAX_INFO_STRING	256

#include "custom.h"

struct player_info_s
{
	int		userid;			// User id on server
	char		userinfo[MAX_INFO_STRING];	// User info string
	char		name[MAX_SCOREBOARDNAME];	// Name (extracted from userinfo)
	int		spectator;		// Spectator or not, unused

	int		ping;
	int		packet_loss;

	// skin information
	char		model[64];
	int		topcolor;
	int		bottomcolor;

	// last frame rendered
	int		renderframe;	

	// Gait frame estimation
	int		gaitsequence;
	float		gaitframe;
	float		gaityaw;
	vec3_t		prevgaitorigin;

	customization_t	customdata;
};

//
// sprite representation in memory
//
typedef enum { SPR_SINGLE = 0, SPR_GROUP, SPR_ANGLED } spriteframetype_t;

struct mspriteframe_s
{
	int		width;
	int		height;
	float		up, down, left, right;
	int		gl_texturenum;
};

struct mspritegroup_s
{
	int		numframes;
	float		*intervals;
	mspriteframe_t	*frames[1];
};

struct mspriteframedesc_s
{
	spriteframetype_t	type;
	mspriteframe_t	*frameptr;
};

struct msprite_s
{
	short		type;
	short		texFormat;
	int		maxwidth;
	int		maxheight;
	int		numframes;
	int		radius;
	int		facecull;
	int		synctype;
	mspriteframedesc_t	frames[1];
};

#endif//COM_MODEL_H
