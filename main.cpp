// #define NB_STRIP_GENERAL_PREFIX
// #include "nb.h"

#if defined(__wasm__) || defined(__wasm) || defined(__wasm32__) || defined(__wasm32) || defined(__wasm64__)
#define OS_WASM 1
#endif

#if defined(__wasm64__) || defined(__wasm64)
#define ARCH_WASM64 1
#elif defined(__wasm32__) || defined(__wasm32)
#define ARCH_WASM32 1
#endif

#ifndef ARCH_WASM64
#define ARCH_WASM64 0
#endif

#ifndef ARCH_WASM32
#define ARCH_WASM32 0
#endif


extern "C" {

extern void wasm_write_string_count(const char *s, int count, bool to_standard_error);

extern void wasm_debug_break(void);

#define STRINGIFY(x) STRINGIFY2(x)
#define STRINGIFY2(x) #x

#define basic_assert(expr) do { \
    if (!(expr)) { \
        wasm_write_string("Assertion Failure: " STRINGIFY(expr) " at " __FILE__ ":" STRINGIFY(__LINE__) "\n", true); \
        wasm_debug_break(); \
    } \
} while (0)

void wasm_write_string(const char *s, bool to_standard_error) {
    const char *it = s;

    while (*it++);

    int count = it - 1 - s;

    wasm_write_string_count(s, count, to_standard_error);
}

int add(int a, int b) {
    return a + b;
}

void wasm_entry_point(void) {
#if OS_WASM
    wasm_write_string("WASM platform\n", false);
#endif

#if ARCH_WASM32
    wasm_write_string("WASM32\n", false);
#elif ARCH_WASM32
    wasm_write_string("WASM64\n", false);
#endif

    wasm_write_string("Hello friend\nTest", false);
    wasm_write_string("Error\n", true);

    basic_assert(!"Test assert condition");

    wasm_write_string("continue program\n", false);
}

}

// int main(void) {
    // write_string("Hello friend\n");
    // return 0;
// }



// #define NB_IMPLEMENTATION
// #include "nb.h"