#ifndef SDK_ENUMS_H_
#define SDK_ENUMS_H_

/* NOTE: This file is included from sdk.h and depends on its declarations */

/* clang-format off */
enum {
    CONTENTS_EMPTY                = 0x0,
    CONTENTS_SOLID                = 0x1,
    CONTENTS_WINDOW               = 0x2,
    CONTENTS_AUX                  = 0x4,
    CONTENTS_GRATE                = 0x8,
    CONTENTS_SLIME                = 0x10,
    CONTENTS_WATER                = 0x20,
    CONTENTS_BLOCKLOS             = 0x40,
    CONTENTS_OPAQUE               = 0x80,
    LAST_VISIBLE_CONTENTS         = 0x80,
    ALL_VISIBLE_CONTENTS          = (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS - 1)),
    CONTENTS_TESTFOGVOLUME        = 0x100,
    CONTENTS_UNUSED               = 0x200,
    CONTENTS_UNUSED6              = 0x400,
    CONTENTS_TEAM1                = 0x800,
    CONTENTS_TEAM2                = 0x1000,
    CONTENTS_IGNORE_NODRAW_OPAQUE = 0x2000,
    CONTENTS_MOVEABLE             = 0x4000,
    CONTENTS_AREAPORTAL           = 0x8000,
    CONTENTS_PLAYERCLIP           = 0x10000,
    CONTENTS_MONSTERCLIP          = 0x20000,
    CONTENTS_CURRENT_0            = 0x40000,
    CONTENTS_CURRENT_90           = 0x80000,
    CONTENTS_CURRENT_180          = 0x100000,
    CONTENTS_CURRENT_270          = 0x200000,
    CONTENTS_CURRENT_UP           = 0x400000,
    CONTENTS_CURRENT_DOWN         = 0x800000,
    CONTENTS_ORIGIN               = 0x1000000,
    CONTENTS_MONSTER              = 0x2000000,
    CONTENTS_DEBRIS               = 0x4000000,
    CONTENTS_DETAIL               = 0x8000000,
    CONTENTS_TRANSLUCENT          = 0x10000000,
    CONTENTS_LADDER               = 0x20000000,
    CONTENTS_HITBOX               = 0x40000000,
};

#define MASK_ALL                   (0xFFFFFFFF)
#define MASK_SOLID                 (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_PLAYERSOLID           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCSOLID              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_WATER                 (CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define MASK_OPAQUE                (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS       (MASK_OPAQUE|CONTENTS_MONSTER)
#define MASK_BLOCKLOS              (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS     (MASK_BLOCKLOS|CONTENTS_MONSTER)
#define MASK_VISIBLE               (MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS      (MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_SHOT                  (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_HULL             (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL           (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY       (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY    (CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC        (CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_SPLITAREAPORTAL       (CONTENTS_WATER|CONTENTS_SLIME)
#define MASK_CURRENT               (CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define MASK_DEADSOLID             (CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)
/* clang-format on */

enum TraceType {
    TRACE_EVERYTHING = 0,
    TRACE_WORLD_ONLY,
    TRACE_ENTITIES_ONLY,
    TRACE_EVERYTHING_FILTER_PROPS,
};

/*----------------------------------------------------------------------------*/

enum EFontFlags {
    FONTFLAG_NONE         = 0x000,
    FONTFLAG_ITALIC       = 0x001,
    FONTFLAG_UNDERLINE    = 0x002,
    FONTFLAG_STRIKEOUT    = 0x004,
    FONTFLAG_SYMBOL       = 0x008,
    FONTFLAG_ANTIALIAS    = 0x010,
    FONTFLAG_GAUSSIANBLUR = 0x020,
    FONTFLAG_ROTARY       = 0x040,
    FONTFLAG_DROPSHADOW   = 0x080,
    FONTFLAG_ADDITIVE     = 0x100,
    FONTFLAG_OUTLINE      = 0x200,
    FONTFLAG_CUSTOM       = 0x400,
    FONTFLAG_BITMAP       = 0x800,
};

/* "drawType" argument in ISurface::DrawPrintText */
typedef enum {
    FONT_DRAW_DEFAULT = 0,
    FONT_DRAW_NONADDITIVE,
    FONT_DRAW_ADDITIVE,
    FONT_DRAW_TYPE_COUNT = 2,
} FontDrawType_t;

