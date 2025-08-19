#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 160
bool effectstickson = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_ms(PlayState* gameState) {

    effectstickson = true;
}

ChaosEffectEntity end_ms(PlayState* gameState) {

    effectstickson = false;
    if (AMMO(ITEM_DEKU_STICK) > CUR_CAPACITY(UPG_DEKU_STICKS) /2) {

        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
    }
    else {

        Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
    }
}

ChaosEffect chaos_sticks = {
    .name = "Mismanaged Sticks",
    .duration = DURATION,

    .on_start_fun = start_ms,
    .on_end_fun = end_ms,
};

RECOMP_HOOK("Player_Update")
void RandoStick(Player* this, PlayState* play) {

    if (effectstickson && CUR_UPG_VALUE(UPG_DEKU_STICKS) != 0) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomStick = better_rand() % CUR_CAPACITY(UPG_DEKU_STICKS);
            AMMO(ITEM_DEKU_STICK) = randomStick;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_sticks(void) {

    chaos_register_effect(&chaos_sticks, CHAOS_DISTURBANCE_LOW, NULL);
}
