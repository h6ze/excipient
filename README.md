# excipient

headers that make decompiler output compile. paste the pseudocode, include the header, build it.

- `libraries/ida.hxx` -> hex-rays pseudocode, drop-in for ida's `defs.h`
- `libraries/ghidra.hxx` -> ghidra c export

c++14 through c++23, plus a reduced c path. no dependencies.

## usage

include it last, after every other header.

```cpp
#include "libraries/ida.hxx"

__int64 __fastcall sub_140001000(__int64 a1, unsigned int a2)
{
    unsigned int v3 = __ROL4__(a2 ^ 0xDEADBEEF, 7);
    LOBYTE(v3) = 0x41;
    return __PAIR64__(v3, a2) + SHIDWORD(a1);
}
```

every name either decompiler emits is covered, and fixed where the stock headers were wrong: partial access is strict-aliasing safe and still assignable, `__ROL__` and `__MKCSHL__` no longer shift by the type width, the carry in forms of `__CFSUB__`/`__OFSUB__` work, `__PAIR128__` works, `__SETP__` and `__CFSHL__` are implemented, ghidras odd operand sizes are masked.

## options

`IDA_NO_EXTRAS`, `IDA_NO_KEYWORDS`, `IDA_NO_INTRINSICS`, `IDA_NO_INT_TYPEDEFS`, `IDA_MEMORY_STORAGE`, `SUB_WITH_CARRY`, `GHIDRA_NO_EXTRAS`, `GHIDRA_NO_KEYWORDS`, `GHIDRA_PACKED_ODD_SIZES`.

set `SUB_WITH_CARRY` to 1 if the decompiled target inverts the borrow flag (arm, ppc). `GHIDRA_PACKED_ODD_SIZES` makes `undefined3`/`uint5`/`int7` byte exact structs instead of widened integers.

## limits

strip by hand: `@<rax>`, `__spoils<...>`, `auVar1._0_4_`, processor userops. `ghidra.hxx` undefines `NAN` to redefine it as a macro.

## tests

```sh
g++ -std=c++17 -O2 tests/ida_test.cpp -o ida_test && ./ida_test
g++ -std=c++17 -O2 tests/ghidra_test.cpp -o ghidra_test && ./ghidra_test
```

`tests/*.c` cover the c path. most checks are `static_assert`, so they run at compile time.

clean reimplementation, no vendor source. not affiliated with hex-rays or the ghidra project.
