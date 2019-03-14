/*
cdll_exp.h - exports for client
Copyright (C) 2013 Uncle Mike

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
#ifndef CDLL_EXP_H
#define CDLL_EXP_H

typedef const vec_t vec3_t_in[3];
typedef vec_t vec3_t_out[3];

// NOTE: ordering is important!
typedef struct cldll_func_s
{
	int	(*pfnInitialize)( cl_enginefunc_t *pEnginefuncs, int iVersion );
	void	(*pfnInit)( void );
	int	(*pfnVidInit)( void );
	int	(*pfnRedraw)( float flTime, int intermission );
	int	(*pfnUpdateClientData)( client_data_t *cdata, float flTime );
	void	(*pfnReset)( void );
	void	(*pfnPlayerMove)( playermove_t *ppmove, int server );
	void	(*pfnPlayerMoveInit)( playermove_t *ppmove );
	char	(*pfnPlayerMoveTexture)( char *name );
	void	(*IN_ActivateMouse)( void );
	void	(*IN_DeactivateMouse)( void );
	void	(*IN_MouseEvent)( int mstate );
	void	(*IN_ClearStates)( void );
	void	(*IN_Accumulate)( void );
	void	(*CL_CreateMove)( float frametime, usercmd_t *cmd, int active );
	int	(*CL_IsThirdPerson)( void );
	void	(*CL_CameraOffset)( vec3_t_out ofs );
	void	*(*KB_Find)( const char *name );
	void	(*CAM_Think)( void );		// camera stuff
	void	(*pfnCalcRefdef)( ref_params_t *pparams );
	int	(*pfnAddEntity)( int type, cl_entity_t *ent, const char *modelname );
	void	(*pfnCreateEntities)( void );
	void	(*pfnDrawNormalTriangles)( void );
	void	(*pfnDrawTransparentTriangles)( void );
	void	(*pfnStudioEvent)( const mstudioevent_t *event, const cl_entity_t *entity );
	void	(*pfnPostRunCmd)( local_state_t *from, local_state_t *to, usercmd_t *cmd, int runfuncs, double time, unsigned int random_seed );
	void	(*pfnShutdown)( void );
	void	(*pfnTxferLocalOverrides)( entity_state_t *state, const clientdata_t *client );
	void	(*pfnProcessPlayerState)( entity_state_t *dst, const entity_state_t *src );
	void	(*pfnTxferPredictionData)( entity_state_t *ps, const entity_state_t *pps, clientdata_t *pcd, const clientdata_t *ppcd, weapon_data_t *wd, const weapon_data_t *pwd );
	void	(*pfnDemo_ReadBuffer)( int size, byte *buffer );
	int	(*pfnConnectionlessPacket)( const netadr_t *net_from, const char *args, char *buffer, int *size );
	int	(*pfnGetHullBounds)( int hullnumber, vec3_t_out mins, vec3_t_out maxs );
	void	(*pfnFrame)( double time );
	int	(*pfnKey_Event)( int eventcode, int keynum, const char *pszCurrentBinding );
	void	(*pfnTempEntUpdate)( double frametime, double client_time, double cl_gravity, TEMPENTITY **ppTempEntFree, TEMPENTITY **ppTempEntActive, int ( *Callback_AddVisibleEntity )( cl_entity_t *pEntity ), void ( *Callback_TempEntPlaySound )( TEMPENTITY *pTemp, float damp ));
	cl_entity_t *(*pfnGetUserEntity)( int index );
	void	(*pfnVoiceStatus)( int entindex, qboolean bTalking );
	void	(*pfnDirectorMessage)( int iSize, void *pbuf );
	int	(*pfnGetStudioModelInterface)( int version, r_studio_interface_t **ppinterface, engine_studio_api_t *pstudio );
	void	(*pfnChatInputPosition)( int *x, int *y );
	int	(*pfnGetPlayerTeam)( int playerIndex );
	void	*(*pfnGetClientFactory)( void );
	// Xash3D extension
	int	(*pfnGetRenderInterface)( int version, render_api_t *renderfuncs, render_interface_t *callback );
	void	(*pfnClipMoveToEntity)( physent_t *pe, const vec3_t start, vec3_t mins, vec3_t maxs, const vec3_t end, pmtrace_t *tr );
} cldll_func_t;

#endif//CDLL_EXP_H
