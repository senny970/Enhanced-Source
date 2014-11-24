//========= Copyright 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "hud.h"
#include "hud_crosshair.h"
#include "iclientmode.h"
#include "view.h"
#include "vgui_controls/controls.h"
#include "vgui/ISurface.h"
#include "IVRenderView.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern ConVar crosshair;
extern ConVar cl_observercrosshair;

using namespace vgui;


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CHudCrosshairTemplate : public CHudElement, public vgui::Panel
{
public:
	DECLARE_CLASS_SIMPLE( CHudCrosshairTemplate, vgui::Panel );

	CHudCrosshairTemplate( const char *name );

	//virtual void OnThink();
	virtual void Paint();
	virtual void Init();
	void VidInit( void );
	virtual bool ShouldDraw();
	virtual void ApplySchemeSettings( vgui::IScheme *scheme );

	//virtual void LevelShutdown( void );

private:

	CHudTexture		*m_pDefaultCrosshair;

	Color			m_clrCrosshair;
	QAngle			m_vecCrossHairOffsetAngle;

	QAngle			m_curViewAngles;
	Vector			m_curViewOrigin;
};

DECLARE_HUDELEMENT( CHudCrosshairTemplate );

CHudCrosshairTemplate::CHudCrosshairTemplate( const char *pName ) :
	vgui::Panel( NULL, "HudCrosshair2" ), CHudElement( pName )
{
	vgui::Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );

	SetHiddenBits( HIDEHUD_CROSSHAIR );
}

void CHudCrosshairTemplate::ApplySchemeSettings( IScheme *scheme )
{
	BaseClass::ApplySchemeSettings( scheme );

	SetPaintBackgroundEnabled( false );
}

void CHudCrosshairTemplate::Init()
{
}

void CHudCrosshairTemplate::VidInit()
{
	Init();

	m_pDefaultCrosshair = HudIcons().GetIcon("crosshair_default");
}


bool CHudCrosshairTemplate::ShouldDraw()
{
	if ( !m_pDefaultCrosshair )
		return false;

	C_BasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();
	if ( !pPlayer )
		return false;

	C_BaseCombatWeapon *pWeapon = pPlayer->GetActiveWeapon();
	if ( pWeapon && !pWeapon->ShouldDrawCrosshair() )
		return false;

	if ( !crosshair.GetBool() && !IsX360() )
		return false;

	return true;
}

void CHudCrosshairTemplate::Paint()
{
	if ( !m_pDefaultCrosshair )
		return;

	if ( !IsCurrentViewAccessAllowed() )
		return;

	int		xCenter	= ( ScreenWidth() - m_pDefaultCrosshair->Width() ) / 2;
	int		yCenter = ( ScreenHeight() - m_pDefaultCrosshair->Height() ) / 2;

	m_clrCrosshair = Color( 255, 255, 255, 255 );

	m_pDefaultCrosshair->DrawSelf( xCenter, yCenter, m_clrCrosshair );

}
