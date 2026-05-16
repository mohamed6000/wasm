// #define NB_STRIP_GENERAL_PREFIX
// #include "nb.h"


extern "C" {

extern void wasm_write_string_count(const char *s, int count, bool to_standard_error);

void wasm_write_string(const char *s, bool to_standard_error) {
    const char *it = s;

    while (*it++);

    int count = it - 1 - s;

    wasm_write_string_count(s, count, to_standard_error);
}

int add(int a, int b) {
    return a + b;
}

int wasm_entry_point(void) {
    wasm_write_string("Hello friend\nTest", false);
    wasm_write_string("Error", true);
    return 0;
}

}

// int main(void) {
    // write_string("Hello friend\n");
    // return 0;
// }



// #define NB_IMPLEMENTATION
// #include "nb.h"