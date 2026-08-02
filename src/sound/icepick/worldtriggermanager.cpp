#include "common.h"

extern "C" void* cMemMan_alloc(int size, const char* tag, unsigned int flags, int d);
extern "C" void* cWorldTriggerManager_cWorldTriggerManager(void* self);
extern const char D_00483588[];
extern void* D_004A52D4;

//99.88%
INCLUDE_ASM("sound/icepick/worldtriggermanager", WORLDTRIGGERMANAGER_Init__Fv);
#ifdef SKIP_ASM
void WORLDTRIGGERMANAGER_Init()
{
    if (D_004A52D4 == 0) {
        void* mem = cMemMan_alloc(0x344, D_00483588, 0, 0);
        D_004A52D4 = cWorldTriggerManager_cWorldTriggerManager(mem);
    }
}
#endif

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B4B48);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B4B70);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B4BE0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B4C08);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B4C38);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5758);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5818);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5838);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5878);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5898);

INCLUDE_ASM("sound/icepick/worldtriggermanager", cWorldTriggerManager_cWorldTriggerManager);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5988);

INCLUDE_ASM("sound/icepick/worldtriggermanager", cWorldTriggerManager_LoadTriggerInfo);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5B90);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5BC0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5C68);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5D78);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5E68);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B5F60);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B63D0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6550);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B65B0);

//100%
INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6628__FPv);
#ifdef SKIP_ASM
int func_002B6628(void* self)
{
    return 0;
}
#endif

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6630);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B66E8);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6740);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B67D8);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6808);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6868);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B68D0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6900);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6988);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B69B8);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6A68);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6AA0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6AE0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6B08);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6B30);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6B50);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6C20);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6C90);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6CF8);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B6F40);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B7318);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B7410);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B75D0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B77C0);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B7848);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B7908);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B8190);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B82B8);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B83F8);

INCLUDE_ASM("sound/icepick/worldtriggermanager", func_002B8818);

