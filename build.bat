@echo off

clang main.cpp --target=wasm32 --no-standard-libraries -Wl,--export=__heap_base -Wl,--no-entry -Wl,--allow-undefined -o main.wasm
