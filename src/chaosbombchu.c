#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 160
bool effectbombchuon = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_mbc(PlayState* gameState) {

    effectbombchuon = true;
}

ChaosEffectEntity end_mbc(PlayState* gameState) {

    effectbombchuon = false;

    if (CUR_UPG_VALUE(UPG_BOMB_BAG) != 0) {

        if (AMMO(ITEM_BOMBCHU) > CUR_CAPACITY(UPG_BOMB_BAG) / 2) {

            Audio_PlaySfx(NA_SE_SY_GET_ITEM);
        }
        else {

            Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
        }

    }
}

ChaosEffect chaos_bombchus = {
    .name = "Mismanaged Bombchus",
    .duration = DURATION,

    .on_start_fun = start_mbc,
    .on_end_fun = end_mbc,
};

RECOMP_HOOK("Player_Update")
void RandoBombchu(Player* this, PlayState* play) {

    if (effectbombchuon && CUR_UPG_VALUE(UPG_BOMB_BAG) != 0) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomBombchu = better_rand() % CUR_CAPACITY(UPG_BOMB_BAG);
        AMMO(ITEM_BOMBCHU) = randomBombchu;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_bombchu(void) {

    chaos_register_effect(&chaos_bombchus, CHAOS_DISTURBANCE_LOW, NULL, 0);
}
