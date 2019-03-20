//========= Copyright (c) 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#pragma once
#if !defined( DEMOH )
#define DEMOH

#include "const.h"

// Types of demo messages we can write/parse
enum
{
	TYPE_SNIPERDOT = 0,
	TYPE_ZOOM
};

void Demo_WriteBuffer( int type, int size, byte *buffer );

extern int g_demosniper;
extern int g_demosniperdamage;
extern Vector g_demosniperangles;
extern Vector g_demosniperorg;
extern float g_demozoom;
#endif
