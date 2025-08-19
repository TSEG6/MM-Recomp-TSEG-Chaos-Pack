#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 160
bool effectnutson = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_mn(PlayState* gameState) {


    effectnutson = true;
}

ChaosEffectEntity end_mn(PlayState* gameState) {

    effectnutson = false;
    if (AMMO(ITEM_DEKU_NUT) > CUR_CAPACITY(UPG_DEKU_NUTS) /2) {

        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
    }
    else {

        Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
    }
}

ChaosEffect chaos_nuts = {
    .name = "Mismanaged Nuts",
    .duration = DURATION,

    .on_start_fun = start_mn,
    .on_end_fun = end_mn,
};

RECOMP_HOOK("Player_Update")
void RandoNut(Player* this, PlayState* play) {

    if (effectnutson && CUR_UPG_VALUE(UPG_DEKU_NUTS) != 0) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomNut = better_rand() % CUR_CAPACITY(UPG_DEKU_NUTS);
            AMMO(ITEM_DEKU_NUT) = randomNut;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_nuts(void) {

    chaos_register_effect(&chaos_nuts, CHAOS_DISTURBANCE_LOW, NULL);
}
