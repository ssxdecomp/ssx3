/*
 * Minimal <stdint.h> for building with ee-gcc 2.95.3 on macOS.
 *
 * On Linux the Wine-run compiler falls back to the host's /usr/include and
 * picks up glibc's stdint.h. macOS has no /usr/include, so configure.py adds
 * this directory to the system include path on darwin only. Types match the
 * 32-bit glibc definitions for the EE (int = 32 bits, long long = 64 bits).
 */
#ifndef _SSX3_MACOS_STDINT_H
#define _SSX3_MACOS_STDINT_H

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

typedef int intptr_t;
typedef unsigned int uintptr_t;

#endif
