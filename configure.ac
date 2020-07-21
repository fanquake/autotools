dnl minimum required version of Autoconf
AC_PREREQ([2.69])

# setup a version number - 0.0.1
define(_VERSION_MAJOR, 0)
define(_VERSION_MINOR, 0)
define(_VERSION_REVISION, 1)

dnl initialize configure: package, version, bug-reporting URL, tarname, project URL
AC_INIT([Basic Autotools],
    m4_join([.], _VERSION_MAJOR, _VERSION_MINOR, _VERSION_REVISION),
    [https://github.com/fanquake/autotools/issues],
    [basic_autotools],
    [https://github.com/fanquake/autotools])

dnl Autoconf will use this file as a sanity check
dnl that it is building the correct directory
AC_CONFIG_SRCDIR([src/basic.cpp])

dnl location of auxiliary build tools
AC_CONFIG_AUX_DIR([build-aux])

dnl location of additional Autoconf macros
AC_CONFIG_MACRO_DIR([build-aux/m4])

dnl find pkg-config
PKG_PROG_PKG_CONFIG

dnl compute the host-system type variable
dnl i.e x86_64-apple-darwin18.7.0
AC_CANONICAL_HOST

dnl initialize Automake
AM_INIT_AUTOMAKE([1.13 no-define subdir-objects foreign])
AM_MAINTAINER_MODE([enable])

dnl make the compilation flags quiet unless V=1 is used
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

dnl determine the C++ compiler to use
AC_PROG_CXX

dnl require that it is C++17 capable
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])

dnl minimum required version of Libtool
LT_PREREQ([2.4.0])

dnl Libtool init checks
LT_INIT([pic-only])

dnl check for base programs
AC_PATH_TOOL(AR, ar)
AC_PATH_TOOL(RANLIB, ranlib)
AC_PATH_TOOL(STRIP, strip)

dnl Check for a flag to turn compiler warnings into errors.
dnl This will be used when testing for the availability of compile flags
AX_CHECK_COMPILE_FLAG([-Werror],[CXXFLAG_WERROR="-Werror"],[CXXFLAG_WERROR=""])

dnl Check for a flag to turn linker warnings into errors.
dnl This will be used when testing for the availability of linker flags.
case $host in
    *darwin*)
        AX_CHECK_LINK_FLAG([-Wl,-fatal_warnings],[LDFLAG_WERROR="-Wl,-fatal_warnings"],[LDFLAG_WERROR=""])
        ;;
    *)
        AX_CHECK_LINK_FLAG([-Wl,--fatal-warnings],[LDFLAG_WERROR="-Wl,--fatal-warnings"],[LDFLAG_WERROR=""])
        ;;
esac

dnl set basic compiler warnings
AX_CHECK_COMPILE_FLAG([-Wall],[WARN_CXXFLAGS="$WARN_CXXFLAGS -Wall"],,[[$CXXFLAG_WERROR]])
AX_CHECK_COMPILE_FLAG([-Wextra],[WARN_CXXFLAGS="$WARN_CXXFLAGS -Wextra"],,[[$CXXFLAG_WERROR]])

dnl do some host dependant configuration
case $host in
    *mingw*)
        TARGET_OS=windows
        AX_CHECK_LINK_FLAG([[-Wl,--no-insert-timestamp]], [LDFLAGS="$LDFLAGS -Wl,--no-insert-timestamp"],, [[$LDFLAG_WERROR]])
        ;;
    *darwin*)
        dnl These flags are specific to ld64, and may cause issues with other linkers.
        AX_CHECK_LINK_FLAG([[-Wl,-dead_strip]], [LDFLAGS="$LDFLAGS -Wl,-dead_strip"],, [[$LDFLAG_WERROR]])
        AX_CHECK_LINK_FLAG([[-Wl,-dead_strip_dylibs]], [LDFLAGS="$LDFLAGS -Wl,-dead_strip_dylibs"],, [[$LDFLAG_WERROR]])
        AX_CHECK_LINK_FLAG([[-Wl,-headerpad_max_install_names]], [LDFLAGS="$LDFLAGS -Wl,-headerpad_max_install_names"],, [[$LDFLAG_WERROR]])
        ;;
    *linux*)
        ;;
esac

AC_ARG_ENABLE([hardening],
  [AS_HELP_STRING([--disable-hardening],
  [do not attempt to harden the resulting executables (default is to harden when possible)])],
  [use_hardening=$enableval],
  [use_hardening=auto])

