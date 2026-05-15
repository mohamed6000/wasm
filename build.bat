@echo off

clang main.cpp --target=wasm32 --no-standard-libraries -Wl,--export-all -Wl,--no-entry -o main.wasm
