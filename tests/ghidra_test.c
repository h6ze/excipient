#include <assert.h>
#include <stdio.h>

#include "../libraries/ghidra.hxx"

undefined8 FUN_00401000(uint param_1, undefined8 param_2) {
	uint uVar1;
	ulonglong uVar2;

	uVar1 = param_1 ^ 0xdeadbeef;
	uVar2 = CONCAT44(SUB84(param_2, 4), uVar1);
	if ( CARRY4(uVar1, 0x10) ) {
		uVar2 = uVar2 ^ ZEXT48(uVar1);
	}
	if ( SBORROW4(uVar1, 1) ) {
		uVar2 = ~uVar2;
	}
	return uVar2;
}

int main(void) {
	undefined8 raw = 0x1122334455667788ULL;

	assert(CONCAT44(1, 2) == 0x100000002ULL);
	assert(CONCAT11(0x12, 0x34) == 0x1234);
	assert(SUB84(raw, 4) == 0x11223344);
	assert(SUB83(raw, 5) == 0x112233);
	assert(SEXT48(0xFFFFFFFF) == -1);
	assert(ZEXT38(0xFF112233) == 0x112233ULL);
	assert(CARRY1(0xFF, 1));
	assert(SCARRY4(0x7FFFFFFF, 1));
	assert(!BORROW8(2, 1));
	assert(POPCOUNT(raw) == 26);
	assert(LZCOUNT(raw) == 3);
	assert(!NAN(1.0));
	assert(ABS(-2.5) == 2.5);
	assert(SQRT(9.0) == 3.0);
	assert(FUN_00401000(0x1337, raw) != 0);

	byte buffer[4] = { 0, 0, 0, 0 };
	*(dword *)buffer = 0x11223344;
	assert(buffer[0] == 0x44);

	printf("ok (C)\n");
	return 0;
}
