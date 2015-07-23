#pragma once
#include "Disassembler.h"

#include <stack>

class RecursiveDisassembler final : public Disassembler
{
public:
    RecursiveDisassembler() = default;
    ~RecursiveDisassembler() = default;

private:
    void PrintDisassemblyImpl(const void * const pStartingAddress);

	std::stack<UIntPtr> m_retStack;
};

