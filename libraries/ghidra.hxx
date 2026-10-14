#ifndef GHIDRA_HXX
#define GHIDRA_HXX

#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#ifdef __cplusplus
	#include <string.h>
	#include <type_traits>
#endif

#if defined(_MSVC_LANG)
	#define __GHIDRA_CXX _MSVC_LANG
#elif defined(__cplusplus)
	#define __GHIDRA_CXX __cplusplus
#else
	#define __GHIDRA_CXX 0
#endif

#if defined(__cplusplus) && __GHIDRA_CXX < 201402L
	#error "ghidra.hxx needs C++14 or later"
#endif

#ifdef __cplusplus
	#define __GHIDRA_INLINE inline
#else
	#define __GHIDRA_INLINE static inline
#endif

#if defined(__GNUC__) || defined(__clang__)
	#define __GHIDRA_MAY_ALIAS __attribute__((__may_alias__))
	#define __GHIDRA_NORETURN __attribute__((noreturn))
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
	#pragma GCC diagnostic ignored "-Wtype-limits"
#else
	#define __GHIDRA_MAY_ALIAS
	#define __GHIDRA_NORETURN __declspec(noreturn)
#endif

#if defined(__SIZEOF_INT128__)
	#define __GHIDRA_HAS_INT128 1
	typedef unsigned __int128 __GHIDRA_MAY_ALIAS uint128;
	typedef __int128 __GHIDRA_MAY_ALIAS int128;
#else
	#define __GHIDRA_HAS_INT128 0
#endif

typedef unsigned char __GHIDRA_MAY_ALIAS byte;
typedef unsigned short __GHIDRA_MAY_ALIAS word;
typedef unsigned int __GHIDRA_MAY_ALIAS dword;
typedef unsigned long long __GHIDRA_MAY_ALIAS qword;
typedef signed char __GHIDRA_MAY_ALIAS sbyte;
typedef short __GHIDRA_MAY_ALIAS sword;
typedef int __GHIDRA_MAY_ALIAS sdword;
typedef long long __GHIDRA_MAY_ALIAS sqword;

typedef unsigned char __GHIDRA_MAY_ALIAS undefined;
typedef unsigned char __GHIDRA_MAY_ALIAS undefined1;
typedef unsigned short __GHIDRA_MAY_ALIAS undefined2;
typedef unsigned int __GHIDRA_MAY_ALIAS undefined4;
typedef unsigned long long __GHIDRA_MAY_ALIAS undefined8;

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef long long longlong;
typedef unsigned long long ulonglong;
typedef long double longdouble;
typedef long double float10;
typedef dword pointer32;
typedef qword pointer64;

#ifdef GHIDRA_PACKED_ODD_SIZES
typedef struct undefined3 { byte b[3]; } undefined3;
typedef struct undefined5 { byte b[5]; } undefined5;
typedef struct undefined6 { byte b[6]; } undefined6;
typedef struct undefined7 { byte b[7]; } undefined7;
typedef struct uint3 { byte b[3]; } uint3;
typedef struct uint5 { byte b[5]; } uint5;
typedef struct uint6 { byte b[6]; } uint6;
typedef struct uint7 { byte b[7]; } uint7;
typedef struct int3 { byte b[3]; } int3;
typedef struct int5 { byte b[5]; } int5;
typedef struct int6 { byte b[6]; } int6;
typedef struct int7 { byte b[7]; } int7;
#else
typedef dword undefined3;
typedef qword undefined5;
typedef qword undefined6;
typedef qword undefined7;
typedef dword uint3;
typedef qword uint5;
typedef qword uint6;
typedef qword uint7;
typedef sdword int3;
typedef sqword int5;
typedef sqword int6;
typedef sqword int7;
#endif

