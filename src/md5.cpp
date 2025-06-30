#include "md5.h"

INCLUDE_ASM("md5", md5_process);
#ifdef SKIP_ASM
#endif

INCLUDE_ASM("md5", md5_init);
#ifdef SKIP_ASM
void md5_init(int* param_1)
{
	return;
}
#endif

INCLUDE_ASM("md5", md5_append);
#ifdef SKIP_ASM
#endif

INCLUDE_ASM("md5", md5_finish);
#ifdef SKIP_ASM
#endif