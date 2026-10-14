#ifndef IDA_HXX
#define IDA_HXX

#include <stddef.h>
#ifdef __cplusplus
	#include <string.h>
	#include <type_traits>
#endif

#if defined(_MSVC_LANG)
	#define __IDA_CXX _MSVC_LANG
#elif defined(__cplusplus)
	#define __IDA_CXX __cplusplus
#else
	#define __IDA_CXX 0
#endif

#if defined(__cplusplus) && __IDA_CXX < 201402L
	#error "ida.hxx needs C++14 or later"
#endif

#ifdef __cplusplus
	#define __IDA_INLINE inline
#else
	#define __IDA_INLINE static inline
#endif

#if defined(__GNUC__) || defined(__clang__)
	#define __IDA_MAY_ALIAS __attribute__((__may_alias__))
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wpedantic"
#else
	#define __IDA_MAY_ALIAS
#endif

#if defined(__GNUC__)
	typedef long long ll;
	typedef unsigned long long ull;
	#define __int64 long long
	#define __int32 int
	#define __int16 short
	#define __int8 char
	#define MAKELL(num) num ## LL
	#define FMT_64 "ll"
#elif defined(_MSC_VER)
	typedef __int64 ll;
	typedef unsigned __int64 ull;
	#define MAKELL(num) num ## i64
	#define FMT_64 "I64"
#elif defined(__BORLANDC__)
	typedef __int64 ll;
	typedef unsigned __int64 ull;
	#define MAKELL(num) num ## i64
	#define FMT_64 "L"
#else
	#error "unknown compiler"
#endif

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef char int8;
typedef signed char sint8;
typedef unsigned char uint8;
typedef short int16;
typedef signed short sint16;
typedef unsigned short uint16;
typedef int int32;
typedef signed int sint32;
typedef unsigned int uint32;
typedef ll int64;
typedef ll sint64;
typedef ull uint64;

#if defined(__SIZEOF_INT128__)
	#define __IDA_HAS_INT128 1
	#define __IDA_MAX_WORD 16
	typedef __int128 int128;
	typedef __int128 sint128;
	typedef unsigned __int128 uint128;
#else
	#define __IDA_HAS_INT128 0
	#define __IDA_MAX_WORD 8
#endif

#define _BYTE uint8
#define _WORD uint16
#define _DWORD uint32
#define _QWORD uint64
#if __IDA_HAS_INT128
	#define _LONGLONG __int128
	#define _OWORD uint128
#endif

typedef int8 _BOOL1;
typedef int16 _BOOL2;
typedef int32 _BOOL4;
typedef int64 _BOOL8;

#if !defined(_WINDOWS_) && !defined(_WINDEF_)
typedef int8 BYTE;
typedef int16 WORD;
typedef int32 DWORD;
typedef int32 LONG;
typedef int BOOL;
#endif
typedef int64 QWORD;
#if !defined(__cplusplus) && !defined(bool) && (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L)
typedef int bool;
#endif

#define __pure

#if defined(__GNUC__) || defined(__clang__)
	#define __noreturn __attribute__((noreturn))
#else
	#define __noreturn __declspec(noreturn)
#endif

#ifndef NULL
	#define NULL 0
#endif

typedef uint8 __IDA_MAY_ALIAS __ida_byte;
typedef uint16 __IDA_MAY_ALIAS __ida_word;
typedef uint32 __IDA_MAY_ALIAS __ida_dword;
typedef uint64 __IDA_MAY_ALIAS __ida_qword;
typedef sint8 __IDA_MAY_ALIAS __ida_sbyte;
typedef sint16 __IDA_MAY_ALIAS __ida_sword;
typedef sint32 __IDA_MAY_ALIAS __ida_sdword;
typedef sint64 __IDA_MAY_ALIAS __ida_sqword;

#define LAST_IND(x, part_type) (sizeof(x)/sizeof(part_type) - 1)
#if (defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__) \
 || (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) \
 || defined(__BIG_ENDIAN__)
	#define LOW_IND(x, part_type) LAST_IND(x, part_type)
	#define HIGH_IND(x, part_type) 0
