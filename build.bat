@echo off

clang main.cpp -Ofast -O0 --target=wasm32 -mbulk-memory -g -fsanitize=undefined -fsanitize-trap --no-standard-libraries -Wl,--export-table -Wl,--export=__heap_base -Wl,--no-entry -Wl,--allow-undefined -o main.wasm
