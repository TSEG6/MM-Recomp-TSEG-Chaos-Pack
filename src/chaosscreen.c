#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z_en_test4.h"

#define DURATION 400
bool effectshrinkon = false;

void startshrink(EnTest4* this, PlayState* play);

ChaosEffectEntity start_shrink(PlayState* gameState) {
    recomp_printf("Shrink On");
    effectshrinkon = true;

    PlayState* play = (PlayState*)gameState;

    EnTest4* test4Actor = NULL;
    startshrink(test4Actor, play);
}

void startshrink(EnTest4* this, PlayState* play) {

    if (!gSaveContext.screenScaleFlag) {

        gSaveContext.screenScale = 500.0f;
        gSaveContext.screenScaleFlag = true;

    }
}

void endshrink(EnTest4* this, PlayState* play) {

    gSaveContext.screenScale = 1000.0f;
        gSaveContext.screenScaleFlag = false;

    }

ChaosEffectEntity end_shrink(PlayState* gameState) {
    recomp_printf("Shrink Off");
    effectshrinkon = false;

    PlayState* play = (PlayState*)gameState;

    EnTest4* test4Actor = NULL;
    endshrink(test4Actor, play);

}

   

ChaosEffect shrinking = {
    .name = "Small Screen",
    .duration = DURATION,
    .on_start_fun = start_shrink,
    .on_end_fun = end_shrink,
};

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_shrink(void) {

    chaos_register_effect(&shrinking, CHAOS_DISTURBANCE_MEDIUM, NULL);
}
