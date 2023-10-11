#!/bin/bash

set -ex

mkdir -p bin/linux bin/win bin/wasm

gcc -Wall -Wextra -I./extern/build/linux/include/ src/game.c -L./extern/build/linux/lib/ -l:libraylib.a -lm -ldl -lpthread -o bin/linux/chess

x86_64-w64-mingw32-gcc -Wall -Wextra -I./extern/build/win/include/ src/game.c -L./extern/build/win/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static -o bin/win/chess.exe  #-mwindows

emcc -o bin/wasm/chess.html -Os -Wall -Wextra ./extern/build/web/lib/libraylib.a -I./extern/build/web/include/ src/game.c -L./extern/build/web/lib/ --shell-file src/minshell.html -s USE_GLFW=3 -DPLATFORM_WEB
