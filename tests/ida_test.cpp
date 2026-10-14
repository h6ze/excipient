#include <assert.h>
#include <stdio.h>

#define IDA_MEMORY_STORAGE
#include "../libraries/ida.hxx"

static_assert(__ROL4__(0x12345678u, 8) == 0x34567812u, "rol4");
static_assert(__ROR4__(0x12345678u, 8) == 0x78123456u, "ror4");
static_assert(__ROL1__(0x81, 1) == 0x03, "rol1");
static_assert(__ROR1__(0x01, 1) == 0x80, "ror1");
static_assert(__ROL2__(0x8001, 1) == 0x0003, "rol2");
static_assert(__ROL8__(0x8000000000000000ull, 1) == 1ull, "rol8");
static_assert(__ROL4__(0x12345678u, 0) == 0x12345678u, "rol4 zero");
static_assert(__ROL4__(0x12345678u, 32) == 0x12345678u, "rol4 full");
static_assert(__ROL4__(0x12345678u, -8) == 0x78123456u, "rol4 negative");
static_assert(__ROL__((sint32)-2, 1) == -3, "rol signed");

static_assert(__CFADD__((uint8)0xFF, (uint8)1) == 1, "cfadd8");
static_assert(__CFADD__((uint8)0x7F, (uint8)1) == 0, "cfadd8 none");
static_assert(__CFADD__(0xFFFFFFFFu, 1u) == 1, "cfadd32");
static_assert(__CFADD__((uint8)0xFF, (uint8)0, (int8)1) == 1, "adc carry out");
static_assert(__CFADD__((uint8)0xFE, (uint8)0, (int8)1) == 0, "adc no carry");
static_assert(__CFSUB__(1u, 2u) == 1, "cfsub");
static_assert(__CFSUB__(2u, 1u) == 0, "cfsub none");
static_assert(__CFSUB__((uint8)0, (uint8)0, (int8)1) == 1, "sbb borrow out");
static_assert(__OFADD__((sint8)127, (sint8)1) == 1, "ofadd8");
static_assert(__OFADD__((sint8)1, (sint8)1) == 0, "ofadd8 none");
static_assert(__OFADD__(0x7FFFFFFF, 1) == 1, "ofadd32");
static_assert(__OFADD__((sint8)126, (sint8)1, (int8)1) == 1, "adc overflow");
static_assert(__OFSUB__((sint8)-128, (sint8)1) == 1, "ofsub8");
static_assert(__OFSUB__(5, 1) == 0, "ofsub none");
static_assert(__OFSUB__((sint8)-128, (sint8)0, (int8)1) == 1, "sbb overflow");
static_assert(__OFSUB__((sint16)-32768, (sint16)1) == 1, "ofsub16");
static_assert(__OFSUB__((sint16)-32768, 1) == 0, "ofsub widens to the larger operand");

static_assert(__MKCSHL__(0x80000000u, 1) == 1, "mkcshl");
static_assert(__MKCSHL__(0x40000000u, 1) == 0, "mkcshl none");
static_assert(__MKCSHL__(0x40000000u, 2) == 1, "mkcshl two");
static_assert(__MKCSHL__(0xFFFFFFFFu, 0) == 0, "mkcshl zero count");
static_assert(__MKCSHR__(2u, 2) == 1, "mkcshr");
static_assert(__MKCSHR__(1u, 1) == 1, "mkcshr one");
static_assert(__MKCSHR__(1u, 0) == 0, "mkcshr zero count");
static_assert(__CFSHL__((uint8)0x80, 1) == 1, "cfshl");

static_assert(__SETS__((sint8)-1) == 1, "sets");
static_assert(__SETS__((uint8)0x80) == 1, "sets unsigned");
static_assert(__SETS__(1) == 0, "sets none");
static_assert(__SETZ__(0u) == 1, "setz");
static_assert(__SETZ__((uint8)0x100) == 1, "setz truncated");
static_assert(__SETP__(3, 0) == 1, "setp even");
static_assert(__SETP__(3, 1) == 0, "setp odd");

static_assert(abs8(-128) == 128u, "abs8");
static_assert(abs8(-7) == 7u, "abs8 small");
static_assert(abs32(-2147483647 - 1) == 2147483648u, "abs32");
static_assert(abs64(-5) == 5u, "abs64");

static_assert(is_mul_ok(0x10, 4) == true, "mulok");
static_assert(is_mul_ok(0xFFFFFFFFu, 4u) == false, "mulok overflow");
static_assert(is_mul_ok(0u, 4u) == true, "mulok zero");
static_assert(saturated_mul<uint32>(4u, 4u) == 16u, "satmul");
static_assert(saturated_mul<uint32>(0xFFFFFFFFu, 4u) == 0xFFFFFFFFu, "satmul saturate");

