extern "C" {
#include "z_en_si.hpp"

#define FLAGS 0x00000201

void EnSi_Init(Actor* actor, GameState* state);
void EnSi_Destroy(Actor* actor, GameState* state);
void EnSi_Update(Actor* actor, GameState* state);
void EnSi_Draw(Actor* actor, GameState* state);

void FUN_003adc80(EnSi* self, PlayState* play);
void FUN_003ad218(EnSi* self, PlayState* play);
void FUN_003d0544(EnSi* self, PlayState* play);

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
}

void FUN_003adc80(EnSi* self, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (self->actor.flags & 0x2000) {
        self->actionFunc = FUN_003ad218;
    } else {
        Math_SmoothStepToF(&self->actor.scale.x, 0.25f, SREG(30) * 0.33333335f * 0.4f, 1.0f, 0.0f);
        Actor_SetScale(&self->actor, self->actor.scale.x);
        self->actor.shape.rot.y += SREG(30) * 0.33333335f * 1024.0f;

        if (!Player_InCsMode(play)) {
            if (self->collider.base.acFlags & AC_HIT) {
                self->collider.base.acFlags &= ~AC_HIT;
            }

            if (self->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
                self->collider.base.ocFlags2 &= ~OC2_HIT_PLAYER;
                Item_Give(play, ITEM_SKULL_TOKEN);
                SET_GS_FLAGS((self->actor.params & 0x1F00) >> 8, self->actor.params & 0xFF);
                player->actor.freezeTimer = (s32)(30.0f / SREG(30) + 0.5f);
                FUN_00367c7c(play, 0xB4, NULL);
                if ((gSaveContext.health != 0) && (play->unk_318C == 0)) {
                    FUN_0035c528(0x10005A6);
                }
                self->actionFunc = FUN_003d0544;
            } else {
                Collider_UpdateCylinder(&self->actor, &self->collider);
                CollisionCheck_SetAC(play, &play->colChkCtx, &self->collider.base);
                CollisionCheck_SetOC(play, &play->colChkCtx, &self->collider.base);
            }
        }
    }
}

void FUN_003ad218(EnSi* self, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Math_SmoothStepToF(&self->actor.scale.x, 0.25f, 0.4f, 1.0f, 0.0f);
    Actor_SetScale(&self->actor, self->actor.scale.x);
    self->actor.shape.rot.y += 0x400;

    if (!(self->actor.flags & 0x2000)) {
        Item_Give(play, ITEM_SKULL_TOKEN);
        SET_GS_FLAGS((self->actor.params & 0x1F00) >> 8, self->actor.params & 0xFF);
        player->actor.freezeTimer = (s32)(30.0f / SREG(30) + 0.5f);
        FUN_00367c7c(play, 0xB4, NULL);
        if ((gSaveContext.health != 0) && (play->unk_318C == 0)) {
            FUN_0035c528(0x10005A6);
        }
        self->actionFunc = FUN_003d0544;
    }
}

void FUN_003d0544(EnSi* self, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((gSaveContext.health != 0) && (play->unk_318C == 0)) {
        if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
            Actor_Kill(&self->actor);
        } else {
            player->actor.freezeTimer = (s32)(30.0f / SREG(30) + 0.5f);
        }
    }
}

void EnSi_Update(Actor* actor, GameState* state) {
    EnSi* self = (EnSi*)actor;
    PlayState* play = (PlayState*)state;

    Actor_MoveForward(&self->actor);
    Actor_UpdateBgCheckInfo(play, &self->actor, 0.0f, 0.0f, 0.0f, 4);
    self->actionFunc(self, play);
    Actor_SetFocus(&self->actor, 16.0f);
}

GLOBAL_ASM("asm/EnSi_Draw.s")
}
