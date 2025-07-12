#include "common.h"

INCLUDE_ASM("bx/bxstring", cBXString_cBXString1);

INCLUDE_ASM("bx/bxstring", cBXString_Realloc);

INCLUDE_ASM("bx/bxstring", cBXString_Reset);

INCLUDE_ASM("bx/bxstring", func_00318120);

INCLUDE_ASM("bx/bxstring", cBXString_Resize);

INCLUDE_ASM("bx/bxstring", func_003181E8);

INCLUDE_ASM("bx/bxstring", cBXString__cBXString);

INCLUDE_ASM("bx/bxstring", cBXString_cBXString2);

INCLUDE_ASM("bx/bxstring", func_00318350);

INCLUDE_ASM("bx/bxstring", cBXString_InitFromCString);

INCLUDE_ASM("bx/bxstring", cBXString_operatorE);

INCLUDE_ASM("bx/bxstring", cBXString_cBXString4);

INCLUDE_ASM("bx/bxstring", func_00318540);

INCLUDE_ASM("bx/bxstring", func_003185C8);

INCLUDE_ASM("bx/bxstring", func_00318630);

INCLUDE_ASM("bx/bxstring", func_003186D0);

INCLUDE_ASM("bx/bxstring", func_00318760);

INCLUDE_ASM("bx/bxstring", func_003187C8);

INCLUDE_ASM("bx/bxstring", cBXString_ConcatImpl);

//94.09%
//https://decomp.me/scratch/4rHwX
INCLUDE_ASM("bx/bxstring", cBXString_Concat);

INCLUDE_ASM("bx/bxstring", func_00318968);

INCLUDE_ASM("bx/bxstring", func_003189A0);

INCLUDE_ASM("bx/bxstring", func_003189D0);

INCLUDE_ASM("bx/bxstring", func_00318A88);

INCLUDE_ASM("bx/bxstring", func_00318AF8);

INCLUDE_ASM("bx/bxstring", func_00318B40);

INCLUDE_ASM("bx/bxstring", func_00318BC0);

INCLUDE_ASM("bx/bxstring", func_00318BF8);

INCLUDE_ASM("bx/bxstring", cBXString_FindLastOf);
//94.17%
//https://decomp.me/scratch/p8aRA

INCLUDE_ASM("bx/bxstring", func_00318C60);

//100%
//https://decomp.me/scratch/ETxUq
INCLUDE_ASM("bx/bxstring", cBXString_FindFirstOf);
#ifdef SKIP_ASM
//int cBXString_FindFirstOf(cBXString* this, char needle)
//{
//    char* pcVar1;
//    int iVar2;
//
//    pcVar1 = 0;//(char*)func_0041ACC0(this->pStrdata, needle);
//    if (pcVar1) {
//        iVar2 = (int)pcVar1 - (int)this->pStrdata;
//    }
//    else {
//        iVar2 = -1;
//    }
//    return iVar2;
//}
#endif

INCLUDE_ASM("bx/bxstring", func_00318CE8);

INCLUDE_ASM("bx/bxstring", func_00318D28);

INCLUDE_ASM("bx/bxstring", func_00318D90);

INCLUDE_ASM("bx/bxstring", func_00318DF8);

INCLUDE_ASM("bx/bxstring", func_00318E68);

INCLUDE_ASM("bx/bxstring", func_00318EB8);

INCLUDE_ASM("bx/bxstring", func_00318F20);

INCLUDE_ASM("bx/bxstring", func_00318F58);

INCLUDE_ASM("bx/bxstring", func_00318F90);

INCLUDE_ASM("bx/bxstring", func_00319028);

INCLUDE_ASM("bx/bxstring", cBXString_cBXString5);

INCLUDE_ASM("bx/bxstring", func_00319120);

INCLUDE_ASM("bx/bxstring", func_00319170);
