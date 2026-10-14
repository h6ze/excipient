#include <assert.h>
#include <stdio.h>

#include "../libraries/ghidra.hxx"

static_assert(CONCAT11(0x12, 0x34) == 0x1234, "concat11");
static_assert(CONCAT22(0x1234, 0x5678) == 0x12345678, "concat22");
static_assert(CONCAT44(1, 2) == 0x100000002ULL, "concat44");
static_assert(CONCAT31(0x112233, 0x44) == 0x11223344, "concat31");
static_assert(CONCAT13(0x11, 0x223344) == 0x11223344, "concat13");
static_assert(CONCAT71(0x11223344556677ULL, 0x88) == 0x1122334455667788ULL, "concat71");
static_assert(CONCAT12(0x11, 0x2233) == 0x112233, "concat12");
static_assert(CONCAT31(0xFF112233, 0x44) == 0x11223344, "concat31 masks the high part");

static_assert(SUB41(0x12345678, 1) == 0x56, "sub41");
static_assert(SUB42(0x12345678, 2) == 0x1234, "sub42");
static_assert(SUB43(0x12345678, 1) == 0x123456, "sub43");
static_assert(SUB81(0x1122334455667788ULL, 7) == 0x11, "sub81");
static_assert(SUB84(0x1122334455667788ULL, 4) == 0x11223344, "sub84");
static_assert(SUB84(0x1122334455667788ULL, 0) == 0x55667788, "sub84 low");
static_assert(SUB83(0x1122334455667788ULL, 5) == 0x112233, "sub83");
static_assert(SUB82(0x1122334455667788ULL, 2) == 0x5566, "sub82");

static_assert(ZEXT12(0xFF) == 0xFF, "zext12");
static_assert(ZEXT48(0xFFFFFFFF) == 0xFFFFFFFFULL, "zext48");
static_assert(ZEXT38(0xFF112233) == 0x112233ULL, "zext38 masks");
static_assert(SEXT14(0x80) == -128, "sext14");
static_assert(SEXT48(0xFFFFFFFF) == -1, "sext48");
static_assert(SEXT24(0x8000) == -32768, "sext24");
static_assert(SEXT38(0x800000) == -8388608, "sext38");
static_assert(SEXT12(0x7F) == 127, "sext12");

static_assert(CARRY4(0xFFFFFFFF, 1), "carry4");
static_assert(!CARRY4(1, 1), "carry4 none");
static_assert(CARRY1(0xFF, 1), "carry1");
static_assert(CARRY8(0xFFFFFFFFFFFFFFFFULL, 1), "carry8");
static_assert(BORROW4(1, 2), "borrow4");
static_assert(!BORROW4(2, 1), "borrow4 none");
static_assert(SCARRY4(0x7FFFFFFF, 1), "scarry4");
static_assert(!SCARRY4(1, 1), "scarry4 none");
static_assert(SCARRY1(127, 1), "scarry1");
static_assert(SBORROW4(-2147483647 - 1, 1), "sborrow4");
static_assert(!SBORROW4(5, 1), "sborrow4 none");
static_assert(SBORROW1(-128, 1), "sborrow1");

static_assert(POPCOUNT((byte)0xFF) == 8, "popcount byte");
static_assert(POPCOUNT((dword)0x10001) == 2, "popcount dword");
static_assert(POPCOUNT((qword)0) == 0, "popcount zero");
static_assert(LZCOUNT((dword)1) == 31, "lzcount");
static_assert(LZCOUNT((byte)0x80) == 0, "lzcount byte");
static_assert(LZCOUNT((qword)0) == 64, "lzcount zero");
static_assert(ABS(-5) == 5, "abs int");
static_assert(ABS((uint)5) == 5, "abs unsigned");

#if __GHIDRA_HAS_INT128
static_assert((qword)(CONCAT88(1, 2) >> 64) == 1, "concat88");
static_assert(SUB168(CONCAT88(0x1122334455667788ULL, 0), 8) == 0x1122334455667788ULL, "sub168");
static_assert((qword)ZEXT816(0xFFFFFFFFFFFFFFFFULL) == 0xFFFFFFFFFFFFFFFFULL, "zext816");
static_assert(SEXT816(0xFFFFFFFFFFFFFFFFULL) == (int128)-1, "sext816");
static_assert(CARRY16(~(uint128)0, 1), "carry16");
#endif

undefined8 FUN_00401000(uint param_1, undefined8 *param_2) {
	uint uVar1;
	undefined4 uVar2;
	ulonglong uVar3;
	bool bVar4;

	uVar1 = param_1 * 0x9e3779b9;
	bVar4 = CARRY4(uVar1, 0x10);
	uVar2 = SUB84(*param_2, 4);
	uVar3 = CONCAT44(uVar2, uVar1);
	if ( bVar4 ) {
		uVar3 = uVar3 ^ ZEXT48(uVar1);
	}
	if ( SCARRY4(uVar1, 1) ) {
		uVar3 = ~uVar3;
	}
	if ( SBORROW4(uVar1, 1) ) {
		uVar3 = uVar3 >> 1;
	}
	return CONCAT44(SUB84(uVar3, 4), SUB84(uVar3, 0) ^ (dword)POPCOUNT(uVar1 & 0xff));
}

void FUN_00401100(code *pcVar1, undefined4 param_1) {
	if ( pcVar1 != (code *)0x0 ) {
		(*pcVar1)(param_1);
	}
}

undefined4 FUN_00401200(double param_1) {
	if ( NAN(param_1) ) {
		return 0;
	}
	if ( ABS(param_1) < 1.0 ) {
		return 1;
	}
	return (undefined4)(dword)SQRT(param_1);
}

void FUN_00401300(byte *param_1) {
	if ( *param_1 == 0xcc ) {
		halt_baddata();
	}
}

int main() {
	undefined8 raw = 0x1122334455667788ULL;
	undefined8 result = FUN_00401000(0x1337, &raw);
	assert(result != 0);

	undefined3 small = SUB43(0x12345678, 0);
	assert(small == 0x345678);

	uint3 three = (uint3)SUB83(raw, 1);
	assert(three == 0x556677);

	word w = CONCAT11(0xAA, 0xBB);
	assert(w == 0xAABB);
	assert(SUB21(w, 1) == 0xAA);

	dword d = 0;
	*(byte *)&d = 0x11;
	*(byte *)((byte *)&d + 1) = 0x22;
	assert(d == 0x2211);

	assert(FUN_00401200(4.0) == 2);
	assert(FUN_00401200(0.5) == 1);

	byte clean = 0;
	FUN_00401300(&clean);
	FUN_00401100((code *)0x0, 0);

	assert(ROUND(2.6) == 3.0);
	assert(FLOOR(2.6) == 2.0);
	assert(CEIL(2.1) == 3.0);
	assert(TRUNC(-2.7) == -2.0);
	assert(POPCOUNT(raw) == 26);

	printf("ok\n");
	return 0;
}
