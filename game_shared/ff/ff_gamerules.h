//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: The TF Game rules object
//
// $Workfile:     $
// $Date: 2005/08/26 22:00:12 $
// $NoKeywords: $
//=============================================================================//

#ifndef FF_GAMERULES_H
#define FF_GAMERULES_H

#ifdef _WIN32
#pragma once
#endif


#include "teamplay_gamerules.h"
#include "convar.h"
#include "gamevars_shared.h"

#ifdef CLIENT_DLL
	#include "c_baseplayer.h"
#else
	#include "player.h"
	#include "ff_buildableobjects_shared.h"
#endif


#ifdef CLIENT_DLL
	#define CFFGameRules C_FFGameRules
	#define CFFGameRulesProxy C_FFGameRulesProxy
#endif


class CFFGameRulesProxy : public CGameRulesProxy
{
public:
	DECLARE_CLASS( CFFGameRulesProxy, CGameRulesProxy );
	DECLARE_NETWORKCLASS();
};


class CFFGameRules : public CTeamplayRules
{
public:
	DECLARE_CLASS( CFFGameRules, CTeamplayRules );

	virtual bool	ShouldCollide( int collisionGroup0, int collisionGroup1 );

	virtual int		PlayerRelationship(CBaseEntity *pPlayer, CBaseEntity *pTarget);
	virtual bool	FPlayerCanTakeDamage(CBasePlayer *pPlayer, CBaseEntity *pAttacker);

	virtual bool	IsTeamplay( void ) { return false;	}

	// Returns whether or not iTeam1 is allied to iTeam2
	int				IsTeam1AlliedToTeam2( int iTeam1, int iTeam2 );

#ifdef CLIENT_DLL

	DECLARE_CLIENTCLASS_NOBASE(); // This makes datatables able to access our private vars.

#else

	DECLARE_SERVERCLASS_NOBASE(); // This makes datatables able to access our private vars.
	
	CFFGameRules();
	virtual ~CFFGameRules();

	virtual void	RadiusDamage(const CTakeDamageInfo &info, const Vector &vecSrc, float flRadius, int iClassIgnore, CBaseEntity *pEntityIgnore);

	virtual float	FlPlayerFallDamage(CBasePlayer *pPlayer);
	virtual bool	FlPlayerFallDeathDoesScreenFade( CBasePlayer *pPlayer );
	virtual bool	ClientCommand( const char *pcmd, CBaseEntity *pEdict );
	virtual void	Think();
	virtual void	BuildableKilled( CFFBuildableObject *pObject, const CTakeDamageInfo& info );

	virtual const char *GetChatPrefix( bool bTeamOnly, CBasePlayer *pPlayer );
	virtual const char *GetChatLocation( bool bTeamOnly, CBasePlayer *pPlayer );

	virtual void	Precache();

private:

#endif

protected:

	// Prematch stuff
	void	StartGame();
	float	m_flGameStarted;
	float	m_flNextMsg;

public:
	bool HasGameStarted() { return !( m_flGameStarted < 0 ); }
};

//-----------------------------------------------------------------------------
// Gets us at the team fortress game rules
//-----------------------------------------------------------------------------

inline CFFGameRules* FFGameRules()
{
	return static_cast<CFFGameRules*>(g_pGameRules);
}


#endif // FF_GAMERULES_H
