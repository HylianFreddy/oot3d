extern "C" {
#include "z_en_honotrap.hpp"

#define FLAGS 0x80000010

void EnHonotrap_Init(Actor* actor, GameState* state);
void EnHonotrap_Destroy(Actor* actor, GameState* state);
void EnHonotrap_Update(Actor* actor, GameState* state);
void EnHonotrap_Draw(Actor* actor, GameState* state);

GLOBAL_ASM("data/z_En_Honotrap.data.o")

ActorInit En_Honotrap_InitVars = {
    ACTOR_EN_HONOTRAP,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw,
};

GLOBAL_ASM("asm/EnHonotrap_Init.s")

GLOBAL_ASM("asm/EnHonotrap_Destroy.s")

GLOBAL_ASM("asm/EnHonotrap_Update.s")

GLOBAL_ASM("asm/EnHonotrap_Draw.s")
}