#if __GHIDRA_HAS_INT128
typedef uint128 undefined9;
typedef uint128 undefined10;
typedef uint128 undefined11;
typedef uint128 undefined12;
typedef uint128 undefined13;
typedef uint128 undefined14;
typedef uint128 undefined15;
typedef uint128 undefined16;
typedef uint128 unkbyte9;
typedef uint128 unkbyte10;
typedef uint128 unkbyte11;
typedef uint128 unkbyte12;
typedef uint128 unkbyte13;
typedef uint128 unkbyte14;
typedef uint128 unkbyte15;
typedef uint128 unkbyte16;
typedef uint128 unkuint9;
typedef uint128 unkuint10;
typedef uint128 unkuint11;
typedef uint128 unkuint12;
typedef uint128 unkuint13;
typedef uint128 unkuint14;
typedef uint128 unkuint15;
typedef uint128 unkuint16;
typedef int128 unkint9;
typedef int128 unkint10;
typedef int128 unkint11;
typedef int128 unkint12;
typedef int128 unkint13;
typedef int128 unkint14;
typedef int128 unkint15;
typedef int128 unkint16;
typedef long double unkfloat10;
#endif

#if !defined(__cplusplus) && !defined(bool) && !defined(IDA_HXX) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L)
typedef unsigned char bool;
	#define true 1
	#define false 0
#endif

#if defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L)
typedef void code(...);
#else
typedef void code();
#endif

#ifndef NULL
	#define NULL 0
#endif

#define CONCAT11(a, b) ((word)(byte)(a) << 8 | (word)(byte)(b))
#define CONCAT12(a, b) ((dword)(byte)(a) << 16 | (dword)(word)(b))
#define CONCAT13(a, b) ((dword)(byte)(a) << 24 | (dword)((dword)(b) & 0xFFFFFFu))
#define CONCAT14(a, b) ((qword)(byte)(a) << 32 | (qword)(dword)(b))
#define CONCAT15(a, b) ((qword)(byte)(a) << 40 | (qword)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT16(a, b) ((qword)(byte)(a) << 48 | (qword)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT17(a, b) ((qword)(byte)(a) << 56 | (qword)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT21(a, b) ((dword)(word)(a) << 8 | (dword)(byte)(b))
#define CONCAT22(a, b) ((dword)(word)(a) << 16 | (dword)(word)(b))
#define CONCAT23(a, b) ((qword)(word)(a) << 24 | (qword)((dword)(b) & 0xFFFFFFu))
#define CONCAT24(a, b) ((qword)(word)(a) << 32 | (qword)(dword)(b))
#define CONCAT25(a, b) ((qword)(word)(a) << 40 | (qword)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT26(a, b) ((qword)(word)(a) << 48 | (qword)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT31(a, b) ((dword)((dword)(a) & 0xFFFFFFu) << 8 | (dword)(byte)(b))
#define CONCAT32(a, b) ((qword)((dword)(a) & 0xFFFFFFu) << 16 | (qword)(word)(b))
#define CONCAT33(a, b) ((qword)((dword)(a) & 0xFFFFFFu) << 24 | (qword)((dword)(b) & 0xFFFFFFu))
#define CONCAT34(a, b) ((qword)((dword)(a) & 0xFFFFFFu) << 32 | (qword)(dword)(b))
#define CONCAT35(a, b) ((qword)((dword)(a) & 0xFFFFFFu) << 40 | (qword)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT41(a, b) ((qword)(dword)(a) << 8 | (qword)(byte)(b))
#define CONCAT42(a, b) ((qword)(dword)(a) << 16 | (qword)(word)(b))
#define CONCAT43(a, b) ((qword)(dword)(a) << 24 | (qword)((dword)(b) & 0xFFFFFFu))
#define CONCAT44(a, b) ((qword)(dword)(a) << 32 | (qword)(dword)(b))
#define CONCAT51(a, b) ((qword)((qword)(a) & 0xFFFFFFFFFFULL) << 8 | (qword)(byte)(b))
#define CONCAT52(a, b) ((qword)((qword)(a) & 0xFFFFFFFFFFULL) << 16 | (qword)(word)(b))
#define CONCAT53(a, b) ((qword)((qword)(a) & 0xFFFFFFFFFFULL) << 24 | (qword)((dword)(b) & 0xFFFFFFu))
#define CONCAT61(a, b) ((qword)((qword)(a) & 0xFFFFFFFFFFFFULL) << 8 | (qword)(byte)(b))
#define CONCAT62(a, b) ((qword)((qword)(a) & 0xFFFFFFFFFFFFULL) << 16 | (qword)(word)(b))
#define CONCAT71(a, b) ((qword)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 8 | (qword)(byte)(b))

