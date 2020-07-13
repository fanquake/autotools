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

dnl compute the host-system type variable
dnl i.e x86_64-apple-darwin18.7.0
AC_CANONICAL_HOST

dnl initialize Automake
AM_INIT_AUTOMAKE([1.13 no-define subdir-objects foreign])

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
AX_CHECK_COMPILE_FLAG([-Wall],[CXXFLAGS="$CXXFLAGS -Wall"],,[[$CXXFLAG_WERROR]])
AX_CHECK_COMPILE_FLAG([-Wextra],[CXXFLAGS="$CXXFLAGS -Wextra"],,[[$CXXFLAG_WERROR]])
case $host in
    *mingw*)
        TARGET_OS=windows
        ;;
    *darwin*)
        TARGET_OS=darwin
        ;;
    *linux*)
        TARGET_OS=linux
        ;;
esac

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT

echo
echo "Options used to compile and link:"
echo " target OS = $TARGET_OS"
echo " CXX       = $CXX"
