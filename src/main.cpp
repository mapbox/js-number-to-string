#include <js-number-to-string.hpp>

#include <iostream>

int main() {
    using namespace JSNumberToString;

    char buffer[kBufferSize];
    std::cout << DoubleToCString(123.456, buffer, kBufferSize) << std::endl;

    return 0;
}