#define SUB21(v, o) ((byte)((word)(v) >> ((o) * 8)))
#define SUB31(v, o) ((byte)((dword)(v) >> ((o) * 8)))
#define SUB32(v, o) ((word)((dword)(v) >> ((o) * 8)))
#define SUB41(v, o) ((byte)((dword)(v) >> ((o) * 8)))
#define SUB42(v, o) ((word)((dword)(v) >> ((o) * 8)))
#define SUB43(v, o) ((dword)(((dword)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB51(v, o) ((byte)((qword)(v) >> ((o) * 8)))
#define SUB52(v, o) ((word)((qword)(v) >> ((o) * 8)))
#define SUB53(v, o) ((dword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB54(v, o) ((dword)((qword)(v) >> ((o) * 8)))
#define SUB61(v, o) ((byte)((qword)(v) >> ((o) * 8)))
#define SUB62(v, o) ((word)((qword)(v) >> ((o) * 8)))
#define SUB63(v, o) ((dword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB64(v, o) ((dword)((qword)(v) >> ((o) * 8)))
#define SUB65(v, o) ((qword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFFFFFULL))
#define SUB71(v, o) ((byte)((qword)(v) >> ((o) * 8)))
#define SUB72(v, o) ((word)((qword)(v) >> ((o) * 8)))
#define SUB73(v, o) ((dword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB74(v, o) ((dword)((qword)(v) >> ((o) * 8)))
#define SUB75(v, o) ((qword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFFFFFULL))
#define SUB76(v, o) ((qword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFULL))
#define SUB81(v, o) ((byte)((qword)(v) >> ((o) * 8)))
#define SUB82(v, o) ((word)((qword)(v) >> ((o) * 8)))
#define SUB83(v, o) ((dword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB84(v, o) ((dword)((qword)(v) >> ((o) * 8)))
#define SUB85(v, o) ((qword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFFFFFULL))
#define SUB86(v, o) ((qword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFULL))
#define SUB87(v, o) ((qword)(((qword)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFFFULL))

#define ZEXT12(v) ((word)(byte)(v))
#define ZEXT13(v) ((dword)(byte)(v))
#define ZEXT14(v) ((dword)(byte)(v))
#define ZEXT15(v) ((qword)(byte)(v))
#define ZEXT16(v) ((qword)(byte)(v))
#define ZEXT17(v) ((qword)(byte)(v))
#define ZEXT18(v) ((qword)(byte)(v))
#define ZEXT23(v) ((dword)(word)(v))
#define ZEXT24(v) ((dword)(word)(v))
#define ZEXT25(v) ((qword)(word)(v))
#define ZEXT26(v) ((qword)(word)(v))
#define ZEXT27(v) ((qword)(word)(v))
#define ZEXT28(v) ((qword)(word)(v))
#define ZEXT34(v) ((dword)((dword)(v) & 0xFFFFFFu))
#define ZEXT35(v) ((qword)((dword)(v) & 0xFFFFFFu))
#define ZEXT36(v) ((qword)((dword)(v) & 0xFFFFFFu))
#define ZEXT37(v) ((qword)((dword)(v) & 0xFFFFFFu))
#define ZEXT38(v) ((qword)((dword)(v) & 0xFFFFFFu))
#define ZEXT45(v) ((qword)(dword)(v))
#define ZEXT46(v) ((qword)(dword)(v))
#define ZEXT47(v) ((qword)(dword)(v))
#define ZEXT48(v) ((qword)(dword)(v))
#define ZEXT56(v) ((qword)((qword)(v) & 0xFFFFFFFFFFULL))
#define ZEXT57(v) ((qword)((qword)(v) & 0xFFFFFFFFFFULL))
#define ZEXT58(v) ((qword)((qword)(v) & 0xFFFFFFFFFFULL))
#define ZEXT67(v) ((qword)((qword)(v) & 0xFFFFFFFFFFFFULL))
#define ZEXT68(v) ((qword)((qword)(v) & 0xFFFFFFFFFFFFULL))
#define ZEXT78(v) ((qword)((qword)(v) & 0xFFFFFFFFFFFFFFULL))

