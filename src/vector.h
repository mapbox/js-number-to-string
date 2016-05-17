// Copyright 2014 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_VECTOR_H_
#define V8_VECTOR_H_

#include "src/base/macros.h"

namespace v8 {
namespace internal {

template <typename T>
class Vector {
 public:
  Vector(T* data, int length) : start_(data), length_(length) {
    DCHECK(length == 0 || (length > 0 && data != nullptr));
  }

  // Returns the length of the vector.
  int length() const { return length_; }

  // Returns the pointer to the start of the data in the vector.
  T* start() const { return start_; }

  // Access individual vector elements - checks bounds in debug mode.
  T& operator[](int index) const {
    DCHECK(0 <= index && index < length_);
    return start_[index];
  }
 private:
  T* start_;
  int length_;
};

inline int StrLength(const char* string) {
  size_t length = strlen(string);
  DCHECK(length == static_cast<size_t>(static_cast<int>(length)));
  return static_cast<int>(length);
}

}  // namespace internal
}  // namespace v8

#endif  // V8_VECTOR_H_
