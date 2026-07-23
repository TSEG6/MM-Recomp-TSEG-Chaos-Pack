#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 160
bool effectbeanson = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_mbe(PlayState* gameState) {


    effectbeanson = true;
}

ChaosEffectEntity end_mbe(PlayState* gameState) {

    effectbeanson = false;
    if (AMMO(ITEM_MAGIC_BEANS) > 20 /2) {

        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
    }
    else {

        Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
    }
}

ChaosEffect chaos_bean = {
    .name = "Mismanaged Beans",
    .duration = DURATION,

    .on_start_fun = start_mbe,
    .on_end_fun = end_mbe,
};

RECOMP_HOOK("Player_Update")
void RandoBean(Player* this, PlayState* play) {

    if (effectbeanson && CUR_UPG_VALUE(UPG_DEKU_NUTS) != 0) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomBean = better_rand() % 20;
        AMMO(ITEM_MAGIC_BEANS) = randomBean;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_beans(void) {

    chaos_register_effect(&chaos_bean, CHAOS_DISTURBANCE_LOW, NULL, 0);
}
