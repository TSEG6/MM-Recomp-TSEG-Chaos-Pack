#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"

#define DURATION 20

ChaosEffectEntity void_out(PlayState* gameState) {

    PlayState* play = (PlayState*)gameState;
    func_80169FDC(play);
    Audio_PlaySfx(NA_SE_OC_ABYSS);
}


ChaosEffect voido = {
    .name = "VoidOut",
    .duration = DURATION,

    .on_start_fun = void_out,
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_voidout(void) {

    chaos_register_effect(&voido, CHAOS_DISTURBANCE_VERY_HIGH, NULL, 0);
}