#else
	#define HIGH_IND(x, part_type) LAST_IND(x, part_type)
	#define LOW_IND(x, part_type) 0
#endif

#define BYTEn(x, n) (*((__ida_byte *)&(x) + (n)))
#define WORDn(x, n) (*((__ida_word *)&(x) + (n)))
#define DWORDn(x, n) (*((__ida_dword *)&(x) + (n)))
#define QWORDn(x, n) (*((__ida_qword *)&(x) + (n)))

#define LOBYTE(x) BYTEn(x, LOW_IND(x, _BYTE))
#define LOWORD(x) WORDn(x, LOW_IND(x, _WORD))
#define LODWORD(x) DWORDn(x, LOW_IND(x, _DWORD))
#define LOQWORD(x) QWORDn(x, LOW_IND(x, _QWORD))
#define HIBYTE(x) BYTEn(x, HIGH_IND(x, _BYTE))
#define HIWORD(x) WORDn(x, HIGH_IND(x, _WORD))
#define HIDWORD(x) DWORDn(x, HIGH_IND(x, _DWORD))
#define HIQWORD(x) QWORDn(x, HIGH_IND(x, _QWORD))
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define BYTE8(x) BYTEn(x, 8)
#define BYTE9(x) BYTEn(x, 9)
#define BYTE10(x) BYTEn(x, 10)
#define BYTE11(x) BYTEn(x, 11)
#define BYTE12(x) BYTEn(x, 12)
#define BYTE13(x) BYTEn(x, 13)
#define BYTE14(x) BYTEn(x, 14)
#define BYTE15(x) BYTEn(x, 15)
#define WORD1(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2)
#define WORD3(x) WORDn(x, 3)
#define WORD4(x) WORDn(x, 4)
#define WORD5(x) WORDn(x, 5)
#define WORD6(x) WORDn(x, 6)
#define WORD7(x) WORDn(x, 7)
#define DWORD1(x) DWORDn(x, 1)
#define DWORD2(x) DWORDn(x, 2)
#define DWORD3(x) DWORDn(x, 3)
#define QWORD1(x) QWORDn(x, 1)

#define SBYTEn(x, n) (*((__ida_sbyte *)&(x) + (n)))
#define SWORDn(x, n) (*((__ida_sword *)&(x) + (n)))
#define SDWORDn(x, n) (*((__ida_sdword *)&(x) + (n)))
#define SQWORDn(x, n) (*((__ida_sqword *)&(x) + (n)))

#define SLOBYTE(x) SBYTEn(x, LOW_IND(x, int8))
#define SLOWORD(x) SWORDn(x, LOW_IND(x, int16))
#define SLODWORD(x) SDWORDn(x, LOW_IND(x, int32))
#define SLOQWORD(x) SQWORDn(x, LOW_IND(x, int64))
#define SHIBYTE(x) SBYTEn(x, HIGH_IND(x, int8))
#define SHIWORD(x) SWORDn(x, HIGH_IND(x, int16))
#define SHIDWORD(x) SDWORDn(x, HIGH_IND(x, int32))
#define SHIQWORD(x) SQWORDn(x, HIGH_IND(x, int64))
#define SBYTE1(x) SBYTEn(x, 1)
#define SBYTE2(x) SBYTEn(x, 2)
#define SBYTE3(x) SBYTEn(x, 3)
#define SBYTE4(x) SBYTEn(x, 4)
#define SBYTE5(x) SBYTEn(x, 5)
#define SBYTE6(x) SBYTEn(x, 6)
#define SBYTE7(x) SBYTEn(x, 7)
#define SBYTE8(x) SBYTEn(x, 8)
#define SBYTE9(x) SBYTEn(x, 9)
#define SBYTE10(x) SBYTEn(x, 10)
#define SBYTE11(x) SBYTEn(x, 11)
#define SBYTE12(x) SBYTEn(x, 12)
#define SBYTE13(x) SBYTEn(x, 13)
#define SBYTE14(x) SBYTEn(x, 14)
#define SBYTE15(x) SBYTEn(x, 15)
#define SWORD1(x) SWORDn(x, 1)
#define SWORD2(x) SWORDn(x, 2)
#define SWORD3(x) SWORDn(x, 3)
#define SWORD4(x) SWORDn(x, 4)
#define SWORD5(x) SWORDn(x, 5)
#define SWORD6(x) SWORDn(x, 6)
#define SWORD7(x) SWORDn(x, 7)
#define SDWORD1(x) SDWORDn(x, 1)
#define SDWORD2(x) SDWORDn(x, 2)
#define SDWORD3(x) SDWORDn(x, 3)

