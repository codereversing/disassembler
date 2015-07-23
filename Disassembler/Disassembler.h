#pragma once

#include <mutex>

#include "ImportDefs.h"

class Disassembler
{
public:
    Disassembler();

    virtual ~Disassembler() = default;

    void PrintDisassembly(const void * const pStartingAddress)
    {
        PrintDisassemblyImpl(pStartingAddress);
    }

private:
    virtual void PrintDisassemblyImpl(const void * const pStartingAddress) = 0;

    void ResolveImports();

    static std::once_flag m_flag;

protected:
    const bool IsUnconditionalFlow(const INSTRTYPE &instruction) const;
	const bool IsJump(const INSTRTYPE &instruction) const;
	const bool IsRet(const INSTRTYPE &instruction) const;
    const bool IsCall(const INSTRTYPE &instruction) const;
	const UIntPtr ResolveAddress(const DISASM &disasm) const;

};
