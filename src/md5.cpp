#include "md5.h"

INCLUDE_ASM("md5", md5_process);

INCLUDE_ASM("md5", md5_init);

INCLUDE_ASM("md5", md5_append);

INCLUDE_ASM("md5", md5_finish);
