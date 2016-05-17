// Copyright 2011 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_CONVERSIONS_H_
#define V8_CONVERSIONS_H_

#include <limits>

#include "src/base/logging.h"
#include "src/utils.h"

namespace v8 {
namespace internal {

// Converts a double to a string value according to ECMA-262 9.8.1.
// The buffer should be large enough for any floating point number.
// 100 characters is enough.
const char* DoubleToCString(double value, Vector<char> buffer);

// Convert an int to a null-terminated string. The returned string is
// located inside the buffer, but not necessarily at the start.
const char* IntToCString(int n, Vector<char> buffer);

}  // namespace internal
}  // namespace v8

#endif  // V8_CONVERSIONS_H_