/* "curStage" argument for IBaseClientDLL::FrameStageNotify */
typedef enum {
    FRAME_UNDEFINED = -1,
    FRAME_START,
    FRAME_NET_UPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_START,
    FRAME_NET_UPDATE_POSTDATAUPDATE_END,
    FRAME_NET_UPDATE_END,
    FRAME_RENDER_START,
    FRAME_RENDER_END,
} ClientFrameStage_t;

/* "mode" argument of EngineVGui::Paint */
enum paint_modes {
    PAINT_UIPANELS     = (1 << 0),
    PAINT_INGAMEPANELS = (1 << 1),
    PAINT_CURSOR       = (1 << 2),
};

/*----------------------------------------------------------------------------*/

enum entity_flags {
    FL_ONGROUND              = (1 << 0),
    FL_DUCKING               = (1 << 1),
    FL_WATERJUMP             = (1 << 2),
    FL_ONTRAIN               = (1 << 3),
    FL_INRAIN                = (1 << 4),
    FL_FROZEN                = (1 << 5),
    FL_ATCONTROLS            = (1 << 6),
    FL_CLIENT                = (1 << 7),
    FL_FAKECLIENT            = (1 << 8),
    FL_INWATER               = (1 << 9),
    FL_FLY                   = (1 << 10),
    FL_SWIM                  = (1 << 11),
    FL_CONVEYOR              = (1 << 12),
    FL_NPC                   = (1 << 13),
    FL_GODMODE               = (1 << 14),
    FL_NOTARGET              = (1 << 15),
    FL_AIMTARGET             = (1 << 16),
    FL_PARTIALGROUND         = (1 << 17),
    FL_STATICPROP            = (1 << 18),
    FL_GRAPHED               = (1 << 19),
    FL_GRENADE               = (1 << 20),
    FL_STEPMOVEMENT          = (1 << 21),
    FL_DONTTOUCH             = (1 << 22),
    FL_BASEVELOCITY          = (1 << 23),
    FL_WORLDBRUSH            = (1 << 24),
    FL_OBJECT                = (1 << 25),
    FL_KILLME                = (1 << 26),
    FL_ONFIRE                = (1 << 27),
    FL_DISSOLVING            = (1 << 28),
    FL_TRANSRAGDOLL          = (1 << 29),
    FL_UNBLOCKABLE_BY_PLAYER = (1 << 30)
};

