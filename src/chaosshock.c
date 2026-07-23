#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

void func_80833B18(PlayState* play, Player* this, s32 arg2, f32 speed, f32 velocityY, s16 arg5, s32 invincibilityTimer);

#define DURATION 20

ChaosEffectEntity shockplayer(PlayState* gameState) {

    PlayState* play = (PlayState*)gameState;
    Player* player = GET_PLAYER(play);
    func_80833B18(play, player, 4, 0.0f, 0.0f, 0, 20);
}


ChaosEffect shock = {
    .name = "Shockgrave",
    .duration = DURATION,

    .on_start_fun = shockplayer,
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_shock(void) {

    chaos_register_effect(&shock, CHAOS_DISTURBANCE_HIGH, NULL, 0);
}
