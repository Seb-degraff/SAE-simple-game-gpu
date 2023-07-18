@REM NOTE: -DXXX defines a define XXX for when preprocessing the source files. It
@REM       is equivalent to adding #define XXX at the start of all code files. Here
@REM       I use it to select the openGL backend (-DSOKOL_GLCORE33)

@REM Build game.dll (-shared). This will also generate game.lib, which is only useful to tell the linker which 
@REM functions are expected to be available at runtime. The dynamic linker will try to find them in game.dll
@REM when the game is launched.
clang++ -o game.dll game.cpp -shared -g -DSOKOL_GLCORE33 -std=c++20 -Wno-c99-designator -Wno-reorder-init-list

@REM Build runner.exe. Link dynamically to game.dll by passing game.lib.
clang++ -o runner.exe engine.cpp game.lib -g -DSOKOL_GLCORE33 -std=c++20 -Wno-c99-designator -Wno-reorder-init-list