dnl setup hardening related compile flags and linker options
if test x$use_hardening != xno; then
AX_CHECK_COMPILE_FLAG([-Wstack-protector],[HARDENED_CXXFLAGS="$HARDENED_CXXFLAGS -Wstack-protector"],,[[$CXXFLAG_WERROR]])
AX_CHECK_COMPILE_FLAG([-fstack-protector-all],[HARDENED_CXXFLAGS="$HARDENED_CXXFLAGS -fstack-protector-all"],,[[$CXXFLAG_WERROR]])
dnl TODO: note why this is CXXFLAG_WERROR
AX_CHECK_LINK_FLAG([[-fPIE -pie]],[PIE_FLAGS="-fPIE"; HARDENED_LDFLAGS="$HARDENED_LDFLAGS -pie"],,[[$CXXFLAG_WERROR]])

if test x$TARGET_OS != xwindows; then
  AX_CHECK_COMPILE_FLAG([-fPIC],[PIC_FLAGS="-fPIC"])
fi

dnl Test if _FORTIFY_SOURCE works. If it does, first undefine it, then redefine
dnl it to 2. This works around toolchains where it may already be defined, and
dnl just blindly appending would result in redefinition warnings.
dnl TODO: swap out for the autoconf macro?
AX_CHECK_PREPROC_FLAG([-D_FORTIFY_SOURCE=2],[AX_CHECK_PREPROC_FLAG([-U_FORTIFY_SOURCE],[HARDENED_CPPFLAGS="$HARDENED_CPPFLAGS -U_FORTIFY_SOURCE"]) HARDENED_CPPFLAGS="$HARDENED_CPPFLAGS -D_FORTIFY_SOURCE=2"])

dnl windows
AX_CHECK_LINK_FLAG([[-Wl,--dynamicbase]],[HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,--dynamicbase"],,[[$LDFLAG_WERROR]])
AX_CHECK_LINK_FLAG([[-Wl,--nxcompat]],[HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,--nxcompat"],,[[$LDFLAG_WERROR]])
AX_CHECK_LINK_FLAG([[-Wl,--high-entropy-va]],[HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,--high-entropy-va"],,[[$LDFLAG_WERROR]])
dnl linux
AX_CHECK_LINK_FLAG([[-Wl,-z,relro]],[HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,-z,relro"],,[[$LDFLAG_WERROR]])
AX_CHECK_LINK_FLAG([[-Wl,-z,now]],[HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,-z,now"],,[[$LDFLAG_WERROR]])
AX_CHECK_LINK_FLAG([[-Wl,-z,separatecode]],[HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,-z,separatecode"],,[[$LDFLAG_WERROR]])
dnl darwin
AX_CHECK_LINK_FLAG([[-Wl,-bind_at_load]], [HARDENED_LDFLAGS="$HARDENED_LDFLAGS -Wl,-bind_at_load"],,[[$LDFLAG_WERROR]])
fi

dnl option to reduce exports
AC_ARG_ENABLE([reduce-exports],
  [AS_HELP_STRING([--enable-reduce-exports],
  [reduce exported symbols in the resulting executable & library (default is no)])],
  [use_reduce_exports=$enableval],
  [use_reduce_exports=no])

if test x$use_reduce_exports = xyes; then
  AX_CHECK_COMPILE_FLAG([-fvisibility=hidden],[RE_CXXFLAGS="-fvisibility=hidden"],
  [AC_MSG_ERROR([Cannot set hidden symbol visibility. Use --disable-reduce-exports.])])

  AX_CHECK_LINK_FLAG([[-Wl,--exclude-libs,ALL]], [RE_LDFLAGS="-Wl,--exclude-libs,ALL"],, [[$LDFLAG_WERROR]])
fi

AC_SUBST(WARN_CXXFLAGS)
AC_SUBST(HARDENED_CXXFLAGS)
AC_SUBST(HARDENED_CPPFLAGS)
AC_SUBST(HARDENED_LDFLAGS)
AC_SUBST(RE_CXXFLAGS)
AC_SUBST(RE_LDFLAGS)
AC_SUBST(PIC_FLAGS)
AC_SUBST(PIE_FLAGS)
AC_SUBST(LIBTOOL_APP_LDFLAGS)

AC_CONFIG_FILES([libboring.pc:libboring.pc.in])
AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT

echo
echo "Options used to compile and link:"
echo " build OS  = $build_os"
echo " target OS = $host_os"
echo
echo " CC          = $CC"
echo " CFLAGS      = $CFLAGS"
echo " CPPFLAGS    = $HARDENED_CPPFLAGS $CPPFLAGS"
echo " CXX         = $CXX"
echo " CXXFLAGS    = $RE_CXXFLAGS $HARDENED_CXXFLAGS $WARN_CXXFLAGS $CXXFLAGS"
echo " LDFLAGS     = $RE_LDFLAGS $HARDENED_LDFLAGS $LDFLAGS"
echo " PIC_FLAGS   = $PIC_FLAGS"
echo " PIE_FLAGS   = $PIE_FLAGS"
if test x$use_reduce_exports = xyes; then
echo " RE_CXXFLAGS = $RE_CXXFLAGS"
echo " RE_LDFLAGS  = $RE_LDFLAGS"
fi
echo
