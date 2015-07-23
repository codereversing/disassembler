#include "LinearDisassembler.h"
#include "RecursiveDisassembler.h"

#include <Windows.h>

void __declspec(naked) TestFunction1()
{
    __asm
    {
        call GetCurrentThreadId
        ret
    }
}

void __declspec(naked) TestFunction2()
{
    __asm
    {
        push ebp
        mov ebp, esp

        mov eax, 0xFF
        call calldest
        xor ebx, ebx
        xchg eax, ebx
        jmp jmpdest

    useless:
        cmp ecx, 0xAABBCCDD
        push 0
        push 0
        push 0
        push 0
        call MessageBoxA

    jmpback:
        pop ebp
        mov esp, ebp
        ret

    calldest:
        add eax, 1
        shl eax, 2
        ret


    jmpdest:
        rol eax, 5
        jmp jmpback
    }
}

int main(int argc, char *argv[])
{
    LinearDisassembler linear;
	linear.PrintDisassembly(TestFunction1);

	RecursiveDisassembler recursive;
	recursive.PrintDisassembly(TestFunction1);

    return 0;
}