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
#ifndef CLIENT_H
#define CLIENT_H

#include "mathlib.h"
#include "edict.h"
#include "util.h"

extern void respawn( entvars_t *pev, BOOL fCopyCorpse );
extern BOOL ClientConnect( edict_t *pEntity, const char *pszName, const char *pszAddress, char szRejectReason[ 128 ] );
extern void ClientDisconnect( edict_t *pEntity );
extern void ClientKill( edict_t *pEntity );
extern void ClientPutInServer( edict_t *pEntity );
extern void ClientCommand( edict_t *pEntity );
extern void ClientUserInfoChanged( edict_t *pEntity, char *infobuffer );
extern void ServerActivate( edict_t *pEdictList, int edictCount, int clientMax );
extern void ServerDeactivate( void );
extern void StartFrame( void );
extern void PlayerPostThink( edict_t *pEntity );
extern void PlayerPreThink( edict_t *pEntity );
extern void ParmsNewLevel( void );
extern void ParmsChangeLevel( void );

extern void ClientPrecache( void );

extern const char *GetGameDescription( void );
extern void PlayerCustomization( edict_t *pEntity, customization_t *pCust );

extern void SpectatorConnect( edict_t *pEntity );
extern void SpectatorDisconnect( edict_t *pEntity );
extern void SpectatorThink( edict_t *pEntity );

extern void Sys_Error( const char *error_string );

extern void SetupVisibility( edict_t *pViewEntity, edict_t *pClient, unsigned char **pvs, unsigned char **pas );
extern void UpdateClientData( const edict_t *ent, int sendweapons, clientdata_t *cd );
extern int AddToFullPack( entity_state_t *state, int e, edict_t *ent, edict_t *host, int hostflags, int player, unsigned char *pSet );
extern void CreateBaseline( int player, int eindex, entity_state_t *baseline, edict_t *entity, int playermodelindex, vec3_t_in player_mins, vec3_t_in player_maxs );
extern void RegisterEncoders( void );

extern int GetWeaponData( edict_t *player, weapon_data_t *info );

extern void CmdStart( const edict_t *player, const usercmd_t *cmd, unsigned int random_seed );
extern void CmdEnd ( const edict_t *player );

extern int ConnectionlessPacket( const netadr_t *net_from, const char *args, char *response_buffer, int *response_buffer_size );

extern int GetHullBounds( int hullnumber, vec3_t_out mins, vec3_t_out maxs );

extern void CreateInstancedBaselines( void );

extern int InconsistentFile( const edict_t *player, const char *filename, char *disconnect_message );

extern int AllowLagCompensation( void );
#endif // CLIENT_H
