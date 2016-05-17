#include <js-number-to-string.hpp>

#include "src/conversions.h"

namespace JSNumberToString {

const char* DoubleToCString(double v, char *data, int length) {
  using namespace v8::internal;
  return DoubleToCString(v, Vector<char>(data, length));
}

const char* IntToCString(int n, char *data, int length) {
  using namespace v8::internal;
  return IntToCString(n, Vector<char>(data, length));
}

} // namespace JSNumberToString