enum ETFClientClass {
    CClass_CTFWearableRazorback                  = 341,
    CClass_CTFWearableDemoShield                 = 338,
    CClass_CTFWearableLevelableItem              = 340,
    CClass_CTFWearableCampaignItem               = 337,
    CClass_CTFBaseRocket                         = 185,
    CClass_CTFWeaponBaseMerasmusGrenade          = 325,
    CClass_CTFWeaponBaseMelee                    = 324,
    CClass_CTFWeaponBaseGun                      = 323,
    CClass_CTFWeaponBaseGrenadeProj              = 322,
    CClass_CTFWeaponBase                         = 321,
    CClass_CTFWearableRobotArm                   = 342,
    CClass_CTFRobotArm                           = 287,
    CClass_CTFWrench                             = 344,
    CClass_CTFProjectile_ThrowableBreadMonster   = 279,
    CClass_CTFProjectile_ThrowableBrick          = 280,
    CClass_CTFProjectile_ThrowableRepel          = 281,
    CClass_CTFProjectile_Throwable               = 278,
    CClass_CTFThrowable                          = 319,
    CClass_CTFSyringeGun                         = 315,
    CClass_CTFKatana                             = 225,
    CClass_CTFSword                              = 314,
    CClass_CSniperDot                            = 118,
    CClass_CTFSniperRifleClassic                 = 308,
    CClass_CTFSniperRifleDecap                   = 309,
    CClass_CTFSniperRifle                        = 307,
    CClass_CTFChargedSMG                         = 197,
    CClass_CTFSMG                                = 306,
    CClass_CTFSlap                               = 305,
    CClass_CTFShovel                             = 304,
    CClass_CTFShotgunBuildingRescue              = 303,
    CClass_CTFPEPBrawlerBlaster                  = 241,
    CClass_CTFSodaPopper                         = 310,
    CClass_CTFShotgun_Revenge                    = 301,
    CClass_CTFScatterGun                         = 297,
    CClass_CTFShotgun_Pyro                       = 300,
    CClass_CTFShotgun_HWG                        = 299,
    CClass_CTFShotgun_Soldier                    = 302,
    CClass_CTFShotgun                            = 298,
    CClass_CTFRocketPack                         = 296,
    CClass_CTFCrossbow                           = 201,
    CClass_CTFRocketLauncher_Mortar              = 295,
    CClass_CTFRocketLauncher_AirStrike           = 293,
    CClass_CTFRocketLauncher_DirectHit           = 294,
    CClass_CTFRocketLauncher                     = 292,
    CClass_CTFRevolver                           = 286,
    CClass_CTFDRGPomson                          = 202,
    CClass_CTFRaygun                             = 284,
    CClass_CTFPistol_ScoutSecondary              = 246,
    CClass_CTFPistol_ScoutPrimary                = 245,
    CClass_CTFPistol_Scout                       = 244,
    CClass_CTFPistol                             = 243,
    CClass_CTFPipebombLauncher                   = 242,
    CClass_CTFWeaponPDA_Spy                      = 332,
    CClass_CTFWeaponPDA_Engineer_Destroy         = 331,
    CClass_CTFWeaponPDA_Engineer_Build           = 330,
    CClass_CTFWeaponPDAExpansion_Teleporter      = 334,
    CClass_CTFWeaponPDAExpansion_Dispenser       = 333,
    CClass_CTFWeaponPDA                          = 329,
    CClass_CTFParticleCannon                     = 239,
    CClass_CTFParachute_Secondary                = 238,
    CClass_CTFParachute_Primary                  = 237,
    CClass_CTFParachute                          = 236,
    CClass_CTFMinigun                            = 234,
    CClass_CTFMedigunShield                      = 231,
    CClass_CWeaponMedigun                        = 352,
    CClass_CTFProjectile_MechanicalArmOrb        = 263,
    CClass_CTFMechanicalArm                      = 230,
    CClass_CTFLunchBox_Drink                     = 229,
    CClass_CTFLunchBox                           = 228,
    CClass_CLaserDot                             = 78,
    CClass_CTFLaserPointer                       = 227,
    CClass_CTFKnife                              = 226,
    CClass_CTFGasManager                         = 212,
    CClass_CTFProjectile_JarGas                  = 261,
    CClass_CTFJarGas                             = 223,
    CClass_CTFProjectile_Cleaver                 = 254,
    CClass_CTFProjectile_JarMilk                 = 262,
    CClass_CTFProjectile_Jar                     = 260,
    CClass_CTFCleaver                            = 198,
    CClass_CTFJarMilk                            = 224,
    CClass_CTFJar                                = 222,
    CClass_CTFWeaponInvis                        = 328,
    CClass_CTFCannon                             = 196,
    CClass_CTFGrenadeLauncher                    = 216,
    CClass_CTFGrenadePipebombProjectile          = 217,
    CClass_CTFGrapplingHook                      = 215,
    CClass_CTFFlareGun_Revenge                   = 210,
    CClass_CTFFlareGun                           = 209,
    CClass_CTFFlameRocket                        = 207,
    CClass_CTFFlameThrower                       = 208,
    CClass_CTFFists                              = 205,
    CClass_CTFFireAxe                            = 204,
    CClass_CTFWeaponFlameBall                    = 327,
    CClass_CTFCompoundBow                        = 200,
    CClass_CTFClub                               = 199,
    CClass_CTFBuffItem                           = 195,
    CClass_CTFStickBomb                          = 312,
    CClass_CTFBreakableSign                      = 194,
    CClass_CTFBottle                             = 192,
    CClass_CTFBreakableMelee                     = 193,
    CClass_CTFBonesaw                            = 190,
    CClass_CTFBall_Ornament                      = 182,
    CClass_CTFStunBall                           = 313,
    CClass_CTFBat_Giftwrap                       = 188,
    CClass_CTFBat_Wood                           = 189,
    CClass_CTFBat_Fish                           = 187,
    CClass_CTFBat                                = 186,
    CClass_CTFProjectile_EnergyRing              = 256,
    CClass_CTFDroppedWeapon                      = 203, /* !!! */
    CClass_CTFWeaponSapper                       = 335,
    CClass_CTFWeaponBuilder                      = 326,
    CClass_C_TFWeaponBuilder                     = 0,
    CClass_CTFProjectile_Rocket                  = 264,
    CClass_CTFProjectile_Flare                   = 257,
    CClass_CTFProjectile_EnergyBall              = 255,
    CClass_CTFProjectile_GrapplingHook           = 258,
    CClass_CTFProjectile_HealingBolt             = 259,
    CClass_CTFProjectile_Arrow                   = 252,
    CClass_CMannVsMachineStats                   = 80,
    CClass_CTFTankBoss                           = 316,
    CClass_CTFBaseBoss                           = 183,
    CClass_CBossAlpha                            = 0,
    CClass_NextBotCombatCharacter                = 357,
    CClass_CTFProjectile_SpellKartBats           = 268,
    CClass_CTFProjectile_SpellKartOrb            = 269,
    CClass_CTFHellZap                            = 220,
    CClass_CTFProjectile_SpellLightningOrb       = 270,
    CClass_CTFProjectile_SpellTransposeTeleport  = 277,
    CClass_CTFProjectile_SpellMeteorShower       = 271,
    CClass_CTFProjectile_SpellSpawnBoss          = 274,
    CClass_CTFProjectile_SpellMirv               = 272,
    CClass_CTFProjectile_SpellPumpkin            = 273,
    CClass_CTFProjectile_SpellSpawnHorde         = 275,
    CClass_CTFProjectile_SpellSpawnZombie        = 276,
    CClass_CTFProjectile_SpellBats               = 266,
    CClass_CTFProjectile_SpellFireball           = 267,
    CClass_CTFSpellBook                          = 311,
    CClass_CHightower_TeleportVortex             = 74,
    CClass_CTeleportVortex                       = 160,
    CClass_CZombie                               = 354,
    CClass_CMerasmusDancer                       = 83,
    CClass_CMerasmus                             = 82,
    CClass_CHeadlessHatman                       = 73,
    CClass_CEyeballBoss                          = 48,
    CClass_CTFBotHintEngineerNest                = 191,
    CClass_CBotNPCMinion                         = 0,
    CClass_CBotNPC                               = 0,
    CClass_CPasstimeGun                          = 94,
    CClass_CTFViewModel                          = 320,
    CClass_CRobotDispenser                       = 112,
    CClass_CTFRobotDestruction_Robot             = 288,
    CClass_CTFReviveMarker                       = 285,
    CClass_CTFPumpkinBomb                        = 282,
    CClass_CTFProjectile_BallOfFire              = 253,
    CClass_CTFBaseProjectile                     = 184,
    CClass_CTFPointManager                       = 250,
    CClass_CBaseObjectUpgrade                    = 11,
    CClass_CTFRobotDestructionLogic              = 291,
    CClass_CTFRobotDestruction_RobotGroup        = 289,
    CClass_CTFRobotDestruction_RobotSpawn        = 290,
    CClass_CTFPlayerDestructionLogic             = 248,
    CClass_CPlayerDestructionDispenser           = 101,
    CClass_CTFMinigameLogic                      = 233,
    CClass_CTFHalloweenMinigame_FallingPlatforms = 219,
    CClass_CTFHalloweenMinigame                  = 218,
    CClass_CTFMiniGame                           = 232,
    CClass_CTFPowerupBottle                      = 251,
    CClass_CTFItem                               = 221,
    CClass_CHalloweenSoulPack                    = 71,
    CClass_CTFGenericBomb                        = 213,
    CClass_CBonusRoundLogic                      = 23,
    CClass_CTFGameRulesProxy                     = 211,
    CClass_CTETFParticleEffect                   = 179,
    CClass_CTETFExplosion                        = 178,
    CClass_CTETFBlood                            = 177,
    CClass_CTFFlameManager                       = 206,
    CClass_CHalloweenGiftPickup                  = 69,
    CClass_CBonusDuckPickup                      = 21,
    CClass_CHalloweenPickup                      = 70,
    CClass_CCaptureFlagReturnIcon                = 27,
    CClass_CCaptureFlag                          = 26,
    CClass_CBonusPack                            = 22,
    CClass_CTFTeam                               = 318,
    CClass_CTFTauntProp                          = 317,
    CClass_CTFPlayerResource                     = 249,
    CClass_CTFPlayer                             = 247, /* !!! */
    CClass_CTFRagdoll                            = 283,
    CClass_CTEPlayerAnimEvent                    = 165,
    CClass_CTFPasstimeLogic                      = 240,
    CClass_CPasstimeBall                         = 93,
    CClass_CTFObjectiveResource                  = 235,
    CClass_CTFGlow                               = 214,
    CClass_CTEFireBullets                        = 152,
    CClass_CTFBuffBanner                         = 0,
    CClass_CTFAmmoPack                           = 181, /* !!! */
    CClass_CObjectTeleporter                     = 89,  /* !!! */
    CClass_CObjectSentrygun                      = 88,  /* !!! */
    CClass_CTFProjectile_SentryRocket            = 265,
    CClass_CObjectSapper                         = 87,
    CClass_CObjectCartDispenser                  = 85,
    CClass_CObjectDispenser                      = 86, /* !!! */
    CClass_CMonsterResource                      = 84,
    CClass_CFuncRespawnRoomVisualizer            = 64,
    CClass_CFuncRespawnRoom                      = 63,
    CClass_CFuncPasstimeGoal                     = 61,
    CClass_CFuncForceField                       = 57,
    CClass_CCaptureZone                          = 28,
    CClass_CCurrencyPack                         = 31, /* !!! */
    CClass_CBaseObject                           = 10,
    CClass_CTestTraceline                        = 176,
    CClass_CTEWorldDecal                         = 180,
    CClass_CTESpriteSpray                        = 174,
    CClass_CTESprite                             = 173,
    CClass_CTESparks                             = 172,
    CClass_CTESmoke                              = 171,
    CClass_CTEShowLine                           = 169,
    CClass_CTEProjectedDecal                     = 167,
    CClass_CTEPlayerDecal                        = 166,
    CClass_CTEPhysicsProp                        = 164,
    CClass_CTEParticleSystem                     = 163,
    CClass_CTEMuzzleFlash                        = 162,
    CClass_CTELargeFunnel                        = 159,
    CClass_CTEKillPlayerAttachments              = 158,
    CClass_CTEImpact                             = 157,
    CClass_CTEGlowSprite                         = 156,
    CClass_CTEShatterSurface                     = 168,
    CClass_CTEFootprintDecal                     = 154,
    CClass_CTEFizz                               = 153,
    CClass_CTEExplosion                          = 151,
    CClass_CTEEnergySplash                       = 150,
    CClass_CTEEffectDispatch                     = 149,
    CClass_CTEDynamicLight                       = 148,
    CClass_CTEDecal                              = 146,
    CClass_CTEClientProjectile                   = 145,
    CClass_CTEBubbleTrail                        = 144,
    CClass_CTEBubbles                            = 143,
    CClass_CTEBSPDecal                           = 142,
    CClass_CTEBreakModel                         = 141,
    CClass_CTEBloodStream                        = 140,
    CClass_CTEBloodSprite                        = 139,
    CClass_CTEBeamSpline                         = 138,
    CClass_CTEBeamRingPoint                      = 137,
    CClass_CTEBeamRing                           = 136,
    CClass_CTEBeamPoints                         = 135,
    CClass_CTEBeamLaser                          = 134,
    CClass_CTEBeamFollow                         = 133,
    CClass_CTEBeamEnts                           = 132,
    CClass_CTEBeamEntPoint                       = 131,
    CClass_CTEBaseBeam                           = 130,
    CClass_CTEArmorRicochet                      = 129,
    CClass_CTEMetalSparks                        = 161,
    CClass_CSteamJet                             = 123,
    CClass_CSmokeStack                           = 117,
    CClass_DustTrail                             = 355,
    CClass_CFireTrail                            = 50,
    CClass_SporeTrail                            = 362,
    CClass_SporeExplosion                        = 361,
    CClass_RocketTrail                           = 359,
    CClass_SmokeTrail                            = 360,
    CClass_CPropVehicleDriveable                 = 108,
    CClass_ParticleSmokeGrenade                  = 358,
    CClass_CParticleFire                         = 90,
    CClass_MovieExplosion                        = 356,
    CClass_CTEGaussExplosion                     = 155,
    CClass_CEnvQuadraticBeam                     = 43,
    CClass_CEmbers                               = 36,
    CClass_CEnvWind                              = 47,
    CClass_CPrecipitation                        = 107,
    CClass_CBaseTempEntity                       = 17,
    CClass_CWeaponIFMSteadyCam                   = 351,
    CClass_CWeaponIFMBaseCamera                  = 350,
    CClass_CWeaponIFMBase                        = 349,
    CClass_CTFWearableVM                         = 343,
    CClass_CTFWearable                           = 336,
    CClass_CTFWearableItem                       = 339,
    CClass_CEconWearable                         = 35,
    CClass_CBaseAttributableItem                 = 3,
    CClass_CEconEntity                           = 34,
    CClass_CHandleTest                           = 72,
    CClass_CTeamplayRoundBasedRulesProxy         = 126,
    CClass_CTeamRoundTimer                       = 127,
    CClass_CSpriteTrail                          = 122,
    CClass_CSpriteOriented                       = 121,
    CClass_CSprite                               = 120,
    CClass_CRagdollPropAttached                  = 111,
    CClass_CRagdollProp                          = 110,
    CClass_CPoseController                       = 106,
    CClass_CGameRulesProxy                       = 68,
    CClass_CInfoLadderDismount                   = 75,
    CClass_CFuncLadder                           = 58,
    CClass_CEnvDetailController                  = 40,
    CClass_CWorld                                = 353,
    CClass_CWaterLODControl                      = 348,
    CClass_CWaterBullet                          = 347,
    CClass_CVoteController                       = 346,
    CClass_CVGuiScreen                           = 345,
    CClass_CPropJeep                             = 0,
    CClass_CPropVehicleChoreoGeneric             = 0,
    CClass_CTest_ProxyToggle_Networkable         = 175,
    CClass_CTesla                                = 170,
    CClass_CTeamTrainWatcher                     = 128,
    CClass_CBaseTeamObjectiveResource            = 16,
    CClass_CTeam                                 = 125,
    CClass_CSun                                  = 124,
    CClass_CParticlePerformanceMonitor           = 91,
    CClass_CSpotlightEnd                         = 119,
    CClass_CSlideshowDisplay                     = 116,
    CClass_CShadowControl                        = 115,
    CClass_CSceneEntity                          = 114,
    CClass_CRopeKeyframe                         = 113,
    CClass_CRagdollManager                       = 109,
    CClass_CPhysicsPropMultiplayer               = 98,
    CClass_CPhysBoxMultiplayer                   = 96,
    CClass_CBasePropDoor                         = 15,
    CClass_CDynamicProp                          = 33,
    CClass_CPointWorldText                       = 105,
    CClass_CPointCommentaryNode                  = 104,
    CClass_CPointCamera                          = 103,
    CClass_CPlayerResource                       = 102,
    CClass_CPlasma                               = 100,
    CClass_CPhysMagnet                           = 99,
    CClass_CPhysicsProp                          = 97,
    CClass_CPhysBox                              = 95,
    CClass_CParticleSystem                       = 92,
    CClass_CMaterialModifyControl                = 81,
    CClass_CLightGlow                            = 79,
    CClass_CInfoOverlayAccessor                  = 77,
    CClass_CFuncTrackTrain                       = 67,
    CClass_CFuncSmokeVolume                      = 66,
    CClass_CFuncRotating                         = 65,
    CClass_CFuncReflectiveGlass                  = 62,
    CClass_CFuncOccluder                         = 60,
    CClass_CFuncMonitor                          = 59,
    CClass_CFunc_LOD                             = 54,
    CClass_CTEDust                               = 147,
    CClass_CFunc_Dust                            = 53,
    CClass_CFuncConveyor                         = 56,
    CClass_CBreakableSurface                     = 25,
    CClass_CFuncAreaPortalWindow                 = 55,
    CClass_CFish                                 = 51,
    CClass_CEntityFlame                          = 38,
    CClass_CFireSmoke                            = 49,
    CClass_CEnvTonemapController                 = 46,
    CClass_CEnvScreenEffect                      = 44,
    CClass_CEnvScreenOverlay                     = 45,
    CClass_CEnvProjectedTexture                  = 42,
    CClass_CEnvParticleScript                    = 41,
    CClass_CFogController                        = 52,
    CClass_CEntityParticleTrail                  = 39,
    CClass_CEntityDissolve                       = 37,
    CClass_CDynamicLight                         = 32,
    CClass_CColorCorrectionVolume                = 30,
    CClass_CColorCorrection                      = 29,
    CClass_CBreakableProp                        = 24,
    CClass_CBasePlayer                           = 13,
    CClass_CBaseFlex                             = 8,
    CClass_CBaseEntity                           = 7,
    CClass_CBaseDoor                             = 6,
    CClass_CBaseCombatCharacter                  = 4,
    CClass_CBaseAnimatingOverlay                 = 2,
    CClass_CBoneFollower                         = 20,
    CClass_CBaseAnimating                        = 1, /* !!! */
    CClass_CInfoLightingRelative                 = 76,
    CClass_CAI_BaseNPC                           = 0,
    CClass_CBeam                                 = 19,
    CClass_CBaseViewModel                        = 18,
    CClass_CBaseProjectile                       = 14,
    CClass_CBaseParticleEntity                   = 12,
    CClass_CBaseGrenade                          = 9,
    CClass_CBaseCombatWeapon                     = 5
};

