#!/bin/bash

sed -i 's/#define SUPPORT_SCREEN_CAPTURE/\/\/#define SUPPORT_SCREEN_CAPTURE/' raylib/src/config.h
sed -i 's/#define SUPPORT_GIF_RECORDING/\/\/#define SUPPORT_GIF_RECORDING/' raylib/src/config.h

mkdir -p build/linux/include
mkdir -p build/linux/lib
mkdir -p build/win/include
mkdir -p build/win/lib
mkdir -p build/web/lib
mkdir -p build/web/include
cd ./raylib/src

#
# build linux
#
make PLATFORM=PLATFORM_DESKTOP CC=gcc RAYLIB_LIBTYPE=STATIC RAYLIB_RELEASE_PATH="../../build/linux/lib" -B
make PLATFORM=PLATFORM_DESKTOP CC=gcc RAYLIB_LIBTYPE=SHARED RAYLIB_RELEASE_PATH="../../build/linux/lib" -B
cp -v ./raylib.h ../../build/linux/include/
cp -v ./raymath.h ../../build/linux/include/
cp -v ./rlgl.h ../../build/linux/include/
cp -v ../CHANGELOG ../../build/linux/include/
cp -v ../README.md ../../build/linux/include/
cp -v ../LICENSE ../../build/linux/include/

#
# build windows
#
make HOST_PLATFORM_OS=LINUX PLATFORM_OS=WINDOWS PLATFORM=PLATFORM_DESKTOP CC=x86_64-w64-mingw32-gcc RAYLIB_LIBTYPE=STATIC RAYLIB_RELEASE_PATH="../../build/win/lib" -B
x86_64-w64-mingw32-windres -i raylib.dll.rc -o raylib.dll.rc.data -O coff --target=pe-x86-64
make HOST_PLATFORM_OS=LINUX PLATFORM_OS=WINDOWS PLATFORM=PLATFORM_DESKTOP CC=x86_64-w64-mingw32-gcc RAYLIB_LIBTYPE=SHARED RAYLIB_RELEASE_PATH="../../build/win/lib" -B
cp -v ./raylib.h ../../build/win/include/
cp -v ./raymath.h ../../build/win/include/
cp -v ./rlgl.h ../../build/win/include/
cp -v ../CHANGELOG ../../build/win/include/
cp -v ../README.md ../../build/win/include/
cp -v ../LICENSE ../../build/win/include/

#
# build web
#
make HOST_PLATFORM_OS=LINUX PLATFORM_OS=WINDOWS PLATFORM=PLATFORM_WEB RAYLIB_LIBTYPE=STATIC RAYLIB_RELEASE_PATH="../../build/web/lib" -B
cp -v ./raylib.h ../../build/web/include/
cp -v ./raymath.h ../../build/web/include/
cp -v ./rlgl.h ../../build/web/include/
cp -v ../CHANGELOG ../../build/web/include/
cp -v ../README.md ../../build/web/include/
cp -v ../LICENSE ../../build/web/include/
