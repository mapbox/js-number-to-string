Formats `double`s and `int`s using V8's `dtoa` implementation. The goal is to get the same characters when stringifying numbers as you would get in JavaScript.

## Usage:

```cpp
#include <js-number-to-string.hpp>

#include <iostream>

int main() {
    using namespace JSNumberToString;

    char buffer[kBufferSize];
    std::cout << DoubleToCString(123.456, buffer, kBufferSize) << std::endl;

    return 0;
}
```

Note that the buffer you pass into `DoubleToCString` or `IntToCString` must have at least 100 bytes, as per V8's requirements. It will be null-terminated, e.g. you can append the output directly to a `std::string` and reuse the buffer.

## Performance

This implementation is very similar to `doubleconv` in [Milo Yip's test case](https://github.com/miloyip/dtoa-benchmark).
