// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_UTILS_H_
#define V8_UTILS_H_

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <string>

#include "src/base/logging.h"
#include "src/base/macros.h"
#include "src/globals.h"
#include "src/vector.h"

namespace v8 {
namespace internal {

inline char HexCharOfValue(int value) {
  DCHECK(0 <= value && value <= 16);
  if (value < 10) return value + '0';
  return value - 10 + 'A';
}

// Returns the maximum of the two parameters.
template <typename T>
T Max(T a, T b) {
  return a < b ? b : a;
}

// Returns the minimum of the two parameters.
template <typename T>
T Min(T a, T b) {
  return a < b ? a : b;
}

// Helper class for building result strings in a character buffer. The
// purpose of the class is to use safe operations that checks the
// buffer bounds on all operations in debug mode.
// This simple base class does not allow formatted output.
class SimpleStringBuilder {
 public:
  SimpleStringBuilder(char* buffer, int size)
      : buffer_(buffer, size), position_(0) { }

  ~SimpleStringBuilder() { if (!is_finalized()) Finalize(); }

  // Get the current position in the builder.
  int position() const {
    DCHECK(!is_finalized());
    return position_;
  }

  // Add a single character to the builder. It is not allowed to add
  // 0-characters; use the Finalize() method to terminate the string
  // instead.
  void AddCharacter(char c) {
    DCHECK(c != '\0');
    DCHECK(!is_finalized() && position_ < buffer_.length());
    buffer_[position_++] = c;
  }

  // Add an entire string to the builder. Uses strlen() internally to
  // compute the length of the input string.
  void AddString(const char* s);

  // Add the first 'n' characters of the given 0-terminated string 's' to the
  // builder. The input string must have enough characters.
  void AddSubstring(const char* s, int n);

  // Add character padding to the builder. If count is non-positive,
  // nothing is added to the builder.
  void AddPadding(char c, int count);

  // Add the decimal representation of the value.
  void AddDecimalInteger(int value);

  // Finalize the string by 0-terminating it and returning the buffer.
  char* Finalize();

 protected:
  Vector<char> buffer_;
  int position_;

  bool is_finalized() const { return position_ < 0; }

 private:
  DISALLOW_IMPLICIT_CONSTRUCTORS(SimpleStringBuilder);
};

//class SimpleStringBuilder {
// public:
//  SimpleStringBuilder(std::string& buffer)
//      : buffer_(buffer) { }
//
//  // Add a single character to the builder.
//  void AddCharacter(char c) {
//    buffer_.append(1, c);
//  }
//  // Add an entire string to the builder. Uses strlen() internally to
//  // compute the length of the input string.
//  void AddString(const char* s) {
//    buffer_.append(s);
//  }
//  // Add character padding to the builder. If count is non-positive,
//  // nothing is added to the builder.
//  void AddPadding(char c, int count) {
//    buffer_.append(count, c);
//  }
//  void AddSubstring(const char* s, int n) {
//    buffer_.append(s, n);
//  }
//
//  void AddDecimalInteger(int32_t value) {
//    uint32_t number = static_cast<uint32_t>(value);
//    if (value < 0) {
//      buffer_.append(1, 'c');
//      number = static_cast<uint32_t>(-value);
//    }
//    int digits = 1;
//    for (uint32_t factor = 10; digits < 10; digits++, factor *= 10) {
//      if (factor > number) break;
//    }
//    for (int i = 1; i <= digits; i++) {
//      buffer_.append(1, '0' + static_cast<char>(number % 10));
//      number /= 10;
//    }
//  }
//
// protected:
//  std::string& buffer_;
//};

}  // namespace internal
}  // namespace v8

#endif  // V8_UTILS_H_