static_assert(__PAIR16__(0x12, 0x34) == 0x1234, "pair16");
static_assert(__PAIR32__(0x1234, 0x5678) == 0x12345678u, "pair32");
static_assert(__PAIR64__(1u, 2u) == 0x100000002ull, "pair64");
static_assert(__SPAIR64__(0xFFFFFFFFu, 0xFFFFFFFFu) == -1, "spair64");
#if __IDA_HAS_INT128
static_assert((uint64)(__PAIR128__(1ull, 2ull) >> 64) == 1ull, "pair128");
static_assert(__SPAIR128__(0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFFull) == (int128)-1, "spair128");
#endif

__int64 __fastcall sub_140001000(__int64 a1, unsigned __int8 *a2, unsigned int a3) {
	unsigned int v3;
	__int64 v4;
	_BOOL4 v5;

	v3 = __ROL4__(a3 ^ 0xDEADBEEF, 7);
	LOBYTE(v3) = 0x41;
	HIWORD(v3) = 0x1337;
	BYTE1(v3) ^= *a2;
	v4 = __PAIR64__(v3, a3);
	if ( __CFADD__(a3, 0x10u) ) { v4 ^= 1; }
	if ( __OFSUB__((int)a3, 5) ) { v4 ^= 2; }
	if ( __SETP__(a3, 3) ) { v4 ^= 4; }
	v5 = __SETS__(v3);
	v4 += SHIDWORD(a1) + BYTE2(a1) + SLOBYTE(a1) + v5;
	return v4;
}

void __usercall sub_140001100(_DWORD *a1, unsigned __int8 a2) {
	*a1 = __ROR4__(*a1, a2 & 0x1F);
	LOBYTE(*a1) = ~LOBYTE(*a1);
	if ( !is_mul_ok(*a1, 4u) ) { *a1 = 0; }
}

int main() {
	CASSERT(sizeof(int32) == 4);
	CASSERT(sizeof(ll) == 8);

	unsigned int dw = 0x12345678;
	assert(LOBYTE(dw) == 0x78);
	assert(BYTE1(dw) == 0x56);
	assert(BYTE2(dw) == 0x34);
	assert(HIBYTE(dw) == 0x12);
	assert(LOWORD(dw) == 0x5678);
	assert(HIWORD(dw) == 0x1234);
	assert(LAST_IND(dw, _BYTE) == 3);

	LOBYTE(dw) = 0xFF;
	assert(dw == 0x123456FF);
	HIWORD(dw) += 1;
	assert(dw == 0x123556FF);
	BYTE1(dw) ^= 0xFF;
	assert(dw == 0x1235A9FF);

	__int64 q = 0x1122334455667788;
	assert(LODWORD(q) == 0x55667788u);
	assert(HIDWORD(q) == 0x11223344u);
	assert(SHIDWORD(q) == 0x11223344);
	assert(DWORD1(q) == 0x11223344u);
	assert(WORD2(q) == 0x3344);
	assert(SLOBYTE(q) == -120);
	assert(SHIBYTE(q) == 0x11);
	assert(SWORD1(q) == 0x5566);

	char signtest = (char)0xF0;
	assert(SLOBYTE(signtest) == -16);

#if __IDA_HAS_INT128
	_OWORD o = __PAIR128__(0x1122334455667788ull, 0x99AABBCCDDEEFF00ull);
	assert(QWORD1(o) == 0x1122334455667788ull);
	assert(LOQWORD(o) == 0x99AABBCCDDEEFF00ull);
	assert(abs128((int128)-5) == 5u);
#endif

	float f = COERCE_FLOAT(0x40490FDBu);
	assert(f > 3.14f && f < 3.15f);
	assert(COERCE_UNSIGNED_INT(f) == 0x40490FDBu);
	assert(COERCE_INT64(1.0) == 0x3FF0000000000000ll);
	assert(COERCE_DOUBLE(0x3FF0000000000000ull) == 1.0);

	_BYTE buffer[16];
	qmemcpy(buffer, "exception.cx", 13);
	assert(buffer[0] == 'e');
	assert(qmemcpy(buffer, buffer, 0) == buffer);

	MEMORY[0x100] = 0x7F;
	assert(MEMORY[0x100] == 0x7F);

#if (defined(__GNUC__) || defined(__clang__)) && !defined(_MSC_VER)
	assert(_byteswap_ulong(0x11223344u) == 0x44332211u);
	assert(_byteswap_ushort(0x1122) == 0x2211);
	ulong index = 0;
	assert(_BitScanReverse(&index, 0x80000000ul) && index == 31);
	assert(_BitScanForward(&index, 0x80000000ul) && index == 31);
	assert(!_BitScanForward(&index, 0));
	assert(_BitScanReverse64(&index, 0x8000000000000000ull) && index == 63);
#endif

	unsigned int target = 0xCAFEBABE;
	uint8 key = 0x5A;
	sub_140001100(&target, 4);
	volatile __int64 result = sub_140001000(q, &key, 0xFFFFFFF8);
	(void)result;

	printf("ok\n");
	return 0;
}