#define __SPAIR16__(high, low) (((int16) (high) << 8) | (uint8) (low))
#define __SPAIR32__(high, low) (((int32) (high) << 16) | (uint16)(low))
#define __SPAIR64__(high, low) (((int64) (high) << 32) | (uint32)(low))
#define __PAIR16__(high, low) (((uint16) (high) << 8) | (uint8) (low))
#define __PAIR32__(high, low) (((uint32) (high) << 16) | (uint16)(low))
#define __PAIR64__(high, low) (((uint64) (high) << 32) | (uint32)(low))
#if __IDA_HAS_INT128
	#define __SPAIR128__(high, low) (((int128) (high) << 64) | (uint64)(low))
	#define __PAIR128__(high, low) (((uint128)(high) << 64) | (uint64)(low))
#endif

#ifndef SUB_WITH_CARRY
	#if defined(__ARM__) || defined(__PPC__)
		#define SUB_WITH_CARRY 1
	#else
		#define SUB_WITH_CARRY 0
	#endif
#endif

#ifdef __cplusplus

#define CASSERT(cnd) static_assert((cnd), #cnd)

template<size_t __n> struct __ida_uint_of;
template<> struct __ida_uint_of<1> { typedef uint8 type; };
template<> struct __ida_uint_of<2> { typedef uint16 type; };
template<> struct __ida_uint_of<4> { typedef uint32 type; };
template<> struct __ida_uint_of<8> { typedef uint64 type; };

template<size_t __n> struct __ida_int_of;
template<> struct __ida_int_of<1> { typedef sint8 type; };
template<> struct __ida_int_of<2> { typedef sint16 type; };
template<> struct __ida_int_of<4> { typedef sint32 type; };
template<> struct __ida_int_of<8> { typedef sint64 type; };

#if __IDA_HAS_INT128
template<> struct __ida_uint_of<16> { typedef uint128 type; };
template<> struct __ida_int_of<16> { typedef sint128 type; };
#endif

constexpr size_t __ida_word_size(size_t size) {
	return size <= 1 ? 1 : size <= 2 ? 2 : size <= 4 ? 4 : size <= 8 ? 8 : (size_t)__IDA_MAX_WORD;
}

template<class T> struct __ida_word_of {
	typedef typename __ida_uint_of<__ida_word_size(sizeof(T))>::type utype;
	typedef typename __ida_int_of<__ida_word_size(sizeof(T))>::type stype;
};

template<class T, class U> struct __ida_wide_of {
	static constexpr size_t size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	typedef typename __ida_uint_of<__ida_word_size(size)>::type utype;
	typedef typename __ida_int_of<__ida_word_size(size)>::type stype;
};

template<class T, class U> constexpr bool is_mul_ok(T count, U elsize) {
	typedef typename __ida_wide_of<T, U>::utype W;
	return (W)count == 0 || (W)elsize == 0 ? true : (W)count <= (W)(W)(~(W)0) / (W)elsize;
}

template<class T> constexpr T saturated_mul(T count, T elsize) {
	return is_mul_ok(count, elsize) ? (T)(count * elsize) : (T)~(T)0;
}

inline void *qmemcpy(void *dst, const void *src, size_t cnt) {
	char *out = (char *)dst;
	const char *in = (const char *)src;
	while ( cnt > 0 ) {
		*out++ = *in++;
		--cnt;
	}
	return dst;
}

