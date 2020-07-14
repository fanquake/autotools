#include <iostream>

#include <boring.h>

int main() {
    std::cout << PACKAGE_STRING << " Binary\n";
    std::cout << "API Version: " << boring_library_version() << "\n";
    std::cout << "Calling some_func(2): " << some_func(2) << "\n";
    return 0;
}
