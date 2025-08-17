#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 160
bool effectmoneyon = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_money(PlayState* gameState) {
    recomp_printf("Rupees");
    effectmoneyon = true;
}

ChaosEffectEntity end_money(PlayState* gameState) {
    recomp_printf("Rupees End");

    effectmoneyon = false;
    if (gSaveContext.save.saveInfo.playerData.rupees > CUR_CAPACITY(UPG_WALLET) / 3) {

        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
    }
    else {

        Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
    }
}

ChaosEffect rupee_rando = {
    .name = "Mismanaged Rupees",
    .duration = DURATION,

    .on_start_fun = start_money,
    .on_end_fun = end_money,
};

RECOMP_HOOK("Player_Update")
void MoneyRando(Player* this, PlayState* play) {

    if (effectmoneyon && (gSaveContext.save.saveInfo.playerData.rupees != 0)) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomRupees = better_rand() % CUR_CAPACITY(UPG_WALLET);
        gSaveContext.save.saveInfo.playerData.rupees = randomRupees;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_money(void) {

    chaos_register_effect(&rupee_rando, CHAOS_DISTURBANCE_MEDIUM, NULL);
}
