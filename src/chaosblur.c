#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"




#define DURATION 420
bool effectbluron = false;
extern Color_RGBA8_u32 gPlayVisMonoColor;


ChaosEffectEntity start_pitch(PlayState* gameState) {


    effectbluron = true;
    Play_EnableMotionBlur(230);
    gPlayVisMonoColor.r = 255;
    gPlayVisMonoColor.g = 255;
    gPlayVisMonoColor.b = 255;
    gPlayVisMonoColor.a = 255;

    
}

ChaosEffectEntity end_pitch(PlayState* gameState) {

    effectbluron = false;
    Play_EnableMotionBlur(0);
    gPlayVisMonoColor.r = 0;
    gPlayVisMonoColor.g = 0;
    gPlayVisMonoColor.b = 0;
    gPlayVisMonoColor.a = 0;
}

ChaosEffect chaos_blur = {
    .name = "Motion Blur",
    .duration = DURATION,

    .on_start_fun = start_pitch,
    .on_end_fun = end_pitch,
};

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_blur(void) {

    chaos_register_effect(&chaos_blur, CHAOS_DISTURBANCE_HIGH, NULL);
}
