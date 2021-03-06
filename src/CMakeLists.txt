set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -fPIC -fno-exceptions -fno-rtti")

add_library(js-number-to-string
    ../include/js-number-to-string.hpp
    js-number-to-string.cc

    # Identical V8 files
    bignum-dtoa.h
    bignum-dtoa.cc
    bignum.h
    bignum.cc
    cached-powers.h
    cached-powers.cc
    diy-fp.h
    diy-fp.cc
    double.h
    dtoa.h
    dtoa.cc
    fast-dtoa.h
    fast-dtoa.cc
    fixed-dtoa.h
    fixed-dtoa.cc

    # Partial V8 files
    base/logging.h
    base/macros.h
    conversions.h
    conversions.cc
    globals.h
    utils.h
    utils.cc
    vector.h
)

install(TARGETS js-number-to-string ARCHIVE DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/include/js-number-to-string.hpp DESTINATION include)

if (BUILD_EXAMPLES)
    # Example executable that uses libjs-number-to-string:
    add_executable(main main.cpp)
    target_link_libraries(main js-number-to-string)
endif()