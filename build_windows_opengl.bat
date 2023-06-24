@REM NOTE: -DXXX defines a define XXX for when preprocessing the source files. It
@REM       is equivalent to adding #define XXX at the start of all code files. Here
@REM       I use it to select the openGL backend (-DSOKOL_GLCORE33)

clang++ -o game.exe game.cpp engine.cpp -g -DSOKOL_GLCORE33 -std=c++20 -Wno-c99-designator -Wno-reorder-init-list
