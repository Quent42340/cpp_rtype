#!/bin/bash

mkdir rtype_windows
make clean 2> /dev/null
rm -f CMakeCache.txt cmake_install.cmake Makefile
rm -rf CMakeFiles
x86_64-w64-mingw32-cmake -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ -DCMAKE_SYSTEM_NAME=Windows . && make -j4
cp client/rtype_client.exe server/rtype_server.exe rtype_windows/
make clean 2> /dev/null

dll_list="
libbz2-1.dll
libFLAC-8.dll
libfreetype-6.dll
libgcc_s_seh-1.dll
libjpeg-8.dll
libogg-0.dll
libstdc++-6.dll
libtinyxml2.dll
libvorbis-0.dll
libvorbisenc-2.dll
libvorbisfile-3.dll
libwinpthread-1.dll
OpenAL32.dll
sfml-audio-2.dll
sfml-graphics-2.dll
sfml-network-2.dll
sfml-system-2.dll
sfml-window-2.dll"

for dll in $dll_list;
do
	cp /usr/x86_64-w64-mingw32/bin/$dll rtype_windows/
done;

cp -r resources/ rtype_windows/

rm -f CMakeCache.txt cmake_install.cmake Makefile
rm -rf CMakeFiles

zip -r rtype_windows.zip rtype_windows/

rm -r rtype_windows
