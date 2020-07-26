#ifndef _LIMITS_H
#define _LIMITS_H

#define CHAR_BIT    8
#define SCHAR_MIN   -127
#define SCHAR_MAX   127
#define UCHAR_MAX   255u
#define CHAR_MIN    SCHAR_MIN
#define CHAR_MAX    SCHAR_MAX
#define MB_LEN_MAX  4

#define SHRT_MIN    -32767
#define SHRT_MAX    32767
#define USHRT_MAX   65535u
#define INT_MIN     -2147483647
#define INT_MAX     2147483647
#define UINT_MAX    4294967295u

#ifdef __x86_64__
#define LONG_MIN    -9223372036854775807l
#define LONG_MAX    9223372036854775807l
#define ULONG_MAX   18446744073709551615l
#else
#define LONG_MIN    -2147483647l
#define LONG_MAX    2147483647l
#define ULONG_MAX   4294967295ul
#endif

#endif
