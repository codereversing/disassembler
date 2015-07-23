#include "RecursiveDisassembler.h"

void RecursiveDisassembler::PrintDisassemblyImpl(const void * const pStartingAddress)
{
	DISASM disasm = { 0 };
	disasm.EIP = (UIntPtr)pStartingAddress;

	int iLength = UNKNOWN_OPCODE;

	do
	{
		iLength = DisasmFnc(&disasm);
		fprintf(stdout, "0x%X -- %s\n",
			disasm.EIP, disasm.CompleteInstr);
		if (IsCall(disasm.Instruction))
		{
			m_retStack.push(disasm.EIP + iLength);
			disasm.EIP = ResolveAddress(disasm);
		}
        else if (IsJump(disasm.Instruction))
        {
            disasm.EIP = ResolveAddress(disasm);
        }
        else if (IsRet(disasm.Instruction))
        {
            if (!m_retStack.empty())
            {
                disasm.EIP = m_retStack.top();
                m_retStack.pop();
            }
            else
            {
                break;
            }
        }
		else
		{
			disasm.EIP += iLength;
		}

	} while (iLength != UNKNOWN_OPCODE);

}