##
# Configure autoconf.
AC_INIT([cscene], [0.0.1], [https://github.com/zappynou])

##
# Setup automake with basic CFLAGS and options.
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

##
# Configure the macro directory.
AC_CONFIG_MACRO_DIRS([m4])

##
# Choose the configuration files generated to be #include in the C.
AC_CONFIG_HEADERS([include/cscene/config.h])

##
# Select programs required by the build system.
AM_PROG_AR
AC_PROG_CC
AC_PROG_CXX

##
# Configure libtool.
LT_INIT([win32-dll pic-only disable-static])

##
# Initialize the compilation flags.
CFLAGS+=' -std=c11'
CPPFLAGS+=' -Wall -Wextra -I$(top_srcdir)/include -I$(top_builddir)/include'

##
# Configure the version.
AC_SUBST([PACKAGE_VERSION_MAJOR], [0])
AC_SUBST([PACKAGE_VERSION_MINOR], [0])
AC_SUBST([PACKAGE_VERSION_REVISION], [1])
AC_SUBST([PACKAGE_BUILD_VERSION], [$(git describe --tags --always)])
AC_SUBST(
    [PACKAGE_VERSION_STRING],
    $PACKAGE_VERSION_MAJOR.$PACKAGE_VERSION_MINOR.$PACKAGE_VERSION_REVISION-$PACKAGE_BUILD_VERSION)
AC_DEFINE_UNQUOTED(
    [PACKAGE_VERSION_MAJOR], [$PACKAGE_VERSION_MAJOR],
    [The major version of the build.])
AC_DEFINE_UNQUOTED(
    [PACKAGE_VERSION_MINOR], [$PACKAGE_VERSION_MINOR],
    [The minor version of the build.])
AC_DEFINE_UNQUOTED(
    [PACKAGE_VERSION_REVISION], [$PACKAGE_VERSION_REVISION],
    [The revision version of the build.])
AC_DEFINE_UNQUOTED(
    [PACKAGE_VERSION_STRING], ["$PACKAGE_VERSION_STRING"],
    [The human representation of the built version.])

##
# Enable debugging build using `--enable-debug` flag.
AC_ARG_ENABLE(
    [debug],
    AS_HELP_STRING(
        [--enable-debug],
        [Build the binaries in debug mode (default: no)]),
    [], [enable_debug=no])
AM_CONDITIONAL([ENABLE_DEBUG], [test x$enable_debug == xyes])
AS_IF([test x$enable_debug == xyes], [
    AC_SUBST([BUILD_MODE], [debug])
    AC_DEFINE([ENABLE_DEBUG], [1], [Building with debug support.])
    CFLAGS+=" -g2 -ggdb -O0"
    CXXFLAGS+=" -g2 -ggdb -O0 -std=gnu++17"
], [
    AC_SUBST([BUILD_MODE], [release])
    AC_DEFINE([ENABLE_RELEASE], [1], [Building without debug support.])
    CXXFLAGS+=" -g0 -O2 -std=gnu++17"
])

##
# Enable tests build using `--enable-tests` flag.
AC_ARG_ENABLE(
    [tests],
    AS_HELP_STRING(
        [--enable-tests],
        [Build the tests together with the binaries (default: no)]),
    [], [enable_tests=no])
AM_CONDITIONAL([ENABLE_TESTS], [test x$enable_tests == xyes])
AS_IF(
    [test x$enable_tests == xyes],
    [AC_DEFINE([ENABLE_TESTS], [1], [Building tests])
     PKG_CHECK_MODULES([CATCH2], [catch2-with-main])
     AC_CHECK_HEADER([fff.h], [], [
         AC_MSG_ERROR([No fff.h found (see https://github.com/meekrosoft/fff)])
     ])
])

##
# Use GTK4 to provide the GUI.
PKG_CHECK_MODULES([GTK4], [gtk4])

#
# Host detection
#
AC_MSG_CHECKING([which host will run the project (using $host)])
case $host in
     *mingw*|*w32*)
        AC_SUBST([OS_HOST], [win32])
        AC_DEFINE([ENABLE_WIN32], [1], [Building for a win32 system.])
        ;;
     *darwin*)
        AC_SUBST([OS_HOST], [macos])
        AC_DEFINE([ENABLE_MACOS], [1], [Building for a macos system.])
        ;;
     *)
        AC_SUBST([OS_HOST], [linux])
        AC_DEFINE([ENABLE_LINUX], [1], [Building for a Linux system.])
        ;;
esac
AC_MSG_RESULT([$OS_HOST])
AM_CONDITIONAL([ENABLE_LINUX], [test x$OS_HOST == xlinux])
AM_CONDITIONAL([ENABLE_MACOS], [test x$OS_HOST == xmacos])
AM_CONDITIONAL([ENABLE_WIN32], [test x$OS_HOST == xwin32])

##
# Setup the files `configure` will generate.
AC_CONFIG_FILES([
        Makefile
        include/cscene/Makefile
        include/cscene/version.h
        lib/Makefile
        src/Makefile
        tests/Makefile
])

AC_SUBST([abs_top_srcdir])

##
# Generate the files.
AC_OUTPUT