#define SEXT12(v) ((sword)(sbyte)(v))
#define SEXT13(v) ((sdword)(sbyte)(v))
#define SEXT14(v) ((sdword)(sbyte)(v))
#define SEXT15(v) ((sqword)(sbyte)(v))
#define SEXT16(v) ((sqword)(sbyte)(v))
#define SEXT17(v) ((sqword)(sbyte)(v))
#define SEXT18(v) ((sqword)(sbyte)(v))
#define SEXT23(v) ((sdword)(sword)(v))
#define SEXT24(v) ((sdword)(sword)(v))
#define SEXT25(v) ((sqword)(sword)(v))
#define SEXT26(v) ((sqword)(sword)(v))
#define SEXT27(v) ((sqword)(sword)(v))
#define SEXT28(v) ((sqword)(sword)(v))
#define SEXT34(v) ((sdword)(((sdword)((dword)(v) << 8)) >> 8))
#define SEXT35(v) ((sqword)(((sdword)((dword)(v) << 8)) >> 8))
#define SEXT36(v) ((sqword)(((sdword)((dword)(v) << 8)) >> 8))
#define SEXT37(v) ((sqword)(((sdword)((dword)(v) << 8)) >> 8))
#define SEXT38(v) ((sqword)(((sdword)((dword)(v) << 8)) >> 8))
#define SEXT45(v) ((sqword)(sdword)(v))
#define SEXT46(v) ((sqword)(sdword)(v))
#define SEXT47(v) ((sqword)(sdword)(v))
#define SEXT48(v) ((sqword)(sdword)(v))
#define SEXT56(v) ((sqword)(((sqword)((qword)(v) << 24)) >> 24))
#define SEXT57(v) ((sqword)(((sqword)((qword)(v) << 24)) >> 24))
#define SEXT58(v) ((sqword)(((sqword)((qword)(v) << 24)) >> 24))
#define SEXT67(v) ((sqword)(((sqword)((qword)(v) << 16)) >> 16))
#define SEXT68(v) ((sqword)(((sqword)((qword)(v) << 16)) >> 16))
#define SEXT78(v) ((sqword)(((sqword)((qword)(v) << 8)) >> 8))

