// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_GLOBALS_H_
#define V8_GLOBALS_H_

#include <stddef.h>
#include <stdint.h>

#include "src/base/logging.h"
#include "src/base/macros.h"

const int kMaxInt = 0x7FFFFFFF;
const int kMinInt = -kMaxInt - 1;
const int kCharSize      = sizeof(char);      // NOLINT

#endif  // V8_GLOBALS_H_