template<class T> constexpr T __ROL__(T value, int count) {
	typedef typename __ida_word_of<T>::utype W;
	const int nbits = (int)(sizeof(T) * 8);
	int shift = count % nbits;
	if ( shift < 0 ) { shift += nbits; }
	if ( shift == 0 ) { return value; }
	const W bits = (W)value;
	return (T)(W)((W)(bits << shift) | (W)(bits >> (nbits - shift)));
}

template<class T> constexpr T __ROR__(T value, int count) { return __ROL__(value, -count); }

constexpr uint8 __ROL1__(uint8 value, int count) { return __ROL__(value, count); }
constexpr uint16 __ROL2__(uint16 value, int count) { return __ROL__(value, count); }
constexpr uint32 __ROL4__(uint32 value, int count) { return __ROL__(value, count); }
constexpr uint64 __ROL8__(uint64 value, int count) { return __ROL__(value, count); }
constexpr uint8 __ROR1__(uint8 value, int count) { return __ROL__(value, -count); }
constexpr uint16 __ROR2__(uint16 value, int count) { return __ROL__(value, -count); }
constexpr uint32 __ROR4__(uint32 value, int count) { return __ROL__(value, -count); }
constexpr uint64 __ROR8__(uint64 value, int count) { return __ROL__(value, -count); }

template<class T> constexpr int8 __MKCSHL__(T value, uint count) {
	typedef typename __ida_word_of<T>::utype W;
	const uint nbits = (uint)(sizeof(T) * 8);
	const uint shift = count % nbits;
	return shift == 0 ? (int8)0 : (int8)(((W)value >> (nbits - shift)) & 1);
}

template<class T> constexpr int8 __MKCSHR__(T value, uint count) {
	typedef typename __ida_word_of<T>::utype W;
	const uint nbits = (uint)(sizeof(T) * 8);
	return count == 0 ? (int8)0 : (int8)(((W)value >> ((count - 1) & (nbits - 1))) & 1);
}

template<class T> constexpr int8 __CFSHL__(T value, uint count) { return __MKCSHL__(value, count); }
template<class T> constexpr int8 __CFSHR__(T value, uint count) { return __MKCSHR__(value, count); }

template<class T> constexpr int8 __SETS__(T x) {
	typedef typename __ida_word_of<T>::stype S;
	return (int8)((S)x < 0);
}

template<class T> constexpr int8 __SETZ__(T x) {
	typedef typename __ida_word_of<T>::utype W;
	return (int8)((W)x == 0);
}

template<class T, class U> constexpr int8 __SETP__(T x, U y) {
	typedef typename __ida_wide_of<T, U>::utype W;
	uint8 bits = (uint8)((W)x - (W)y);
	bits = (uint8)(bits ^ (bits >> 4));
	bits = (uint8)(bits ^ (bits >> 2));
	bits = (uint8)(bits ^ (bits >> 1));
	return (int8)((bits & 1) == 0);
}

template<class T, class U> constexpr int8 __OFADD__(T x, U y) {
	typedef typename __ida_wide_of<T, U>::utype W;
	typedef typename __ida_wide_of<T, U>::stype S;
	const S a = (S)x;
	const S b = (S)y;
	const S r = (S)(W)((W)a + (W)b);
	return (int8)(((a ^ r) & (b ^ r)) < 0);
}

template<class T, class U> constexpr int8 __OFSUB__(T x, U y) {
	typedef typename __ida_wide_of<T, U>::utype W;
	typedef typename __ida_wide_of<T, U>::stype S;
	const S a = (S)x;
	const S b = (S)y;
	const S r = (S)(W)((W)a - (W)b);
	return (int8)(((a ^ b) & (a ^ r)) < 0);
}

template<class T, class U> constexpr int8 __CFADD__(T x, U y) {
	typedef typename __ida_wide_of<T, U>::utype W;
	const W a = (W)x;
	return (int8)((W)(a + (W)y) < a);
}

template<class T, class U> constexpr int8 __CFSUB__(T x, U y) {
	typedef typename __ida_wide_of<T, U>::utype W;
	const bool res = (W)x < (W)y;
	return (int8)(SUB_WITH_CARRY ? !res : res);
}

