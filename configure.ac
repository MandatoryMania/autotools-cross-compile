AC_CONFIG_MACRO_DIRS([m4])
AC_INIT([example], [0.1], [buggy@example.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AC_CONFIG_HEADERS([config.h])

dnl Check for SDL
SDL_VERSION=2.0
AM_PATH_SDL2($SDL_VERSION,
            :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!])
)
CFLAGS="$CFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"
  
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])

AC_OUTPUT
