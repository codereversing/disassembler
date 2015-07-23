#include "Disassembler.h"

#include <Windows.h>

std::once_flag Disassembler::m_flag;

Disassembler::Disassembler()
{
    std::call_once(m_flag, [&]() { ResolveImports(); });
}

void Disassembler::ResolveImports()
{
    HMODULE hBeaEngine = LoadLibrary(L"BeaEngine.dll");
    if (hBeaEngine == nullptr)
    {
        fprintf(stderr, "Could not load BeaEngine.\n");
        abort();
    }

    DisasmFnc = (pDisasmFnc)GetProcAddress(hBeaEngine, "_Disasm@4");
    if (DisasmFnc == nullptr)
    {
        fprintf(stderr, "Could not find Disasm function.\n");
        abort();
    }

    BeaEngineVersionFnc = (pBeaEngineVersionFnc)GetProcAddress(hBeaEngine, "_BeaEngineVersion@0");
    BeaEngineRevisionFnc = (pBeaEngineRevisionFnc)GetProcAddress(hBeaEngine, "_BeaEngineRevision@0");
    if (BeaEngineVersionFnc != nullptr && BeaEngineRevisionFnc != nullptr)
    {
        fprintf(stdout, "BeaEngine version: %s\n"
            "BeaEngine revision: %s\n\n",
            BeaEngineVersionFnc(), BeaEngineRevisionFnc());
    }
    else
    {
        fprintf(stderr, "Could not resolve disassembler version and revision\n");
    }
}

const bool Disassembler::IsUnconditionalFlow(const INSTRTYPE &instruction) const
{
    return IsJump(instruction) || IsRet(instruction);
}

const bool Disassembler::IsJump(const INSTRTYPE &instruction) const
{
	return instruction.BranchType == JmpType;
}

const bool Disassembler::IsRet(const INSTRTYPE &instruction) const
{
	return instruction.BranchType == RetType;
}

const bool Disassembler::IsCall(const INSTRTYPE &instruction) const
{
    return instruction.BranchType == CallType;
}

const UIntPtr Disassembler::ResolveAddress(const DISASM &disasm) const
{
    UIntPtr ulDestAddress = 0;
    if (IsCall(disasm.Instruction) || IsJump(disasm.Instruction))
    {
        if (disasm.Argument1.ArgType | RELATIVE_)
        {
            if (disasm.Instruction.AddrValue != 0)
            {
                ulDestAddress = (UIntPtr)disasm.Instruction.AddrValue;
            }
            else
            {
                //Only decode instructions with no offsets, i.e. ignore instructions like
                //call [0xABCD + ESI * 4]
                if (disasm.Argument1.Memory.BaseRegister == 0 && disasm.Argument1.Memory.Scale == 0)
                {
                    ulDestAddress = *(UIntPtr *)(disasm.Argument1.Memory.Displacement);
                }
            }
        }
        else
        {
            abort();
        }
    }

    return ulDestAddress;
}