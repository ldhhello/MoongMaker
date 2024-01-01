// This file prevents source code editor (like VSCode) not to think the WASM-specific code as error.
// You need to define WASM_BUILD when building on WASM.

#pragma once

#ifdef WASM_BUILD

#include <emscripten/emscripten.h>

#else

#define EMSCRIPTEN_KEEPALIVE
#define EM_ASM(...)
#define EM_JS(a, b, c, d) extern a b c ;
#define MAIN_THREAD_EM_ASM(...)
#define MAIN_THREAD_EM_ASM_INT(...) 0

#endif