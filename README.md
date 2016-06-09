#Developing on linux 
```bash
./bootstrap.sh
./configure 
make 
```

#Cross Compiling from linux to windows. 
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

