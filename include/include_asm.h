#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#if !defined(SPLAT) && !defined(M2CTX) && !defined(PERMUTER) && !defined(SKIP_ASM)
#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)                                       \
    __asm__(                                                           \
        ".section .text\n"                                             \
        "\t.align\t3\n"                                                \
        "\t.globl\t" #NAME "\n"                                        \
        "\t.ent\t" #NAME "\n" #NAME ":\n"                              \
        "\t.include \"asm/nonmatchings/" FOLDER "/" #NAME ".s\"\n"     \
        "\t.set reorder\n"                                             \
        "\t.set at\n"                                                  \
        "\t.end\t" #NAME);
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)                                    \
    __asm__(                                                            \
        ".section .rodata\n"                                            \
        "    .include \"asm/nonmatchings/" FOLDER "/" #NAME ".s\"\n"    \
        ".section .text"                                                \
    )
#endif
__asm__(".include \"include/macro.inc\"\n");
#else
#ifndef INCLUDE_ASM
#define INCLUDE_ASM(FOLDER, NAME)
#endif
#ifndef INCLUDE_RODATA
#define INCLUDE_RODATA(FOLDER, NAME)
#endif
#endif

#endif /* INCLUDE_ASM_H */