template<class T, class U> constexpr int8 __CFADD__(T x, U y, int8 cf) {
	typedef typename __ida_wide_of<T, U>::utype W;
	const W a = (W)x;
	const W sum = (W)(a + (W)y);
	return (int8)(sum < a || (W)(sum + (W)(cf != 0)) < sum);
}

template<class T, class U> constexpr int8 __CFSUB__(T x, U y, int8 cf) {
	typedef typename __ida_wide_of<T, U>::utype W;
	const W a = (W)x;
	const W b = (W)y;
	const W borrow = (W)(SUB_WITH_CARRY ? (cf == 0) : (cf != 0));
	const bool res = a < b || (W)(a - b) < borrow;
	return (int8)(SUB_WITH_CARRY ? !res : res);
}

template<class T, class U> constexpr int8 __OFADD__(T x, U y, int8 cf) {
	typedef typename __ida_wide_of<T, U>::utype W;
	typedef typename __ida_wide_of<T, U>::stype S;
	const S a = (S)x;
	const S b = (S)y;
	const S r = (S)(W)((W)a + (W)b + (W)(cf != 0));
	return (int8)(((a ^ r) & (b ^ r)) < 0);
}

template<class T, class U> constexpr int8 __OFSUB__(T x, U y, int8 cf) {
	typedef typename __ida_wide_of<T, U>::utype W;
	typedef typename __ida_wide_of<T, U>::stype S;
	const S a = (S)x;
	const S b = (S)y;
	const W borrow = (W)(SUB_WITH_CARRY ? (cf == 0) : (cf != 0));
	const S r = (S)(W)((W)a - (W)b - borrow);
	return (int8)(((a ^ b) & (a ^ r)) < 0);
}

constexpr uint8 abs8(int8 x) { return (uint8) ((sint8) x < 0 ? -(uint8) x : (uint8) x); }
constexpr uint16 abs16(int16 x) { return (uint16)((sint16)x < 0 ? -(uint16)x : (uint16)x); }
constexpr uint32 abs32(int32 x) { return (uint32)((sint32)x < 0 ? -(uint32)x : (uint32)x); }
constexpr uint64 abs64(int64 x) { return (uint64)((sint64)x < 0 ? -(uint64)x : (uint64)x); }
#if __IDA_HAS_INT128
constexpr uint128 abs128(int128 x) { return (uint128)(x < 0 ? -(uint128)x : (uint128)x); }
#endif

template<class T, class F>
inline typename std::enable_if<sizeof(T) <= sizeof(F), T>::type __coerce(F f) {
	T t{};
	memcpy(&t, &f, sizeof(T));
	return t;
}

#define COERCE_FLOAT(v) __coerce<float>(v)
#define COERCE_DOUBLE(v) __coerce<double>(v)
#define COERCE_LONG_DOUBLE(v) __coerce<long double>(v)
#define COERCE_INT(v) __coerce<int32>(v)
#define COERCE_UNSIGNED_INT(v) __coerce<unsigned int>(v)
#define COERCE_INT64(v) __coerce<int64>(v)
#define COERCE_UNSIGNED_INT64(v) __coerce<uint64>(v)

#else

#define __ROL__(x, y) __rotl__(x, y)
#define __ROR__(x, y) __rotr__(x, y)
#define __CFSHL__(x, y) invalid_operation
#define __CFSHR__(x, y) invalid_operation
#define __CFADD__(x, y) invalid_operation
#define __CFSUB__(x, y) invalid_operation
#define __OFADD__(x, y) invalid_operation
#define __OFSUB__(x, y) invalid_operation
#define __SETP__(x, y) invalid_operation

#define abs8(x) (int8) ((int8) (x) >= 0 ? (x) : -(x))
#define abs16(x) (int16) ((int16) (x) >= 0 ? (x) : -(x))
#define abs32(x) (int32) ((int32) (x) >= 0 ? (x) : -(x))
#define abs64(x) (int64) ((int64) (x) >= 0 ? (x) : -(x))
#define abs128(x) (int128)((int128)(x) >= 0 ? (x) : -(x))

#endif

#if defined(__MIPS__)

