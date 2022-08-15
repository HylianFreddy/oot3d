#ifndef _Z_OBJ_KIBAKO_H_
#define _Z_OBJ_KIBAKO_H_

#include "global.hpp"

struct ObjKibako;

typedef void (*ObjKibakoActionFunc)(struct ObjKibako*, PlayState*);

typedef struct ObjKibako {
    /* 0x000 */ Actor actor;
    /* 0x1A4 */ ObjKibakoActionFunc actionFunc;
    /* 0x1A8 */ ColliderCylinder collider;
    /* 0x200 */ SkeletonAnimationModel* skelAnimModel;
    /* 0x204 */ u32 unk_204;
    /* 0x208 */ u32 unk_208;
} ObjKibako; // size = 0x20C

extern ActorInit Obj_Kibako_InitVars;

#endif
