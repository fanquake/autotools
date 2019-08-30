#include <string>
#include <functional>
#include <iostream>
#include <optional>

// std::optional is C++17
// https://en.cppreference.com/w/cpp/utility/optional

std::optional<std::string> create(bool b) {
    if (b)
        return "Godzilla";
    return {};
}

auto create2(bool b) {
    return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}

auto create_ref(bool b) {
    static std::string value = "Godzilla";
    return b ? std::optional<std::reference_wrapper<std::string>>{value} : std::nullopt;
}

int main() {
    std::cout << "create(false) returned "
        << create(false).value_or("empty") << "\n";
    
    if (auto str = create2(true)) {
        std::cout << "create2(true) returned " << *str << "\n";
    }

    if (auto str = create_ref(true)) {
        std::cout << "create_ref(true) returned " << str->get() << "\n";
        str->get() = "Mothra";
        std::cout << "modifying it changed it to " << str->get() << "\n";
    }
}
