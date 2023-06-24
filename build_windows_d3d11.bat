@REM NOTE: -DXXX defines a define XXX for when preprocessing the source files. It
@REM       is equivalent to adding #define XXX at the start of all code files. Here
@REM       I use it to select the direct X backend (-DSOKOL_D3D11)

clang++ -o game.exe game.cpp engine.cpp -g -DSOKOL_D3D11 -std=c++20 -Wno-c99-designator -Wno-reorder-init-list
