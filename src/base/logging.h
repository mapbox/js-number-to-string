// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_BASE_LOGGING_H_
#define V8_BASE_LOGGING_H_

#include <assert.h>
#include <string.h>

#define UNIMPLEMENTED() abort()
#define UNREACHABLE() abort()
#define USE(name) ((void)name)

// The DCHECK macro is equivalent to CHECK except that it only
// generates code in debug builds.
#ifdef DEBUG
#define DCHECK(condition) assert(condition)
#else
#define DCHECK(condition) ((void)0)
#endif

#endif // V8_BASE_LOGGING_H_
