#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z_en_test4.h"
#include "z_en_okarina_effect.h"

#define DURATION 600
#define RAIN_INTENSITY 255  

bool effectrainon = false;

void start_rain(PlayState* play);
void stop_rain(PlayState* play);
void maintain_rain(PlayState* play);


void start_storm(PlayState* gameState) {
    effectrainon = true;

    PlayState* play = (PlayState*)gameState;
    start_rain(play);
}


void end_storm(PlayState* gameState) {
    effectrainon = false;

    PlayState* play = (PlayState*)gameState;
    stop_rain(play);
}


void start_rain(PlayState* play) {
    if (CURRENT_DAY != 2) { 
        gWeatherMode = WEATHER_MODE_RAIN;
        play->envCtx.stormState = STORM_STATE_ON;
        play->envCtx.lightningState = LIGHTNING_ON;

        play->envCtx.precipitation[PRECIP_RAIN_CUR] = RAIN_INTENSITY;
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = RAIN_INTENSITY;

        
        Environment_PlayStormNatureAmbience(play);
    }
}


void stop_rain(PlayState* play) {
    if (CURRENT_DAY != 2) {
        play->envCtx.stormState = STORM_STATE_OFF;
        play->envCtx.lightningState = LIGHTNING_OFF;

        play->envCtx.precipitation[PRECIP_RAIN_CUR] = 0;
        play->envCtx.precipitation[PRECIP_RAIN_MAX] = 0;

        Environment_StopStormNatureAmbience(play);

        gWeatherMode = WEATHER_MODE_CLEAR;
    }
}


void maintain_rain(PlayState* play) {
    if (!effectrainon || CURRENT_DAY == 2) return;

    gWeatherMode = WEATHER_MODE_RAIN;
    play->envCtx.stormState = STORM_STATE_ON;
    play->envCtx.lightningState = LIGHTNING_ON;

    play->envCtx.precipitation[PRECIP_RAIN_CUR] = RAIN_INTENSITY;
    play->envCtx.precipitation[PRECIP_RAIN_MAX] = RAIN_INTENSITY;
}


ChaosEffect sudden_storm = {
    .name = "Sudden Storm",
    .duration = DURATION,
    .on_start_fun = start_storm,
    .on_end_fun = end_storm,
    .update_fun = maintain_rain, 
};


RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects(void) {
    chaos_register_effect(&sudden_storm, CHAOS_DISTURBANCE_MEDIUM, NULL, 0);
}