/* CBaseHandle */
#define MAX_EDICT_BITS        11
#define MAX_EDICTS            (1 << MAX_EDICT_BITS)
#define NUM_ENT_ENTRY_BITS    (MAX_EDICT_BITS + 1)
#define NUM_ENT_ENTRIES       (1 << NUM_ENT_ENTRY_BITS)
#define ENT_ENTRY_MASK        (NUM_ENT_ENTRIES - 1)
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF

enum ETFClass {
    CLASS_NONE = 0,
    CLASS_SCOUT,
    CLASS_SNIPER,
    CLASS_SOLDIER,
    CLASS_DEMOMAN,
    CLASS_MEDIC,
    CLASS_HEAVY,
    CLASS_PYRO,
    CLASS_SPY,
    CLASS_ENGINEER
};

enum BoneMasks {
    BONE_USED_MASK           = 0x0007FF00,
    BONE_USED_BY_ANYTHING    = 0x0007FF00,
    BONE_USED_BY_HITBOX      = 0x00000100,
    BONE_USED_BY_ATTACHMENT  = 0x00000200,
    BONE_USED_BY_VERTEX_MASK = 0x0003FC00,
    BONE_USED_BY_VERTEX_LOD0 = 0x00000400,
    BONE_USED_BY_VERTEX_LOD1 = 0x00000800,
    BONE_USED_BY_VERTEX_LOD2 = 0x00001000,
    BONE_USED_BY_VERTEX_LOD3 = 0x00002000,
    BONE_USED_BY_VERTEX_LOD4 = 0x00004000,
    BONE_USED_BY_VERTEX_LOD5 = 0x00008000,
    BONE_USED_BY_VERTEX_LOD6 = 0x00010000,
    BONE_USED_BY_VERTEX_LOD7 = 0x00020000,
    BONE_USED_BY_BONE_MERGE  = 0x00040000,
};

