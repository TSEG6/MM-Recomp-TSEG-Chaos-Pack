#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 160
bool effectarrowson = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_ma(PlayState* gameState) {

    effectarrowson = true;
}

ChaosEffectEntity end_ma(PlayState* gameState) {

    effectarrowson = false;

    if (CUR_UPG_VALUE(UPG_QUIVER) != 0) {

        if (AMMO(ITEM_BOW) > CUR_CAPACITY(UPG_QUIVER) / 2) {

            Audio_PlaySfx(NA_SE_SY_GET_ITEM);
        }
        else {

            Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
        }

    }
}

ChaosEffect chaos_arrows = {
    .name = "Mismanaged Arrows",
    .duration = DURATION,

    .on_start_fun = start_ma,
    .on_end_fun = end_ma,
};

RECOMP_HOOK("Player_Update")
void RandoArrow(Player* this, PlayState* play) {

    if (effectarrowson && CUR_UPG_VALUE(UPG_QUIVER) != 0) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomArrow = better_rand() % CUR_CAPACITY(UPG_QUIVER);
            AMMO(ITEM_BOW) = randomArrow;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_arrows(void) {

    chaos_register_effect(&chaos_arrows, CHAOS_DISTURBANCE_LOW, NULL);
}
