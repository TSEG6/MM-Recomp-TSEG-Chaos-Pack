#include "chaos_dep.h"
#include "recomputils.h"
#include "modding.h"
#include "global.h"
#include "recompconfig.h"
#include "z64player.h"

#define DURATION 180
bool effectmagicon = false;

static unsigned int seed;

static unsigned int better_rand(void) {

    seed = (1103515245U * seed + 12345U) & 0x7fffffffU;
    return seed;
}

ChaosEffectEntity start_hm(PlayState* gameState) {
    recomp_printf("Magic");
    effectmagicon = true;
}

ChaosEffectEntity end_hm(PlayState* gameState) {
    recomp_printf("Magic End");
    effectmagicon = false;
    if (gSaveContext.save.saveInfo.playerData.magic > gSaveContext.magicCapacity /2) {

        Audio_PlaySfx(NA_SE_SY_GET_ITEM);
    }
    else {

        Audio_PlaySfx(NA_SE_SY_QUIZ_INCORRECT);
    }
}

ChaosEffect chaos_magic = {
    .name = "Haunted Magic",
    .duration = DURATION,

    .on_start_fun = start_hm,
    .on_end_fun = end_hm,
};

RECOMP_HOOK("Player_Update")
void RandoMagic(Player* this, PlayState* play) {

    if (effectmagicon && (gSaveContext.save.saveInfo.playerData.isMagicAcquired)) {
        if (seed == 0) {
            seed = (unsigned int)osGetTime() ^ play->state.frames ^ (unsigned int)this->actor.world.pos.x;
        }

        int randomMagic = better_rand() % gSaveContext.magicCapacity;
        gSaveContext.save.saveInfo.playerData.magic = randomMagic;
    }
}

RECOMP_CALLBACK("mm_recomp_chaos_framework", chaos_on_init)
void register_chaos_effects_magic(void) {

    chaos_register_effect(&chaos_magic, CHAOS_DISTURBANCE_MEDIUM, NULL);

}
