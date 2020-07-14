#include <boring.h>
#include <random>

// do something unlikely to be inlined so that we can observe a
// non-external symbol when building with reduced-exports
int some_internal_func(const int num) {
    std::random_device r;
    std::uniform_int_distribution<int> dist(0,42);
    return num + dist(r);
}

int some_func(const int num) {
    return some_internal_func(num) * num;
}

unsigned int boring_library_version() {
    return BORING_LIBRARY_VERSION;
}