// Copyright 2011 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/utils.h"
#include "src/base/logging.h"

namespace v8 {
namespace internal {

void SimpleStringBuilder::AddString(const char* s) {
  AddSubstring(s, StrLength(s));
}

void SimpleStringBuilder::AddSubstring(const char* s, int n) {
  DCHECK(!is_finalized() && position_ + n <= buffer_.length());
  DCHECK(static_cast<size_t>(n) <= strlen(s));
  memcpy(&buffer_[position_], s, n * kCharSize);
  position_ += n;
}

void SimpleStringBuilder::AddPadding(char c, int count) {
  for (int i = 0; i < count; i++) {
    AddCharacter(c);
  }
}

void SimpleStringBuilder::AddDecimalInteger(int32_t value) {
  uint32_t number = static_cast<uint32_t>(value);
  if (value < 0) {
    AddCharacter('-');
    number = static_cast<uint32_t>(-value);
  }
  int digits = 1;
  for (uint32_t factor = 10; digits < 10; digits++, factor *= 10) {
    if (factor > number) break;
  }
  position_ += digits;
  for (int i = 1; i <= digits; i++) {
    buffer_[position_ - i] = '0' + static_cast<char>(number % 10);
    number /= 10;
  }
}

char* SimpleStringBuilder::Finalize() {
  DCHECK(!is_finalized() && position_ <= buffer_.length());
  // If there is no space for null termination, overwrite last character.
  if (position_ == buffer_.length()) {
    position_--;
    // Print ellipsis.
    for (int i = 3; i > 0 && position_ > i; --i) buffer_[position_ - i] = '.';
  }
  buffer_[position_] = '\0';
  // Make sure nobody managed to add a 0-character to the
  // buffer while building the string.
  DCHECK(strlen(buffer_.start()) == static_cast<size_t>(position_));
  position_ = -1;
  DCHECK(is_finalized());
  return buffer_.start();
}

}  // namespace internal
}  // namespace v8