void __noreturn __integer_oveflow(void);
void __noreturn __divide_by_zero(void);
void __noreturn __trap(uint16 trapcode);
void __noreturn __break(uint16 code, uint16 subcode);
#endif

#define __RCL__(x, y) invalid_operation
#define __RCR__(x, y) invalid_operation
#define __MKCRCL__(x, y) invalid_operation
#define __MKCRCR__(x, y) invalid_operation

#define _UNKNOWN char

#if defined(_MSC_VER) && _MSC_VER < 1900
	#define snprintf _snprintf
	#define vsnprintf _vsnprintf
#endif

#define ADJ(p) (__parentof(p) *)(p-__deltaof(p))

#ifndef IDA_NO_EXTRAS

#ifndef IDA_NO_KEYWORDS
	#define __usercall
	#define __userpurge
	#define __golang
	#define __hidden
	#define __return_ptr
	#define __struct_ptr
	#define __array_ptr
	#define __spoils(...)
	#define __shifted(parent, delta)

	#if !defined(_MSC_VER)
		#define __cdecl
		#define __stdcall
		#define __fastcall
		#define __thiscall
		#define __vectorcall
		#define __unaligned
		#define __ptr32
		#define __ptr64
		#define __forceinline inline
		#define __declspec(x)
	#endif
#endif

extern _UNKNOWN MEMORY[];

#ifdef IDA_MEMORY_STORAGE
_UNKNOWN MEMORY[0x10000];
#endif

#if (defined(__GNUC__) || defined(__clang__)) && !defined(_MSC_VER) && !defined(IDA_NO_INTRINSICS)

__IDA_INLINE uint16 _byteswap_ushort(uint16 value) { return __builtin_bswap16(value); }
__IDA_INLINE uint32 _byteswap_ulong(uint32 value) { return __builtin_bswap32(value); }
__IDA_INLINE uint64 _byteswap_uint64(uint64 value) { return __builtin_bswap64(value); }

__IDA_INLINE uchar _BitScanForward(ulong *index, ulong mask) {
	if ( mask == 0 ) { return 0; }
	*index = (ulong)__builtin_ctzl(mask);
	return 1;
}

__IDA_INLINE uchar _BitScanReverse(ulong *index, ulong mask) {
	if ( mask == 0 ) { return 0; }
	*index = (ulong)(8 * sizeof(ulong) - 1 - (size_t)__builtin_clzl(mask));
	return 1;
}

__IDA_INLINE uchar _BitScanForward64(ulong *index, uint64 mask) {
	if ( mask == 0 ) { return 0; }
	*index = (ulong)__builtin_ctzll(mask);
	return 1;
}

__IDA_INLINE uchar _BitScanReverse64(ulong *index, uint64 mask) {
	if ( mask == 0 ) { return 0; }
	*index = (ulong)(63 - __builtin_clzll(mask));
	return 1;
}

__IDA_INLINE void __debugbreak(void) { __builtin_trap(); }

	#if (defined(__x86_64__) || defined(__i386__)) && !defined(__clang__)
__IDA_INLINE uint64 __rdtsc(void) { return __builtin_ia32_rdtsc(); }
	#endif

	#if defined(__x86_64__)
__IDA_INLINE uint64 __readgsqword(ulong offset) {
	uint64 value = 0;
	__asm__ __volatile__("movq %%gs:(%1), %0" : "=r"(value) : "r"((uint64)offset));
	return value;
}

__IDA_INLINE uint32 __readgsdword(ulong offset) {
	uint32 value = 0;
	__asm__ __volatile__("movl %%gs:(%1), %0" : "=r"(value) : "r"((uint64)offset));
	return value;
}
	#endif

	#if defined(__i386__)
__IDA_INLINE uint32 __readfsdword(ulong offset) {
	uint32 value = 0;
	__asm__ __volatile__("movl %%fs:(%1), %0" : "=r"(value) : "r"(offset));
	return value;
}
	#endif

#endif

#endif

#if defined(__GNUC__) || defined(__clang__)
	#pragma GCC diagnostic pop
#endif

#endif
