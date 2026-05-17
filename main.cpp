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

extern float wasm_canvas_get_width(void);
extern float wasm_canvas_get_height(void);
extern void wasm_canvas_get_size(float result_pointer[2]);

extern void context2d_clear_render_target(float r, float g, float b, float a);

extern void context2d_draw_quad(float x0, float y0, float x1, float y1, float r, float g, float b, float a);

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


extern unsigned char __heap_base;

static unsigned char *bump_pointer = &__heap_base;

typedef unsigned long size_t;

void *basic_malloc(size_t size) {
    void *result = bump_pointer;
    bump_pointer += size;
    return result;
}

void basic_free(void *mem) {
    (void)(mem);
}

__attribute((export_name("process_one_frame")))
bool process_one_frame(float dt) {
    static float x = 0;

    context2d_clear_render_target(1,1,1,1);

    // float w = wasm_canvas_get_width();
    // float h = wasm_canvas_get_height();

    float size[2];
    wasm_canvas_get_size(size);
    float w = size[0];
    float h = size[1];

    float x0 = w * 0.1f;
    float y0 = h * 0.1f;
    float x1 = w * 0.9f;
    float y1 = h * 0.9f;
    context2d_draw_quad(x0, y0, x1, y1, 0,0,1,1);
    
    x += 100 * dt;
    context2d_draw_quad(x, 10, x+10, 20, 1,0,0,1);

    return true;
}

__attribute((export_name("wasm_entry_point")))
void wasm_entry_point(void) {
#if OS_WASM
    wasm_write_string("WASM platform\n", false);
#endif

#if ARCH_WASM32
    wasm_write_string("WASM32\n", false);
#elif ARCH_WASM32
    wasm_write_string("WASM64\n", false);
#endif

    // Address 0 is valid for WASM runtime.
    // So we compile with -fsanitize=undefined -fsanitize-trap for clang.
    // int *pointer = 0;
    // *pointer = 0xFF;

    char *p = (char *)basic_malloc(12+1);
    __builtin_memset(p, 0, 13);

    char msg[] = "Hello friend";
    for (int i = 0; i < 12; ++i) {
        p[i] = msg[i];
    }

    wasm_write_string(p, false);
    wasm_write_string("\n", false);

    basic_free(p);
}

}

// int main(void) {
    // write_string("Hello friend\n");
    // return 0;
// }



// #define NB_IMPLEMENTATION
// #include "nb.h"