// Copyright 2011 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/conversions.h"

#include <limits.h>
#include <stdarg.h>
#include <cmath>

#include "src/dtoa.h"
#include "src/utils.h"

#ifndef _STLP_VENDOR_CSTD
// STLPort doesn't import fpclassify into the std namespace.
using std::fpclassify;
#endif

namespace v8 {
namespace internal {

const char* DoubleToCString(double v, Vector<char> buffer) {
  switch (fpclassify(v)) {
    case FP_NAN: return "NaN";
    case FP_INFINITE: return (v < 0.0 ? "-Infinity" : "Infinity");
    case FP_ZERO: return "0";
    default: {
      SimpleStringBuilder builder(buffer.start(), buffer.length());
      int decimal_point;
      int sign;
      const int kV8DtoaBufferCapacity = kBase10MaximalLength + 1;
      char decimal_rep[kV8DtoaBufferCapacity];
      int length;

      DoubleToAscii(v, DTOA_SHORTEST, 0,
                    Vector<char>(decimal_rep, kV8DtoaBufferCapacity),
                    &sign, &length, &decimal_point);

      if (sign) builder.AddCharacter('-');

      if (length <= decimal_point && decimal_point <= 21) {
        // ECMA-262 section 9.8.1 step 6.
        builder.AddString(decimal_rep);
        builder.AddPadding('0', decimal_point - length);

      } else if (0 < decimal_point && decimal_point <= 21) {
        // ECMA-262 section 9.8.1 step 7.
        builder.AddSubstring(decimal_rep, decimal_point);
        builder.AddCharacter('.');
        builder.AddString(decimal_rep + decimal_point);

      } else if (decimal_point <= 0 && decimal_point > -6) {
        // ECMA-262 section 9.8.1 step 8.
        builder.AddString("0.");
        builder.AddPadding('0', -decimal_point);
        builder.AddString(decimal_rep);

      } else {
        // ECMA-262 section 9.8.1 step 9 and 10 combined.
        builder.AddCharacter(decimal_rep[0]);
        if (length != 1) {
          builder.AddCharacter('.');
          builder.AddString(decimal_rep + 1);
        }
        builder.AddCharacter('e');
        builder.AddCharacter((decimal_point >= 0) ? '+' : '-');
        int exponent = decimal_point - 1;
        if (exponent < 0) exponent = -exponent;
        builder.AddDecimalInteger(exponent);
      }
    return builder.Finalize();
    }
  }
}

const char* IntToCString(int n, Vector<char> buffer) {
  bool negative = false;
  if (n < 0) {
    // We must not negate the most negative int.
    if (n == kMinInt) return DoubleToCString(n, buffer);
    negative = true;
    n = -n;
  }
  // Build the string backwards from the least significant digit.
  int i = buffer.length();
  buffer[--i] = '\0';
  do {
    buffer[--i] = '0' + (n % 10);
    n /= 10;
  } while (n);
  if (negative) buffer[--i] = '-';
  return buffer.start() + i;
}

}  // namespace internal
}  // namespace v8
