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
//  cdll_int.h
//
// 4-23-98  
// JOHN:  client dll interface declarations
//
#pragma once
#ifndef CDLL_INT_H
#define CDLL_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "const.h"
#include "cvardef.h"
#include "con_nprint.h"
#include "cl_entity.h"
#include "pmtrace.h"
#include "com_model.h"
#include "event_args.h"
#include "screenfade.h"
#include "r_efx.h"
#include "event_api.h"
#include "demo_api.h"
#include "net_api.h"
#include "triangleapi.h"
#include "ivoicetweak.h"

#define MAX_ALIAS_NAME	32

typedef struct cmdalias_s cmdalias_t;
struct cmdalias_s
{
	cmdalias_t	*next;
	char		name[MAX_ALIAS_NAME];
	char		*value;
};

// this file is included by both the engine and the client-dll,
// so make sure engine declarations aren't done twice

typedef int HSPRITE;	// handle to a graphic
typedef int (*pfnUserMsgHook)( const char *pszName, int iSize, void *pbuf );

#include "wrect.h"

#define SCRINFO_SCREENFLASH	1
#define SCRINFO_STRETCHED	2

typedef struct SCREENINFO_s
{
	int		iSize;
	int		iWidth;
	int		iHeight;
	int		iFlags;
	int		iCharHeight;
	short		charWidths[256];
} SCREENINFO;

typedef struct client_data_s
{
	// fields that cannot be modified  (ie. have no effect if changed)
	vec3_t		origin;

	// fields that can be changed by the cldll
	vec3_t		viewangles;
	int		iWeaponBits;
	float		fov;		// field of view
} client_data_t;

typedef struct client_sprite_s
{
	char		szName[64];
	char		szSprite[64];
	int		hspr;
	int		iRes;
	wrect_t		rc;
} client_sprite_t;

typedef struct client_textmessage_s
{
	int		effect;
	byte		r1, g1, b1, a1;	// 2 colors for effects
	byte		r2, g2, b2, a2;
	float		x;
	float		y;
	float		fadein;
	float		fadeout;
	float		holdtime;
	float		fxtime;
	const char	*pName;
	const char	*pMessage;
} client_textmessage_t;

#if _MSC_VER == 1200
#define ulonglong_t __int64
#else
#define ulonglong_t unsigned long long
#endif

typedef struct hud_player_info_s
{
	char		*name;
	short		ping;
	byte		thisplayer;	// TRUE if this is the calling player

	// stuff that's unused at the moment,  but should be done
	byte		spectator;
	byte		packetloss;
	char		*model;
	short		topcolor;
	short		bottomcolor;

	ulonglong_t	m_nSteamID;
} hud_player_info_t;