#if __GHIDRA_HAS_INT128
#define CONCAT18(a, b) ((uint128)(byte)(a) << 64 | (uint128)(qword)(b))
#define CONCAT27(a, b) ((uint128)(word)(a) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT28(a, b) ((uint128)(word)(a) << 64 | (uint128)(qword)(b))
#define CONCAT36(a, b) ((uint128)((dword)(a) & 0xFFFFFFu) << 48 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT37(a, b) ((uint128)((dword)(a) & 0xFFFFFFu) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT38(a, b) ((uint128)((dword)(a) & 0xFFFFFFu) << 64 | (uint128)(qword)(b))
#define CONCAT45(a, b) ((uint128)(dword)(a) << 40 | (uint128)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT46(a, b) ((uint128)(dword)(a) << 48 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT47(a, b) ((uint128)(dword)(a) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT48(a, b) ((uint128)(dword)(a) << 64 | (uint128)(qword)(b))
#define CONCAT54(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFULL) << 32 | (uint128)(dword)(b))
#define CONCAT55(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFULL) << 40 | (uint128)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT56(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFULL) << 48 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT57(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFULL) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT58(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFULL) << 64 | (uint128)(qword)(b))
#define CONCAT63(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFULL) << 24 | (uint128)((dword)(b) & 0xFFFFFFu))
#define CONCAT64(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFULL) << 32 | (uint128)(dword)(b))
#define CONCAT65(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFULL) << 40 | (uint128)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT66(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFULL) << 48 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT67(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFULL) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT68(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFULL) << 64 | (uint128)(qword)(b))
#define CONCAT72(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 16 | (uint128)(word)(b))
#define CONCAT73(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 24 | (uint128)((dword)(b) & 0xFFFFFFu))
#define CONCAT74(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 32 | (uint128)(dword)(b))
#define CONCAT75(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 40 | (uint128)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT76(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 48 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT77(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT78(a, b) ((uint128)((qword)(a) & 0xFFFFFFFFFFFFFFULL) << 64 | (uint128)(qword)(b))
#define CONCAT81(a, b) ((uint128)(qword)(a) << 8 | (uint128)(byte)(b))
#define CONCAT82(a, b) ((uint128)(qword)(a) << 16 | (uint128)(word)(b))
#define CONCAT83(a, b) ((uint128)(qword)(a) << 24 | (uint128)((dword)(b) & 0xFFFFFFu))
#define CONCAT84(a, b) ((uint128)(qword)(a) << 32 | (uint128)(dword)(b))
#define CONCAT85(a, b) ((uint128)(qword)(a) << 40 | (uint128)((qword)(b) & 0xFFFFFFFFFFULL))
#define CONCAT86(a, b) ((uint128)(qword)(a) << 48 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFULL))
#define CONCAT87(a, b) ((uint128)(qword)(a) << 56 | (uint128)((qword)(b) & 0xFFFFFFFFFFFFFFULL))
#define CONCAT88(a, b) ((uint128)(qword)(a) << 64 | (uint128)(qword)(b))
#define CONCAT412(a, b) ((uint128)(dword)(a) << 96 | (uint128)((uint128)(b) & ((((uint128)1) << 96) - 1)))
#define CONCAT124(a, b) ((uint128)((uint128)(a) & ((((uint128)1) << 96) - 1)) << 32 | (uint128)(dword)(b))
#define SUB121(v, o) ((byte)((uint128)(v) >> ((o) * 8)))
#define SUB122(v, o) ((word)((uint128)(v) >> ((o) * 8)))
#define SUB123(v, o) ((dword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB124(v, o) ((dword)((uint128)(v) >> ((o) * 8)))
#define SUB125(v, o) ((qword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFFFFFULL))
#define SUB126(v, o) ((qword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFULL))
#define SUB127(v, o) ((qword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFFFULL))
#define SUB128(v, o) ((qword)((uint128)(v) >> ((o) * 8)))
#define SUB161(v, o) ((byte)((uint128)(v) >> ((o) * 8)))
#define SUB162(v, o) ((word)((uint128)(v) >> ((o) * 8)))
#define SUB163(v, o) ((dword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFu))
#define SUB164(v, o) ((dword)((uint128)(v) >> ((o) * 8)))
#define SUB165(v, o) ((qword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFFFFFULL))
#define SUB166(v, o) ((qword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFULL))
#define SUB167(v, o) ((qword)(((uint128)(v) >> ((o) * 8)) & 0xFFFFFFFFFFFFFFULL))
#define SUB168(v, o) ((qword)((uint128)(v) >> ((o) * 8)))
#define SUB1612(v, o) ((uint128)(((uint128)(v) >> ((o) * 8)) & ((((uint128)1) << 96) - 1)))
#define ZEXT112(v) ((uint128)(byte)(v))
#define SEXT112(v) ((int128)(sbyte)(v))
#define ZEXT116(v) ((uint128)(byte)(v))
#define SEXT116(v) ((int128)(sbyte)(v))
#define ZEXT212(v) ((uint128)(word)(v))
#define SEXT212(v) ((int128)(sword)(v))
#define ZEXT216(v) ((uint128)(word)(v))
#define SEXT216(v) ((int128)(sword)(v))
#define ZEXT312(v) ((uint128)((dword)(v) & 0xFFFFFFu))
#define SEXT312(v) ((int128)(((sdword)((dword)(v) << 8)) >> 8))
#define ZEXT316(v) ((uint128)((dword)(v) & 0xFFFFFFu))
#define SEXT316(v) ((int128)(((sdword)((dword)(v) << 8)) >> 8))
#define ZEXT412(v) ((uint128)(dword)(v))
#define SEXT412(v) ((int128)(sdword)(v))
#define ZEXT416(v) ((uint128)(dword)(v))
#define SEXT416(v) ((int128)(sdword)(v))
#define ZEXT512(v) ((uint128)((qword)(v) & 0xFFFFFFFFFFULL))
#define SEXT512(v) ((int128)(((sqword)((qword)(v) << 24)) >> 24))
#define ZEXT516(v) ((uint128)((qword)(v) & 0xFFFFFFFFFFULL))
#define SEXT516(v) ((int128)(((sqword)((qword)(v) << 24)) >> 24))
#define ZEXT612(v) ((uint128)((qword)(v) & 0xFFFFFFFFFFFFULL))
#define SEXT612(v) ((int128)(((sqword)((qword)(v) << 16)) >> 16))
#define ZEXT616(v) ((uint128)((qword)(v) & 0xFFFFFFFFFFFFULL))
#define SEXT616(v) ((int128)(((sqword)((qword)(v) << 16)) >> 16))
#define ZEXT712(v) ((uint128)((qword)(v) & 0xFFFFFFFFFFFFFFULL))
#define SEXT712(v) ((int128)(((sqword)((qword)(v) << 8)) >> 8))
#define ZEXT716(v) ((uint128)((qword)(v) & 0xFFFFFFFFFFFFFFULL))
#define SEXT716(v) ((int128)(((sqword)((qword)(v) << 8)) >> 8))
#define ZEXT812(v) ((uint128)(qword)(v))
#define SEXT812(v) ((int128)(sqword)(v))
#define ZEXT816(v) ((uint128)(qword)(v))
#define SEXT816(v) ((int128)(sqword)(v))
#define ZEXT1216(v) ((uint128)((uint128)(v) & ((((uint128)1) << 96) - 1)))
#define SEXT1216(v) ((int128)(((int128)((uint128)(v) << 32)) >> 32))
#endif

