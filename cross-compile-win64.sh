#!/bin/bash


function make_binary_package()
{
    #First build all files and put them into a temp dir
    make DESTDIR=$(pwd)/inst install
    cd $(pwd)/inst
    find . -type f -print > ../files.lst
}

#Disable pkg-config for cross-compiling
PKG_CONFIG="" ./configure --build=x86_64-pc-linux-gnu --host=x86_64-w64-mingw32  --with-sdl-prefix=/usr/x86_64-w64-mingw32