enum ObsModes {
    OBS_MODE_NONE = 0,
    OBS_MODE_DEATHCAM,
    OBS_MODE_FREEZECAM,
    OBS_MODE_FIXED,
    OBS_MODE_IN_EYE,
    OBS_MODE_CHASE,
    OBS_MODE_POI,
    OBS_MODE_ROAMING,
    NUM_OBSERVER_MODES,
};

/*----------------------------------------------------------------------------*/

/* "flag" argument of IMaterial::SetMaterialVarFlag() */
enum MaterialVarFlags_t {
    MATERIAL_VAR_DEBUG                    = (1 << 0),
    MATERIAL_VAR_NO_DEBUG_OVERRIDE        = (1 << 1),
    MATERIAL_VAR_NO_DRAW                  = (1 << 2),
    MATERIAL_VAR_USE_IN_FILLRATE_MODE     = (1 << 3),
    MATERIAL_VAR_VERTEXCOLOR              = (1 << 4),
    MATERIAL_VAR_VERTEXALPHA              = (1 << 5),
    MATERIAL_VAR_SELFILLUM                = (1 << 6),
    MATERIAL_VAR_ADDITIVE                 = (1 << 7),
    MATERIAL_VAR_ALPHATEST                = (1 << 8),
    MATERIAL_VAR_MULTIPASS                = (1 << 9),
    MATERIAL_VAR_ZNEARER                  = (1 << 10),
    MATERIAL_VAR_MODEL                    = (1 << 11),
    MATERIAL_VAR_FLAT                     = (1 << 12),
    MATERIAL_VAR_NOCULL                   = (1 << 13),
    MATERIAL_VAR_NOFOG                    = (1 << 14),
    MATERIAL_VAR_IGNOREZ                  = (1 << 15),
    MATERIAL_VAR_DECAL                    = (1 << 16),
    MATERIAL_VAR_ENVMAPSPHERE             = (1 << 17),
    MATERIAL_VAR_NOALPHAMOD               = (1 << 18),
    MATERIAL_VAR_ENVMAPCAMERASPACE        = (1 << 19),
    MATERIAL_VAR_BASEALPHAENVMAPMASK      = (1 << 20),
    MATERIAL_VAR_TRANSLUCENT              = (1 << 21),
    MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
    MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = (1 << 23),
    MATERIAL_VAR_OPAQUETEXTURE            = (1 << 24),
    MATERIAL_VAR_ENVMAPMODE               = (1 << 25),
    MATERIAL_VAR_SUPPRESS_DECALS          = (1 << 26),
    MATERIAL_VAR_HALFLAMBERT              = (1 << 27),
    MATERIAL_VAR_WIREFRAME                = (1 << 28),
    MATERIAL_VAR_ALLOWALPHATOCOVERAGE     = (1 << 29),
    MATERIAL_VAR_IGNORE_ALPHA_MODULATION  = (1 << 30),
};

