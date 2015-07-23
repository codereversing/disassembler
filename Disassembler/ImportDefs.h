#pragma once

#include "BeaEngine.h"

using pDisasmFnc = int(__stdcall *)(DISASM *);
using pBeaEngineVersionFnc = char *(__stdcall *)(void);
using pBeaEngineRevisionFnc = char *(__stdcall *)(void);

extern pDisasmFnc DisasmFnc;
extern pBeaEngineVersionFnc BeaEngineVersionFnc;
extern pBeaEngineRevisionFnc BeaEngineRevisionFnc;
