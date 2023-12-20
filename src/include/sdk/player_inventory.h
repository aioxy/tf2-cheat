#ifndef SDK_PLAYER_INVENTORY_H_
#define SDK_PLAYER_INVENTORY_H_

/* NOTE: This file is included from sdk.h and depends on its declarations */

typedef struct CTFPlayerInventory CTFPlayerInventory;

typedef struct {
    PAD(4 * 10);
    int (*GetMaxItemCount)(CTFPlayerInventory*); /* 10 */
} VMT_CTFPlayerInventory;

struct CTFPlayerInventory {
    VMT_CTFPlayerInventory* vmt;
};

#endif /* SDK_PLAYER_INVENTORY_H_ */
