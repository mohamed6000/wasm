// #define NB_STRIP_GENERAL_PREFIX
// #include "nb.h"

extern "C" {

int add(int a, int b) {
    return a + b;
}

int wasm_entry_point(void) {
    return 0;
}

}

// int main(void) {
    // write_string("Hello friend\n");
    // return 0;
// }



// #define NB_IMPLEMENTATION
// #include "nb.h"