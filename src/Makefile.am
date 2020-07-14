AM_LIBTOOLFLAGS = --preserve-dup-deps
EXTRA_LIBRARIES =

AM_CPPFLAGS = $(HARDENED_CPPFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS) $(WARN_CXXFLAGS) $(RE_CXXFLAGS)
AM_LDFLAGS = $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS) $(RE_LDFLAGS)

LIB_BORING = lib_boring.a
EXTRA_LIBRARIES += $(LIB_BORING)

LIBBORING = libboring.la
lib_LTLIBRARIES = $(LIBBORING)

bin_PROGRAMS =
noinst_PROGRAMS =

# boring library
lib_boring_a_SOURCES = boring.cpp
lib_boring_a_CPPFLAGS = $(AM_CPPFLAGS)
lib_boring_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
# end boring library

# boring libtool archive
include_HEADERS = boring.h
libboring_la_SOURCES = $(lib_boring_a_SOURCES)
libboring_la_CPPFLAGS = $(AM_CPPFLAGS)
libboring_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libboring_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined
# end boring libtool archive

# boring binary
bin_PROGRAMS += basic_binary
basic_binary_SOURCES = basic.cpp
basic_binary_CPPFLAGS = $(AM_CPPFLAGS)
basic_binary_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
basic_binary_LDFLAGS = $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)
basic_binary_LDADD = $(LIB_BORING)

CLEANFILES = $(EXTRA_LIBRARIES)