# NOTE: -DXXX defines a define XXX for when preprocessing the source files. It
#       is equivalent to adding #define XXX at the start of all code files. Here
#       I use it to select the open gl backend (-DSOKOL_GLCORE33)

clang++ -o game \
    game.cpp engine.cpp \
    -fobjc-arc -ObjC++ \
    -g \
    -framework OpenGL -framework Cocoa \
    -DSOKOL_GLCORE33
