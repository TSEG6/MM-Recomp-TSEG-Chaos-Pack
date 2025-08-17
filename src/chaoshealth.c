#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 180
bool effecthealthon = false;

static unsigned int seed;

static unsigned int better_rand(void) {
    // Linear Congruential Generator example
    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_ha(PlayState* gameState) {
    recomp_printf("Health");
    effecthealthon = true;
}

ChaosEffectEntity end_ha(PlayState* gameState) {
    recomp_printf("Health End");
    effecthealthon = false;
    if (gSaveContext.save.saveInfo.playerData.health > gSaveContext.save.saveInfo.playerData.healthCapacity / 2) {

        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
    }
    else {

        Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
    }
}

ChaosEffect heart_attack = {
    .name = "Heart Attack",
    .duration = DURATION,

    .on_start_fun = start_ha,
    .on_end_fun = end_ha,
};

RECOMP_HOOK("Player_Update")
void RandoHealth(Player* this, PlayState* play) {
    if (effecthealthon) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomHealth = better_rand() % gSaveContext.save.saveInfo.playerData.healthCapacity;
        gSaveContext.save.saveInfo.playerData.health = randomHealth;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_health(void) {

    chaos_register_effect(&heart_attack, CHAOS_DISTURBANCE_MEDIUM, NULL);
}
