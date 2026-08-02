#include "md5.h"

struct md5_ctx {
    unsigned int lo; // 0x0
    unsigned int hi; // 0x4
    unsigned int a; // 0x8
    unsigned int b; // 0xC
    unsigned int c; // 0x10
    unsigned int d; // 0x14
};

INCLUDE_ASM("md5", md5_process);
#ifdef SKIP_ASM
#endif

//100%
INCLUDE_ASM("md5", md5_init__FP7md5_ctx);
#ifdef SKIP_ASM
void md5_init(md5_ctx* ctx)
{
    unsigned int a = 0x67452301;
    unsigned int b = 0xEFCDAB89;
    unsigned int c = 0x98BADCFE;
    unsigned int d = 0x10325476;
    ctx->a = a;
    ctx->d = d;
    ctx->b = b;
    ctx->c = c;
    ctx->lo = 0;
    ctx->hi = 0;
}
#endif

INCLUDE_ASM("md5", md5_append);
#ifdef SKIP_ASM
#endif

INCLUDE_ASM("md5", md5_finish);
#ifdef SKIP_ASM
#endif