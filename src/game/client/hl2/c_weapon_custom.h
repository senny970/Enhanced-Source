#ifndef	C_WEAPONCUSTOM_H
#define	C_WEAPONCUSTOM_H
#ifdef _WIN32
#pragma once
#endif
#include "hl2/c_basehlcombatweapon.h"

class C_WeaponCustom : public C_HLSelectFireMachineGun
{
	DECLARE_CLASS( C_WeaponCustom, C_HLSelectFireMachineGun );
public:
	DECLARE_PREDICTABLE();
	DECLARE_CLIENTCLASS();
	C_WeaponCustom() {}
	C_WeaponCustom( const char* className );

	char const				*GetClassname( void ) { return m_szClassName; }

private:
	C_WeaponCustom( const C_WeaponCustom & );
	int scopeNum;
	char m_szClassName[128];
};				

#endif	//WEAPONCUSTOM_H