#ifdef __cplusplus
	#define __GHIDRA_CONSTEXPR constexpr
#else
	#define __GHIDRA_CONSTEXPR static inline
#endif

__GHIDRA_CONSTEXPR bool CARRY1(byte a, byte b) { return (byte)(a + b) < a; }
__GHIDRA_CONSTEXPR bool CARRY2(word a, word b) { return (word)(a + b) < a; }
__GHIDRA_CONSTEXPR bool CARRY4(dword a, dword b) { return (dword)(a + b) < a; }
__GHIDRA_CONSTEXPR bool CARRY8(qword a, qword b) { return (qword)(a + b) < a; }

__GHIDRA_CONSTEXPR bool BORROW1(byte a, byte b) { return a < b; }
__GHIDRA_CONSTEXPR bool BORROW2(word a, word b) { return a < b; }
__GHIDRA_CONSTEXPR bool BORROW4(dword a, dword b) { return a < b; }
__GHIDRA_CONSTEXPR bool BORROW8(qword a, qword b) { return a < b; }

__GHIDRA_CONSTEXPR bool SCARRY1(sbyte a, sbyte b) {
	sbyte r = (sbyte)((byte)a + (byte)b);
	return ((a ^ r) & (b ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SCARRY2(sword a, sword b) {
	sword r = (sword)((word)a + (word)b);
	return ((a ^ r) & (b ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SCARRY4(sdword a, sdword b) {
	sdword r = (sdword)((dword)a + (dword)b);
	return ((a ^ r) & (b ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SCARRY8(sqword a, sqword b) {
	sqword r = (sqword)((qword)a + (qword)b);
	return ((a ^ r) & (b ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SBORROW1(sbyte a, sbyte b) {
	sbyte r = (sbyte)((byte)a - (byte)b);
	return ((a ^ b) & (a ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SBORROW2(sword a, sword b) {
	sword r = (sword)((word)a - (word)b);
	return ((a ^ b) & (a ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SBORROW4(sdword a, sdword b) {
	sdword r = (sdword)((dword)a - (dword)b);
	return ((a ^ b) & (a ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SBORROW8(sqword a, sqword b) {
	sqword r = (sqword)((qword)a - (qword)b);
	return ((a ^ b) & (a ^ r)) < 0;
}

#if __GHIDRA_HAS_INT128
__GHIDRA_CONSTEXPR bool CARRY16(uint128 a, uint128 b) { return (uint128)(a + b) < a; }
__GHIDRA_CONSTEXPR bool BORROW16(uint128 a, uint128 b) { return a < b; }

__GHIDRA_CONSTEXPR bool SCARRY16(int128 a, int128 b) {
	int128 r = (int128)((uint128)a + (uint128)b);
	return ((a ^ r) & (b ^ r)) < 0;
}

__GHIDRA_CONSTEXPR bool SBORROW16(int128 a, int128 b) {
	int128 r = (int128)((uint128)a - (uint128)b);
	return ((a ^ b) & (a ^ r)) < 0;
}
#endif

#ifdef __cplusplus

template<class T> constexpr int POPCOUNT(T value) {
	typedef typename std::make_unsigned<T>::type bits_t;
	bits_t bits = (bits_t)value;
	int count = 0;
	while ( bits != 0 ) {
		count += (int)(bits & 1);
		bits = (bits_t)(bits >> 1);
	}
	return count;
}

template<class T> constexpr int LZCOUNT(T value) {
	typedef typename std::make_unsigned<T>::type bits_t;
	const bits_t bits = (bits_t)value;
	const int total = (int)(sizeof(T) * 8);
	int count = 0;
	while ( count < total && ((bits >> (total - 1 - count)) & 1) == 0 ) { ++count; }
	return count;
}

template<class T> constexpr T ABS(T value) { return value > (T)0 ? value : (T)-value; }

#else

static inline int POPCOUNT(qword value) {
	int count = 0;
	while ( value != 0 ) {
		count += (int)(value & 1);
		value >>= 1;
	}
	return count;
}

static inline int LZCOUNT(qword value) {
	int count = 0;
	while ( count < 64 && ((value >> (63 - count)) & 1) == 0 ) { ++count; }
	return count;
}

static inline double ABS(double value) { return value > 0 ? value : -value; }

#endif

#ifdef NAN
	#undef NAN
#endif

__GHIDRA_INLINE bool __ghidra_isnan(double value) { return value != value; }

#define NAN(x) __ghidra_isnan(x)

__GHIDRA_INLINE double SQRT(double value) { return sqrt(value); }
__GHIDRA_INLINE double ROUND(double value) { return round(value); }
__GHIDRA_INLINE double CEIL(double value) { return ceil(value); }
__GHIDRA_INLINE double FLOOR(double value) { return floor(value); }
__GHIDRA_INLINE double TRUNC(double value) { return trunc(value); }

__GHIDRA_NORETURN __GHIDRA_INLINE void halt_baddata(void) { abort(); }
__GHIDRA_NORETURN __GHIDRA_INLINE void halt_unimplemented(void) { abort(); }
__GHIDRA_NORETURN __GHIDRA_INLINE void invalidInstructionException(void) { abort(); }

#ifndef GHIDRA_NO_EXTRAS
#ifndef GHIDRA_NO_KEYWORDS
	#if !defined(_MSC_VER)
		#define __cdecl
		#define __stdcall
		#define __fastcall
		#define __thiscall
		#define __vectorcall
		#define __regparm1
		#define __regparm2
		#define __regparm3
		#define __forceinline inline
		#define __declspec(x)
	#endif
#endif
#endif

#if defined(__GNUC__) || defined(__clang__)
	#pragma GCC diagnostic pop
#endif

#endif
