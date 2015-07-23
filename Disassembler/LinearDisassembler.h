#pragma once
#include "Disassembler.h"

class LinearDisassembler final : public Disassembler
{
public:
    LinearDisassembler() = default;
    ~LinearDisassembler() = default;

private:
    void PrintDisassemblyImpl(const void * const pStartingAddress);

};

