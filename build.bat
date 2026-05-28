@echo off

clang main.cpp -Ofast --target=wasm32 -g -fsanitize=undefined -fsanitize-trap --no-standard-libraries -Wl,--export-table -Wl,--export=__heap_base -Wl,--no-entry -Wl,--allow-undefined -o main.wasm
