#ifndef SDK_WEAPON_H_
#define SDK_WEAPON_H_

/* NOTE: This file is included from sdk.h and depends on its declarations */

typedef struct Weapon Weapon;

typedef struct {
    PAD(4 * 79);
    int (*GetIndex)(Weapon*); /* 79 */
    PAD(4 * 318);
    int (*GetSlot)(Weapon*); /* 398 */
    PAD(4 * 1);
    const char* (*GetName)(Weapon*); /* 400 */
    PAD(4 * 48);
    int (*GetWeaponId)(Weapon*);   /* 449 */
    int (*GetDamageType)(Weapon*); /* 450 */
    PAD(4 * 14);
    bool (*CalcIsAttackCriticalHelper)(Weapon*); /* 465 */
    PAD(4 * 28);
    bool (*CanFireCriticalShot)(Weapon*, bool bIsHeadshot); /* 494 */
    PAD(4 * 30);
    int (*GetSwingRange)(Weapon*); /* 525 */
} VMT_Weapon;

/* NOTE: Most of these offsets are from the game's NetVars, and have been dumped
 * using 8dcc/source-netvar-dumper. Until I figure out a good netvar system in
 * C, it might be a good idea to re-dump them on each game update. */
struct Weapon {
    VMT_Weapon* vmt;
    PAD(0x924);
    int m_iItemDefinitionIndex; /* 0x928 */
    PAD(0x10C);
    CBaseHandle hOwner; /* 0xA38 */
    PAD(0x10);
    float flNextPrimaryAttack; /* 0xA4C */
    PAD(0x1DC);
    float smackTime; /* 0xC2C, see CTFWeaponBaseMelee::ItemPostFrame() */
    PAD(0x10);
    bool bReadyToBackstab; /* 0xC40 */
};

static inline bool IsMedigunHealing(Weapon* w) {
	/* CWeaponMedigun->m_bHealing */
	const size_t offset = 0xC31;
	return *(bool*)((uint32_t)w + offset);
}

static inline CBaseHandle GetMedigunHealingHandler(Weapon* w) {
	/* CWeaponMedigun->m_hHealingTarget */
	const size_t offset = 0xC28;
	return *(CBaseHandle*)((uint32_t)w + offset) ;
}

static inline bool SniperCanHeadshot(Weapon* w) {
    return METHOD_ARGS(w, CanFireCriticalShot, true);
}

#endif /* SDK_WEAPON_H_ */