typedef struct cl_enginefuncs_s
{
	// sprite handlers
	HSPRITE	(*pfnSPR_Load)( const char *szPicName );
	int	(*pfnSPR_Frames)( HSPRITE hPic );
	int	(*pfnSPR_Height)( HSPRITE hPic, int frame );
	int	(*pfnSPR_Width)( HSPRITE hPic, int frame );
	void	(*pfnSPR_Set)( HSPRITE hPic, int r, int g, int b );
	void	(*pfnSPR_Draw)( int frame, int x, int y, const wrect_t *prc );
	void	(*pfnSPR_DrawHoles)( int frame, int x, int y, const wrect_t *prc );
	void	(*pfnSPR_DrawAdditive)( int frame, int x, int y, const wrect_t *prc );
	void	(*pfnSPR_EnableScissor)( int x, int y, int width, int height );
	void	(*pfnSPR_DisableScissor)( void );
	client_sprite_t *(*pfnSPR_GetList)( const char *psz, int *piCount );

	// screen handlers
	void	(*pfnFillRGBA)( int x, int y, int width, int height, int r, int g, int b, int a );
	int	(*pfnGetScreenInfo)( SCREENINFO *pscrinfo );
	void	(*pfnSetCrosshair)( HSPRITE hspr, wrect_t rc, int r, int g, int b );

	// cvar handlers
	cvar_t *(*pfnRegisterVariable)( const char *szName, const char *szValue, int flags );
	float	(*pfnGetCvarFloat)( const char *szName );
	char*	(*pfnGetCvarString)( const char *szName );

	// command handlers
	int	(*pfnAddCommand)( const char *cmd_name, void (*function)(void) );
	int	(*pfnHookUserMsg)( const char *szMsgName, pfnUserMsgHook pfn );
	int	(*pfnServerCmd)( const char *szCmdString );
	int	(*pfnClientCmd)( const char *szCmdString );

	void	(*pfnGetPlayerInfo)( int ent_num, hud_player_info_t *pinfo );

	// sound handlers
	void	(*pfnPlaySoundByName)( const char *szSound, float volume );
	void	(*pfnPlaySoundByIndex)( int iSound, float volume );

	// vector helpers
	void	(*pfnAngleVectors)( const float *vecAngles, float *forward, float *right, float *up );

	// text message system
	client_textmessage_t *(*pfnTextMessageGet)( const char *pName );
	int	(*pfnDrawCharacter)( int x, int y, int number, int r, int g, int b );
	int	(*pfnDrawConsoleString)( int x, int y, const char *string );
	void	(*pfnDrawSetTextColor)( float r, float g, float b );
	void	(*pfnDrawConsoleStringLen)(  const char *string, int *length, int *height );

	void	(*pfnConsolePrint)( const char *string );
	void	(*pfnCenterPrint)( const char *string );

	// Added for user input processing
	int	(*GetWindowCenterX)( void );
	int	(*GetWindowCenterY)( void );
	void	(*GetViewAngles)( float * );
	void	(*SetViewAngles)( float * );
	int	(*GetMaxClients)( void );
	void	(*Cvar_SetValue)( const char *cvar, float value );

	int       (*Cmd_Argc)( void );	
	char	*(*Cmd_Argv)( int arg );
	void	(*Con_Printf)( const char *fmt, ... );
	void	(*Con_DPrintf)( const char *fmt, ... );
	void	(*Con_NPrintf)( int pos, const char *fmt, ... );
	void	(*Con_NXPrintf)( con_nprint_t *info, const char *fmt, ... );

	const char* (*PhysInfo_ValueForKey)( const char *key );
	const char* (*ServerInfo_ValueForKey)( const char *key );
	float	(*GetClientMaxspeed)( void );
	int	(*CheckParm)( const char *parm, const char **ppnext );

	void	(*Key_Event)( int key, int down );
	void	(*GetMousePosition)( int *mx, int *my );
	int	(*IsNoClipping)( void );

	cl_entity_t *(*GetLocalPlayer)( void );
	cl_entity_t *(*GetViewModel)( void );
	cl_entity_t *(*GetEntityByIndex)( int idx );

	float	(*GetClientTime)( void );
	void	(*V_CalcShake)( void );
	void	(*V_ApplyShake)( float *origin, float *angles, float factor );

	int	(*PM_PointContents)( float *point, int *truecontents );
	int	(*PM_WaterEntity)( float *p );
	pmtrace_t *(*PM_TraceLine)( float *start, float *end, int flags, int usehull, int ignore_pe );

	model_t *(*CL_LoadModel)( const char *modelname, int *index );
	int	(*CL_CreateVisibleEntity)( int type, cl_entity_t *ent );

	const model_t* (*GetSpritePointer)( HSPRITE hSprite );
	void	(*pfnPlaySoundByNameAtLocation)( const char *szSound, float volume, const float *origin );
	
	unsigned short (*pfnPrecacheEvent)( int type, const char* psz );
	void	(*pfnPlaybackEvent)( int flags, const edict_t *pInvoker, unsigned short eventindex, float delay, const float *origin, const float *angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2 );
	void	(*pfnWeaponAnim)( int iAnim, int body );
	float	(*pfnRandomFloat)( float flLow, float flHigh );	
	int	(*pfnRandomLong)( int lLow, int lHigh );
	void	(*pfnHookEvent)( const char *name, void ( *pfnEvent )( event_args_t *args ));
	int	(*Con_IsVisible) ();
	const char *(*pfnGetGameDirectory)( void );
	cvar_t *(*pfnGetCvarPointer)( const char *szName );
	const char *(*Key_LookupBinding)( const char *pBinding );
	const char *(*pfnGetLevelName)( void );
	void	(*pfnGetScreenFade)( screenfade_t *fade );
	void	(*pfnSetScreenFade)( screenfade_t *fade );
	void*	(*VGui_GetPanel)( );
	void	(*VGui_ViewportPaintBackground)( int extents[4] );

	byte*	(*COM_LoadFile)( const char *path, int usehunk, int *pLength );
	char*	(*COM_ParseFile)( const char *data, const char *token );
	void	(*COM_FreeFile)( void *buffer );

	triangleapi_t	*pTriAPI;
	efx_api_t		*pEfxAPI;
	event_api_t		*pEventAPI;
	demo_api_t		*pDemoAPI;
	net_api_t		*pNetAPI;
	IVoiceTweak		*pVoiceTweak;

	// returns 1 if the client is a spectator only (connected to a proxy), 0 otherwise or 2 if in dev_overview mode	
	int	(*IsSpectateOnly)( void );
	model_t *(*LoadMapSprite)( const char *filename );

	// file search functions
	void	 (*COM_AddAppDirectoryToSearchPath)( const char *pszBaseDir, const char *appName );
	int	 (*COM_ExpandFilename)( const char *fileName, char *nameOutBuffer, int nameOutBufferSize );

	// User info
	// playerNum is in the range (1, MaxClients)
	// returns NULL if player doesn't exit
	// returns "" if no value is set
	const char *( *PlayerInfo_ValueForKey )( int playerNum, const char *key );
	void	(*PlayerInfo_SetValueForKey )( const char *key, const char *value );

	// Gets a unique ID for the specified player. This is the same even if you see the player on a different server.
	// iPlayer is an entity index, so client 0 would use iPlayer=1.
	// Returns false if there is no player on the server in the specified slot.
	qboolean	(*GetPlayerUniqueID)(int iPlayer, const char playerID[16]);

	// TrackerID access
	int	(*GetTrackerIDForPlayer)(int playerSlot);
	int	(*GetPlayerForTrackerID)(int trackerID);

	// Same as pfnServerCmd, but the message goes in the unreliable stream so it can't clog the net stream
	// (but it might not get there).
	int	( *pfnServerCmdUnreliable )( const char *szCmdString );

	void	(*pfnGetMousePos)( struct tagPOINT *ppt );
	void	(*pfnSetMousePos)( int x, int y );
	void	(*pfnSetMouseEnable)( qboolean fEnable );

	// undocumented interface starts here
	cvar_t*	(*pfnGetFirstCvarPtr)( void );
	void*		(*pfnGetFirstCmdFunctionHandle)( void );
	void*		(*pfnGetNextCmdFunctionHandle)( void *cmdhandle );
	const char*	(*pfnGetCmdFunctionName)( void *cmdhandle );
	float		(*pfnGetClientOldTime)( void );
	float		(*pfnGetGravity)( void );
	model_t*	(*pfnGetModelByIndex)( int index );
	void		(*pfnSetFilterMode)( int mode ); // same as gl_texsort in original Quake
	void		(*pfnSetFilterColor)( float red, float green, float blue );
	void		(*pfnSetFilterBrightness)( float brightness );
	void		*(*pfnSequenceGet)( const char *fileName, const char *entryName );
	void		(*pfnSPR_DrawGeneric)( int frame, int x, int y, const wrect_t *prc, int blendsrc, int blenddst, int width, int height );
	void		*(*pfnSequencePickSentence)( const char *groupName, int pickMethod, int *entryPicked );
	int		(*pfnDrawString)( int x, int y, const char *str, int r, int g, int b );
	int		(*pfnDrawStringReverse)( int x, int y, const char *str, int r, int g, int b );
	const char	*(*LocalPlayerInfo_ValueForKey)( const char* key );
	int		(*pfnVGUI2DrawCharacter)( int x, int y, int ch, unsigned int font );
	int		(*pfnVGUI2DrawCharacterAdditive)( int x, int y, int ch, int r, int g, int b, unsigned int font );
	unsigned int	(*pfnGetApproxWavePlayLen)( const char *filename );
	void*		(*GetCareerGameUI)( void );	// g-cont. !!!! potential crash-point!
	void		(*Cvar_Set)( const char *name, const char *value );
	int		(*pfnIsPlayingCareerMatch)( void );
	void		(*pfnPlaySoundVoiceByName)( const char *szSound, float volume, int pitch );
	void		(*pfnPrimeMusicStream)( const char *filename, int looping );
	double		(*pfnSys_FloatTime)( void );

	// decay funcs
	void		(*pfnProcessTutorMessageDecayBuffer)( int *buffer, int buflen );
	void		(*pfnConstructTutorMessageDecayBuffer)( int *buffer, int buflen );
	void		(*pfnResetTutorMessageDecayData)( void );

	void		(*pfnPlaySoundByNameAtPitch)( const char *szSound, float volume, int pitch );
	void		(*pfnFillRGBABlend)( int x, int y, int width, int height, int r, int g, int b, int a );
	int		(*pfnGetAppID)( void );
	cmdalias_t	*(*pfnGetAliases)( void );
	void		(*pfnVguiWrap2_GetMouseDelta)( int *x, int *y );
} cl_enginefunc_t;

#define CLDLL_INTERFACE_VERSION	7

#ifdef __cplusplus
}
#endif

#endif//CDLL_INT_H