/* "nOverrideType" argument of ModelRender::ForcedMaterialOverride() */
enum OverrideType_t {
    OVERRIDE_NORMAL = 0,
    OVERRIDE_BUILD_SHADOWS,
    OVERRIDE_DEPTH_WRITE,
    OVERRIDE_SSAO_DEPTH_WRITE,
};

/* From csgo, might be wrong/outdated. Currently using GROUP_MODEL */
#define TEXTURE_GROUP_LIGHTMAP                    "Lightmaps"
#define TEXTURE_GROUP_WORLD                       "World textures"
#define TEXTURE_GROUP_MODEL                       "Model textures"
#define TEXTURE_GROUP_VGUI                        "VGUI textures"
#define TEXTURE_GROUP_PARTICLE                    "Particle textures"
#define TEXTURE_GROUP_DECAL                       "Decal textures"
#define TEXTURE_GROUP_SKYBOX                      "SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS              "ClientEffect textures"
#define TEXTURE_GROUP_OTHER                       "Other textures"
#define TEXTURE_GROUP_PRECACHED                   "Precached"
#define TEXTURE_GROUP_CUBE_MAP                    "CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET               "RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED                 "Unaccounted textures"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER         "Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP   "Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR  "Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD  "World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS "Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER  "Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER        "Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER       "Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER                "DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL                  "ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS               "Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS              "Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE       "RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS               "Morph Targets"

