#!/bin/bash

gcc -Wall -Wextra -I./raylib/build/linux/include/ game.c -L./raylib//build/linux/lib/ -l:libraylib.a -lm -ldl -lpthread

x86_64-w64-mingw32-gcc -Wall -Wextra -I./raylib/build/win/include/ game.c -L./raylib/build/win/lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -static  #-mwindows

emcc -o chess.html -Os -Wall -Wextra ./raylib/build/web/lib/libraylib.a -I./raylib/build/web/include/ game.c -L./raylib/build/web/lib/ --shell-file minshell.html -s USE_GLFW=3 -DPLATFORM_WEB
