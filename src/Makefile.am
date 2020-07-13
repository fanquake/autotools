AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS)
AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)

LIB_BORING = lib_boring.a
EXTRA_LIBRARIES = $(LIB_BORING)

LIBBORING = libboring.la
lib_LTLIBRARIES = $(LIBBORING)

bin_PROGRAMS =
noinst_PROGRAMS =

# boring library
include_HEADERS = boring.h
lib_boring_a_SOURCES = boring.cpp

lib_boring_a_CPPFLAGS = $(AM_CPPFLAGS)
lib_boring_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
lib_boring_a_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RE_LDFLAGS)
# end boring library

# boring executable
bin_PROGRAMS += basic_autotools
basic_autotools_SOURCES = basic.cpp
basic_autotools_CPPFLAGS = $(AM_CPPFLAGS)
basic_autotools_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
basic_autotools_LDFLAGS = $(AM_LDFLAGS) $(RE_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)
basic_autotools_LDADD = $(LIB_BORING)

CLEANFILES = $(EXTRA_LIBRARIES)