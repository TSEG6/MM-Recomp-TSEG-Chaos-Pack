#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

#define DURATION 240

static s32 OriginalTimeSpeed = 0;

ChaosEffectEntity timemess(PlayState* gameState) {

    
    OriginalTimeSpeed = R_TIME_SPEED;

    
    R_TIME_SPEED = 10;
}

ChaosEffectEntity timefix(PlayState* gameState) {

    
    R_TIME_SPEED = OriginalTimeSpeed;
}

ChaosEffect time = {
    .name = "Speedrun",
    .duration = DURATION,

    .on_start_fun = timemess,
    .on_end_fun = timefix,
};

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_time(void) {

    chaos_register_effect(&time, CHAOS_DISTURBANCE_MEDIUM, NULL, 0);
}