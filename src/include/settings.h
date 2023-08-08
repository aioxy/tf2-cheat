#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <stdbool.h>

#define OFF 0

enum settings_rage {
    LEGIT = 1,
    RAGE  = 2,
};

enum settings_friendly {
    FRIENDLY = 1,
    ENEMY    = 2,
    ALL      = 3,
};

typedef struct {
    int bhop;
    int autostrafe;
    int box_esp;
} Settings;

extern Settings settings;

#endif /* SETTINGS_H_ */
