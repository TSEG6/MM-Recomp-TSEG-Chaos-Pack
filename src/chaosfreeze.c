#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

void func_80833B18(PlayState* play, Player* this, s32 arg2, f32 speed, f32 velocityY, s16 arg5, s32 invincibilityTimer);
int DRModActive;

RECOMP_CALLBACK("*", recomp_on_init) void on_init() {

    DRModActive = recomp_is_dependency_met("mm_recomp_deltarune_ost") == DEPENDENCY_STATUS_FOUND;
}

#define DURATION 20

ChaosEffectEntity freezeplayer(PlayState* gameState) {

    PlayState* play = (PlayState*)gameState;
    Player* player = GET_PLAYER(play);
    func_80833B18(play, player, 3, 0.0f, 0.0f, 0, 20);
    if (DRModActive) Audio_PlayFanfare(NA_BGM_FAILURE_0);
}


ChaosEffect freeze = {
    .name = "Snowgrave",
    .duration = DURATION,

    .on_start_fun = freezeplayer,
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_freeze(void) {

    chaos_register_effect(&freeze, CHAOS_DISTURBANCE_HIGH, NULL, 0);
}
