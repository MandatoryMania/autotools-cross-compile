#Developing on linux 
```bash
./bootstrap.sh
./configure 
make 
```
#Developing on linux and cross-compiling to Windows
```bash
./bootstrap.sh
./cross-compile-win64.sh
make
```

#Cross compile SDL2 on linux for windows
Most non-trivial programs have library dependencies. When you are cross-compiling on Linux you first need to 
go and cross compile all the dependencies and install all the correct headers. For this example project we will
use SDL2 as an example for you to follow. 

- Grab SDL2 [sources](https://libsdl.org/release/SDL2-2.0.4.tar.gz)
- Apply the [gcc patches](https://github.com/Alexpux/MINGW-packages/tree/master/mingw-w64-SDL2)
- Once you have the patched source then build SDL2 (64 bit!) with the
  command below
- *NOTE*: The --prefix argument below assumes that your cross compiler
(mingw) is installed in /usr/x86_64-w64-mingw32 if this is not the
case then you will need to updated the prefix with the correct path.

```bash
cd <SDL2 source >
mkdir build
cd build
../configure --prefix /usr/x86_64-w64-mingw32 --build=x86_64-pc-linux-gnu  --host=x86_64-w64-mingw32
make -j 8 DESTDIR=$HOME/SDL2_64 install 
```

- Inspect the resulting build in $HOME/SDL2_64 and make sure
everything looks good and maps the correct directories. Once you are
sure everything is good then install everything were it should go.

```bash
sudo make install 
```

- You now should be able to build the application for windows on a linux box!

##Common issues when cross compiling to Windows

When you run the configure script you should not get *ANY*
warnings. For example if you see `configure: WARNING: using cross
tools not prefixed with host triplet` after running the
cross-compile-win64.sh script then you probably don't have all the
proper build tools installed. Below is a list of packages installed
that should get you all up and running quickly. The biggest potential
problem comes from pkg-config. When cross compiling autotools will
look for a pkg-config wrapper that matches the triplet of the host you
are targeting. In this case we are using the triplet
`x86_64-w64-mingw32` so we need a pkg-config wrapper named
`x86_64-w64-mingw32-pkg-config`.  On Debian based systems this is
contained in the package mingw-w64-tools.

```
[spanter@segfault ~]$ dpkg --get-selections | grep -v deinstall | grep mingw
binutils-mingw-w64-i686				install
binutils-mingw-w64-x86-64			install
g++-mingw-w64					    install
g++-mingw-w64-i686				    install
g++-mingw-w64-x86-64				install
gcc-mingw-w64					    install
gcc-mingw-w64-base				    install
gcc-mingw-w64-i686				    install
gcc-mingw-w64-x86-64				install
mingw-w64					        install
mingw-w64-common				    install
mingw-w64-i686-dev				    install
mingw-w64-tools					    install
mingw-w64-x86-64-dev				install

[spanter@segfault ~]$ locate pkg-config
...
/usr/bin/i686-linux-gnu-pkg-config
/usr/bin/i686-w64-mingw32-pkg-config
/usr/bin/pkg-config
/usr/bin/x86_64-linux-gnu-pkg-config
/usr/bin/x86_64-pc-linux-gnu-pkg-config
/usr/bin/x86_64-w64-mingw32-pkg-config
/usr/lib/pkg-config.multiarch
...
```

##Sample output for this project on a system that is setup correctly
```bash
[spanter@segfault cross-compile-autotools(master)↑ ]$ ./bootstrap.sh 
configure.ac:4: installing './compile'
configure.ac:3: installing './install-sh'
configure.ac:3: installing './missing'
src/Makefile.am: installing './depcomp'
[spanter@segfault cross-compile-autotools(master)↑ ]$ ls
aclocal.m4      bootstrap.sh  config.h.in  configure.ac            depcomp  GRTAGS  install-sh  m4           Makefile.in  README.md
autom4te.cache  compile       configure    cross-compile-win64.sh  GPATH    GTAGS   LICENSE     Makefile.am  missing      src
[spanter@segfault cross-compile-autotools(master)↑ ]$ ./cross-compile-win64.sh 
checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for x86_64-w64-mingw32-strip... x86_64-w64-mingw32-strip
checking for a thread-safe mkdir -p... /bin/mkdir -p
checking for gawk... no
checking for mawk... mawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking for x86_64-w64-mingw32-gcc... x86_64-w64-mingw32-gcc
checking whether the C compiler works... yes
checking for C compiler default output file name... a.exe
checking for suffix of executables... .exe
checking whether we are cross compiling... yes
checking for suffix of object files... o
checking whether we are using the GNU C compiler... yes
checking whether x86_64-w64-mingw32-gcc accepts -g... yes
checking for x86_64-w64-mingw32-gcc option to accept ISO C89... none needed
checking whether x86_64-w64-mingw32-gcc understands -c and -o together... yes
checking for style of include used by make... GNU
checking dependency style of x86_64-w64-mingw32-gcc... gcc3
checking for x86_64-w64-mingw32-pkg-config... /usr/bin/x86_64-w64-mingw32-pkg-config
checking pkg-config is at least version 0.9.0... yes
checking for SDL... yes
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating Makefile
config.status: creating src/Makefile
config.status: creating config.h
config.status: executing depfiles commands
[spanter@segfault cross-compile-autotools(master)↑ ]$ make
make  all-recursive
make[1]: Entering directory '/home/spanter/repos/github/cross-compile-autotools'
Making all in src
make[2]: Entering directory '/home/spanter/repos/github/cross-compile-autotools/src'
x86_64-w64-mingw32-gcc -DHAVE_CONFIG_H -I. -I..     -g -O2 -Dmain=SDL_main -I/usr/x86_64-w64-mingw32/include/SDL2 -MT main.o -MD -MP -MF .deps/main.Tpo -c -o main.o main.c
mv -f .deps/main.Tpo .deps/main.Po
x86_64-w64-mingw32-gcc  -g -O2 -Dmain=SDL_main -I/usr/x86_64-w64-mingw32/include/SDL2   -o example.exe main.o  -L/usr/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -mwindows
make[2]: Leaving directory '/home/spanter/repos/github/cross-compile-autotools/src'
make[2]: Entering directory '/home/spanter/repos/github/cross-compile-autotools'
make[2]: Leaving directory '/home/spanter/repos/github/cross-compile-autotools'
make[1]: Leaving directory '/home/spanter/repos/github/cross-compile-autotools'
[spanter@segfault cross-compile-autotools(master)↑ ]$ 
```
