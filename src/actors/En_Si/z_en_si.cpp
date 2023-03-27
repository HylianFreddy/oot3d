extern "C" {
#include "z_en_si.hpp"

#define FLAGS 0x00000201

void EnSi_Init(Actor* actor, GameState* state);
void EnSi_Destroy(Actor* actor, GameState* state);
void EnSi_Update(Actor* actor, GameState* state);
void EnSi_Draw(Actor* actor, GameState* state);

void FUN_003ad218(Actor* actor, GameState* state);
void FUN_003adc80(Actor* actor, GameState* state);
void FUN_003d0544(Actor* actor, GameState* state);

GLOBAL_ASM("data/z_En_Si.data.o")

ActorInit En_Si_InitVars = {
    ACTOR_EN_SI,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_ST,
    sizeof(EnSi),
    (ActorFunc)EnSi_Init,
    (ActorFunc)EnSi_Destroy,
    (ActorFunc)EnSi_Update,
    (ActorFunc)EnSi_Draw,
};

GLOBAL_ASM("asm/EnSi_Init.s")

void EnSi_Destroy(Actor* actor, GameState* state) {
    PlayState* play = (PlayState*)state;
    EnSi* self = (EnSi*)actor;

    Collider_DestroyCylinder(play, &self->collider);
    
    for (int i = 0; i < 2; i++) {
        SkeletonAnimationModel* skel = self->skelAnimModels[i];
        if (skel != NULL) {
            skel->vTable->destroy(skel);
            self->skelAnimModels[i] = NULL;
        }
    }
    return;
}

GLOBAL_ASM("asm/FUN_003ad218.s")

GLOBAL_ASM("asm/FUN_003adc80.s")

GLOBAL_ASM("asm/FUN_003d0544.s")

GLOBAL_ASM("asm/EnSi_Update.s")

GLOBAL_ASM("asm/EnSi_Draw.s")
}
