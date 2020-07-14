// Needs to be done properly. Good enough for test purposes.
#if defined(_WIN32)
    #define EXPORT_SYMBOL __declspec(dllexport)
#else
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
#endif

#define BORING_LIBRARY_VERSION 1

int some_internal_func(const int num);

EXPORT_SYMBOL int some_func(const int num);

EXPORT_SYMBOL unsigned int boring_library_version();

#undef EXPORT_SYMBOL