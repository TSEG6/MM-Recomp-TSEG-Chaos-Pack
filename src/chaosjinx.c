#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

#define DURATION 600

ChaosEffectEntity jinxplayer(PlayState* gameState) {

    recomp_printf("Cursed");

    gSaveContext.jinxTimer = 600;
}

ChaosEffectEntity fixplayer(PlayState* gameState) {

    recomp_printf("Cleaned");

    gSaveContext.jinxTimer = 0;
}


ChaosEffect jinx = {
    .name = "Jinxed",
    .duration = DURATION,

    .on_start_fun = jinxplayer,
    .on_end_fun = fixplayer,
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_jinx(void) {

    chaos_register_effect(&jinx, CHAOS_DISTURBANCE_HIGH, NULL);
}
