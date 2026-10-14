#include <assert.h>
#include <stdio.h>

#define IDA_MEMORY_STORAGE
#include "../libraries/ida.hxx"

int main(void) {
	uint32 dw = 0x12345678;
	int64 q = 0x1122334455667788LL;

	assert(LOBYTE(dw) == 0x78);
	assert(HIWORD(dw) == 0x1234);
	LOBYTE(dw) = 0xFF;
	assert(dw == 0x123456FF);
	assert(SLOBYTE(q) == -120);
	assert(HIDWORD(q) == 0x11223344u);
	assert(__PAIR64__(1u, 2u) == 0x100000002ULL);
	assert(abs32(-5) == 5);

	MEMORY[0x20] = 0x41;
	assert(MEMORY[0x20] == 0x41);
	assert(_byteswap_ulong(0x11223344u) == 0x44332211u);

	printf("ok (C)\n");
	return 0;
}
