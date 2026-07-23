#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

#define DURATION 20

ChaosEffectEntity stolen_items(PlayState* gameState) {

    AMMO(ITEM_BOW) = (AMMO(ITEM_BOW) >= 15) ? (AMMO(ITEM_BOW) - 15) : 0;
    AMMO(ITEM_BOMB) = (AMMO(ITEM_BOMB) >= 10) ? (AMMO(ITEM_BOMB) - 10) : 0;
    AMMO(ITEM_DEKU_NUT) = (AMMO(ITEM_DEKU_NUT) >= 2) ? (AMMO(ITEM_DEKU_NUT) - 5) : 0;
    AMMO(ITEM_DEKU_STICK) = (AMMO(ITEM_DEKU_STICK) >= 2) ? (AMMO(ITEM_DEKU_STICK) - 5) : 0;
    AMMO(ITEM_BOMBCHU) = (AMMO(ITEM_BOMBCHU) >= 10) ? (AMMO(ITEM_BOMBCHU) - 10) : 0;
    AMMO(ITEM_MAGIC_BEANS) = (AMMO(ITEM_MAGIC_BEANS) >= 2) ? (AMMO(ITEM_MAGIC_BEANS) - 5) : 0;
    Audio_PlaySfx(NA_SE_EN_STALKIDS_LAUGH_MD2);
}


ChaosEffect stolenitems = {
    .name = "StolenItems",
    .duration = DURATION,

    .on_start_fun = stolen_items,
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_stolenitems(void) {

    chaos_register_effect(&stolenitems, CHAOS_DISTURBANCE_HIGH, NULL, 0);
}
