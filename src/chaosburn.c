#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

s32 func_80834534(PlayState* play, Player* this);

#define DURATION 20

ChaosEffectEntity burnplayer(PlayState* gameState) {

    PlayState* play = (PlayState*)gameState;
    Player* player = GET_PLAYER(play);
    func_80834534(play, player);
}


ChaosEffect burn = {
    .name = "Firegrave",
    .duration = DURATION,

    .on_start_fun = burnplayer,
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_burn(void) {

    chaos_register_effect(&burn, CHAOS_DISTURBANCE_HIGH, NULL, 0);
}