/*----------------------------------------------------------------------------*/

#define DMG_GENERIC               0
#define DMG_CRUSH                 (1 << 0)
#define DMG_BULLET                (1 << 1)
#define DMG_SLASH                 (1 << 2)
#define DMG_BURN                  (1 << 3)
#define DMG_VEHICLE               (1 << 4)
#define DMG_FALL                  (1 << 5)
#define DMG_BLAST                 (1 << 6)
#define DMG_CLUB                  (1 << 7)
#define DMG_SHOCK                 (1 << 8)
#define DMG_SONIC                 (1 << 9)
#define DMG_ENERGYBEAM            (1 << 10)
#define DMG_PREVENT_PHYSICS_FORCE (1 << 11)
#define DMG_NEVERGIB              (1 << 12)
#define DMG_ALWAYSGIB             (1 << 13)
#define DMG_DROWN                 (1 << 14)
#define DMG_PARALYZE              (1 << 15)
#define DMG_NERVEGAS              (1 << 16)
#define DMG_POISON                (1 << 17)
#define DMG_RADIATION             (1 << 18)
#define DMG_DROWNRECOVER          (1 << 19)
#define DMG_ACID                  (1 << 20)
#define DMG_SLOWBURN              (1 << 21)
#define DMG_REMOVENORAGDOLL       (1 << 22)
#define DMG_PHYSGUN               (1 << 23)
#define DMG_PLASMA                (1 << 24)
#define DMG_AIRBOAT               (1 << 25)
#define DMG_DISSOLVE              (1 << 26)
#define DMG_BLAST_SURFACE         (1 << 27)
#define DMG_DIRECT                (1 << 28)
#define DMG_BUCKSHOT              (1 << 29)

