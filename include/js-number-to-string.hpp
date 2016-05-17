#ifndef JS_NUMBER_TO_STRING
#define JS_NUMBER_TO_STRING

#include <string>

namespace JSNumberToString {

static const int kBufferSize = 100;

// Converts a double to a string value according to ECMA-262 9.8.1.
// The buffer should be large enough for any floating point number.
// 100 characters is enough.
const char* DoubleToCString(double value, char *data, int length);

// Convert an int to a null-terminated string. The returned string is
// located inside the buffer, but not necessarily at the start.
const char* IntToCString(int n, char *data, int length);

}  // namespace JSNumberToString

#endif
