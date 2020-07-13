#include <boring.h>

unsigned int some_internal_func() {
    return 42;
}

int some_func(const int num) {
    return some_internal_func() * num;
}

unsigned int boring_library_version() {
    return BORING_LIBRARY_VERSION;
}