enum {
    WPN_SLOT_PRIMARY   = 0,
    WPN_SLOT_SECONDARY = 1,
    WPN_SLOT_MELEE     = 2,
    WPN_SLOT_GRENADES  = 3,
    WPN_SLOT_BOMB      = 4,
};

/*----------------------------------------------------------------------------*/

enum in_buttons {
    IN_ATTACK    = (1 << 0),
    IN_JUMP      = (1 << 1),
    IN_DUCK      = (1 << 2),
    IN_FORWARD   = (1 << 3),
    IN_BACK      = (1 << 4),
    IN_USE       = (1 << 5),
    IN_CANCEL    = (1 << 6),
    IN_LEFT      = (1 << 7),
    IN_RIGHT     = (1 << 8),
    IN_MOVELEFT  = (1 << 9),
    IN_MOVERIGHT = (1 << 10),
    IN_ATTACK2   = (1 << 11),
    IN_RUN       = (1 << 12),
    IN_RELOAD    = (1 << 13),
    IN_ALT1      = (1 << 14),
    IN_ALT2      = (1 << 15),
    IN_SCORE     = (1 << 16),
    IN_SPEED     = (1 << 17),
    IN_WALK      = (1 << 18),
    IN_ZOOM      = (1 << 19),
    IN_WEAPON1   = (1 << 20),
    IN_WEAPON2   = (1 << 21),
    IN_BULLRUSH  = (1 << 22),
    IN_GRENADE1  = (1 << 23),
    IN_GRENADE2  = (1 << 24),
    IN_ATTACK3   = (1 << 25),
};

#endif /* SDK_ENUMS_H_ */
