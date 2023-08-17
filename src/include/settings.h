#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "menu.h"

#define CONFIG_FOLDER "enoch-configs/"

enum settings_rage {
    OFF   = 0,
    LEGIT = 1,
    RAGE  = 2,
};
enum settings_friendly {
    FRIENDLY = 1,
    ENEMY    = 2,
    ALL      = 3,
};
enum settings_building_type {
    BTYPE_ALL        = 0,
    BTYPE_SENTRY     = 1,
    BTYPE_DISPENSER  = 2,
    BTYPE_TELEPORTER = 3,
};

enum settings_selected_hitbox {
    SETTING_HITBOX_HEAD = 0,
    SETTING_HITBOX_TORSO,
    SETTING_HITBOX_ARMS,
    SETTING_HITBOX_LEGS,
};

typedef struct {
    /* ESP */
    int player_esp;
    int player_box_esp;
    int skeleton_esp;
    int player_health_esp;
    int player_name_esp;
    int player_class_esp;
    int player_weapon_esp;

    int building_esp;
    int building_esp_type;
    int building_box_esp;
    int building_hp_esp;
    int building_name_esp;

    int ammobox_esp;
    int healthpack_esp;

    /* Aim */
    int aimbot;
    float aim_fov;
    float aim_smooth;
    int aim_hitbox;
    int aim_silent;
    int aim_shoot_if_target;
    int aim_draw_fov;
    int aim_off_spectated;

    /* Misc */
    int bhop;
    int autostrafe;
    int autostab;
    int watermark;
    int speclist;

    /* Colors */
    struct nk_colorf col_friend_esp;
    struct nk_colorf col_enemy_esp;
    struct nk_colorf col_enemy_build;
    struct nk_colorf col_friend_build;
    struct nk_colorf col_ammobox_esp;
    struct nk_colorf col_healthpack_esp;
    struct nk_colorf col_aim_fov;
} Settings;

extern Settings settings;

/*----------------------------------------------------------------------------*/

void save_config(const char* filename);
void load_config(const char* filename);

#endif /* SETTINGS_H_ */
