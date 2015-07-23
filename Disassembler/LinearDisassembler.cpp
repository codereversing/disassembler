#include "LinearDisassembler.h"

void LinearDisassembler::PrintDisassemblyImpl(const void * const pStartingAddress)
{
    DISASM disasm = { 0 };
    disasm.EIP = (UIntPtr)pStartingAddress;

    int iLength = UNKNOWN_OPCODE;
    do
    {
        iLength = DisasmFnc(&disasm);
        fprintf(stdout, "0x%X -- %s\n",
            disasm.EIP, disasm.CompleteInstr);
        
        disasm.EIP += iLength;

    } while (!IsRet(disasm.Instruction) && iLength != UNKNOWN_OPCODE);
}